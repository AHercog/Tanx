//
// Created by silvair on 25.12.18.
//

#ifndef CZOLGI_ENEMY_LIKE_H
#define CZOLGI_ENEMY_LIKE_H

class EnemyLike : public Collidable {
public:
    virtual void run(float delta, const std::list<Collidable *> &collidableList) = 0;

    virtual void render() const = 0;

    virtual void getHit(int damage) = 0;

    virtual bool shouldBeDestroyed() = 0;
};

#endif //CZOLGI_ENEMY_LIKE_H
