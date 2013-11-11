/* 
 * File:   GameOverScene.cpp
 * Author: avenhack
 * 
 * Created on October 8, 2013, 5:19 PM
 */

#include "GameOverScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"

GameOverScene::GameOverScene() {
}

GameOverScene::~GameOverScene() {
}

CCScene* GameOverScene::scene() {
     // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameOverScene *layer = GameOverScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool GameOverScene::init() {
    if (!CCLayer::init()) {
        return false;
    }
    
    initBg();
    initControls();
    initScore();
    
    return true;
}

void GameOverScene::initBg() {
     CCSprite *bg = CCSprite::create("fondo-game-over2.png");
     bg->setAnchorPoint(CCPointZero);
     bg->setPosition(ccp(0 , 0));
     
     this->addChild(bg,Z_BACKGROUND);
 }

void GameOverScene::initScore() {
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    _score = CCLabelTTF::create("0","Felt",52);
    this->_score->setColor(ccc3(255,255,255));
    this->_score->setAnchorPoint(CCPointZero);
    this->_score->setPosition(ccp(0,winSize.height - this->_score->getContentSize().height));

    this->addChild(this->_score, Z_MIDDLEGROUND);
}

void GameOverScene::initControls() {
    //flecha izquierda
    CCMenuItemImage *izq = CCMenuItemImage::create("flecha-izquierda.png","flecha-izquierda-pressed.png",this, menu_selector(GameOverScene::flechaIzqCallBack));
    izq->setAnchorPoint(CCPointZero);
    izq->setPosition(ccp(5, 10));
    
       
    //Creo el menu
    CCMenu * menu = CCMenu::create(izq, NULL);
    menu->setPosition(CCPointZero);
    
    this->addChild(menu,Z_MIDDLEGROUND);
    
 }

void GameOverScene::flechaIzqCallBack(CCObject* sender) {
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,  MainMenuScene::scene()));    
}
