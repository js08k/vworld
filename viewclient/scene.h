#ifndef SCENE_H
#define SCENE_H

#include <QWidget>
#include <QTimer>
#include "basicobjectview.h"

class Scene : public QWidget
{
    Q_OBJECT
public:
    explicit Scene(QWidget *parent = 0);
    virtual ~Scene();
    void makeCube( QList<Point> *pointsList, qreal size=1 );
    void makeChassis(QList<Point> *pointsList , qreal size);
    
signals:
    void resized();
    
public slots:
    virtual void resize();
    void timeout();

protected:
    virtual void paintEvent(QPaintEvent *);
    BasicObjectView *m_object;
    QTimer *m_timer;
    
};

#endif // SCENE_H
