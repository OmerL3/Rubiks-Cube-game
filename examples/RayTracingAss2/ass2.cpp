// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <vector>
// #include <string>
// #include <Light.h>
// #include <Ambient.h>
// #include <Spotlight.h>
// #include <Directional.h>
// #include "Object.h"
// #include <Sphere.h>
// #include <Plane.h>
// #include <Ray.h>
// #include <Intersection.h>


// #include <stb/stb_image.h>
// #include <stb/stb_image_write.h>
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>

// using namespace std;


// void parse_line(const string& line, vector<Light*>& lights, vector<Object*>& objects, glm::vec3& eye)
// {
//     stringstream ss(line);
//     char type;
//     ss >> type;
    
//     vector<float> values;
//     float val;

//     while(ss >> val) values.push_back(val);


//     switch (type)
//     {
//     case 'e':
//         eye = glm::vec3(values[0], values[1], values[2]);
//         break;

//     case 'a':
//         lights.push_back(new Ambient(values[0], values[1], values[2]));
//         break;
    
//     case 'd':
//         if(values[3] == 0.0f)
//             lights.push_back(new Directional(glm::vec3(values[0], values[1], values[2])));
//         else
//             lights.push_back(new Spotlight(glm::vec3(values[0], values[1], values[2])));
//         break;

//     case 'p':
//         for(Light* light : lights)
//         {
//             if(light->is_spotlight())
//             {
//                 if(dynamic_cast<Spotlight*>(light)->get_angle() == -1.0f)
//                 {
//                    dynamic_cast<Spotlight*>(light)->set_angle(values[3]);
//                    dynamic_cast<Spotlight*>(light)->set_point(glm::vec3(values[0], values[1], values[2]));
//                    break;
//                 }
//             }
//         }
//         break;

//     case 'i':
//         for(Light* light : lights)
//         {
//             if(!light->is_ambient() && !light->is_intensity_set()){
//                 light->set_intensity(values[0], values[1], values[2]);
//                 break;
//             }    
//         }
//         break;
    
//     case 'o':
//     case 'r':
//     case 't':
//         opticalT optType;
//         if(type == 'o') optType = NORMAL;
//         else if(type == 'r') optType = REFLECTIVE;
//         else optType = TRANSPARENT;

//         if(values[3] > 0)
//         {
//             objects.push_back(new Sphere(glm::vec3(values[0], values[1], values[2]), values[3], optType));
//         }
//         else
//         {
//             objects.push_back(new Plane(glm::vec3(values[0], values[1], values[2]), values[3], optType));
//         }
//         break;

//     case 'c':
//         for(Object* obj : objects)
//         {
//             if(!obj->is_rgb_set())
//             {
//                 obj->set_rgb(values[0], values[1], values[2], values[3]);
//                 break;
//             }
//         }
//         break;

//     default:
//         cout << "Wrong instructions in type: " << type << endl;
//         break;
//     }

// }

// int parse(const string& filename, vector<Light*>& lights, vector<Object*>& objects, glm::vec3& eye)
// {
//     ifstream inputFile(filename);

//     if (!inputFile.is_open()) {
//         cerr << "Error: Could not open file " << filename << endl;
//         return -1;
//     }

//     cout << "Parsing file: " << filename << endl;

//     string line;
//     while (getline(inputFile, line)) {
//         if (line.empty()) {
//             continue;
//         }

//         parse_line(line, lights, objects, eye);
//     }

//     inputFile.close();
//     return 0;
// }


// std::vector<Ray> construct_rays(int R_x, int R_y, glm::vec3 eye, int rays_per_pixel)  
// {
//     std::vector<Ray> rays;
//     const float epsilon = 1e-3f; 
//     rays.reserve(R_x*R_y*rays_per_pixel);


//     glm::vec3 bottomLeft(-1,-1,0);

//     float step = 2.0f / R_x;

