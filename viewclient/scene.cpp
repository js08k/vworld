#include "scene.h"
#include <QPainter>

Scene::Scene(QWidget *parent) :
    QWidget(parent)
{
    QWidget::resize( parent->size() );

    QList<Point> pointsList;
    m_object = new BasicObjectView( NULL, this );
    makeCube( &pointsList, 1 );
//    makeChassis( &pointsList, 1 );
    m_object->importList( pointsList );
    m_object->translate( 10, 7, 0 );

    BasicObjectView *child = new BasicObjectView( m_object, this );
    makeCube( &pointsList, .1 );
    child->importList( pointsList );
    child->translate( 2, 2, 2 );

    child = new BasicObjectView( m_object, this );
    makeCube( &pointsList, .1 );
    child->importList( pointsList );
    child->translate( -2, -2, -2 );

    child = new BasicObjectView( m_object, this );
    makeCube( &pointsList, .5 );
    child->importList( pointsList );
    child->translate( -2, 2, 2 );

    child = new BasicObjectView( m_object, this );
    makeCube( &pointsList, .5 );
    child->importList( pointsList );
    child->translate( 2, -2, -2 );

    m_timer = new QTimer( this );
    m_timer->setInterval( 5 );
    connect( m_timer, SIGNAL(timeout()), this, SLOT(timeout()) );
    m_timer->start();
}

Scene::~Scene()
{

}

void Scene::makeCube(QList<Point> *pointsList , qreal size)
{
    if( pointsList )
    {
        Point* point;

        pointsList->clear();

        point = new Point;
        point->set(  -1*size, -1*size, -1*size );
        pointsList->append( *point );

        point = new Point;
        point->set(  -1*size, -1*size, 1*size );
        pointsList->append( *point );

        point = new Point;
        point->set(  -1*size,  1*size, -1*size );
        pointsList->append( *point );

        point = new Point;
        point->set(  -1*size,  1*size, 1*size );
        pointsList->append( *point );

        point = new Point;
        point->set(  1*size, -1*size,  -1*size );
        pointsList->append( *point );

        point = new Point;
        point->set(  1*size, -1*size,  1*size );
        pointsList->append( *point );

        point = new Point;
        point->set(  1*size,  1*size, -1*size );
        pointsList->append( *point );

        point = new Point;
        point->set(  1*size,  1*size,  1*size );
        pointsList->append( *point );

        point = new Point;
        point->set(  0,  0,  0 );
        pointsList->append( *point );
    }
}

void Scene::makeChassis(QList<Point> *pointsList , qreal size)
{
    if( pointsList )
    {
        Point* point;

        pointsList->clear();

        point = new Point;
        point->set(  -.6*size, 1*size, -.5*size );
        pointsList->append( *point );

        point = new Point;
        point->set( .6*size, 1*size, -.5*size );
        pointsList->append( *point );

        point = new Point;
        point->set(  -.6*size, 1*size, 0*size );
        pointsList->append( *point );

        point = new Point;
        point->set( .6*size, 1*size, 0*size );
        pointsList->append( *point );

        point = new Point;
        point->set( 1*size, -.5*size, -.5*size );
        pointsList->append( *point );

        point = new Point;
        point->set( -1*size, -.5*size, -.5*size );
        pointsList->append( *point );

        point = new Point;
        point->set( 1*size, -.5*size, 0*size );
        pointsList->append( *point );

        point = new Point;
        point->set( -1*size, -.5*size, 0*size );
        pointsList->append( *point );

        point = new Point;
        point->set( 1*size, -1.2*size, -.5*size );
        pointsList->append( *point );

        point = new Point;
        point->set( -1*size, -1.2*size, -.5*size );
        pointsList->append( *point );

        point = new Point;
        point->set( 1*size, -1.2*size, 0*size );
        pointsList->append( *point );

        point = new Point;
        point->set( -1*size, -1.2*size, 0*size );
        pointsList->append( *point );

        point = new Point;
        point->set( .6*size, -.3*size, -.8*size );
        pointsList->append( *point );

        point = new Point;
        point->set( -.6*size, -.3*size, -.8*size );
        pointsList->append( *point );

        point = new Point;
        point->set( .6*size, -.3*size, 0*size );
        pointsList->append( *point );

        point = new Point;
        point->set( -.6*size, -.3*size, 0*size );
        pointsList->append( *point );

        point = new Point;
        point->set( .6*size, -1.2*size, -.8*size );
        pointsList->append( *point );

        point = new Point;
        point->set( -.6*size, -1.2*size, -.8*size );
        pointsList->append( *point );

        point = new Point;
        point->set( .6*size, -1.2*size, 0*size );
        pointsList->append( *point );

        point = new Point;
        point->set( -.6*size, -1.2*size, 0*size );
        pointsList->append( *point );

        point = new Point;
        point->set(  -.6*size, -1.4*size, -.5*size );
        pointsList->append( *point );

        point = new Point;
        point->set( .6*size, -1.4*size, -.5*size );
        pointsList->append( *point );

        point = new Point;
        point->set(  -.6*size, -1.4*size, 0*size );
        pointsList->append( *point );

        point = new Point;
        point->set( .6*size, -1.4*size, 0*size );
        pointsList->append( *point );

        point = new Point;
        point->set(  0,  0,  0 );
        pointsList->append( *point );
    }
}


void Scene::paintEvent(QPaintEvent *)
{
    QPainter painter( this );

    painter.setBrush( Qt::black );
    painter.setPen( Qt::black );
    painter.drawRect( 0, 0, QWidget::width() - 1, QWidget::height() - 1 );
    painter.end();
}

void Scene::resize()
{
    QWidget *parent = dynamic_cast<QWidget *>( QWidget::parent() );

    if( parent )
    {
        QWidget::resize( parent->size() );
        emit resized();
        update();
    }
}

void Scene::timeout()
{
    if( m_object )
    {
        m_object->rotate( 0, 0.01, 0 );
    }

    update();
}
