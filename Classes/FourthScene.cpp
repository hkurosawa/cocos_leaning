#include "FirstScene.h"
#include "FourthScene.h"
#include "MySprite.h"

USING_NS_CC;

Scene* FourthScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = FourthScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool FourthScene::init()
{
    CCLOG("init scene");
    
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B::GRAY) )
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
                                           CC_CALLBACK_1(FourthScene::menuCloseCallback, this));
    
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
    
    auto label = LabelTTF::create("4th Scene \nSound Tester", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 4);
    
    auto label2 = LabelTTF::create("placeholder", "Arial", 18);
    
    // position the label on the center of the screen
    label2->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height*2));
    
    // add the label as a child to this layer
    this->addChild(label2, 3, "aLabel");
    
    Size layerSize = this->getContentSize();

    ui::Layout* layout = ui::Layout::create();
    layout->setLayoutType(ui::Layout::Type::VERTICAL);
    layout->setContentSize(Size(this->getContentSize().width-40, 300));//Button height is 80px
    layout->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    layout->setPosition(Vec2(layerSize.width/2, layerSize.height/2));
    layout->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
    layout->setBackGroundColor(Color3B(64, 64, 64));
    this->addChild(layout, 0, "layout");
    
    ui::LinearLayoutParameter* lp = ui::LinearLayoutParameter::create();
    lp->setGravity(ui::LinearLayoutParameter::LinearGravity::CENTER_HORIZONTAL);
    lp->setMargin(ui::Margin(0.0f, 10.0f, 0.0f, 10.0f));
    
    auto button_play = cocos2d::ui::Button::create();
    button_play->setLayoutParameter(lp);

    button_play->loadTextures("button.png", "button_r.png");
    //Size layerSize = this->getContentSize();
    //button->setPosition(Vec2(layerSize.width/2, layerSize.height/2));
    button_play->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    button_play->setPosition(Vec2(layout->getContentSize().width / 2.0f, layout->getContentSize().height / 2.0f));
    button_play->setPressedActionEnabled(true);
    button_play->addTouchEventListener(CC_CALLBACK_2(FourthScene::onPlayButtonTouchEvent, this));
    button_play->setTitleFontSize(36.0f);
    button_play->setTitleText("Play BGM");
    layout->addChild(button_play, 1, "playButton");
    
    auto button = cocos2d::ui::Button::create();
    button->setLayoutParameter(lp);
    button->loadTextures("button.png", "button_r.png");
    //Size layerSize = this->getContentSize();
    //button->setPosition(Vec2(layerSize.width/2, layerSize.height/2));
    button->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    button->setPosition(Vec2(layout->getContentSize().width / 2.0f, layout->getContentSize().height / 2.0f));
    button->setPressedActionEnabled(true);
    button->addTouchEventListener(CC_CALLBACK_2(FourthScene::onButtonTouchEvent, this));
    button->setTitleFontSize(36.0f);
    button->setTitleText("Back");
    layout->addChild(button, 1);
    
    // activate mainloop void update(float delta) method
    this->scheduleUpdate();
    this->counter = 0;
    
    // adding sprite
    //auto sprite = MySprite::create();
    //sprite->setTexture("sprite_blue.png");
    //位置を設定
    //Size s = this->getContentSize();
    //sprite->setPosition(Vec2(s.width/2,s.height/2));
    //画面に追加をしています。
    //sprite->scheduleUpdate();
    //this->addChild(sprite, 2, "aSprite"); //bigger numbers = front
    
    // getting touch event on Layer
    this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(FourthScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(FourthScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(FourthScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(FourthScene::onTouchCancelled, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto drawNode = DrawNode::create();
    this->addChild(drawNode, 3, "drawNode");
    
    this->isPlaying = false;
    //CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("background-music-aac.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("pew-pew-lei.wav");
    return true;
}

void FourthScene::onPlayButtonTouchEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType type) {
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::BEGAN:
            CCLOG("BEGAN");
            if (this->isPlaying) {
                this->stopBgm();
            } else {
                this->playBgm();
            }
            break;
        case cocos2d::ui::Widget::TouchEventType::MOVED:
            CCLOG("MOVED");
            break;
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            CCLOG("ENDED");
            break;
        case cocos2d::ui::Widget::TouchEventType::CANCELED:
            CCLOG("CANCELED");
            break;
    }
}
    
void FourthScene::onButtonTouchEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType type) {
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::BEGAN:
            CCLOG("BEGAN");
            break;
        case cocos2d::ui::Widget::TouchEventType::MOVED:
            CCLOG("MOVED");
            break;
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            CCLOG("ENDED");
            //this->getChildByName("aSprite")->removeFromParent();
            CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
            CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("");
            Director::getInstance()->replaceScene(TransitionFlipX::create(1.0f, FirstScene::createScene()));
            break;
        case cocos2d::ui::Widget::TouchEventType::CANCELED:
            CCLOG("CANCELED");
            break;
    }
}

