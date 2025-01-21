
// #include <stb/stb_image.h>
// #include <stb/stb_image_write.h>
// #include <string.h>
// #include <iostream>
// #include <vector>
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <algorithm>

// enum grayscaleT 
// {
//     AVERAGE,
//     WEIGHTED
// };

// enum filterT
// {
//     LAPLAC,
//     GAUSS
// };



// /* Prototypes */
// int grayscale(unsigned char* buffer, int width, int height, int* comps, grayscaleT type);
// int cannyEdgeDetector(unsigned char* buffer, int width, int height, int comps, filterT ft);
// int blur(unsigned char* buffer, int width, int height, int comps, filterT ft);
// void convolve(unsigned char* buffer, int width, int height, int comps, std::vector<float> filter);
// int getIndex(int x, int y, int width, int comps, int comp);
// void sobel(unsigned char* buffer, int width, int height, int comps, std::vector<float>& angles);
// int nonMaxSuppression(unsigned char* buffer, int width, int height, int comps, std::vector<float>& angles);
// unsigned char * halftone(unsigned char * buffer, unsigned char * newBuff, int width, int height, int comps);
// void floydSteinberg(unsigned char * buffer, int w, int h, int comps);


// int main(int argc, char* argv[])
// {
//     std::string filepath = "res/textures/Lenna.png";
//     int width, height, comps;
//     int req_comps = 4;
    
//     /* GRAYSCALE */
//     unsigned char * buffer = stbi_load(filepath.c_str(), &width, &height, &comps, req_comps);
//     if (!buffer) {
//         return -173;
//     }
//     grayscale(buffer, width, height, &comps, WEIGHTED);
//     std::string graypath = "res/textures/Grayscale.png";
//     stbi_write_png(graypath.c_str(), width, height, comps, buffer, width * comps);
//     std::cout << "Grayscale -> COMPLETED" << std::endl;


//     /* CANNY EDGE DETECTOR */
//     req_comps = 2;
//     //grayscale image already in buffer
//     cannyEdgeDetector(buffer, width, height, comps, GAUSS);
//     stbi_write_png("res/textures/Canny.png", width, height, comps, buffer, width * comps);
//     std::cout << "Canny Edge Detection -> COMPLETED" << std::endl;
//     stbi_image_free(buffer);


//     /* HALFTONE */
//     buffer = stbi_load(graypath.c_str(), &width, &height, &comps, req_comps);
//     if (!buffer) {
//         return -193;
//     }
//     int newW = width<<1;
//     int newH = height<<1;
//     unsigned char* newBuff = (unsigned char*)std::calloc(newW * newH * comps, sizeof(unsigned char));
//     if (!newBuff) {
//         return -193;
//     }
//     halftone(buffer, newBuff, newW, newH, comps);
//     stbi_write_png("res/textures/Halftone.png", newW, newH, comps, newBuff, newW * comps);
//     std::cout << "Halftone -> COMPLETED" << std::endl;
//     free(newBuff);


//     /* FLOYD STEINBERG DITHERING */
//     floydSteinberg(buffer, width, height, comps);
//     stbi_write_png("res/textures/FloydSteinberg.png", width, height, comps, buffer, width * comps);
//     std::cout << "Floyd-Steinberg -> COMPLETED" << std::endl;
//     stbi_image_free(buffer);
    
//     return 0;
// }




// int grayscale(unsigned char* buffer, int width, int height, int *comps, grayscaleT type)
// {
//     if(!buffer) return -1;

//     std::vector<unsigned char> tempBuffer(buffer, buffer + width * height * (*comps));

//     for(int i = 0, j = 0; i < width*height*(*comps); i+=4, j+=2)
//     {
//         unsigned char r = tempBuffer[i];
//         unsigned char g = tempBuffer[i + 1];
//         unsigned char b = tempBuffer[i + 2];
//         unsigned char a = tempBuffer[i + 3];
//         unsigned char gray = type == AVERAGE ? (r + g + b)/3 : static_cast<unsigned char>(r*0.299 + g*0.587 + b*0.114);

//         buffer[j] = gray;
//         buffer[j + 1] = a;
//     }

