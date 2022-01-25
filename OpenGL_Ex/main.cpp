//
//  main.cpp
//  OpenGL_Ex
//
//  Created by Plum on 2021/12/9.
//

#include <iostream>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Camera.hpp"
#include "Model.hpp"

void processInput(GLFWwindow *window);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xpos, double ypos);

unsigned int loadTexture(char const *path);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


Camera camera(glm::vec3(0.0f, 0.0f, 6.0f));

// light position
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


float deltaTime = 0.0f;
float lastTime = 0.0f;
float lastX = 400, lastY = 300;
bool isFirstTime = true;

int main(int argc, const char * argv[]) {
    // insert code here...
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);
    
    Shader objctShader("shaders/model.shader.vs", "shaders/model.shader.fs");
    Model modelData("nanosuit/nanosuit.obj");
    
    while (!glfwWindowShouldClose(window)) {
        
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastTime;
        lastTime = currentFrame;
        
        processInput(window);
        
        // render commands
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
//        lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
//        lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;
//
//        glm::vec3 lightColor(1.0);
//        lightColor.x = sin(glfwGetTime() * 2.0f);
//        lightColor.y = sin(glfwGetTime() * 0.7f);
//        lightColor.z = sin(glfwGetTime() * 1.3f);
//        glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
//        glm::vec3 ambientColor = lightColor * glm::vec3(0.2f);
        
        // draw
        objctShader.use();
//        objctShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        /*
        objctShader.setVec3("light.position", camera.position);
        objctShader.setVec3("light.direction", camera.front);
        objctShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
        objctShader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
        
        objctShader.setVec3("viewPos", camera.position);
        
//        objctShader.setInt("material.diffuse", 0);
//        objctShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
        objctShader.setFloat("material.shininess", 32.0f);
        
        // directional light
        objctShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        objctShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        objctShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        objctShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        // point light 1
        objctShader.setVec3("pointLights[0].position", pointLightPositions[0]);
        objctShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        objctShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        objctShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        objctShader.setFloat("pointLights[0].constant", 1.0f);
        objctShader.setFloat("pointLights[0].linear", 0.09f);
        objctShader.setFloat("pointLights[0].quadratic", 0.032f);
        // point light 2
        objctShader.setVec3("pointLights[1].position", pointLightPositions[1]);
        objctShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        objctShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        objctShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        objctShader.setFloat("pointLights[1].constant", 1.0f);
        objctShader.setFloat("pointLights[1].linear", 0.09f);
        objctShader.setFloat("pointLights[1].quadratic", 0.032f);
        // point light 3
        objctShader.setVec3("pointLights[2].position", pointLightPositions[2]);
        objctShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        objctShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        objctShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        objctShader.setFloat("pointLights[2].constant", 1.0f);
        objctShader.setFloat("pointLights[2].linear", 0.09f);
        objctShader.setFloat("pointLights[2].quadratic", 0.032f);
        // point light 4
        objctShader.setVec3("pointLights[3].position", pointLightPositions[3]);
        objctShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        objctShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        objctShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        objctShader.setFloat("pointLights[3].constant", 1.0f);
        objctShader.setFloat("pointLights[3].linear", 0.09f);
        objctShader.setFloat("pointLights[3].quadratic", 0.032f);
        // spotLight
        objctShader.setVec3("spotLight.position", camera.position);
        objctShader.setVec3("spotLight.direction", camera.front);
        objctShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        objctShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        objctShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        objctShader.setFloat("spotLight.constant", 1.0f);
        objctShader.setFloat("spotLight.linear", 0.09f);
        objctShader.setFloat("spotLight.quadratic", 0.032f);
        objctShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        objctShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
        */
        // view
        glm::mat4 view = camera.getViewMatrix();
        objctShader.setMatrix4("view", view);
        
        // projection
        glm::mat4 proj = glm::perspective(glm::radians(camera.zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        objctShader.setMatrix4("projection", proj);
        
        // model
        glm::mat4 model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.2f, .2f, .2f));
        objctShader.setMatrix4("model", model);
        modelData.draw(objctShader);
        
        /*
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseTexture);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularTexure);
        
        // 渲染光照后的箱子
        glBindVertexArray(objVAO);
        for (unsigned int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            objctShader.setMatrix4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        lightShader.use();
        lightShader.setMatrix4("view", view);
        lightShader.setMatrix4("projection", proj);
        
        glBindVertexArray(lightVAO);
        for (unsigned int i = 0; i < 4; i++) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f));
            lightShader.setMatrix4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
         */
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
//    glDeleteVertexArrays(1, &objVAO);
//    glDeleteVertexArrays(1, &lightVAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteTextures(1, &diffuseTexture);
//    glDeleteTextures(1, &specularTexure);
    
    glfwTerminate();
    return 0;
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (isFirstTime) {
        lastX = xpos;
        lastY = ypos;
        isFirstTime = false;
    }
    
    float xOffset = xpos - lastX;
    float yOffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    
    camera.processMouseMovement(xOffset, yOffset);
}

void scroll_callback(GLFWwindow *window, double xpos, double ypos) {
    camera.precessMouseScroll(ypos);
}

void processInput(GLFWwindow *window) {
    float currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.processKeyboard(FORWARD, deltaTime);
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.processKeyboard(BACKWARD, deltaTime);
    } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.processKeyboard(LEFT, deltaTime);
    } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.processKeyboard(RIGHT, deltaTime);
    }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

unsigned int loadTexture(char const *path) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    
    int width, height, components;
    
    unsigned char *data = stbi_load(path, &width, &height, &components, 0);
    if (data) {
        GLenum format = 0;
        if (components == 1) {
            format = GL_RED;
        } else if (components == 3) {
            format = GL_RGB;
        } else if (components == 4) {
            format = GL_RGBA;
        }
        
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
                
    }
    
    stbi_image_free(data);
    return textureID;
}
