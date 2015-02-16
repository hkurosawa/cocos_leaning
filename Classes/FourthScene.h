#ifndef __FOURTHSCENE_SCENE_H__
#define __FOURTHSCENE_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"  
// http://www.cocos2d-x.org/wiki/Chapter_6_-_How_to_Play_Music_and_Sound_Effect

class FourthScene : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(FourthScene);
    
    void onPlayButtonTouchEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    void onButtonTouchEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    void update(float delta);

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);

    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
    
private:
    int counter;
    bool isPlaying;
    void playBgm();
    void stopBgm();
};

#endif // __FOURTHSCENE_SCENE_H__
