#ifndef __MYSPRITE_H__
#define __MYSPRITE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class MySprite : public cocos2d::Sprite
{
public:
    CREATE_FUNC(MySprite);
    virtual void onEnter();
    virtual void update(float delta) override;
    
private:
    float dx, dy;

};

#endif // __MYSPRITE_H__