//     *comps = 2;
    
//     return 1;
// }




// /*
//     using 3x3 kernel, supporting Laplacian/Gaussian filter 
//     Laplacian       Gaussian   
//     [0   1  0]      [1 2 1]
//     |1  -4  1|      |2 4 2| * 1/16
//     [0   1  0]      [1 2 1]
// */
// int blur(unsigned char* buffer, int width, int height, int comps, filterT ft)
// {

//     std::vector<float> filter;

//     switch (ft)
//     {
//     case LAPLAC:
//         filter.assign({0.0,-1.0,0.0,
//                        -1.0,4.0,-1.0,
//                        0.0,-1.0,0.0});
//         break;
    
//     case GAUSS:
//         filter.assign({1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f,
//                        2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f,
//                        1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f});
//         break;
    
//     default:
//         return -3;
//     }


//     convolve(buffer, width, height, comps, filter);
  
//     return 1;

// }

// int getIndex(int x, int y, int width, int comps, int comp)
// {
//     return (y*width + x)*comps + comp;
// }

// int getMirrorIndex(int idx, int max)
// {
//     if (idx < 0) return -idx;
//     if (idx >= max) return 2 * max - idx - 2;
//     return idx;
// }


// // convolution for 3x3 ONLY
// void convolve(unsigned char* buffer, int width, int height, int comps, const std::vector<float> filter)
// {
    
//     std::vector<unsigned char> tempBuffer(buffer, buffer + width * height * comps);

//     for (int y = 0; y < height; y++)
//     {
//         for (int x = 0; x < width; x++)
//         {
//             for (int c = 0; c < comps; c++)
//             {
                
//                 if (c == comps - 1) 
//                 {
//                     buffer[getIndex(x, y, width, comps, c)] = tempBuffer[getIndex(x, y, width, comps, c)];
//                     continue;
//                 }

//                 float newVal = 0.0f;

                
//                 for (int i = -1; i <= 1; i++)
//                 {
//                     for (int j = -1; j <= 1; j++)
//                     {
//                         int adjX = getMirrorIndex(x + j, width);
//                         int adjY = getMirrorIndex(y + i, height);

//                         int tempBuffIdx = getIndex(adjX, adjY, width, comps, c);
//                         int filterIdx = (i + 1) * 3 + (j + 1); 

//                         newVal += static_cast<float>(tempBuffer[tempBuffIdx]) * filter[filterIdx];
//                     }
//                 }

//                 int buffIdx = getIndex(x, y, width, comps, c);
//                 buffer[buffIdx] = static_cast<unsigned char>(glm::clamp(newVal, 0.0f, 255.0f));
//             }
//         }
//     }
// }



// void sobel(unsigned char* buffer, int width, int height, int comps, std::vector<float>& angles)
// {
//     std::vector<float> g_x = { 1.0f,  0.0f, -1.0f,
//                             2.0f,  0.0f, -2.0f,
//                             1.0f,  0.0f, -1.0f };

//     std::vector<float> g_y = { 1.0f,  2.0f,  1.0f,
//                             0.0f,  0.0f,  0.0f,
//                             -1.0f, -2.0f, -1.0f };

//     std::vector<unsigned char> tempBuffer(buffer, buffer + width * height * comps);

//     for(int y = 1; y < height - 1; y++)
//     {
//         for(int x = 1; x < width - 1; x++)
//         {


//             float gradX = 0.0f;
//             float gradY = 0.0f;

//             for(int i = -1; i <= 1; i++)
//             {
//                 for(int j = -1; j <= 1; j++)
//                 {
//                     int tempBuffIdx = getIndex(x + j, y + i, width, comps, 0);
//                     int filterIdx = (i + 1) * 3 + (j + 1);

//                     gradX += static_cast<float>(tempBuffer[tempBuffIdx])*g_x[filterIdx];
//                     gradY += static_cast<float>(tempBuffer[tempBuffIdx])*g_y[filterIdx];
//                 }
//             }

//             float magnitude = glm::sqrt(gradX*gradX + gradY*gradY);
//             float angle = std::atan2(gradY, gradX);

