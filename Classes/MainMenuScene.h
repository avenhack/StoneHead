/* 
 * File:   MainMenuScene.h
 * Author: avenhack
 *
 * Created on October 5, 2013, 5:31 PM
 */

#ifndef MAINMENUSCENE_H
#define	MAINMENUSCENE_H

#include <cocos2d.h>
#include <SimpleAudioEngine.h>

using namespace cocos2d;
using namespace CocosDenshion; 

class MainMenuScene : public CCLayer {
public:
      
    static CCScene* scene();
    virtual bool init();
    
    void initBG();
    void initSonds();
    void initMenus(); 
    
    void playCallBack(CCObject* sender);
    void scoresCallBack(CCObject* sender);
    void exitCallBack(CCObject* sender);
    
    void manageSondBGCallBack(CCObject* sender);
    
       
    CREATE_FUNC(MainMenuScene);
    CC_SYNTHESIZE(bool, _bgMusic, BgMusic);
    
private:

};

#endif	/* MAINMENUSCENE_H */

