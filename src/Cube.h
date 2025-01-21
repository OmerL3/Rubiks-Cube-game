#pragma once

#include <vector>
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



class Cube
{
    private:
        int m_id;
        Shader* m_shader;
        Texture* m_tex;
        glm::mat4 m_trans;
        glm::mat4 m_rot;
        VertexArray* m_va;
        // glm::mat4 m_pick_trans = glm::mat4(1.0f);
        // glm::mat4 m_pick_rot = glm::mat4(1.0f);

    public:
        Cube(int id, Shader* shader, Texture* tex, glm::mat4 trans, VertexArray* va);
        ~Cube();


        int get_id() { return m_id; }
        glm::mat4 get_trans() { return m_trans; }
        glm::mat4 get_rot() { return m_rot; }


        void set_transform(glm::mat4 trans, glm::mat4 rot);
        void set_rotate(float angle, glm::vec3 axis);
        void set_tot_rot(float angle, glm::vec3 axis);
        void add_translate(glm::vec3 trans_vec);
        void set_translate(glm::mat4 trans);


        void render(glm::mat4 mvp);
        void render_back_buffer(glm::mat4 mvp);


};