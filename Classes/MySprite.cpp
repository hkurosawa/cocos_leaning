#include "MySprite.h"

USING_NS_CC;

void MySprite::onEnter() {
    Sprite::onEnter();//call superclass onEnter
    
    CCLOG("sprite onEnter");
    this->dx = 3 - ((rand()%60) / 10.0f);
    if (this->dx<0) {
        this->dx -= 1;
    } else {
        this->dx += 1;
    }
    this->dy = 3 - ((rand()%60) / 10.0f);
    if (this->dy<0) {
        this->dy -= 1;
    } else {
        this->dy += 1;
    }
    scheduleUpdate();
}

void MySprite::update(float delta) {
    Vec2 p = this->getPosition();
    CCLOG("Sprite update: %f, %f", p.x, p.y);

    if (p.x<0||p.x>this->getParent()->getContentSize().width) {
        this->dx *= -1;
    }
    
    if (p.y<0||p.y>this->getParent()->getContentSize().height) {
        this->dy *= -1;
    }
    
    this->setPosition(p.x+this->dx, p.y+this->dy);
}
