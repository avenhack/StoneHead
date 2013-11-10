/* 
 * File:   ScoresScene.cpp
 * Author: randy
 * 
 * Created on October 18, 2013, 5:37 PM
 */

#include "ScoresScene.h"
#include "AppMacros.h"
#include "MainMenuScene.h"

ScoresScene::ScoresScene() 
{
    _scoresLabel = new vector<CCLabelTTF*>(5);
}

ScoresScene::~ScoresScene() {
}

bool ScoresScene::init() {
    if (!CCLayer::init()) {
        return false;
    }
    
    initBg();
    initControls();
    initScore();
    
    return true;
}

CCScene* ScoresScene::scene() {
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    ScoresScene *layer = ScoresScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void ScoresScene::initBg() {
     CCSprite *bg = CCSprite::create("fondo-scores2.png");
     bg->setAnchorPoint(CCPointZero);
     bg->setPosition(ccp(0 , 0));
     
     this->addChild(bg,Z_BACKGROUND);
 }

void ScoresScene::initScore() {
    //CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    for (int i=0; i<5; ++i) {
        CCString* key = CCString::createWithFormat("score%i",i);
        string score = CCUserDefault::sharedUserDefault()->getStringForKey(key->getCString());
        
        if (score.compare(string("")) == 0) 
            score = "-";
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        _scoresLabel->at(i) = CCLabelTTF::create(score.c_str(),"Felt",24);
        _scoresLabel->at(i)->setColor(ccc3(255,255,255));
        _scoresLabel->at(i)->setAnchorPoint(CCPointZero);
        _scoresLabel->at(i)->setPosition(ccp(winSize.width / 2 - _scoresLabel->at(i)->getContentSize().width / 2 ,winSize.height - 90 - _scoresLabel->at(i)->getContentSize().height * i));
        this->addChild(_scoresLabel->at(i), Z_MIDDLEGROUND);
    }
}

void ScoresScene::initControls() {
    //flecha izquierda
    CCMenuItemImage *izq = CCMenuItemImage::create("flecha-izquierda.png","flecha-izquierda-pressed.png",this, menu_selector(ScoresScene::flechaIzqCallBack));
    izq->setAnchorPoint(CCPointZero);
    izq->setPosition(ccp(5, 10));
    
       
    //Creo el menu
    CCMenu * menu = CCMenu::create(izq, NULL);
    menu->setPosition(CCPointZero);
    
    this->addChild(menu,Z_MIDDLEGROUND);
    
 }

void ScoresScene::flechaIzqCallBack(CCObject* sender) {
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,  MainMenuScene::scene()));    
}