//     for (int i = 0; i < R_y; ++i) {
//         for (int j = 0; j < R_x; ++j) {
//             if(rays_per_pixel == 1)
//             {
//                 glm::vec3 pixelPos(
//                     bottomLeft.x + step*j,
//                     bottomLeft.y + step*i,
//                     0
//                 );
//                 glm::vec3 direction = glm::normalize(pixelPos - eye);
//                 rays.push_back(Ray(eye, direction));
//             }
//             else
//             {
//                 glm::vec3 pixelPos1(
//                     bottomLeft.x + step*j + epsilon,
//                     bottomLeft.y + step*i + epsilon,
//                     0
//                 );
//                 glm::vec3 pixelPos2(
//                     bottomLeft.x + step*j + epsilon,
//                     bottomLeft.y + step*i - epsilon,
//                     0
//                 );
//                 glm::vec3 pixelPos3(
//                     bottomLeft.x + step*j - epsilon,
//                     bottomLeft.y + step*i + epsilon,
//                     0
//                 );
//                 glm::vec3 pixelPos4(
//                     bottomLeft.x + step*j - epsilon,
//                     bottomLeft.y + step*i - epsilon,
//                     0
//                 );
//                 glm::vec3 direction1 = glm::normalize(pixelPos1 - eye);
//                 glm::vec3 direction2 = glm::normalize(pixelPos2 - eye);
//                 glm::vec3 direction3 = glm::normalize(pixelPos3 - eye);
//                 glm::vec3 direction4 = glm::normalize(pixelPos4 - eye);


//                 rays.push_back(Ray(eye, direction1));
//                 rays.push_back(Ray(eye, direction2));
//                 rays.push_back(Ray(eye, direction3));
//                 rays.push_back(Ray(eye, direction4));

//             }


//         }
//     }

//     return rays;
// }


// glm::vec3 checkerboardColor(glm::vec3 rgbColor, glm::vec3 hitPoint)  
// {
//     float scaleParameter = 0.5f;
//     float checkerboard = 0;
//     if (hitPoint.x < 0) {
//         checkerboard += floor((0.5 - hitPoint.x) / scaleParameter);
//     } else {
//         checkerboard += floor(hitPoint.x / scaleParameter);
//     }
//     if (hitPoint.y < 0) {
//         checkerboard += floor((0.5 - hitPoint.y) / scaleParameter);
//     } else {
//         checkerboard += floor(hitPoint.y / scaleParameter);
//     }
//     checkerboard = (checkerboard * 0.5) - int(checkerboard * 0.5);
//     checkerboard *= 2;
//     if (checkerboard > 0.5) {
//         return 0.5f * rgbColor;
//     }
//     return rgbColor;
// }

// void parsing_validator(vector<Light*>& lights, vector<Object*>& objects, glm::vec3 eye)
// {
//     for(size_t i = 0; i<objects.size(); i++)
//     {
//         if(objects[i] == nullptr) cout<<"null object"<<endl;
//         else cout<<objects[i]->to_string_print()<<endl;

//     }
//     for(size_t i = 0; i<lights.size(); i++)
//     {
//         if(lights[i] == nullptr) cout<<"null light"<<endl;
//         else cout<<lights[i]->to_string_print()<<endl;    
//     }
//     cout << "eye = (" + std::to_string(eye.x) + "," + std::to_string(eye.y) + "," + std::to_string(eye.z) + ")\n" << endl;
// }

// void rays_validator(vector<Ray> rays)
// {
//     int counter = 0;
//     for(Ray r : rays)
//     {
//         if(counter%16384 == 0)
//             cout << std::to_string(r.get_direction().x) + "," +  std::to_string(r.get_direction().y) +","+ std::to_string(r.get_direction().z) << endl;
//         counter++;
//     }
// }

// Intersection* single_find_intersection(Ray ray, vector<Object*>& objects)
// {
//     float min_distance = FLT_MAX;
//     Intersection* closest_intersection = nullptr;                         

