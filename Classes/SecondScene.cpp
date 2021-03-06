#include "FirstScene.h"
#include "SecondScene.h"

USING_NS_CC;

Scene* SecondScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SecondScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SecondScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B::BLUE) )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(SecondScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Second Scene \nwith Colored Background", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);
    
    auto button = cocos2d::ui::Button::create();
    button->loadTextures("button.png", "button_r.png");
    Size layerSize = this->getContentSize();
    button->setPosition(Vec2(layerSize.width/2, layerSize.height/2));
    button->setPressedActionEnabled(true);
    button->addTouchEventListener(CC_CALLBACK_2(SecondScene::onButtonTouchEvent, this));
    button->setTitleFontSize(36.0f);
    button->setTitleText("Back");
    this->addChild(button, 10);
    
    return true;
}

void SecondScene::onButtonTouchEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType type) {
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::BEGAN:
            CCLOG("BEGAN");
            break;
        case cocos2d::ui::Widget::TouchEventType::MOVED:
            CCLOG("MOVED");
            break;
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            CCLOG("ENDED");
            Director::getInstance()->replaceScene(TransitionFlipX::create(1.0f, FirstScene::createScene()));
            break;
        case cocos2d::ui::Widget::TouchEventType::CANCELED:
            CCLOG("CANCELED");
            break;
    }
}

void SecondScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
