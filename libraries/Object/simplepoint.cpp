#include "simplepoint.h"
#include <cmath>

using namespace SimplePoint;

const qreal Pi = 3.14159265359;

Cartesian::Cartesian( qreal x, qreal y, qreal z )
{
    xVal = x;
    yVal = y;
    zVal = z;
}

Cartesian::Cartesian( const Cartesian &point )
{
    xVal = point.xVal;
    yVal = point.yVal;
    zVal = point.zVal;
}

Cartesian::Cartesian( const Spherical &point )
{
    qreal sintheta;
    qreal costheta;
    qreal sinphi;
    qreal cosphi;

    if( point.rVal == 0 )
    {
        xVal = 0;
        yVal = 0;
        zVal = 0;
        return;
    }
    else if( point.tVal == 0 || point.tVal == Pi )
    {
        sinphi = 0;
        cosphi = 0;
    }
    else
    {
        sinphi = sin( point.pVal );
        cosphi = cos( point.pVal );
    }

    sintheta = sin( point.tVal );
    costheta = cos( point.tVal );

    xVal = point.rVal * sintheta * cosphi;
    yVal = point.rVal * sintheta * sinphi;
    zVal = point.rVal * costheta;
}

Spherical::Spherical( qreal r, qreal t, qreal p )
{
    rVal = r;
    tVal = t;
    pVal = p;
}

Spherical::Spherical( const Spherical& p )
{
    rVal = p.rVal;
    tVal = p.tVal;
    pVal = p.pVal;
}

Spherical::Spherical( const Cartesian& p )
{
    rVal = sqrt( p.xVal*p.xVal + p.yVal*p.yVal + p.zVal*p.zVal );
    tVal = acos( p.zVal / rVal );
    pVal = atan2( p.xVal, p.yVal );
}
