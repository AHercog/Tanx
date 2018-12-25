//
// Created by silvair on 25.12.18.
//

#ifndef CZOLGI_ENEMY_LIKE_H
#define CZOLGI_ENEMY_LIKE_H


class EnemyLike {
public:
    virtual void run(float delta, const std::list<Wall> &wallList) = 0;

    virtual void render() const = 0;
};


#endif //CZOLGI_ENEMY_LIKE_H
