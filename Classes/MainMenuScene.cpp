/* 
 * File:   MainMenuScene.cpp
 * Author: avenhack
 * 
 * Created on October 5, 2013, 5:31 PM
 */

#include "MainMenuScene.h"
#include "GameScene.h"
#include "ScoresScene.h"

CCScene* MainMenuScene::scene() {
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MainMenuScene *layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool MainMenuScene::init() {
    if ( !CCLayer::init() ) {
        return false;
    }
    
    initBG();
    initMenus();
    initSonds();
    
    return true;
    
}


void MainMenuScene::initBG() {
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *bg = CCSprite::create("fondo2.png");
    bg->setAnchorPoint(CCPointZero);
    bg->setPosition(ccp(0 , 0));
    
    
    CCSprite *stone = CCSprite::create("stone.png");
    stone->setPosition(ccp(winSize.width * 0.4 , winSize.height * 0.8));
    
    CCSprite *head = CCSprite::create("head.png");
    head->setPosition(ccp(winSize.width * 0.63 , winSize.height * 0.65));

    
    
    this->addChild(stone,1);
    this->addChild(head,1);
    this->addChild(bg, 0);
}

void MainMenuScene::initSonds() {
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.1f);
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
    if (CCUserDefault::sharedUserDefault()->getBoolForKey(ENABLE_MUSIC)) {
        SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("music.ogg");
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music.ogg", true);
    }
}
void MainMenuScene::initMenus() {
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize(); 
    
    //Menu play
    CCMenuItemImage *play = CCMenuItemImage::create("play.png","play-pressed.png",this, menu_selector(MainMenuScene::playCallBack));
    play->setPosition(ccp(winSize.width/2 , winSize.height * 0.45));
    
    //Menu scores
    CCMenuItemImage *scores = CCMenuItemImage::create("highscores.png","highscores-pressed.png",this, menu_selector(MainMenuScene::scoresCallBack));
    scores->setPosition(ccp(winSize.width/2 , winSize.height * 0.30));
    
    
    //Menu exit
    CCMenuItemImage *exit = CCMenuItemImage::create("exit.png","exit-pressed.png",this, menu_selector(MainMenuScene::exitCallBack));
    exit->setPosition(ccp(winSize.width/2 , winSize.height * 0.13));
        
    //Habilitar y deshabilitar el sonido
    setBgMusic(true);
    CCMenuItemImage *on = CCMenuItemImage::create("bocina.png","bocina-pressed.png");
    CCMenuItemImage *off = CCMenuItemImage::create("no-bocina.png","no-bocina-pressed.png");
    
    CCMenuItemToggle *sound = CCMenuItemToggle::createWithTarget(this, menu_selector(MainMenuScene::manageSondBGCallBack),on, off, NULL);
    sound->setAnchorPoint(CCPointZero);
    sound->setPosition(ccp(sound->getContentSize().width, sound->getContentSize().height));
    
    if (!CCUserDefault::sharedUserDefault()->getBoolForKey(ENABLE_MUSIC))
        sound->setSelectedIndex(1);
    
        //Creo el menu
    CCMenu * menu = CCMenu::create(play, scores, exit, sound, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
    
    
}

void MainMenuScene::playCallBack(CCObject* sender) {

    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,  GameScene::scene()));
}
void MainMenuScene::scoresCallBack(CCObject* sender){
   SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
   SimpleAudioEngine::sharedEngine()->stopAllEffects();
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,  ScoresScene::scene()));
}

void MainMenuScene::exitCallBack(CCObject* sender) {
   CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void MainMenuScene::manageSondBGCallBack(CCObject* sender) {
    
    if (CCUserDefault::sharedUserDefault()->getBoolForKey(ENABLE_MUSIC)) {
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
        CCUserDefault::sharedUserDefault()->setBoolForKey(ENABLE_MUSIC,false);
        CCUserDefault::sharedUserDefault()->flush();
    } else {
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music.ogg", true);
        CCUserDefault::sharedUserDefault()->setBoolForKey(ENABLE_MUSIC,true);
        CCUserDefault::sharedUserDefault()->flush();
    }    
}
