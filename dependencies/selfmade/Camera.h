#ifndef OPENGLSETUP_CAMERA_H
#define OPENGLSETUP_CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// Defines several possible options for camera movement.
// Used as abstraction to stay away from window-system specific input methods
// 移动方位的枚举
enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// 移动视角枚举
// 只能在地面模式 | 飞天模式
enum Camera_View
{
    FPS_ONLY_GROUND,
    FPS_ALL
};

// Default camera values
// 默认相机的参数
// 横扭 | 纵扭 | 速度 | 移动敏感度 | 缩放(可以理解成fov)
const float YAW = -90.0f;
const float PITCH = 0.0f;
float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM_MIN = 1.0f;
const float ZOOM_MAX = 110.0f;

// An abstract camera class that processes input and
// calculates the corresponding Euler Angles, Vectors and Matrices
// for use in OpenGL
// 总之是欧拉角的Camera类
class Camera
{
  public:
    // Camera Attributes
    // 简单属性 位置|local前 local上 local右|世界上
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    // Euler Angles
    // 欧拉: 横扭 | 纵扭
    float Yaw;
    float Pitch;

    // Camera options
    // 相机选项: 移动速度 鼠标敏感度 缩放
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // Constructor with vectors
    // 矢量构造器
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED),
                                                   MouseSensitivity(SENSITIVITY), Zoom(ZOOM_MAX)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // Constructor with scalar values
    // 标量构造器
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM_MAX)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    // 朝向
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    // Processes input received from any keyboard-like input system.
    // Accepts input parameter in the form of camera defined ENUM
    // (to abstract it from windowing systems)
    // 键盘操作 : 方向移动
    void ProcessKeyboard_Move(Camera_Movement direction, float deltaTime, Camera_View camera_view = FPS_ONLY_GROUND)
    {
        float velocity = MovementSpeed * deltaTime;
        if (camera_view == FPS_ONLY_GROUND)
        {
            if (direction == FORWARD)
                Position += glm::vec3(Front.x, 0, Front.z) * velocity;
            if (direction == BACKWARD)
                Position -= glm::vec3(Front.x, 0, Front.z) * velocity;
            if (direction == LEFT)
                Position -= glm::vec3(Right.x, 0, Right.z) * velocity;
            if (direction == RIGHT)
                Position += glm::vec3(Right.x, 0, Right.z) * velocity;
        }
        if (camera_view == FPS_ALL)
        {
            if (direction == FORWARD)
                Position += Front * velocity;
            if (direction == BACKWARD)
                Position -= Front * velocity;
            if (direction == LEFT)
                Position -= Right * velocity;
            if (direction == RIGHT)
                Position += Right * velocity;
        }
    }

    // Processes input received from a mouse input system.
    // Expects the offset value in both the x and y direction.
    // 鼠标操作
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        // 保证不超越旋转边界 - 不会导致万向节死锁
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // Update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // Processes input received from a mouse scroll-wheel event.
    // Only requires input on the vertical wheel-axis
    // 滚轮操作
    void ProcessMouseScroll(float yoffset)
    {
        if (Zoom >= ZOOM_MIN && Zoom <= ZOOM_MAX)
            Zoom -= yoffset;
        if (Zoom <= ZOOM_MIN)
            Zoom = ZOOM_MIN;
        if (Zoom >= ZOOM_MAX)
            Zoom = ZOOM_MAX;
    }

    void ChangeSpeed(float targetSpeed = SPEED)
    {
        MovementSpeed = targetSpeed;
    }

  private:
    // Calculates the front vector from the Camera's (updated) Euler Angles
    // 私有:更新各个变量
    void updateCameraVectors()
    {
        // Calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);

        // Also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front,
                                          WorldUp)); // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));
    }
};
// OPENGLSETUP_CAMERA_H
#endif