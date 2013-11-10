/* 
 * File:   GameScene.h
 * Author: randy
 *
 * Created on October 6, 2013, 3:34 PM
 */

#ifndef GAMESCENE_H
#define	GAMESCENE_H

#include <cocos2d.h>
#include <SimpleAudioEngine.h>
#include "AppMacros.h"

using namespace cocos2d; 
using namespace CocosDenshion;
using namespace std;


class GameScene : public CCLayer {
public:
    GameScene();
    virtual ~GameScene();
    
    static CCScene* scene();
    virtual bool init();
    
    void initSnake(); 
    void initBg();
    void initControls();
    void initScore();
    void initSonds();
    
    int getRandomNumber(int min, int max);
    void placeFruit();
    void changeHead();
    void checkCollitions();
    void checkGameOver();
    void checkFruit();
        
    void updateGame(float dt);
    void updateSnake();
    
    void flechaIzqCallBack(CCObject *sender);
    void flechaDerCallBack(CCObject *sender);
    void pauseCallBack(CCObject *sender);
    
    CREATE_FUNC(GameScene);
    
private:
    bool snakeContainPos(CCPoint pos);
    bool collisionsSpriteWithSprite(CCSprite* sprite1,CCSprite* sprite2);
    bool spriteContainPos(CCSprite* sprite, CCPoint pos);
    void eat();
    
    CCSprite *_leftArrow;
    CCSprite *_rightArrow;
    CCSprite *_fruit;
    CCArray  *_snake;    
    
    bool _gameOver;
    bool _bgMusic;
    bool _headIsChanged;
    Direction _dir;
    int       _cantParts;
    int       _score;  
    CCSize    _winSize;   
    float     _tick;
    float     _tickTime;
    CCLabelTTF *_scoreLabel;
    
};

#endif	/* GAMESCENE_H */

