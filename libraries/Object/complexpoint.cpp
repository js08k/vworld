#include "point.h"
#include <cmath>
#include <QDebug>

Point::Point()
{
    // Initialize all values to zero
    m_xCoord = 0;
    m_yCoord = 0;
    m_zCoord = 0;
    m_radius = 0;
    m_theta = 0;
    m_phi = 0;
    m_rotatedTheta = 0;
    m_rotatedPhi = 0;
    m_xRotated = 0;
    m_yRotated = 0;
    m_zRotated = 0;
    m_rotatedValuesAreOld = false;
}

/*!
 * \brief Sets the cartesian and spherical origional points. If there is a
 * rotation already existing on this point, the rotation is unaffected. However,
 * the cartesian rotation values will be old.
 * \param x X coordinate of the point being used
 * \param y Y coordinate of the point being used
 * \param z Z coordinate of the point being used
 * \note The optimization todo is less important in this function since this
 * function is expected to only be called once per point.
 */
void Point::set( qreal x, qreal y, qreal z )
{
    m_xCoord = x;
    m_yCoord = y;
    m_zCoord = z;

    if( x == 0 && y == 0 && z == 0 )
    {
        // Special case point
        m_radius = 0;
        m_theta = 0;
        m_phi = 0;
    }
    else
    {
        /// \todo: Expensive chunk of code. Look for optimization algorithms
        m_radius = sqrt( x*x + y*y + z*z );
        m_rotatedTheta = m_theta = acos( z / m_radius );
        m_rotatedPhi = m_phi = atan2( y , x );
    }

    // Rotated values are old, but no need to update them here.
    m_rotatedValuesAreOld = true;
}

void Point::shift( qreal x, qreal y, qreal z )
{
    Q_UNUSED( x )
    Q_UNUSED( y )
    Q_UNUSED( z )
//    updateRotatedValues();
}

/*!
 * \brief This is a costly calculation and should only be performed when the
 * values of x,y,z are needed. They will be needed when drawing this object,
 * or when the object these points are a part of is moving within the parent's
 * coordinate system. If the rotational values are equal to the origional
 * rotational values, the x,y,z origional values are used rather than
 * calculating the x,y,z values. This is done to aid in squashing error
 * propegation.
 */
void Point::updateRotatedValues()
{
    // Check if the rotated values are out of date.
    if( m_rotatedValuesAreOld )
    {
        // This chunk is the costly part of the calculation
        qreal sinphi;
        qreal cosphi;

        // Accounting for theta values that result in an undefined phi value
        if( m_rotatedTheta == 0 || m_rotatedTheta == PI )
        {
            // sin( phi = 0 )
            sinphi = 0;
            // cos( phi = 0 )
            cosphi = 1;
        }
        else
        {
            sinphi = sin( m_rotatedPhi );
            cosphi = cos( m_rotatedPhi );
        }

        qreal sintheta = sin( m_rotatedTheta );
        qreal costheta = cos( m_rotatedTheta );

        // cheap portion
        m_xRotated = m_radius * sintheta * cosphi;
        m_yRotated = m_radius * sintheta * sinphi;
        m_zRotated = m_radius * costheta;

        // Rotated values have been updated.
        m_rotatedValuesAreOld = false;
    }
}

/*!
 * \brief Rotates the point about the x axis.
 * \param radians
 * \note Both theta and phi will be effected by this rotation
 * \note This may cause theta's value to be 0 or Pi which will cause phi to
 * become "undefined". Phi's value must be treated as 0 when theta's value is
 * equal to 0 or Pi.
 */
void Point::xAxisAddRotate( qreal radians )
{
    /// \todo: Find a better algorithm or find a way to introduce error
    /// correction. This very likley can lead to error propegation, there must
    /// be a better way to do this.
    updateRotatedValues();

    qreal cosval = cos( radians );
    qreal sinval = sin( radians );

    qreal yprime = m_yRotated*cosval - m_zRotated*sinval;
    qreal zprime = m_yRotated*sinval + m_zRotated*cosval;

    m_yRotated = yprime;
    m_zRotated = zprime;

    m_rotatedTheta = m_theta = acos( m_zRotated / m_radius );
    m_rotatedPhi = m_phi = atan2( m_yRotated , m_xRotated );
}

/*!
 * \brief Rotates the point about the y axis.
 * \param radians
 * \note Both theta and phi will be effected by this rotation
 * \note This may cause theta's value to be 0 or Pi which will cause phi to
 * become "undefined". Phi's value must be treated as 0 when theta's value is
 * equal to 0 or Pi.
 */
void Point::yAxisAddRotate( qreal radians )
{
    /// \todo: Find a better algorithm or find a way to introduce error
    /// correction. This very likley can lead to error propegation, there must
    /// be a better way to do this.
    updateRotatedValues();

    qreal cosval = cos( radians );
    qreal sinval = sin( radians );

    qreal xprime = m_xRotated*cosval + m_zRotated*sinval;
    qreal zprime = m_zRotated*cosval - m_xRotated*sinval;

    m_xRotated = xprime;
    m_zRotated = zprime;

    m_rotatedTheta = m_theta = acos( m_zRotated / m_radius );
    m_rotatedPhi = m_phi = atan2( m_yRotated , m_xRotated );
}

/*!
 * \brief Rotates the point about the z axis.
 * \param radians
 * \note Rotation about the z axis can be directly applied to phi
 */
void Point::zAxisAddRotate( qreal radians )
{
    if( radians )
    {
        // add the rotation directly to phi's rotated value
        m_rotatedPhi += radians;

        // Make sure rotated phi is still in range: [0, 2PI)
        if( m_rotatedPhi >= 2*PI )
        {
            m_rotatedPhi -= 2*PI;
        }
        else if( m_rotatedPhi < 0 )
        {
            m_rotatedPhi += 2*PI;
        }

        // Rotated values are old, but no need to update them here.
        m_rotatedValuesAreOld = true;
    }
}
