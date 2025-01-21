#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <Debugger.h>
#include <Shader.h>
#include <Rubiks.h>


class Camera
{
    private:
        // View and Projection
        glm::mat4 m_View = glm::mat4(1.0f);
        glm::mat4 m_Projection = glm::mat4(1.0f);

        // View matrix paramters
        glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 m_Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

        // Projection matrix parameters
        float m_FieldOfView = 45.0f;
        float m_Near = 0.1f; 
        float m_Far = 100.0f;
        int m_Width;
        int m_Height;
        float m_AspectRatio;

        // Orthographic Projection parameters
        float m_Left = -1.0f;
        float m_Right = 1.0f;
        float m_Bottom = -1.0f; 
        float m_Top = 1.0f;

        // Looking around parameters
        float m_sensitivity = 0.01f;

        Rubiks* m_rubik_cube;



    public:

        // Prevent the camera from jumping around when first clicking left click
        double m_OldMouseX = 0.0;
        double m_OldMouseY = 0.0;
        double m_NewMouseX = 0.0;
        double m_NewMouseY = 0.0;
        
        bool print_log_on = true;
        float m_depth = -1.0f;
        
        bool picking_on = false;
        int picked_cube_id = -1;
        
    public:
        Camera(int width, int height, Rubiks* r_cube)
            : m_Width(width), m_Height(height), m_AspectRatio((float)width / (float)height), 
                m_rubik_cube(r_cube),
                print_log_on(true) {};

        // Update Projection matrix for Orthographic mode
        void SetOrthographic(float near, float far);

        // Update Projection matrix for Perspective mode
        void SetPerspective(float near, float far, float fov);

        // Handle camera inputs
        void EnableInputs(GLFWwindow* window);

        inline glm::mat4 GetViewMatrix() const { return m_View; }
        inline glm::mat4 GetProjectionMatrix() const { return m_Projection; }
        void set_zoom(double zoom_by);
        void rotate_view();
        void move_camera();
        void rotate_wall(int wall);
        void swap_clockwise() { m_rubik_cube->set_clockwise(); };
        void set_degree(float mult);
        void mix();
        void update_view();
        void change_COR(char dir);
        void change_picking_mode();
        void set_picked_cube(double x, double y);
        bool print_log();
        void clean_start();
};