//             angles[getIndex(x, y, width, 1, 0)] = angle;
//             buffer[getIndex(x, y, width, comps, 0)] = static_cast<unsigned char>(glm::clamp(magnitude, 0.0f, 255.0f));
        
//         }
//     }
    
// }


// void fixBorder(unsigned char* buffer, int width, int height, int comps)
// {
//     for(int x = 0; x < width; x++)
//     {
//         buffer[getIndex(x, 0, width, comps, 0)] /= 2;
//         buffer[getIndex(x, height - 1, width, comps, 0)] /= 2;
//     }

//     for(int y = 0; y < height; y++)
//     {
//         buffer[getIndex(0, y, width, comps, 0)] /= 2;
//         buffer[getIndex(width - 1, y, width, comps, 0)] /= 2;
//     }
// }


// int nonMaxSuppression(unsigned char* buffer, int width, int height, int comps, std::vector<float>& angles)
// {
//     std::vector<unsigned char> tempBuffer(buffer, buffer + width * height * comps);
//     float PI = glm::pi<float>();

//     for(int y = 1; y < height - 1; y++)
//     {
//         for(int x = 1; x < width - 1; x++)
//         {
//             int buffIndex = getIndex(x, y, width, comps, 0);
//             int angleIndex = getIndex(x, y, width, 1, 0);

//             float angle = angles[angleIndex];
//             while(angle < -PI/2) angle += PI;
//             while(angle >= PI/2) angle -= PI;

//             unsigned char adj1 = 0;
//             unsigned char adj2 = 0;

//             if(angle >= -PI/8 && angle < PI/8)
//              // (1,0) direction
//             {
//                 adj1 = tempBuffer[getIndex(x + 1, y, width, comps, 0)];
//                 adj2 = tempBuffer[getIndex(x - 1, y, width, comps, 0)];
//             }
//             else if(angle >= PI/8 && angle < 3*PI/8)
//              // (1,1) direction
//             {
//                 adj1 = tempBuffer[getIndex(x + 1, y + 1, width, comps, 0)];
//                 adj2 = tempBuffer[getIndex(x - 1, y - 1, width, comps, 0)];
//             }
//             else if(angle >= 3*PI/8 && angle < PI/2) 
//             // (0,1) direction
//             {
//                 adj1 = tempBuffer[getIndex(x, y + 1, width, comps, 0)];
//                 adj2 = tempBuffer[getIndex(x, y - 1, width, comps, 0)];
//             }
//             else 
//             // (1,-1) direction
//             {
//                 adj1 = tempBuffer[getIndex(x + 1, y - 1, width, comps, 0)];
//                 adj2 = tempBuffer[getIndex(x - 1, y + 1, width, comps, 0)];
//             }
            
//             if(tempBuffer[buffIndex] < glm::max(adj1, adj2)) buffer[buffIndex] = 0;

//         }
//     }

//     fixBorder(buffer, width, height, comps);

//     return 4;
// }


// void doubleThresholding(unsigned char* buffer, int width, int height, int comps)
// {
//     for (int y = 0; y < height; y++)
//     {
//         for (int x = 0; x < width; x++)
//         {
//             int idx = getIndex(x, y, width, comps, 0);
//             int pixel = buffer[idx];

//             if(pixel < 100) buffer[idx] = 0;
//             else if(pixel > 170) buffer[idx] = 255;
            
//         }
//     }
// }


// void hysteresis(unsigned char* buffer, int width, int height, int comps)
// {
//     for(int y = 1; y < height - 1; y++)
//     {
//         for(int x = 1; x < width - 1; x++)
//         {
//             int idx = getIndex(x, y, width, comps, 0);
//             if(buffer[idx] > 0 && buffer[idx] < 255)
//             {
//                 if( buffer[getIndex(x + 1, y, width, comps, 0)] == 255 ||
//                     buffer[getIndex(x - 1, y, width, comps, 0)] == 255 ||
//                     buffer[getIndex(x, y + 1, width, comps, 0)] == 255 ||
//                     buffer[getIndex(x, y - 1, width, comps, 0)] == 255)
//                         buffer[idx] = 255;
//                 else buffer[idx] = 0;
//             }
//         }
//     }
// }

