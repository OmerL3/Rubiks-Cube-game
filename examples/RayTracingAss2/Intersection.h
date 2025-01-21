#pragma once

#define GLM_ENABLE_EXPERIMENTAL


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

#include <string.h>
#include <iostream>
#include <vector>
#include <Object.h>


class Intersection
{
    protected:
        glm::vec3 point;
        Object* object;

    public:
        Intersection(glm::vec3 p, Object* obj);
        
        float distance(glm::vec3 v);
        Object* get_object() {return object;}
        glm::vec3 get_point() {return point;}

        ~Intersection();

};