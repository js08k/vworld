#ifndef SIMPLEPOINT_H
#define SIMPLEPOINT_H

#include <QTypeInfo>

namespace SimplePoint
{
    struct Spherical;

    struct Cartesian
    {
        Cartesian( qreal x = 0, qreal y = 0, qreal z = 0 );
        Cartesian( const Cartesian& point );
        Cartesian( const Spherical& point );
        qreal xVal;
        qreal yVal;
        qreal zVal;
    };

    struct Spherical
    {
        Spherical( qreal r = 0, qreal t = 0, qreal p = 0 );
        Spherical( const Spherical& point );
        Spherical( const Cartesian& point );
        qreal rVal;
        qreal tVal;
        qreal pVal;
    };

//    struct Eular
//    {
//        Eular( qreal a = 0, qreal b = 0, qreal y = 0 );
//    };
};

#endif // SIMPLEPOINT_H
