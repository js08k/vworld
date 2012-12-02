#include "clearcontainer.h"

#include <QPainter>
#include <QDebug>
#include <QPixmap>
#include <QPolygon>
#include <QLinearGradient>

ClearContainer::ClearContainer(QWidget *parent) :
    QWidget(parent)
{
    // Set the default value of the containers expansion/collapse direction
    m_horizontal = true;

    // Set the default size of this widget to that of the parent
    QWidget::resize( parent->size() );

    if( m_horizontal )
    {
        // Set the expansion/collapse button width to 5 pixels
        m_buttonSize.setWidth( 6 );
        // Set the expansion/collapse button height to 15 pixels
        m_buttonSize.setHeight( 12 );
    }
    else
    {
        // Set the expansion/collapse button width to 15 pixels
        m_buttonSize.setWidth( 6 );
        // Set the expansion/collapse button height to 5 pixels
        m_buttonSize.setHeight( 12 );
    }

    // Set the container to default to expanded
    m_expanded = true;

    // Set the default expansion width
    m_expandedSize.setWidth( QWidget::width() );
    // Set the default expansion height
    m_expandedSize.setHeight( QWidget::height() );
}

ClearContainer::~ClearContainer()
{

}

/*!
 * \brief Checks if the resize was to a size expected, if it is nothing is done.
 * if it was not, we copy the unexpected size to be expected in the future.
 * \param event Used to pass through to QWidget's implementation of resizeEvent
 */
void ClearContainer::resizeEvent(QResizeEvent *event)
{
    // Call QWidget's resizeEvent
    QWidget::resizeEvent(event);

    // Check if the resize was a size we were expecting
    if( m_expanded && this->size() != m_expandedSize )
    {
        // Expecting the expanded size, but was not.
        // Copying the new size as the expanded size.
        m_expandedSize = this->size();
    }
    else if( this->size() != m_collapsedSize )
    {
        // Expected the collapsed size, but was not.
        // Copying the new size as the collapsed size.
        m_collapsedSize = this->size();

        if( m_horizontal )
        {
            // The widget must be the width of the button
            m_collapsedSize.setWidth( m_buttonSize.width() );
        }
        else
        {
            // The widget must be the height of the button
            m_collapsedSize.setHeight( m_buttonSize.height() );
        }

        // Fix any of the size changes that were made
        resize( m_collapsedSize );
    }
}

/*!
 * \brief Paints the button indicating the container can be expanded.
 * \param loc point of the button
 * \param painter painter is the device the button is drawn on
 */
void ClearContainer::drawExpansionButton( QPoint loc, QPainter &painter )
{
    painter.setPen( Qt::gray );
    painter.setBrush( Qt::white );
    painter.drawRect( QRect( loc, m_buttonSize ) );

    painter.setPen( Qt::black );
    QPoint point1( ( loc.x() + m_buttonSize.width()-1 ),
                   ( loc.y() + m_buttonSize.height()/2 ) );
    QPoint point2( point1.x()-( m_buttonSize.width()/2 ),
                   point1.y()-(m_buttonSize.width()/2 ) );
    QPoint point3( point1.x()-(m_buttonSize.width()/2 ),
                   point1.y()+ (m_buttonSize.width()/2 ) );

    painter.drawLine( point1, point2 );
    painter.drawLine( point2, point3 );
    painter.drawLine( point3, point1 );
}

/*!
 * \brief Paints the button indicating the container can be collapsed.
 * \param loc point of the button
 * \param painter painter is the device the button is drawn on
 */
void ClearContainer::drawCollapseButton( QPoint loc, QPainter &painter )
{
    QLinearGradient gradient;
    gradient.setCoordinateMode( QGradient::ObjectBoundingMode );
    gradient.setStart( 0, .5 );
    gradient.setFinalStop( 1, .5 );

    gradient.setColorAt( 0.0, Qt::white );
    gradient.setColorAt( 0.5, Qt::gray );
    gradient.setColorAt( 1.0, Qt::white );

    painter.setBrush( gradient );
    painter.setPen( QPen( gradient, 0 ) );

    painter.drawRect( QRect( loc, m_buttonSize ) );
}

void ClearContainer::paintEvent(QPaintEvent *)
{
    QPainter painter( this );

    painter.setOpacity( .6 );
    painter.setBrush( Qt::transparent );

    if( m_expanded )
    {
        painter.setPen( Qt::gray );
        painter.drawRect( 0, 0, QWidget::width() - 1, QWidget::height() - 1 );
        painter.setPen( Qt::white );
        painter.drawRect( 1, 1, QWidget::width() - 3, QWidget::height() - 3 );
        painter.setOpacity( .2 );
        painter.setPen( Qt::lightGray );
        painter.setBrush( Qt::white );
        painter.drawRect( 2, 2, QWidget::width() - 5, QWidget::height() - 5 );

        painter.setOpacity( 1 );

//        painter.drawPixmap( 10, 10, *m_expand );

        QPoint point( this->width() - m_buttonSize.width(),
                      this->height() / 2 - m_buttonSize.height() / 2 );
        drawExpansionButton( point, painter );
    }
    else
    {

    }

    painter.end();
}


