#include "FirstScene.h"
#include "SecondScene.h"
#include "ThirdScene.h"
#include "FourthScene.h"

USING_NS_CC;

Scene* FirstScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = FirstScene::create();

    // add layer as a child to scene
    scene->addChild(layer, 0, "rootLayer");

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool FirstScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
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
                                           CC_CALLBACK_1(FirstScene::menuCloseCallback, this));
    
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
    
    auto label = LabelTTF::create("First Scene\nUsing Layout", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);
    Size layerSize = this->getContentSize();
    
    // Create the layout
    ui::Layout* layout = ui::Layout::create();
    layout->setLayoutType(ui::Layout::Type::VERTICAL);
    layout->setContentSize(Size(this->getContentSize().width-40, 300));//Button height is 80px
    layout->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    CCLOG("%f, %f", layout->getAnchorPoint().x, layout->getAnchorPoint().y);
    layout->setPosition(Vec2(layerSize.width/2, layerSize.height/2));
    layout->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
    layout->setBackGroundColor(Color3B(64, 64, 64));
    this->addChild(layout);
    
    auto button = cocos2d::ui::Button::create();
    button->loadTextures("button.png", "button_r.png");
    button->setPosition(Vec2(layout->getContentSize().width / 2.0f, layout->getContentSize().height / 2.0f));
    button->setPressedActionEnabled(true);
    button->addTouchEventListener(CC_CALLBACK_2(FirstScene::onButtonTouchEvent, this));
    button->setTitleFontSize(24.0f);
    button->setTitleText("2.Colored\nBackground");
    layout->addChild(button, 10);
    
    ui::LinearLayoutParameter* lp = ui::LinearLayoutParameter::create();
    button->setLayoutParameter(lp);
    lp->setGravity(ui::LinearLayoutParameter::LinearGravity::CENTER_HORIZONTAL);
    lp->setMargin(ui::Margin(0.0f, 10.0f, 0.0f, 10.0f));
    
    auto button2 = cocos2d::ui::Button::create();
    button2->loadTextures("button.png", "button_r.png");
    button2->setPosition(Vec2(layout->getContentSize().width / 2.0f, layout->getContentSize().height / 2.0f+100));
    button2->setPressedActionEnabled(true);
    button2->addTouchEventListener(CC_CALLBACK_2(FirstScene::onButton2TouchEvent, this));
    button2->setTitleFontSize(24.0f);
    button2->setTitleText("3.Using Mainloop");
    button2->setLayoutParameter(lp);
    layout->addChild(button2, 10);
    
    auto button3 = cocos2d::ui::Button::create();
    button3->loadTextures("button.png", "button_r.png");
    button3->setPosition(Vec2(layout->getContentSize().width / 2.0f, layout->getContentSize().height / 2.0f+100));
    button3->setPressedActionEnabled(true);
    button3->addTouchEventListener(CC_CALLBACK_2(FirstScene::onButton3TouchEvent, this));
    button3->setTitleFontSize(24.0f);
    button3->setTitleText("4.Sound Tester");
    button3->setLayoutParameter(lp);
    layout->addChild(button3, 10);
    
    return true;
}


void FirstScene::onButtonTouchEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType type) {
    CCLOG("Button1");
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::BEGAN:
            CCLOG("BEGAN");
            break;
        case cocos2d::ui::Widget::TouchEventType::MOVED:
            CCLOG("MOVED");
            break;
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            CCLOG("ENDED");
            Director::getInstance()->replaceScene(TransitionFlipX::create(1.0f, SecondScene::createScene()));
            break;
        case cocos2d::ui::Widget::TouchEventType::CANCELED:
            CCLOG("CANCELED");
            break;
    }
}
void FirstScene::onButton2TouchEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType type) {
    CCLOG("Button2");
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::BEGAN:
            CCLOG("BEGAN");
            break;
        case cocos2d::ui::Widget::TouchEventType::MOVED:
            CCLOG("MOVED");
            break;
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            CCLOG("ENDED");
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, ThirdScene::createScene()));
            break;
        case cocos2d::ui::Widget::TouchEventType::CANCELED:
            CCLOG("CANCELED");
            break;
    }
}
void FirstScene::onButton3TouchEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType type) {
    CCLOG("Button3");
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::BEGAN:
            CCLOG("BEGAN");
            break;
        case cocos2d::ui::Widget::TouchEventType::MOVED:
            CCLOG("MOVED");
            break;
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            CCLOG("ENDED");
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, FourthScene::createScene()));
            break;
        case cocos2d::ui::Widget::TouchEventType::CANCELED:
            CCLOG("CANCELED");
            break;
    }
}

void FirstScene::menuCloseCallback(Ref* pSender)
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
