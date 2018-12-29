//
// Created by xaaq on 29.12.18.
//

#ifndef CZOLGI_HEALTH_BAR_H
#define CZOLGI_HEALTH_BAR_H


class HealthBar {
public:
    HealthBar(int maxHp);

    void render(float x, float y) const;

    void setHp(int hp) {this->hp = hp;}
private:
    const int maxHp;
    int hp;
};


#endif //CZOLGI_HEALTH_BAR_H
