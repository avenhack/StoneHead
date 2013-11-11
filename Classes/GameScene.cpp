/* 
 * File:   GameScene.cpp
 * Author: avenhack
 * 
 * Created on October 6, 2013, 3:34 PM
 */

#include <unistd.h>

#include "GameScene.h"
#include "GameOverScene.h"

GameScene::GameScene() : 
        _leftArrow(NULL),
        _rightArrow(NULL),
        _gameOver(false),
        _headIsChanged(false),
        _scoreLabel(NULL)

{
    _cantParts = 3; //La cabeza y dos colas
    _score = 0;
    _winSize = CCDirector::sharedDirector()->getWinSize();
    _snake = new CCArray();
    _dir = UP;
    _tick = TICK_INITIAL;

}


GameScene::~GameScene() {
}

CCScene* GameScene::scene() {
    CCScene *scene = CCScene::create();
    GameScene *layer = GameScene::create();
    scene->addChild(layer);
    
    return scene;    
}

 void GameScene::initSnake() {
     CCArray *headAnimationFrames = new CCArray(); 
     
     headAnimationFrames->addObject(CCSpriteFrame::create("cara-arriba.png",CCRectMake(0,0,40,40)));
     headAnimationFrames->addObject(CCSpriteFrame::create("cara-derecha.png",CCRectMake(0,0,40,40)));
     headAnimationFrames->addObject(CCSpriteFrame::create("cara-abajo.png",CCRectMake(0,0,40,40)));
     headAnimationFrames->addObject(CCSpriteFrame::create("cara-izquierda.png",CCRectMake(0,0,40,40)));
     
     CCAnimation * cara = CCAnimation::createWithSpriteFrames(headAnimationFrames); 
     
     CCAnimationCache::sharedAnimationCache()->addAnimation(cara,"CaraAnimation");
     
     CCSprite *head = CCSprite::createWithSpriteFrame(dynamic_cast<CCSpriteFrame*>(headAnimationFrames->objectAtIndex(_dir)));
     head->setAnchorPoint(CCPointZero);
     head->setPosition(ccp(_winSize.width/2, _winSize.height/2));
     
     //Free array memory
     //CC_SAFE_RELEASE_NULL(headAnimationFrames);
     
     CCSprite *body = CCSprite::create("hielo.png");
     body->setAnchorPoint(CCPointZero);
     body->setPosition(ccp(head->getPosition().x , head->getPosition().y - head->getContentSize().height));
     
     CCSprite *body2 = CCSprite::create("hielo.png");
     body2->setAnchorPoint(CCPointZero);
     body2->setPosition(ccp(head->getPosition().x, body->getPosition().y - body->getContentSize().height));
     
     _snake->addObject(head);  
     _snake->addObject(body);
     _snake->addObject(body2);
     _snake->retain();
     
     this->addChild(head,Z_MIDDLEGROUND,HEAD_TAG);
     this->addChild(body,Z_MIDDLEGROUND);
     this->addChild(body2,Z_MIDDLEGROUND);             
 }

 void GameScene::initBg() {
     CCSprite *bg = CCSprite::create("fondo-game2.png");
     bg->setAnchorPoint(CCPointZero);
     bg->setPosition(ccp(0 , 0));
     
//     CCSprite *borde = CCSprite::create("borde.png");
//     borde->setAnchorPoint(CCPointZero);
//     borde->setPosition(ccp(0 , 0));
     
     this->addChild(bg,Z_BACKGROUND);
//     this->addChild(borde,Z_MIDDLEGROUND);
 }
 
 void GameScene::initControls() {
    //flecha izquierda
    CCMenuItemImage *izq = CCMenuItemImage::create("flecha-izquierda.png","flecha-izquierda-pressed.png",this, menu_selector(GameScene::flechaIzqCallBack));
    izq->setAnchorPoint(CCPointZero);
    izq->setPosition(ccp(5, 10));
    
    //flecha  derecha
    CCMenuItemImage *der = CCMenuItemImage::create("flecha-derecha.png","flecha-derecha-pressed.png",this, menu_selector(GameScene::flechaDerCallBack));
    der->setAnchorPoint(CCPointZero);
    der->setPosition(ccp(_winSize.width - der->getContentSize().width - 5 , 10));
    
    //Pause y Continue
    CCMenuItemImage *pause = CCMenuItemImage::create("pause.png","pause-pressed.png");
    CCMenuItemImage *play = CCMenuItemImage::create("play2.png","play2-pressed.png");
    
    CCMenuItemToggle *control = CCMenuItemToggle::createWithTarget(this, menu_selector(GameScene::pauseCallBack),pause, play, NULL);
    control->setAnchorPoint(CCPointZero);
    control->setPosition(ccp(0, _winSize.height - pause->getContentSize().height));
    
    //Creo el menu
    CCMenu * menu = CCMenu::create(izq, der, control, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu,Z_FOREGROUND);
    
 }
 
 void GameScene::initScore() {
     _scoreLabel = CCLabelTTF::create("0","Felt",42);
             
     _scoreLabel->setColor(ccc3(255,255,255));
     _scoreLabel->setAnchorPoint(CCPointZero);
     _scoreLabel->setPosition(ccp(_winSize.width / 2 - _scoreLabel->getContentSize().width/2,0));

    this->addChild(_scoreLabel, Z_FOREGROUND);
 }

 void GameScene::initSonds() {
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.1f);
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
    
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("music.ogg");
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music.ogg", true);
}
 