//     for(Object* obj : objects)
//     {
//         glm::vec3 t_point = obj->get_intersection(ray);

//         if(t_point.x == std::numeric_limits<float>::infinity()) continue; 

//         float distance = glm::distance2(t_point, ray.get_start());

//         if(distance < min_distance)
//         {
//             min_distance = distance;
//             if(closest_intersection == nullptr) delete(closest_intersection);
//             closest_intersection = new Intersection(t_point, obj);
                
//         }
//     }
//     return closest_intersection;
// }

// vector<Intersection*> find_intersections(vector<Ray> rays, vector<Object*>& objects)
// {

//     vector<Intersection*> intersections;
//     intersections.reserve(rays.size());

//     for(Ray ray : rays)
//     {
//         Intersection* interPoint = single_find_intersection(ray, objects);
//         intersections.push_back(interPoint);
//     }
//     return intersections;
// }

// void swap_y_coor(unsigned char* buffer, int width, int height, int comps)
// {
//         int row_size = width * comps;

//     for (int y = 0; y < height / 2; ++y) {
//         unsigned char* top_row = buffer + y * row_size;
//         unsigned char* bottom_row = buffer + (height - 1 - y) * row_size;

//         for (int i = 0; i < row_size; ++i) {
//             unsigned char temp = top_row[i];
//             top_row[i] = bottom_row[i];
//             bottom_row[i] = temp;
//         }
//     }
// }

// glm::vec3 calc_diffuse(Intersection* point, Light*& light, vector<Object*>& objects)
// {
//     Object* obj = point->get_object();
//     glm::vec3 p_vec = point->get_point();

//     //Diffuse
//     glm::vec3 N = obj->get_normal(p_vec);
//     glm::vec3 L;
//     if(light->is_spotlight())
//     {
//         L = glm::normalize(dynamic_cast<Spotlight*>(light)->get_point() - p_vec);
//     }
//     else
//     {
//         L = glm::normalize(-light->get_direction());
//     }
//     float NL = glm::max(glm::dot(N,L), 0.0f);
//     glm::vec3 K_D = obj->get_rgb();
    
    
//     return K_D*NL;
// }

// glm::vec3 calc_specular(Intersection* point, Light*& light, vector<Object*>& objects, Ray ray)
// {
//     Object* obj = point->get_object();
//     glm::vec3 p_vec = point->get_point();

//     glm::vec3 N = obj->get_normal(p_vec);
//     glm::vec3 L;
//     if(light->is_spotlight())
//     {
//         L = glm::normalize(dynamic_cast<Spotlight*>(light)->get_point() - p_vec);
//     }
//     else
//     {
//         L = glm::normalize(-light->get_direction());
//     }

//     //Specular
//     glm::vec3 V = glm::normalize(ray.get_start() - p_vec);
//     glm::vec3 R = glm::normalize(2*glm::dot(N,L)*N - L);
//     float VR_n = glm::pow(glm::max(glm::dot(V, R), 0.0f), obj->get_shininess());

//     glm::vec3 K_S(0.7f, 0.7f, 0.7f);
    
    
//     return K_S*VR_n;
// }

// glm::vec3 single_pixel_phong(Intersection* point, vector<Light*>& lights, vector<Object*>& objects, Ray ray, int recDepth = 5, int layer = 4)
// {
//     if(recDepth <= 0) return glm::vec3(0.0f);
//     Object* obj = point->get_object();
//     glm::vec3 p = point->get_point();


//     if(!obj->is_normal())
//     {
//         if(obj->is_reflective())
//         {
//             const float epsilon = 1e-4f;

//             glm::vec3 N = obj->get_normal(p);
//             glm::vec3 dir = glm::normalize(ray.get_direction());
//             glm::vec3 symmtericDirection = glm::normalize(dir - 2.0f*glm::dot(N, dir)*N);
//             Ray reflectiveRay(p + epsilon*symmtericDirection, symmtericDirection);

