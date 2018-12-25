//
// Created by silvair on 24.12.18.
//

#ifndef CZOLGI_ENVIRONMENT_H
#define CZOLGI_ENVIRONMENT_H


class Environment {
public:
    Environment();

    void run(float delta);

    void render();
private:
    void drawGround();
};


#endif //CZOLGI_ENVIRONMENT_H