bool GameScene::init() {
    if (!CCLayer::init()) {
        return false;
    }
    
    initBg();
    initSnake();
    initControls();
    initScore();
    if(_bgMusic) 
        initSonds();
    
    placeFruit();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
    this->schedule(schedule_selector(GameScene::updateGame));
    
    return true;
    
}

void GameScene::changeHead() {
    CCSprite* head = dynamic_cast<CCSprite*>(_snake->objectAtIndex(0));
    head->setDisplayFrameWithAnimationName("CaraAnimation",_dir);    
} 


void GameScene::flechaIzqCallBack(CCObject *sender) {
    stopAllActions();
       
    switch(_dir) {
        case UP :
            _dir = LEFT;
            break;
        case DOWN :
            _dir = RIGHT;             
            break;
        case RIGHT :
            _dir = UP;
            break;
        case LEFT :
            _dir = DOWN;
            break;         
    }
    changeHead();
    
}
void GameScene::flechaDerCallBack(CCObject *sender) {
    stopAllActions();
    
    switch(_dir) {
        case UP :
            _dir = RIGHT;
            break;
        case DOWN :
            _dir = LEFT;
            break;
        case RIGHT :
            _dir = DOWN;
            break;
        case LEFT :
            _dir = UP;
            break;         
    }   
    changeHead();
    
}

void GameScene::pauseCallBack(CCObject *sender) {
    CCMenuItemToggle* menu = dynamic_cast<CCMenuItemToggle*>(sender); 
    
    if (menu && (menu->getSelectedIndex() == 1)) { 
        CCDirector::sharedDirector()->pause();
        SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    }
    else {
        CCDirector::sharedDirector()->resume();
        SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    }
}


void GameScene::updateGame(float dt) {
    checkGameOver();
    
    _tickTime += dt;
    
    if (_tickTime > _tick) {
        _tickTime -= _tick;
        updateSnake();
    }
    checkCollitions();
    
}

int GameScene::getRandomNumber(int min, int max) {
    return (rand() % (max - min)) + min;
}

void GameScene::placeFruit() {
    CCPoint pos;
    
    do {
        pos = CCPoint(getRandomNumber(0,_winSize.width - FRUIT_SIZE), getRandomNumber(BORDER_HEIGHT,_winSize.height - FRUIT_SIZE));
    } while(snakeContainPos(pos));
    
    CCSprite * fruit;
    int type = getRandomNumber(0,2);
    
    switch (type) {
        case 0 :
            fruit = CCSprite::create("manzana.png");
            break;
        case 1 :
            fruit = CCSprite::create("rabano.png");
            break;
        case 2 :
            fruit = CCSprite::create("zanahoria.png");
            break;
        default:
            fruit = CCSprite::create("manzana.png");
    }
    
    
    fruit->setAnchorPoint(CCPointZero);
    fruit->setPosition(pos);
    _fruit = fruit;
    this->addChild(_fruit,Z_MIDDLEGROUND,FRUIT_TAG);
    
}

bool GameScene::snakeContainPos(CCPoint pos) {
    int len = _snake->count();
    CCSprite *part;
    
    for (int i=0; i<len; ++i) {
        part = dynamic_cast<CCSprite*>(_snake->objectAtIndex(i));
        if (part->boundingBox().intersectsRect(CCRectMake(pos.x,pos.y,32,32))) 
            return true;
    }
    
    return false;
}
bool GameScene::spriteContainPos(CCSprite* sprite, CCPoint pos) {
      if (sprite->boundingBox().containsPoint(pos)) 
            return true;
      return false;
}


void GameScene::checkFruit() {
    
}

