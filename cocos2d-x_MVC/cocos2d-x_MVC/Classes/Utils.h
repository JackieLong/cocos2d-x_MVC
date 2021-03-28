#pragma once

#ifndef _UTILS_MVC_H_
#define _UTILS_MVC_H_

#include "cocos2d.h"
#include "Macro.h"

NS_MVC_BEGIN

static cocos2d::Node* shitTargetNode = nullptr;

static void _findNodeByTag( cocos2d::Node* target, int id )
{
    if( shitTargetNode )
    {
        return;
    }
    else
        if( target->getTag() == id )
        {
            shitTargetNode = target;
            return;
        }
        else
        {
            for( auto child : target->getChildren() )
            {
                _findNodeByTag( child, id );
                if( shitTargetNode )
                {
                    return;
                }
            }
        }
}

// 遍历查找UI树中指定tag的节点，以target为根节点的UI树
template<typename T>
static T findTargetByTag( cocos2d::Node* target, const int &id, T fuck = nullptr )
{
    shitTargetNode = nullptr;
    if( target )
    {
        _findNodeByTag( target, id );
    }

    return static_cast< T >( shitTargetNode );
}

// 遍历查找UI树中指定tag的节点，以target为根节点的UI树
static cocos2d::Node* findNodeByTag( cocos2d::Node* target, const int &id )
{
    shitTargetNode = nullptr;
    if( target )
    {
        _findNodeByTag( target, id );
    }
    return ( cocos2d::Node* ) shitTargetNode;
}


NS_MVC_END

#endif