//
// Created by xaaq on 29.12.18.
//

#ifndef CZOLGI_MODEL_HANDLER_H
#define CZOLGI_MODEL_HANDLER_H


#include <string>
#include <assimp/scene.h>

class ModelHandler {
public:
    explicit ModelHandler(char *filePath);

    void drawModel(int meshIndex) const;
private:
    const aiScene *model;
};


#endif //CZOLGI_MODEL_HANDLER_H
