#pragma once
#include <GL/glew.h>
#include "Texture.h"
#include <vector>
GLfloat skyboxVertices_1[] = {
    // Positions
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f,  1.0f
};
class SkyBox {
public:
    GLuint skyboxVBO, skyboxVAO, cubemapTexture;

    SkyBox(GLchar* right, GLchar* left, GLchar* top, GLchar* bottom, GLchar* back, GLchar* front,
        GLfloat* skyboxVertices,GLint skyBoxVerticesSize) {

        glGenVertexArrays(1, &this->skyboxVAO);
        glGenBuffers(1, &this->skyboxVBO);
        glBindVertexArray(this->skyboxVAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->skyboxVBO);
        glBufferData(GL_ARRAY_BUFFER, skyBoxVerticesSize, skyboxVertices, GL_STATIC_DRAW);
        
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);

        // Load textures
        vector<const GLchar*> faces;
        faces.push_back(right);
        faces.push_back(left);
        faces.push_back(top);
        faces.push_back(bottom);
        faces.push_back(back);
        faces.push_back(front);

        this->cubemapTexture = TextureLoading::LoadCubemap(faces);

    }
    void Draw() {
        glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
        // skybox cube
        glBindVertexArray(this->skyboxVAO);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, this->cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // Set depth function back to default
    }

};