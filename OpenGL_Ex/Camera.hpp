//
//  Camera.hpp
//  OpenGL_Ex
//
//  Created by Plum on 2021/12/30.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <glad/glad.h>


enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


class Camera {
    
public:
glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 left;
    glm::vec3 worldUp;
    
    float yaw;
    float pitch;
    
    float movementSpeed;
    float mouseSensitivity;
    float zoom;
    
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM) {
        this->position = position;
        this->worldUp = up;
        this->yaw = yaw;
        this->pitch = pitch;
        
        updateCameraVectors();
    };
    
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM) {
        position = glm::vec3(posX, posY, posZ);
        worldUp = glm::vec3(upX, upY, upZ);
        yaw = yaw;
        pitch = pitch;
        
        updateCameraVectors();
    }
    
    glm::mat4 getViewMatrix() {
        return glm::lookAt(position, position + front, up);
    }
    
    void processKeyboard(Camera_Movement dirction, float deltaTime) {
        float velocity = movementSpeed * deltaTime;
        switch (dirction) {
            case FORWARD:
                position += front * velocity;
                break;
                
            case BACKWARD:
                position -= front * velocity;
                break;
                
            case LEFT:
                position -= right * velocity;
                break;
                
            case RIGHT:
                position += right * velocity;
                break;
                
            default:
                break;
        }
    }
    
    void processMouseMovement(float xOffset, float yOffset, GLboolean constraintPitch = true) {
        xOffset *= mouseSensitivity;
        yOffset *= mouseSensitivity;
        
        yaw += xOffset;
        pitch += yOffset;
        
        if (constraintPitch) {
            if (pitch > 89.0f) {
                pitch = 89.0f;
            } else if (pitch < -89.0f) {
                pitch = -89.0f;
            }
        }
        
        updateCameraVectors();
    }
    
    void precessMouseScroll(float yOffset) {
        zoom -= yOffset;
        if (zoom < 1.0f) {
            zoom = 1.0f;
        }
        if (zoom > 45.0f) {
            zoom = 45.0f;
        }
    }
    
private:
    void updateCameraVectors() {
        glm::vec3 front;
        front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
        front.y = sin(glm::radians(pitch));
        front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
        this->front = glm::normalize(front);
        
        right = glm::normalize(glm::cross(this->front, worldUp));
        up = glm::normalize(glm::cross(this->right, this->front));
    }
};


#endif /* Camera_hpp */
