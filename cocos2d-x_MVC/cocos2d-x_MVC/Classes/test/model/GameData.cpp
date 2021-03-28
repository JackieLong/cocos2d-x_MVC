#include "GameData.h"

GameData::GameData()
    : _lifeNum( 0 )
    , _attackDensity( 0.0 )
    , _attacking( false )
    , _pause( false )
{

}

GameData::~GameData()
{

}

void GameData::onInit()
{
    _lifeNum       = INIT_LIFE_NUM;
    _attackDensity = 0.0;
    _attacking     = true;
    _pause = false;
}

void GameData::changeDensity( const float &change )
{
    _attackDensity += change;
    if( _attackDensity < 0 )
    {
        _attackDensity = 0.0f;
    }
    dispatchEvent( "DensityChange" );
}

void GameData::changeLife( const int &change )
{
    _lifeNum += change;
    dispatchEvent( "LifeChange" );
}

void GameData::lossLife()
{
    if( _lifeNum == 0 )  { return; }

    if( _lifeNum > 0 )
    {
        _lifeNum -= 1;

        dispatchEvent( "LifeChange" );
    }

    if( _lifeNum == 0 ) { dispatchEvent( "Dead" ); }
}

bool GameData::dead()
{
    return _lifeNum <= 0;
}