//             Intersection* nextP = single_find_intersection(reflectiveRay, objects);
//             if(!nextP) return glm::vec3(0.0f);

//             return single_pixel_phong(nextP, lights, objects, reflectiveRay, recDepth - 1, layer);
            
//         }
//         else
//         {
//             glm::vec3 refractiveValue(0.0f);
//             Sphere* sphere = dynamic_cast<Sphere*>(obj);
//             Ray refractiveRay = ray;
//             Intersection* nextP = single_find_intersection(refractiveRay, objects);
//             for(size_t i = 1; i<lights.size(); i++)
//             {
//                 if(!lights[i]->is_shadowed(point, objects))
//                 {

//                     if (lights[i]->is_spotlight())
//                     {
//                         refractiveRay = sphere->calc_snell(p, glm::normalize(dynamic_cast<Spotlight*>(lights[i])->get_point() - p));
//                     }
//                     else
//                     {
//                         refractiveRay = sphere->calc_snell(p, -glm::normalize(lights[i]->get_direction()));
//                     }

//                     nextP = single_find_intersection(refractiveRay, objects);
//                     if(!nextP) continue;
                    
//                 }
//             }
//             if(!nextP) return glm::vec3(0.0f);
//             return single_pixel_phong(nextP, lights, objects, refractiveRay, recDepth - 1, layer);
//         }
//     }
//     else
//     {
//         glm::vec3 ambient = obj->get_rgb()*dynamic_cast<Ambient*>(lights[0])->get_rgb();
//         glm::vec3 diffuse = glm::vec3(0.0f);    
//         glm::vec3 specular = glm::vec3(0.0f);

//         for(size_t i = 1; i<lights.size(); i++)
//         {
//             glm::vec3 I_L = lights[i]->get_intensity();
//             if(!lights[i]->is_shadowed(point, objects))
//             {
//                 diffuse += calc_diffuse(point, lights[i], objects)*I_L;
//                 specular += calc_specular(point, lights[i], objects, ray)*I_L;
//             }
//         }

//         glm::vec3 rgb = glm::vec3(0);
//         if(layer == 1) rgb = ambient;
//         if(layer == 2) rgb = diffuse;
//         if(layer == 3) rgb = specular;
//         if(layer == 4) rgb = ambient + diffuse + specular;
//         if(point->get_object()->is_plane() && point->get_object()->is_normal()) 
//             rgb = checkerboardColor(rgb, point->get_point());

//         return rgb;
//     }
// }


// vector<unsigned char> apply_phong(vector<Intersection*> intersections, vector<Light*>& lights, vector<Object*>& objects, const glm::vec3 eye, int l=4)
// {
//     vector<unsigned char> I_values;
//     I_values.reserve(intersections.size() * 4);

//     for(size_t i = 0; i<intersections.size(); i++)
//     {
//         if(intersections[i] != nullptr)
//         {
//             Ray ray(eye, intersections[i]->get_point() - eye);
//             glm::vec3 I_rgb = single_pixel_phong(intersections[i], lights, objects, ray, 5, l); // get RGB value from phong

//             I_rgb.r = glm::clamp(I_rgb.r, 0.0f, 1.0f);
//             I_rgb.g = glm::clamp(I_rgb.g, 0.0f, 1.0f);
//             I_rgb.b = glm::clamp(I_rgb.b, 0.0f, 1.0f);

//             I_values.push_back(static_cast<unsigned char>(I_rgb.r * 255.0f)); // R
//             I_values.push_back(static_cast<unsigned char>(I_rgb.g * 255.0f)); // G
//             I_values.push_back(static_cast<unsigned char>(I_rgb.b * 255.0f)); // B
//             I_values.push_back(255); // A (opacity)
//         }
//         else
//         {
//             //BACKGROUND IS BLACK
//             I_values.push_back(0); // R
//             I_values.push_back(0); // G
//             I_values.push_back(0); // B
//             I_values.push_back(255); // A(opacity)
//         }
//     }

