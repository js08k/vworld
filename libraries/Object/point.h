#ifndef POINT_H
#define POINT_H

// Include for Qt Types
#include <QTypeInfo>

#define PI 3.14159265

class Point
{
public:
    Point();

    /// Getters:
    inline qreal xRotated() const
    {   return m_xRotated; }
    inline qreal yRotated() const
    {   return m_yRotated; }
    inline qreal zRotated() const
    {   return m_zRotated; }
    inline qreal deltaTheta() const
    {   return m_rotatedTheta; }
    inline qreal deltaPhi() const
    {   return m_rotatedPhi; }
    inline qreal theta() const
    {   return m_theta; }
    inline qreal phi() const
    {   return m_phi; }
    inline qreal radius() const
    {   return m_radius; }
    inline qreal xCoord() const
    {   return m_xCoord; }
    inline qreal yCoord() const
    {   return m_yCoord; }
    inline qreal zCoord() const
    {   return m_zCoord; }

    /// Manipulating functions
    void set( qreal x, qreal y, qreal z );
    void shift( qreal x, qreal y, qreal z );
    void updateRotatedValues();
    void xAxisAddRotate( qreal radians );
    void yAxisAddRotate( qreal radians );
    void zAxisAddRotate( qreal radians );

private:
    /// x orig. Range: Unbounded
    qreal m_xCoord;

    /// y orig. Range: Unbounded
    qreal m_yCoord;

    /// z orig. Range: Unbounded
    qreal m_zCoord;

    /// radius. Range: [0,infinity)
    qreal m_radius;

    /// theta orig. Range: [0,PI]
    qreal m_theta;

    /// Phi orig. Range: [0,2PI)
    qreal m_phi;

    /// The rotated value of x. Range: Unbounded
    qreal m_xRotated;

    /// The rotated value of y. Range: Unbounded
    qreal m_yRotated;

    /// The rotated value of z. Range: Unbounded
    qreal m_zRotated;

    /// Flag indicating the Rotated cartesian values are out of date
    bool m_rotatedValuesAreOld;

    /// The rotated value of theta. Range: [0, Pi]
    qreal m_rotatedTheta;

    /// The rotated valu of phi. Range: [0, 2Pi)
    qreal m_rotatedPhi;
};

#endif // POINT_H
