#ifndef CAMERA_H_
#define CAMERA_H_

#include "uniform.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/matrix.hpp>

struct CameraPos {
    glm::vec3 eye_pos;
    glm::vec3 gaze_dir;
    glm::vec3 up_dir;
};

struct CameraField {
    float fovy;
    float aspect;
    float z_near;
    float z_far;
};

constexpr float PI = 3.1415926f;

constexpr CameraPos DEFAULT_CAMERA_POS = {
    glm::vec3(0.f, 0.f, 5.f),
    glm::vec3(0.f, 0.f, -1.f),
    glm::vec3(0.f, 1.f, 0.f)
};

constexpr CameraField DEFAULT_CAMERA_FIELD = {0.33f * PI, 1.f, 0.01f, 100.f};

class Camera {
protected:
    CameraPos pos_;
    CameraField field_;

public:
    Camera(CameraPos pos = DEFAULT_CAMERA_POS, CameraField field = DEFAULT_CAMERA_FIELD);
    ~Camera() = default;

    void AlterUniformViewMat(Uniform &uniform);
    void AlterUniformProjMat(Uniform &uniform);
    void AlterUniform(Uniform &uniform);
};

#endif // CAMERA_H_