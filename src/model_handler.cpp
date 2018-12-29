//
// Created by xaaq on 29.12.18.
//

#include <model_handler.h>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#include <iostream>
#include <GL/gl.h>

ModelHandler::ModelHandler(char *filePath) {
    model = aiImportFile(filePath,
                         aiProcess_CalcTangentSpace |
                         aiProcess_Triangulate |
                         aiProcess_JoinIdenticalVertices |
                         aiProcess_SortByPType);
}

void ModelHandler::drawModel(int meshIndex) const {
    auto mesh = this->model->mMeshes[meshIndex];

    for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
        const aiFace *face = &mesh->mFaces[t];
        GLenum face_mode;

        switch (face->mNumIndices) {
            case 1:
                face_mode = GL_POINTS;
                break;
            case 2:
                face_mode = GL_LINES;
                break;
            case 3:
                face_mode = GL_TRIANGLES;
                break;
            case 4:
                face_mode = GL_POLYGON;
                break;
            default:
                face_mode = GL_POINTS;
        }

        glBegin(face_mode);

        for (unsigned int i = 0; i < face->mNumIndices; ++i) {
            int vertexIndex = face->mIndices[i];

            if (mesh->mNormals != nullptr) {
                if (mesh->HasTextureCoords(0)) {
                    glTexCoord2f(mesh->mTextureCoords[0][vertexIndex].x, 1 - mesh->mTextureCoords[0][vertexIndex].y);
                }
                glNormal3fv(&mesh->mNormals[vertexIndex].x);
            }
            glVertex3fv(&mesh->mVertices[vertexIndex].x);
        }

        glEnd();
    }
}
