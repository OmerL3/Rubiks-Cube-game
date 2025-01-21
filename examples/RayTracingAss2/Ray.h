#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

#include <string.h>
#include <iostream>
#include <vector>


class Ray
{
    protected:
        glm::vec3 startP;
        glm::vec3 directionV;

    public:
        Ray(glm::vec3 s, glm::vec3 d);
        
        glm::vec3 at(float t);
        glm::vec3 get_direction() {return directionV;}
        glm::vec3 get_start() {return startP;}

        ~Ray();

};