#include <Cube.h>



Cube::Cube(int id, Shader* shader, Texture* tex, glm::mat4 trans, VertexArray* va) : 
    m_id(id),
    m_shader(shader),
    m_tex(tex),
    m_trans(trans),
    m_rot(glm::mat4(1.0f)),
    m_va(va)
{
}

Cube::~Cube()
{
}

void Cube::render(glm::mat4 mvp)
{
    glm::mat4 cube_model = m_rot * m_trans;   
    glm::mat4 draw_mvp = mvp * cube_model;
    glm::vec4 color;


    color = glm::vec4(1.0, 1.0f, 1.0f, 1.0f);

    m_tex->Bind(0);
    m_shader->Bind();
    m_shader->SetUniform1i("u_PickingMode", 0);
    m_shader->SetUniform4f("u_Color", color); 
    m_shader->SetUniformMat4f("u_MVP", draw_mvp);
    m_shader->SetUniform1i("u_Texture", 0);
    m_va->Bind();
    GLCall(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr));
}

void Cube::render_back_buffer(glm::mat4 mvp)
{
    glm::mat4 cube_model = m_rot * m_trans;   
    glm::mat4 draw_mvp = mvp * cube_model;

    glm::vec4 color = glm::vec4(static_cast<float>(m_id) / 255.0f, 0.0f, 0.0f, 1.0f);
    
    m_tex->Bind(0);
    m_shader->Bind();
    m_shader->SetUniform1i("u_PickingMode", 1);
    m_shader->SetUniform4f("u_Color", color);
    m_shader->SetUniformMat4f("u_MVP", draw_mvp);

    m_va->Bind();
    GLCall(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr));
}

void Cube::set_tot_rot(float angle, glm::vec3 axis)
{
    m_rot = glm::rotate(glm::mat4(1.0f), angle, axis) * m_rot;
}

void Cube::add_translate(glm::vec3 trans_vec)
{
    glm::mat3 inverse = glm::transpose(m_rot * m_trans);
    m_trans = glm::translate(m_trans, inverse * trans_vec);
}

void Cube::set_transform(glm::mat4 trans, glm::mat4 rot)
{
    m_trans = trans;
    m_rot = rot;
}

void Cube::set_rotate(float angle, glm::vec3 axis)
{
    glm::mat3 inverse = glm::transpose(m_rot * m_trans);
    m_trans = m_trans * glm::rotate(glm::mat4(1.0f), angle, inverse * axis);
}

void Cube::set_translate(glm::mat4 trans)
{
    m_trans = trans;
}

