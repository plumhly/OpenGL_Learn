//
//  Model.hpp
//  OpenGL_Ex
//
//  Created by Plum on 2022/1/21.
//

#ifndef Model_hpp
#define Model_hpp

#include <assimp/mesh.h>
#include <assimp/scene.h>

#include <stdio.h>
#include "Shader.hpp"
#include <vector>
#include <string>
#include <map>
#include "Mesh.hpp"


class Model {
    
public:
    Model(const char *path);
    
    void draw(Shader shader);
    
private:
    vector<Mesh> meshes;
    vector<Texture> loadedTextures;
    string directory;
    
    void loadModel(string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
    
    unsigned int textureFromFile(const char *path, const string &directory, bool gamma = false);
};

#endif /* Model_hpp */
