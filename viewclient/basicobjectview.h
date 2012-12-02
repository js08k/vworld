#ifndef BASICOBJECTVIEW_H
#define BASICOBJECTVIEW_H
#include "basicobject.h"

#include <QWidget>

class BasicObjectView : public QWidget, public BasicObject
{
    Q_OBJECT
public:
    explicit BasicObjectView(BasicObjectView *object=NULL, QWidget *parent = 0);
    virtual ~BasicObjectView();

    virtual void paintEvent(QPaintEvent *);
    
signals:
    void resized();
    
public slots:
    virtual void resize();

private:
    double m_sizeModifier;
    double m_xoffset;
    double m_yoffset;
};

#endif // BASICOBJECTVIEW_H
