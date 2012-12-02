#ifndef OBJECT_H
#define OBJECT_H

#include "Object_global.h"
#include <QList>
#include "point.h"


/*!
 * \brief The BasicObject class provides an generic item that can be inherited
 * and give the basic properties of an object to a subclass. The BasicObjects
 * can be "put together" to form complex virtual structures and can move
 * independent of objects to which they are connected. An entity is a
 * compilation of objects, where the most parental object is the Parent Entity.
 */
class OBJECTSHARED_EXPORT BasicObject
{
public:
    BasicObject( BasicObject *parent = NULL );

    virtual ~BasicObject();

    ///
    inline void addChild( BasicObject* child )
    {   m_children.append( child ); }

    /// Build the pointsList of the BasicObject
//    inline void buildObject( const QList<Points> &points )
//    {   m_pointsList = points;  }

    /// Get the pointsList of the BasicObject
    inline const QList<Point> &pointsList() const
    {   return m_pointsList; }

    inline void importList( QList<Point> &pointsList )
    {   m_pointsList = pointsList; }

    /// Rotate the object
    void rotate( qreal x, qreal y, qreal z );

    /// Translate object
    void translate( qreal x, qreal y, qreal z );

    /// To Global
    Point getGlobal( const Point& point );

//    /// Rotates the object about the x axis
//    void xAxisRotate( double radians );

//    /// Rotates the object about the z axis
//    void zAxisRotate( double radians );

//    /// Rotates the object about the y axis
//    void yAxisRotate( double radians );

protected:

    /// Translate local rotation into parent's rotation
//    vec toParentRotation( const vec& local );

    /// Object's center within the parent's coordinate system
    Point m_location;

    /// Parent object
    BasicObject *m_parent;

    /// Children objects list
    QList<BasicObject*> m_children;

private:
    /// Object's points
    QList<Point> m_pointsList;
};

#endif // OBJECT_H
