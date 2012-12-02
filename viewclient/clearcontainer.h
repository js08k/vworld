#ifndef CLEARCONTAINER_H
#define CLEARCONTAINER_H

#include <QWidget>

class ClearContainer : public QWidget
{
    Q_OBJECT
public:
    explicit ClearContainer(QWidget *parent = 0);
    virtual ~ClearContainer();
    
signals:
    
public slots:

protected:
    virtual void resizeEvent(QResizeEvent *);
    virtual void paintEvent(QPaintEvent *);
    void drawButtons( int width, int height );

    virtual void drawExpansionButton( QPoint loc, QPainter &painter );
    virtual void drawCollapseButton( QPoint loc, QPainter &painter );

private:
    //! Container's orientation, which direction expansion and collapse occur.
    bool m_horizontal;

    //! Size of the expansion/collapse button
    QSize m_buttonSize;

    //! Flag indicating the state of the widget (expanded or collapsed)
    bool m_expanded;

    //! Size of the container in expanded state
    QSize m_expandedSize;

    //! Size of the container in collapsed state
    QSize m_collapsedSize;
};

#endif // CLEARCONTAINER_H
