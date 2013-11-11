/* 
 * File:   GameOverScene.h
 * Author: avenhack
 *
 * Created on October 8, 2013, 5:19 PM
 */

#ifndef GAMEOVERSCENE_H
#define	GAMEOVERSCENE_H

#include <cocos2d.h>

using namespace cocos2d;

class GameOverScene : public CCLayer{
public:
    GameOverScene();
    virtual ~GameOverScene();

    static CCScene* scene();
    virtual bool init();
    
    void initBg();
    void initControls();
    void initScore();
    
    void flechaIzqCallBack(CCObject* sender);
    
    CC_SYNTHESIZE(CCLabelTTF*, _score, Score);
    CREATE_FUNC(GameOverScene);
private:

};

#endif	/* GAMEOVERSCENE_H */