// int cannyEdgeDetector(unsigned char* buffer, int width, int height, int comps, filterT ft)
// {
//     //invariant: buffer holds grayscale picture
    
//     std::vector<float> angles(width*height, 0.0);
    
//     int error = blur(buffer, width, height, comps, ft);
//     if(error != 1) return error;
//     sobel(buffer, width, height, comps, angles);
//     nonMaxSuppression(buffer, width, height, comps, angles);
//     doubleThresholding(buffer, width, height, comps);
//     hysteresis(buffer, width, height, comps);

//     return error;
// }





// /* HALFTONE*/
// void updateHalftone(unsigned char* buffer, int w, int comps, int x, int y, int pixel, int a)
// {
//     // Opacity (A)
//     buffer[getIndex(x, y + 1, w, comps, 1)] = a;    
//     buffer[getIndex(x + 1, y, w, comps, 1)] = a;
//     buffer[getIndex(x + 1, y + 1, w, comps, 1)] = a;
//     buffer[getIndex(x, y, w, comps, 1)] = a;

//     /* Coloring
//         gray level:     0<=l<0.2    0.2<=l<0.4     0.4<=l<0.6      0.6<=l<0.8      0.8<=l<1

//                         | 0 0 |     |  0  0 |     |  0  255 |     |  0  255 |     | 255 255 |
//                         | 0 0 |     | 255 0 |     | 255  0  |     | 255 255 |     | 255 255 |
    
//     */
//     if(51 <= pixel) buffer[getIndex(x, y + 1, w, comps, 0)] = 255;    
//     if(102 <= pixel) buffer[getIndex(x + 1, y, w, comps, 0)] = 255;
//     if(153 <= pixel) buffer[getIndex(x + 1, y + 1, w, comps, 0)] = 255;
//     if(204 <= pixel) buffer[getIndex(x, y, w, comps, 0)] = 255;

// }


// unsigned char* halftone(unsigned char* buffer, unsigned char* newBuff, int width, int height, int comps)
// {
//     int w0 = width>>1;
//     int h0 = height>>1;

//     for (int y = 0; y < h0; y++)
//     {
//         for (int x = 0; x < w0; x++)
//         {
//             int idx = getIndex(x, y, w0, comps, 0);
//             int pixel = buffer[idx];
//             int a = buffer[idx + 1];

//             updateHalftone(newBuff, width, comps, x<<1, y<<1, pixel, a);
//         }
//     }

//     return newBuff;
// }   





// /* FLOYD STEINBERG*/

// void floydSteinberg(unsigned char * buffer, int w, int h, int comps)
// {
//     for (int y = 0; y < h; y++)
//     {
//         for (int x = 0; x < w; x++)
//         {
//             int idx = getIndex(x, y, w, comps, 0);
//             int oldPixel = buffer[idx];
//             int newPixel = ((buffer[idx] + 8)/16) * 16;
            
//             int error = oldPixel - newPixel;

//             buffer[idx] = newPixel;

//             if(x < w - 1)
//             {
//                 // right
//                 int rIdx = getIndex(x + 1, y, w, comps, 0);
//                 buffer[rIdx] += std::clamp((7*error)/16, 0, 255);
//             }

//             if(y < h - 1)
//             {
//                 if(x < w - 1) 
//                 { 
//                     // right-bottom
//                     int rbIdx = getIndex(x + 1, y + 1, w, comps, 0);
//                     buffer[rbIdx] += std::clamp(error/16, 0, 255);  
//                 }

//                 if(x > 0)
//                 {
//                     // left-bottom
//                     int lbIdx = getIndex(x - 1, y + 1, w, comps, 0);
//                     buffer[lbIdx] += std::clamp((3*error)/16, 0, 255);  
//                 }

//                 // bottom
//                 int bIdx = getIndex(x, y + 1, w, comps, 0);
//                 buffer[bIdx] += std::clamp((5*error)/16, 0, 255);  
//             }
//         }
//     }
// }
