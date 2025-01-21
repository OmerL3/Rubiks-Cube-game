#include <Camera.h>

void Camera::update_view()
{
    m_View = glm::lookAt(m_Position, m_Position + m_Orientation, m_Up); 
}

void Camera::SetOrthographic(float near, float far)
{
    m_Near = near;
    m_Far = far;

    m_Projection = glm::ortho(m_Left, m_Right, m_Bottom, m_Top, near, far);
    update_view();
}


void Camera::SetPerspective(float near, float far, float fov)
{
    m_Near = near;
    m_Far = far;
    m_FieldOfView = fov;   

    m_Projection = glm::perspective(glm::radians(m_FieldOfView), m_AspectRatio, m_Near, m_Far);
    update_view();
}

void Camera::set_zoom(double zoom_by)
{
    m_Position += glm::vec3(0.0f, 0.0f, -zoom_by);
    update_view();
}

void Camera::rotate_view()
{
    if(!picking_on)
    {
        m_rubik_cube->model_rotate((float) -m_NewMouseX * m_sensitivity * 0.1f, m_Up);
        m_rubik_cube->model_rotate((float) -m_NewMouseY * m_sensitivity * 0.1f, glm::normalize(glm::cross(m_Orientation, m_Up)));

        // Ofir's implementation
        // glm::mat3 viewRotateInverse = glm::transpose(glm::mat3(GetViewMatrix()));
        // m_View = glm::rotate(m_View, (float) m_NewMouseX * m_sensitivity, viewRotateInverse * glm::vec3(0.0f, -1.0f, 0.0f));
        // m_View = glm::rotate(m_View, (float) m_NewMouseY * m_sensitivity, viewRotateInverse * glm::vec3(-1.0f, 0.0f, 0.0f));

    }
    else //picking on - left click
    { 
        if (picked_cube_id >= 0) // Check if an object is picked
        {
            m_rubik_cube->rotate_cube(picked_cube_id, (float)-m_NewMouseX * m_sensitivity * 0.5f, m_Up);
            m_rubik_cube->rotate_cube(picked_cube_id, (float)-m_NewMouseY * m_sensitivity * 0.5f, glm::normalize(glm::cross(m_Orientation, m_Up)));

        }
    }
}


void Camera::move_camera()
{
    if(!picking_on)
    {
        m_Position += glm::vec3(m_NewMouseX * m_sensitivity, -m_NewMouseY * m_sensitivity, 0.0f);
        update_view();

        // Ofir's implementation:
        // glm::mat3 viewRotateInverse = glm::transpose(glm::mat3(GetViewMatrix()));
        // m_View = glm::translate(viewRotateInverse * glm::vec3((float) m_NewMouseX * m_sensitivity * 0.1f, (float) -m_NewMouseY * m_sensitivity * 0.1f, 0.0f));
    }
    else //picking on - right click
    {
        if (picked_cube_id >= 0) // Check if an object is picked
        {
            float z = m_Far + m_depth * (m_Near - m_Far);
            float x_new = ((m_NewMouseX * m_Far) / (m_Width * z)) * m_Near * 2 * glm::tan(m_AspectRatio);
            float y_new = ((m_NewMouseY * m_Far) / (m_Width * z)) * m_Near * 2 * glm::tan(m_AspectRatio);
            
            glm::vec3 trans = glm::vec3(-x_new * m_Position.z * 5, y_new * m_Position.z * 5, 0.0f);

            m_rubik_cube->translate_cube(picked_cube_id, trans);
        }
    }
}

void Camera::rotate_wall(int wall)
{
    m_rubik_cube->rotate_wall(wall);
}

void Camera::set_degree(float mult)
{
    m_rubik_cube->set_rotate_degree(mult); 
}

void Camera::mix()
{
    m_rubik_cube->rand_mix();
}

void Camera::change_COR(char dir)
{
    m_rubik_cube->change_center_of_rotation(dir);
}

void Camera::change_picking_mode()
{
    picking_on = !picking_on;
    m_rubik_cube->swap_picking(picking_on);
}

void Camera::set_picked_cube(double x, double y)
{

    unsigned char color_picked[]{ 0, 0, 0, 0 };
    glReadPixels(x, 800 - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color_picked);
    int color_id = color_picked[0];
    if(color_id > 27) picked_cube_id = -1;
    else picked_cube_id = color_id;
}

bool Camera::print_log()
{
    return print_log_on;
}

void Camera::clean_start()
{
    m_rubik_cube->restart();
}

/////////////////////
// Input Callbacks //
/////////////////////

