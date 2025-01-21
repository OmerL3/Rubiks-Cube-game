#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Debugger.h>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <Shader.h>
#include <Texture.h>
#include <Camera.h>
#include <iostream>

#include <Cube.h>
#include <Rubiks.h>

/* Window size */
const unsigned int width = 800;
const unsigned int height = 800;
const float FOVdegree = 45.0f;  // Field Of View Angle
const float near = 0.1f;
const float far = 100.0f;


float vertices[] = {

    // positions            // colors            // texCoords
    // Front face           white
    -0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f,  // Bottom-left
     0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f,  // Bottom-right
     0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f,  // Top-right
    -0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f,  // Top-left

    // Back face            yellow
    -0.5f, -0.5f, -0.5f,    1.0f, 0.9f, 0.0f,    0.0f, 0.0f,  // Bottom-left
     0.5f, -0.5f, -0.5f,    1.0f, 0.9f, 0.0f,    1.0f, 0.0f,  // Bottom-right
     0.5f,  0.5f, -0.5f,    1.0f, 0.9f, 0.0f,    1.0f, 1.0f,  // Top-right
    -0.5f,  0.5f, -0.5f,    1.0f, 0.9f, 0.0f,    0.0f, 1.0f,  // Top-left

    // Left face            green
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f,  // Bottom-left
    -0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,    1.0f, 0.0f,  // Bottom-right
    -0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f,  // Top-right
    -0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,  // Top-left

    // Right face           blue
     0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f,     0.0f, 0.0f,  // Bottom-left
     0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,     1.0f, 0.0f,  // Bottom-right
     0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,     1.0f, 1.0f,  // Top-right
     0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f,     0.0f, 1.0f,  // Top-left

    // Top face             orange
    -0.5f,  0.5f, -0.5f,    1.0f, 0.4f, 0.0f,    0.0f, 0.0f,  // Bottom-left
     0.5f,  0.5f, -0.5f,    1.0f, 0.4f, 0.0f,    1.0f, 0.0f,  // Bottom-right
     0.5f,  0.5f,  0.5f,    1.0f, 0.4f, 0.0f,    1.0f, 1.0f,  // Top-right
    -0.5f,  0.5f,  0.5f,    1.0f, 0.4f, 0.0f,    0.0f, 1.0f,  // Top-left

    // Bottom face          red
    -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // Bottom-left
     0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f,  // Bottom-right
     0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,  // Top-right
    -0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f   // Top-left
}; 

unsigned int indices[] = {
    0, 1, 2, 2, 3, 0, // Front face
    4, 5, 6, 6, 7, 4, // Back face
    8, 9, 10, 10, 11, 8, // Left face
    12, 13, 14, 14, 15, 12, // Right face
    16, 17, 18, 18, 19, 16, // Top face
    20, 21, 22, 22, 23, 20  // Bottom face
};



int main(int argc, char* argv[])
{
    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
    {
        return -1;
    }
    /* Set OpenGL to Version 3.3.0 */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Rubik's Cube", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    /* Load GLAD so it configures OpenGL */
    gladLoadGL();
    /* Control frame rate */
    glfwSwapInterval(1);
    {
        /* Blend to fix images with transperancy */
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
     
        /* Generate VAO, VBO, EBO and bind them */
        VertexArray va;
        VertexBuffer vb(vertices, sizeof(vertices));
        VertexBufferLayout layout;
        layout.Push<float>(3);  // positions
        layout.Push<float>(3);  // colors
        layout.Push<float>(2);  // texCoords
        va.AddBuffer(vb, layout);
        IndexBuffer ib(indices, sizeof(indices));
        
        int cube_size = 3;
        // std::cout<< "Choose cube size: " << std::endl;
        // std::cin>>cube_size;

        Texture texture("res/textures/plane.png");
        Shader shader("res/shaders/basic.shader");
        Rubiks rubik_cube(cube_size, &shader, &texture, &va);

        Camera camera(width, height, &rubik_cube);
        
    	GLCall(glEnable(GL_DEPTH_TEST));

        camera.SetPerspective(near, far, FOVdegree);
        camera.EnableInputs(window);

        
        while (!glfwWindowShouldClose(window))
        {
            /* Set white background color */
            GLCall(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
            GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

            glm::mat4 view = camera.GetViewMatrix(); 
            glm::mat4 proj = camera.GetProjectionMatrix();
            
            ib.Bind();
            rubik_cube.render_rubik(view, proj, glfwGetTime());
            ib.Unbind();
            
            
            glfwSwapBuffers(window);

            if(rubik_cube.should_pick()) 
            {
                ib.Bind();
                GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
                rubik_cube.draw_back_buffer(view, proj);
                ib.Unbind();
            }

            
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}