//     return I_values;
// }


// int main()
// {
//     char again = 'y';
//     while(again == 'y'){
//         int sceneNum;
//         cout << "Enter scene number: (1-7)" <<endl;
//         cin >> sceneNum;
//         string filename = "res/scenes/scene" + to_string(sceneNum) + ".txt";
//         glm::vec3 eye;

//         char antialiasing;

//         cout << "Antialiasing? (y/n)" << endl;
//         cin >> antialiasing;

//         int numOfRays = antialiasing == 'y' ? 4 : 1;

//         int layers;
//         cout << "Choose layers: \n1) Ambient only\n2) Diffuse only\n3) Specular only\n4) All\n(1-4)" << endl;
//         cin >> layers;

        


//         vector<Light*> lights;
//         vector<Object*> objects;

//         parse(filename, lights, objects, eye);
//         // parsing_validator(lights, objects, eye);

//         int width = 800;
//         int height = 800;
//         int comps = 4;

//         unsigned char* buffer = (unsigned char*)std::calloc(width * height * comps, sizeof(unsigned char));
//         if (!buffer)
//         {
//             std::cerr << "Failed to allocate image buffer!" << std::endl;
//             return -1;
//         }

//         cout<<"Shooting " + to_string(width*height*numOfRays) + " rays" <<endl;
//         vector<Ray> rays = construct_rays(width, height, eye, numOfRays);
//         // rays_validator(rays);

//         vector<Intersection*> intersectPoints = find_intersections(rays, objects);
//         if (intersectPoints.empty())
//         {
//             std::cerr << "No intersections found!" << std::endl;
//             return -1;
//         }

//         cout<<"Assigning colors to rays... this might take a couple of seconds"<<endl;
//         vector<unsigned char> t_buffer = apply_phong(intersectPoints, lights, objects, eye, layers);

//         if(antialiasing == 'y')
//         {
//             for(size_t i = 0; i<t_buffer.size(); i+=16)
//             {   
//                 buffer[i / 4] = (t_buffer[i] + t_buffer[i + 4] + t_buffer[i + 8] + t_buffer[i + 12]) / 4;
//                 buffer[(i / 4) + 1] = (t_buffer[i + 1] + t_buffer[i + 5] + t_buffer[i + 9] + t_buffer[i + 13]) / 4;
//                 buffer[(i / 4) + 2] = (t_buffer[i + 2] + t_buffer[i + 6] + t_buffer[i + 10] + t_buffer[i + 14]) / 4;
//                 buffer[(i / 4) + 3] = (t_buffer[i + 3] + t_buffer[i + 7] + t_buffer[i + 11] + t_buffer[i + 15]) / 4;
//             }
//         }
//         else
//         {
//             for(size_t i = 0; i<t_buffer.size(); i++)
//             {   
//                 buffer[i] = t_buffer[i];
//             }
//         }

//         swap_y_coor(buffer, width, height, comps);

//         if (!stbi_write_png("res/textures/RTcheck.png", width, height, comps, buffer, width * comps))
//         {
//             std::cerr << "Failed to write image!" << std::endl;
//             return -1;
//         }

//         free(buffer);

//         for (Light* light : lights) {
//         delete light;
//         }
//         lights.clear();

//         for (Object* object : objects) {
//             delete object;
//         }
//         objects.clear();

//         for (Intersection* inter : intersectPoints) {
//             delete inter;
//         }
//         intersectPoints.clear();

//         cout<< "Ray tracing scene " + to_string(sceneNum) + " -> COMPLETED" <<endl;
//         cout << "\nAgain? (enter y for another one)" <<endl;
//         cin >> again;
//     }

// }
