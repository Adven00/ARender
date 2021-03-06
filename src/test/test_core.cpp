#include "core/render.h"
#include "core/camera.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

void SaveImage(int w, int h, unsigned char* frame_data)
{
    stbi_flip_vertically_on_write(1);
    stbi_write_bmp("test.bmp", w, h ,4, frame_data);
}

Vertex *MakeVertex(glm::vec4 pos, glm::vec4 color) {
    Vertex *v = new Vertex;
    v->attr.vec4_attr["color"] = color;
    v->coord.world = pos;
    return v;
}
Vertex *MakeVertex(glm::vec4 pos, glm::vec2 uv) {
    Vertex *v = new Vertex;
    v->attr.vec2_attr["uv"] = uv;
    v->coord.world = pos;
    return v;
}

Triangle MakeTriangle(std::array<glm::vec4, 3> vertices, glm::vec4 color) {
    Vertex *a = MakeVertex(vertices[0], color);
    Vertex *b = MakeVertex(vertices[1], color);
    Vertex *c = MakeVertex(vertices[2], color);

    return {a, b, c};
}

//#define BASIC_TEST
#define MODEL_TEST

inline void VS_1(Vertex *v, Uniform &uniform_) {
    v->coord.csc = uniform_.mvp_mat * v->coord.world;
}

inline glm::vec4 FS_1(Attr &attr, Uniform &uniform_) {
    return attr.vec4_attr["color"];
}

inline glm::vec4 FS_2(Attr &attr, Uniform &uniform) {
    float u = attr.vec2_attr["uv"].x;
    float v = attr.vec2_attr["uv"].y;

    return uniform.texture.Color(u, v);
}

int main() {
    const int w = 1000;
    const int h = 1000;

    auto r = Render::Instance(w, h);
    r->SetVertexShader(VS_1);

#ifdef BASIC_TEST

    r->SetFragmentShader(FS_1);

    glm::vec4 red(255.f, 0.f, 0.f, 255.f);
    glm::vec4 blue(0.f, 0.f, 255.f, 255.f);
    glm::vec4 green(0.f, 255.f, 0.f, 255.f);
    glm::vec4 yellow(255.f, 255.f, 0.f, 255.f);
    glm::vec4 cyan(0.f, 255.f, 255.f, 255.f);
    glm::vec4 purple(255.f ,0.f, 255.f, 255.f);
    glm::vec4 pink(255.f ,192.f, 203.f, 255.f);

    glm::vec4 _1(1.f, -1.f, -1.f, 1.f);
    glm::vec4 _2(1.f, -1.f, 1.f, 1.f);
    glm::vec4 _3(-1.f, -1.f, 1.f, 1.f);
    glm::vec4 _4(-1.f, -1.f, -1.f, 1.f);
    glm::vec4 _5(1.f, 1.f, -1.f, 1.f);
    glm::vec4 _6(1.f, 1.f, 1.f, 1.f);
    glm::vec4 _7(-1.f, 1.f, 1.f, 1.f);
    glm::vec4 _8(-1.f, 1.f, -1.f, 1.f);

    glm::vec4 _9(-1.f, 1.f, 0.f, 1.f);
    glm::vec4 _10(-1.f, -1.f, 0.f, 1.f);
    glm::vec4 _11(1.f, 1.f, -2.f, 1.f);
    glm::vec4 _12(1.f, -1.f, -2.f, 1.f);

    Triangle t_1 = MakeTriangle({_5, _1, _4}, red);
    Triangle t_2 = MakeTriangle({_5, _8, _4}, red);
    Triangle t_3 = MakeTriangle({_3, _8, _7}, yellow);
    Triangle t_4 = MakeTriangle({_3, _8, _4}, yellow);
    Triangle t_5 = MakeTriangle({_3, _2, _6}, blue);
    Triangle t_6 = MakeTriangle({_3, _6, _7}, blue);
    Triangle t_7 = MakeTriangle({_1, _5, _2}, green);
    Triangle t_8 = MakeTriangle({_5, _6, _2}, green);
    Triangle t_9 = MakeTriangle({_5, _6, _8}, purple);
    Triangle t_10 = MakeTriangle({_8, _7, _6}, purple);
    Triangle t_11 = MakeTriangle({_1, _2, _3}, cyan);
    Triangle t_12 = MakeTriangle({_3, _4, _1}, cyan);

    // test depth buffer
    Triangle t_13 = MakeTriangle({_9, _10, _11}, pink);
    Triangle t_14 = MakeTriangle({_10, _11, _12}, pink);

    r->DrawTriangle(t_1);
    r->DrawTriangle(t_2);
    r->DrawTriangle(t_3);
    r->DrawTriangle(t_4);
    // r.DrawTriangle(t_5);
    // r.DrawTriangle(t_6);
    r->DrawTriangle(t_7);
    r->DrawTriangle(t_8);
    r->DrawTriangle(t_9);
    r->DrawTriangle(t_10);
    r->DrawTriangle(t_11);
    r->DrawTriangle(t_12);
    r->DrawTriangle(t_13);
    r->DrawTriangle(t_14);

#endif

#ifdef MODEL_TEST

    r->SetFragmentShader(FS_2);
    r->DrawModel();

#endif


    SaveImage(w, h, r->GetFrameData());

    return 0;
};