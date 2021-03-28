#include "GameActivity.h"
#include <math.h>
#include "../utils.h"

using namespace std;
USING_NS_CC;
USING_NS_MVC;

GameActivity::GameActivity()
    : _dt( 0.0f )
    , _holePos( Vec2::ZERO )
    , _gameData( nullptr )
{
}

GameActivity::~GameActivity()
{
}

void GameActivity::onCreate()
{
    Activity::onCreate();

    Director::getInstance()->pushScene( ( Scene* )( _gameView.viewRoot = _gameView.onCreate() ) );

    _gameData = GetDataProxy( GameData*, "GameData" );
    _gameData->onInit();

    _holePos = findNodeByTag( _gameView.viewRoot, HOLE )->getPosition();

    findTargetByTag<MenuItem*>( _gameView.viewRoot, BTN_INCRI )->setCallback( CC_CALLBACK_1( GameActivity::onBtnClickListener, this ) );
    findTargetByTag<MenuItem*>( _gameView.viewRoot, BTN_DECRI )->setCallback( CC_CALLBACK_1( GameActivity::onBtnClickListener, this ) );
    findTargetByTag<MenuItem*>( _gameView.viewRoot, BTN_START )->setCallback( CC_CALLBACK_1( GameActivity::onBtnClickListener, this ) );
    findTargetByTag<MenuItem*>( _gameView.viewRoot, BTN_STOP )->setCallback( CC_CALLBACK_1( GameActivity::onBtnClickListener, this ) );
    findTargetByTag<MenuItem*>( _gameView.viewRoot, BTN_RESTART )->setCallback( CC_CALLBACK_1( GameActivity::onBtnClickListener, this ) );
    findTargetByTag<MenuItem*>( _gameView.viewRoot, BTN_PAUSE )->setCallback( CC_CALLBACK_1( GameActivity::onBtnClickListener, this ) );

    updateView();

    // Adds Touch Event Listener
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [&]( Touch * touch, Event * event ) -> bool
    {
        for( auto it = _bugs.begin(); it != _bugs.end(); it++ )
        {
            if( Rect( 0, 0, ( *it )->getContentSize().width, ( *it )->getContentSize().height ).containsPoint( ( *it )->convertToNodeSpace( touch->getLocation() ) ) )
            {
                ( *it )->removeFromParent();
                it = _bugs.erase( it );
            }
        }
        return false;
    };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority( listener, 1 );

    Director::getInstance()->getScheduler()->scheduleUpdate( this, 1, false );
}

void GameActivity::onResume()
{
    Activity::onResume();
}

void GameActivity::onPause()
{
    Activity::onPause();
}

void GameActivity::onDestroy()
{
    _gameView.viewRoot = nullptr;
    Director::getInstance()->popScene();
    Activity::onDestroy();
}

const std::vector<std::pair<DataProxyID, const cocos2d::Ref*>> GameActivity::onDataProxy()
{
    return
    {
        { "GameData", new GameData }
    };
}

const std::vector<EventNameMVC> GameActivity::onEvent()
{
    return{ "Dead", "LifeChange", "DensityChange"  };
}

void GameActivity::handleEvent( const EventNameMVC &eventName, void* data /*= nullptr */ )
{
    if( eventName == "Dead" )
    {
        stop();
    }
    else
        if( eventName == "LifeChange" || "DensityChange" )
        {
            updateView();
        }
}

void GameActivity::update( float dt )
{
    if( !_gameData->_pause && _gameData->_attacking )
    {
        _dt += dt;
        if( _dt > 1.5 + CCRANDOM_MINUS1_1() - _gameData->_attackDensity * 0.01f )
        {
            auto attackSpeed = 100.0f + ( 100.0f + _gameData->_attackDensity * 0.01f ) * CCRANDOM_0_1();
            auto targetPos = findNodeByTag( _gameView.viewRoot, HOLE )->getPosition();
            auto radius = sqrt( visibleSizePos.lengthSquared() ) / 2 + 100;
            auto randomAngle = CCRANDOM_MINUS1_1() * 3.1415926;
            Vec2 startPos = Vec2( cos( randomAngle ) * radius, sin( randomAngle ) * radius ) + targetPos;

            auto bug = genBug();
            findNodeByTag( _gameView.viewRoot, LAND )->addChild( bug );
            bug->setPosition( startPos );
            bug->runAction( MoveTo::create( startPos.distance( targetPos ) / attackSpeed, targetPos ) );

            _bugs.push_back( bug );

            _dt = 0;
        }

        for( auto it = _bugs.begin(); it != _bugs.end(); it++ )
        {
            if( ( *it )->getPosition().distanceSquared( _holePos ) <= 5 * 5 )
            {
                _gameData->lossLife();

                if( _gameData->dead() ) { break; }

                ( *it )->removeFromParent();
                it = _bugs.erase( it );
            }
        }
    }
}

void GameActivity::onBtnClickListener( cocos2d::Ref* target )
{
    auto tag = static_cast< Node* >( target )->getTag();

    switch( tag )
    {
        case BTN_START:
            start();
            break;
        case BTN_RESTART:
            restart();
            break;
        case BTN_STOP:
            stop();
            break;
        case BTN_INCRI:
            _gameData->changeDensity( 3 );
            break;
        case BTN_DECRI:
            _gameData->changeDensity( -3 );
            break;
        case BTN_PAUSE:
            pause();
            break;
        default:
            break;
    }
}

cocos2d::Node* GameActivity::genBug()
{
    auto pRet = Sprite::create( "Images/ball.png" );
    pRet->setScale( 2.5 );
    return pRet;
}

void GameActivity::stop()
{
    if( _gameData->_attacking )
    {
        _gameData->_pause = false;
        _gameData->_attacking = false;
        for( auto it : _bugs )
        {
            it->removeFromParent();
        }
        _bugs.clear();
        _dt = 0.0f;
    }
    else
    {
        if( _gameData->_pause ) { _gameData->_pause = false; }
    }
}

void GameActivity::updateView()
{
    findTargetByTag<Label*>( _gameView.viewRoot, TXT_DENSITY )->setString( StringUtils::format( "Density: %.2f", _gameData->_attackDensity ) );
    findTargetByTag<Label*>( _gameView.viewRoot, TXT_LIFE )->setString( StringUtils::format( "Life: %d", _gameData->_lifeNum ) );
}

void GameActivity::start()
{
    if( !_gameData->_attacking )
    {
        _dt = 0;
        if( _gameData->dead() )
        {
            _gameData->changeLife( GameData::INIT_LIFE_NUM );
        }
        _gameData->_attacking = true;
        if( _gameData->_pause )
        {
            _gameData->_pause = false;
            for( auto it : _bugs )
            {
                it->resume();
            }
        }
    }
    else
    {
        if( _gameData->_pause )
        {
            _gameData->_pause = false;
            for( auto it : _bugs )
            {
                it->resume();
            }
        }
    }
}

void GameActivity::restart()
{
    if( !_gameData->_attacking )
    {
        start();
    }
    else
    {
        _dt = 0.0f;
        _gameData->_lifeNum = GameData::INIT_LIFE_NUM;
        _gameData->_attacking = true;
        _gameData->_pause = false;

        for( auto it : _bugs )
        {
            it->removeFromParent();
        }
        _bugs.clear();
    }
}

void GameActivity::pause()
{
    if( !_gameData->_pause )
    {
        if( _gameData->_attacking )
        {
            _gameData->_pause = true;

            for( auto it : _bugs )
            {
                it->pause();
            }
        }
    }
}
