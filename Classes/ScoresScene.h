/* 
 * File:   ScoresScene.h
 * Author: avenhack
 *
 * Created on October 18, 2013, 5:37 PM
 */

#ifndef SCORESSCENE_H
#define	SCORESSCENE_H

#include <cocos2d.h>
#include <vector>

using namespace cocos2d;
using namespace std;

class ScoresScene : public CCLayer {
public:
    ScoresScene();
    virtual ~ScoresScene();
    
    static CCScene* scene();
    virtual bool init();
    
    void initBg();
    void initControls();
    void initScore();
    
    void flechaIzqCallBack(CCObject* sender);
    
    CREATE_FUNC(ScoresScene);
    
private:
    vector<CCLabelTTF*>* _scoresLabel;
};

#endif	/* SCORESSCENE_H */