void FourthScene::update(float delta) {
    auto label = dynamic_cast<LabelTTF*>(this->getChildByName("aLabel"));
    char s[2];
    sprintf(s, "%02d", counter++%60);
    std::string ss(s);
    label->setString("update/delta: " + std::to_string(delta) + "\nframe: " + ss);
}

bool FourthScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    auto pos = touch->getLocation();
    CCLOG("onTouchBegan: %f, %f", pos.x, pos.y);
    float pitch = pos.y / 320.0f;
    float pan = (pos.x - 480.0f) / 480.0f; //-1.0f to 1.0f
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pew-pew-lei.wav", 0, pitch, pan);
    return true;
}

void FourthScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
    auto pos = touch->getLocation();
    CCLOG("onTouchMoved: %f, %f", pos.x, pos.y);
}

void FourthScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    auto pos = touch->getLocation();
    CCLOG("onTouchEnded: %f, %f", pos.x, pos.y);
}

void FourthScene::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event) {
    auto pos = touch->getLocation();
    CCLOG("onTouchCancelled: %f, %f", pos.x, pos.y);
}

void FourthScene::draw(cocos2d::Renderer *renderer, const Mat4 &transform, uint32_t flags) {
    //CCLOG("draw");
    //DrawPrimitives::drawLine(Vec2(0.0f, 0.0f), Vec2(100.0f, 100.0f));
    /*
    Vector<Vec2> v = Vector<Vec2>(5);
    v.pushBack(Vec2(0.0f, 0.0f));
    v.pushBack(Vec2(100.0f, 100.0f));
    v.pushBack(Vec2(200.0f, 120.0f));
    v.pushBack(Vec2(210.0f, 60.0f));
    v.pushBack(Vec2(300.0f, 320.0f));
     */
    //Vec2 v[] = { Vec2(30,130), Vec2(30,230), Vec2(50,200) };
    //DrawPrimitives::drawPoly(v, 3, false);
    //DrawNode *node = dynamic_cast<DrawNode*>(this->getChildByName("drawNode"));
    //node->drawPolygon(v, 3, Color4F(1.0f, 0.0f, 0.0f, 1.0f), 2.0f, Color4F(0.0f, 1.0f, 0.0f, 1.0f));
}


void FourthScene::menuCloseCallback(Ref* pSender)
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

void FourthScene::playBgm()
{
    CCLOG("playBgm");
    auto layout = dynamic_cast<cocos2d::ui::Layout*>(this->getChildByName("layout"));
    auto button = dynamic_cast<cocos2d::ui::Button*>(layout->getChildByName("playButton"));
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("background-music-aac.wav", true);//maybe needs to implement pre-load
    button->setTitleText("Stop BGM");
    this->isPlaying = true;
}

void FourthScene::stopBgm()
{
    CCLOG("stopBgm");
    auto layout = dynamic_cast<cocos2d::ui::Layout*>(this->getChildByName("layout"));
    auto button = dynamic_cast<cocos2d::ui::Button*>(layout->getChildByName("playButton"));
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    button->setTitleText("Play BGM");
    this->isPlaying = false;
}
