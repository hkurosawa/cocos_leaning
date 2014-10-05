#ifndef __THIRDSCENE_SCENE_H__
#define __THIRDSCENE_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class ThirdScene : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(ThirdScene);
    
    void onButtonTouchEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    void update(float delta);

private:
    int counter;
};

#endif // __THIRDSCENE_SCENE_H__
