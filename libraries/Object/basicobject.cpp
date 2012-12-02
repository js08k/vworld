#include "basicobject.h"
#include <QDebug>
#include <cmath>
#include <QTimer>

BasicObject::BasicObject( BasicObject *parent ) :
    m_parent( parent )
{
    if( parent )
    {
        parent->addChild( this );
    }
}

BasicObject::~BasicObject()
{

}

/*
    theta = x axis rotations
    phi = z axis rotations
    r = sqrt( x^2 + y^2 + z^2 )

    x = r*sin(theta)*cos(phi)
    y = r*sin(theta)*cos(phi)
    z = r*cos(theta)
*/
void BasicObject::rotate( qreal x, qreal y, qreal z )
{
    // Check if a x rotation is requested
    if( x )
    {
        // If this object has a parent, then it must rotate
        if( m_parent )
        {
            m_location.xAxisAddRotate( x );
        }

        for( int i=0; i < m_pointsList.size(); ++i )
        {
            m_pointsList[i].xAxisAddRotate( x );
        }
    }

    // Check if a y rotation is requested
    if( y )
    {
        // If this object has a parent, then it must rotate
        if( m_parent )
        {
            m_location.yAxisAddRotate( y );
        }

        for( int i=0; i < m_pointsList.size(); ++i )
        {
            m_pointsList[i].yAxisAddRotate( y );
        }
    }

    // Check if a z rotation is requested
    if( z )
    {
        // If this object has a parent, then it must rotate
        if( m_parent )
        {
            m_location.zAxisAddRotate( z );
        }

        for( int i=0; i < m_pointsList.size(); ++i )
        {
            m_pointsList[i].zAxisAddRotate( z );
        }
    }

    for( int i=0; i < m_children.size(); ++i )
    {
        m_children[i]->rotate( x, y, z );
    }
}

void BasicObject::translate( qreal x, qreal y, qreal z )
{
    //
    m_location.set( x, y, z );

    m_location.updateRotatedValues();
}

Point BasicObject::getGlobal( const Point& point )
{
    Point globalPoint = point;

    globalPoint.set( m_location.xCoord(), m_location.yCoord(), m_location.zCoord() );

    if( m_parent )
    {
        return m_parent->getGlobal( globalPoint );
    }
    else
    {
        return globalPoint;
    }
}