void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
    Camera* camera = (Camera*) glfwGetWindowUserPointer(window);
    if (!camera) {
        std::cout << "Warning: Camera wasn't set as the Window User Pointer! KeyCallback is skipped" << std::endl;
        return;
    }

    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
            case GLFW_KEY_UP:
                if(camera->print_log()) std::cout << "UP Pressed" << std::endl;
                camera->change_COR('^');
                break;
            case GLFW_KEY_DOWN:
                if(camera->print_log()) std::cout << "DOWN Pressed" << std::endl;
                camera->change_COR('v');
                break;
            case GLFW_KEY_LEFT:
                if(camera->print_log()) std::cout << "LEFT Pressed" << std::endl;
                camera->change_COR('<');
                break;
            case GLFW_KEY_RIGHT:
                if(camera->print_log()) std::cout << "RIGHT Pressed" << std::endl;
                camera->change_COR('>');
                break;
            case GLFW_KEY_I:
                if(camera->print_log()) std::cout << "I Pressed" << std::endl;
                camera->change_COR('I');
                break;
            case GLFW_KEY_O:
                if(camera->print_log()) std::cout << "O Pressed" << std::endl;
                camera->change_COR('O');
                break;
            case GLFW_KEY_R:
                if(camera->print_log()) std::cout << "R Pressed" << std::endl;
                camera->rotate_wall(1);
                break;
            case GLFW_KEY_L:
                if(camera->print_log()) std::cout << "L Pressed" << std::endl;
                camera->rotate_wall(0);
                break;
            case GLFW_KEY_U:
                if(camera->print_log()) std::cout << "U Pressed" << std::endl;
                camera->rotate_wall(3);
                break;
            case GLFW_KEY_D:
                if(camera->print_log()) std::cout << "D Pressed" << std::endl;
                camera->rotate_wall(2);
                break;
            case GLFW_KEY_B:
                if(camera->print_log()) std::cout << "B Pressed" << std::endl;
                camera->rotate_wall(5);
                break;
            case GLFW_KEY_F:
                if(camera->print_log()) std::cout << "F Pressed" << std::endl;
                camera->rotate_wall(4);
                break;
            case GLFW_KEY_SPACE:
                if(camera->print_log()) std::cout << "Space Pressed" << std::endl;
                camera->swap_clockwise();
                break;
            case GLFW_KEY_Z:
                if(camera->print_log()) std::cout << "Z Pressed" << std::endl;
                camera->set_degree(0.5f);
                break;
            case GLFW_KEY_A:
                if(camera->print_log()) std::cout << "A Pressed" << std::endl;
                camera->set_degree(2.0f);
                break;
            case GLFW_KEY_M:
                if(camera->print_log()) std::cout << "M Pressed" << std::endl;
                camera->mix();
                break;
            case GLFW_KEY_P:
                if(camera->print_log()) std::cout << "P Pressed" << std::endl;
                camera->change_picking_mode();
                break;
            case GLFW_KEY_Q:
                if(camera->print_log()) std::cout << "Q Pressed" << std::endl;
                camera->clean_start();
                break;
            default:
                break;
        }
    }
}

void MouseButtonCallback(GLFWwindow* window, double currMouseX, double currMouseY)
{
    Camera* camera = (Camera*) glfwGetWindowUserPointer(window);
    if (!camera) {
        std::cout << "Warning: Camera wasn't set as the Window User Pointer! KeyCallback is skipped" << std::endl;
        return;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        if(camera->print_log()) std::cout << "MOUSE LEFT Click" << std::endl;
        if(camera->picking_on)
        {
            camera->set_picked_cube(camera->m_OldMouseX, camera->m_OldMouseY);
        } 
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        if(camera->print_log()) std::cout << "MOUSE RIGHT Click" << std::endl;
        if(camera->picking_on)
        {
            glReadPixels(currMouseX, 800 - currMouseY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &camera->m_depth);
            camera->set_picked_cube(camera->m_OldMouseX, camera->m_OldMouseY);
        }
    }
}

void CursorPosCallback(GLFWwindow* window, double currMouseX, double currMouseY)
{
    Camera* camera = (Camera*) glfwGetWindowUserPointer(window);
    if (!camera) {
        std::cout << "Warning: Camera wasn't set as the Window User Pointer! KeyCallback is skipped" << std::endl;
        return;
    }

    camera->m_NewMouseX = camera->m_OldMouseX - currMouseX;
    camera->m_NewMouseY = camera->m_OldMouseY - currMouseY;
    camera->m_OldMouseX = currMouseX;
    camera->m_OldMouseY = currMouseY;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        if(camera->print_log()) std::cout << "MOUSE LEFT Motion" << std::endl;
        camera->rotate_view();
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        if(camera->print_log()) std::cout << "MOUSE RIGHT Motion" << std::endl;
        camera->move_camera();
    }
}


void ScrollCallback(GLFWwindow* window, double scrollOffsetX, double scrollOffsetY)
{
    Camera* camera = (Camera*) glfwGetWindowUserPointer(window);
    if (!camera) {
        std::cout << "Warning: Camera wasn't set as the Window User Pointer! ScrollCallback is skipped" << std::endl;
        return;
    }

    camera->set_zoom(scrollOffsetY);
    
}

void Camera::EnableInputs(GLFWwindow* window)
{
    // Set camera as the user pointer for the window
    glfwSetWindowUserPointer(window, this);

    // Handle key inputs
    glfwSetKeyCallback(window, (void(*)(GLFWwindow *, int, int, int, int)) KeyCallback);

    // Handle cursor buttons
    glfwSetMouseButtonCallback(window, (void(*)(GLFWwindow *, int, int, int)) MouseButtonCallback);

    // Handle cursor position and inputs on motion
    glfwSetCursorPosCallback(window , (void(*)(GLFWwindow *, double, double)) CursorPosCallback);

    // Handle scroll inputs
    glfwSetScrollCallback(window, (void(*)(GLFWwindow *, double, double)) ScrollCallback);
}