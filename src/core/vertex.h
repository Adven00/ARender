#ifndef VERTEX_H_
#define VERTEX_H_ 

#include <array>
#include <map>
#include <string>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

// vertex attributes
// reserved key : "uv", "normal"
struct Attr {
    std::map<std::string, glm::vec4> vec4_attr;
    std::map<std::string, glm::vec3> vec3_attr;
    std::map<std::string, glm::vec2> vec2_attr;
    std::map<std::string, float> float_attr;
};

// vertex coordinates
struct Coord {
    glm::vec4 world;        // homogeneous world coordinates (w = 1)
    glm::vec4 csc;          // homogeneous clip space coordinates
    glm::vec3 ndc;          // normalized device coordinates (w = 1)
    glm::vec2 screen;       // screen coordinates
    glm::ivec2 screen_int;  // interger screen coordinates
};

struct Vertex {
    Coord coord;
    Attr attr;
};

using Triangle = std::array<Vertex *, 3>;

#endif // VERTEX_H_
