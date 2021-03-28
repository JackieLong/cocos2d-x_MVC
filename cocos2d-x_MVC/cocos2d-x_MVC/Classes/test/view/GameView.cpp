#include "GameView.h"
#include "../utils.h"

using namespace std;
USING_NS_CC;
USING_NS_MVC;

GameView::GameView()
{

}

GameView::~GameView()
{

}

Node* GameView::onCreate()
{
    auto gameScene = Scene::create();

    auto _land = Layer::create();
    _land->setTag( LAND );
    gameScene->addChild( _land );

    auto _hole = Sprite::create( "Images/Icon.png " );
    _hole->setTag( HOLE );
    _hole->setPosition( Vec2( visibleSize.width / 2 + visibleOrigin.x, visibleOrigin.y + visibleSize.height / 2 ) );
    _land->addChild( _hole );

    auto attackDensity = Label::createWithSystemFont( "Density: 0.0", "", 10 );
    attackDensity->setPosition( visibleWidth2 + visibleOriginX - 40, 50 );
    attackDensity->setTag( TXT_DENSITY );
    _land->addChild( attackDensity );

    auto lifeTxt = Label::createWithSystemFont( "Life: 0", "", 10 );
    lifeTxt->setPosition( visibleWidth2 + visibleOriginX + 40, 50 );
    lifeTxt->setTag( TXT_LIFE );
    _land->addChild( lifeTxt );

    MenuItemFont::setFontSize( 20 );

    auto btnStart = MenuItemFont::create( "start" );
    auto btnRestart = MenuItemFont::create( "restart" );
    auto btnStop = MenuItemFont::create( "stop" );
    auto btnIncr = MenuItemFont::create( "+" );
    auto btnDecr = MenuItemFont::create( "-" );
    auto btnPause = MenuItemFont::create( "pause" );

    btnStart->setTag( BTN_START );
    btnRestart->setTag( BTN_RESTART );
    btnStop->setTag( BTN_STOP );
    btnIncr->setTag( BTN_INCRI );
    btnDecr->setTag( BTN_DECRI );
    btnPause->setTag( BTN_PAUSE );

    auto offsetX = -90;

    btnDecr->setPosition( visibleOriginX + visibleWidth2 - 40 + offsetX, 30 );
    btnIncr->setPosition( visibleOriginX + visibleWidth2 - 20 + offsetX, 30 );
    btnStop->setPosition( visibleOriginX + visibleWidth2 + 25 + offsetX, 30 );
    btnStart->setPosition( visibleOriginX + visibleWidth2 + 80 + offsetX, 30 );
    btnRestart->setPosition( visibleOriginX + visibleWidth2 + 150 + offsetX, 30 );
    btnPause->setPosition( visibleOriginX + visibleWidth2 + 220 + offsetX, 30 );

    auto menu = CCMenu::create( btnIncr, btnDecr, btnStart, btnStop, btnRestart, btnPause, nullptr );
    menu->setIgnoreAnchorPointForPosition( false );

    _land->addChild( menu, 1 );

    return gameScene;
}
