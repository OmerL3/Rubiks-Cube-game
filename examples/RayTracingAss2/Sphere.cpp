#include <Sphere.h>

Sphere::Sphere(glm::vec3 c, float r, opticalT t)
        : Object(t), center(c), radius(r) {
            // std::cout<<"A Sphere created"<<std::endl;
        }

std::string Sphere::to_string_print() 
{
    std::string str = "Sphere: c=";
    str += std::to_string(K_da.x) + "," + std::to_string(K_da.y) + "," + std::to_string(K_da.z);


    str += " || center=" + std::to_string(center.x) + "," + std::to_string(center.y) + "," + std::to_string(center.z);

    str += " || r=" + std::to_string(radius);

    str += " || shininess= " + std::to_string(n_shiny);

    str += " || type = " + std::to_string(type);


    return str;

};



glm::vec3 Sphere::get_intersection(Ray ray)
{

    glm::vec3 ray_V = glm::normalize(ray.get_direction());
    glm::vec3 ray_P0 = ray.get_start();

    glm::vec3 vector_L = center - ray_P0;

    float t_m = glm::dot(vector_L, ray_V);

    float d_squared = glm::dot(vector_L, vector_L) - (t_m*t_m);

    float r_squared = radius * radius;

    if(d_squared - r_squared > std::numeric_limits<float>::epsilon()) return glm::vec3(std::numeric_limits<float>::infinity());

    float t_h = glm::sqrt(r_squared - d_squared);

    float t1 = t_m - t_h;
    float t2 = t_m + t_h;

    if (t1 >= 0) return ray.at(t1); 
    if (t2 >= 0) return ray.at(t2);
    return glm::vec3(std::numeric_limits<float>::infinity());
}

glm::vec3 Sphere::get_furthest_intersection(Ray ray)
{
    glm::vec3 ray_V = glm::normalize(ray.get_direction());
    glm::vec3 ray_P0 = ray.get_start();

    glm::vec3 vector_L = center - ray_P0;

    float t_m = glm::dot(ray_V, vector_L);

    float d_squared = glm::dot(vector_L, vector_L) - (t_m*t_m);

    float r_squared = radius * radius;

    if(d_squared - r_squared > std::numeric_limits<float>::epsilon()) return glm::vec3(std::numeric_limits<float>::infinity());

    float t_h = glm::sqrt(r_squared - d_squared);

    float t1 = t_m - t_h;
    float t2 = t_m + t_h;

    if (t2 >= 0) return ray.at(t2);
    if (t1 >= 0) return ray.at(t1); 
    return glm::vec3(std::numeric_limits<float>::infinity());
}


Ray Sphere::calc_snell(glm::vec3 point, glm::vec3 L) 
{
    const float epsilon = 1e-4f;
    float refract_in = 1.0f / 1.5f;
    float refract_out = 1.5f;

    glm::vec3 N = get_normal(point);

    float cos_theta_i = glm::clamp(glm::dot(N, L), -1.0f, 1.0f);
    float sin_2_theta_i =  glm::clamp(1.0f - cos_theta_i * cos_theta_i, -1.0f, 1.0f);
    float sin_2_theta_r =  glm::clamp(refract_in * refract_in * sin_2_theta_i, -1.0f, 1.0f);
    float cos_theta_r =  glm::clamp(glm::sqrt(1.0f - sin_2_theta_r), -1.0f, 1.0f);

    glm::vec3 T = glm::normalize((refract_in * cos_theta_i - cos_theta_r) * N - refract_in * L);

    glm::vec3 exit_point = get_furthest_intersection(Ray(point + epsilon * T, T));
    if(exit_point == glm::vec3(std::numeric_limits<float>::infinity())) 
        std::cout<< "point " + std::to_string(point.x) + ","+ std::to_string(point.y) + "," + std::to_string(point.z) + " has no exit point"<<std::endl;;

    glm::vec3 exit_normal = -get_normal(exit_point);
    T = -T;

    cos_theta_i =  glm::clamp(glm::dot(exit_normal, T), -1.0f, 1.0f);
    sin_2_theta_i =  glm::clamp(1.0f - cos_theta_i * cos_theta_i, -1.0f, 1.0f);
    sin_2_theta_r =  glm::clamp(refract_out * refract_out * sin_2_theta_i, -1.0f, 1.0f);
    cos_theta_r =  glm::clamp(glm::sqrt(1.0f - sin_2_theta_r), -1.0f, 1.0f);

    glm::vec3 out_dir = glm::normalize((refract_out * cos_theta_i - cos_theta_r) * exit_normal - refract_out * T);

    return Ray(exit_point + epsilon * out_dir, out_dir);

}

// Ray Sphere::calc_snell(glm::vec3 point, glm::vec3 L) 
// {
//     const float epsilon = 1e-3f;
//     float refract_in = 1.0f / 1.5f; 
//     float refract_out = 1.5f / 1.0f; 

//     glm::vec3 N = get_normal(point);

//     glm::vec3 T = glm::normalize(glm::refract(-glm::normalize(L), N, refract_in));

//     glm::vec3 exit_point = get_furthest_intersection(Ray(point + epsilon * T, T));
//     if (exit_point == glm::vec3(std::numeric_limits<float>::infinity())) {
//         std::cout << "point " << point.x << "," << point.y << "," << point.z << " has no exit point" << std::endl;
//         return Ray(point, glm::vec3(0)); 
//     }

//     glm::vec3 exit_normal = -get_normal(exit_point);
//     T = glm::normalize(glm::refract(T, exit_normal, refract_out));

//     return Ray(exit_point + epsilon * T, T);
// }




glm::vec3 Sphere::get_normal(glm::vec3 p)
{
    return glm::normalize((p - center) / radius);
}


bool Sphere::is_plane() {return false;}

Sphere::~Sphere() {}



