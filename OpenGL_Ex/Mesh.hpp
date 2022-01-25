//
//  Mesh.hpp
//  OpenGL_Ex
//
//  Created by Plum on 2022/1/20.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "Shader.hpp"

using namespace std;

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct Texture {
    unsigned int id;
    string type;
    string path;
};

class Mesh {
    
    
public:
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    
    Mesh(vector<Vertex> vertices, vector<unsigned int>indices, vector<Texture> textures);
    
    void draw(Shader shader);
    
private:
    unsigned int VAO, VBO, EBO;
    void setupMesh();
};

#endif /* Mesh_hpp */