void GameScene::checkGameOver() {
    if (_gameOver) {
        this->unschedule(schedule_selector(GameScene::updateGame));
	stopAllActions();
	
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->stopAllEffects();
	SimpleAudioEngine::sharedEngine()->playEffect("uh.wav");
	
        //Creo la scene de gameOver y le paso el score
        CCScene *scene = GameOverScene::scene();
	char scoreLabel[128];
        char sc[20];
	sprintf(scoreLabel, "Score: %d", _score);
        sprintf(sc, "%d", _score);
        
        //Si el score rompio record, entonces lo guardo
        for (int i=0; i<5; ++i) {
                CCString* key = CCString::createWithFormat("score%i",i);
                string score = CCUserDefault::sharedUserDefault()->getStringForKey(key->getCString());
                int scoreOld;
                
                //Si hay uno de los 5 score vacio, entonces en ese pongo el nuevo score y rompo
                if (score.compare(string("")) == 0) {
                        CCUserDefault::sharedUserDefault()->setStringForKey(key->getCString(),string(sc));
                    CCUserDefault::sharedUserDefault()->flush();
                    break;
                } 
                        
                //Si esta lleno, pero este es mayor, ACTUALIZO
                sscanf(score.c_str(),"%d",&scoreOld);
                if (_score > scoreOld) {
                    for (int j=4; j>i; --j) { 
                        CCString* key2 = CCString::createWithFormat("score%i",j);
                        CCString* keyNew = CCString::createWithFormat("score%i",j-1);
                        string temp = CCUserDefault::sharedUserDefault()->getStringForKey(keyNew->getCString());
                        CCUserDefault::sharedUserDefault()->setStringForKey(key2->getCString(),temp);
                    }
                    CCUserDefault::sharedUserDefault()->setStringForKey(key->getCString(),string(sc));
                    CCUserDefault::sharedUserDefault()->flush();
                    break;
                }
        }
	
        dynamic_cast<GameOverScene*>(scene->getChildren()->objectAtIndex(0))->getScore()->setString(scoreLabel);
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,scene));
	
    }
}

void GameScene::checkCollitions() {
    CCSprite* head = dynamic_cast<CCSprite*>(_snake->objectAtIndex(0));
    CCPoint pos = head->getPosition();
    CCSprite *part;
    
    //chequeo si topa con algun borde
    if (pos.x <= 0 || pos.x >= _winSize.width || pos.y <= BORDER_HEIGHT || pos.y >= _winSize.height) {
        _gameOver = true;
        return;
    }
    
    //chequeo si se come el mismo
    int len = _snake->count();
    for (int i=1; i<len; ++i) {
        part = dynamic_cast<CCSprite*>(_snake->objectAtIndex(i));
        if (head->getPosition().equals(part->getPosition())) {
            _gameOver = true;
            return;
        }
    }
    
    //chequeo si topa con una fruta
    if ((_fruit != NULL) &&  collisionsSpriteWithSprite(head,_fruit)) {
        eat();
        placeFruit();
    }
    
}

void GameScene::eat() {
    //Anhado la parte en la posicion de la ultima que habia 
     CCSprite* last = dynamic_cast<CCSprite*>(_snake->lastObject()); 
     CCSprite *body = CCSprite::create("hielo.png");
     
     
     body->setAnchorPoint(CCPointZero);
     body->setPosition(last->getPosition());
     _snake->addObject(body);
     this->addChild(body, Z_MIDDLEGROUND); 
     
     //Quito la fruta
     this->removeChildByTag(FRUIT_TAG);
     _fruit = NULL;
     
     //Aumento el score
     _score += SCORE_INCREMENT;
     char scoreLabel[128];
     sprintf(scoreLabel,"%d",_score);
     _scoreLabel->setString(scoreLabel);
     
     //Si el score es multiplo de 100 aumento velocidad
     if (!(_score % 100)) 
         _tick -= TICK_DECREMENT;
     
     //Hago sonido
     SimpleAudioEngine::sharedEngine()->playEffect("score.wav");
     
}

bool GameScene::collisionsSpriteWithSprite(CCSprite* sprite1,CCSprite* sprite2) {
	CCPoint position1 = sprite1->getPosition();
	CCSize size1 = sprite1->getContentSize();
	CCRect spriteRect1 = CCRectMake(position1.x, position1.y, size1.width,
			size1.height);

	CCPoint position2 = sprite2->getPosition();
	CCSize size2 = sprite2->getContentSize();
	CCRect spriteRect2 = CCRectMake(position2.x, position2.y, size2.width,
			size2.height);
	return spriteRect1.intersectsRect(spriteRect2);
}

void GameScene::updateSnake() {
    CCSprite *before, *current;
    CCPoint next;
    int len = _snake->count(); 
    
    //Muevo las partes de atras para alante
    for (unsigned int i=len-1; i>0; --i) {
        before = dynamic_cast<CCSprite*>(_snake->objectAtIndex(i-1));
        current = dynamic_cast<CCSprite*>(_snake->objectAtIndex(i));
        current->runAction(CCMoveTo::create(0,before->getPosition()));                
    }
    
        //Luego muevo la cabeza en la direccion que este apuntando
        current = dynamic_cast<CCSprite*>(_snake->objectAtIndex(0)); 
        
        switch (_dir) {
            case UP :            
                next = CCPoint(current->getPosition().x, current->getPosition().y + current->getContentSize().height);
                current->runAction(CCMoveTo::create(0,next));
                break;
            case DOWN :                
                next = CCPoint(current->getPosition().x, current->getPosition().y - current->getContentSize().height);
                current->runAction(CCMoveTo::create(0,next));
                break;
            case LEFT :                
                next = CCPoint(current->getPosition().x - current->getContentSize().width, current->getPosition().y);
                current->runAction(CCMoveTo::create(0,next));
                break;
            case RIGHT :                
                next = CCPoint(current->getPosition().x + current->getContentSize().width, current->getPosition().y);
                current->runAction(CCMoveTo::create(0,next));
                break;
        }
}
