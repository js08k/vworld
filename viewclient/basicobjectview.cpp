#include "basicobjectview.h"
#include <armadillo>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <clearcontainer.h>
#include <point.h>

using namespace arma;

BasicObjectView::BasicObjectView(BasicObjectView *object, QWidget *parent) :
    QWidget(parent),
    BasicObject( dynamic_cast<BasicObject*>( object ) )
{
    QWidget::resize( parent->size() );
    m_sizeModifier = 20;
    m_xoffset = this->width()/2;
    m_yoffset = this->height()/2;
}

BasicObjectView::~BasicObjectView()
{

}

void BasicObjectView::paintEvent(QPaintEvent *)
{
    QPainter painter( this );

    for( int i=0; i < pointsList().size(); ++i )
    {
        Point point = pointsList().at(i);
        point.updateRotatedValues();
        qreal x;
        qreal y;
        qreal z;
        if( m_parent )
        {
            Point diff = getGlobal( Point() );

            x = m_sizeModifier * ( point.xRotated() + m_location.xRotated() + diff.xCoord() );
            y = m_sizeModifier * ( point.yRotated() + m_location.yRotated() + diff.yCoord() );
            z = m_sizeModifier * ( point.zRotated() + m_location.zRotated() + diff.zCoord() );
        }
        else
        {
            x = m_sizeModifier * ( point.xRotated() + m_location.xRotated() );
            y = m_sizeModifier * ( point.yRotated() + m_location.yRotated() );
            z = m_sizeModifier * ( point.zRotated() + m_location.zRotated() );
        }
        ;

        if( z > 0 )
        {
            painter.setPen( QPen( Qt::blue, 2 ) );
        }
        else if( z < 0 )
        {
            painter.setPen( QPen( Qt::green, 2 ) );
        }
        else
        {
            painter.setPen( QPen( Qt::red, 2 ) );
        }

        x += z / 2;
        y -= z / 2;

        painter.drawPoint( (int)x, (int)y );
    }

    //    if( m_children.size() > 0 )
    //    {
    //        for( int i=0; i < m_children.size(); ++i )


    //    }
}

void BasicObjectView::resize()
{
    QWidget *parent = dynamic_cast<QWidget *>( QWidget::parent() );

    if( parent )
    {
        QWidget::resize( parent->size() );

        m_xoffset = this->width()/2;
        m_yoffset = this->height()/2;

        emit resized();
        update();
    }
}

