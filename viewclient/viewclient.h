#ifndef VIEWCLIENT_H
#define VIEWCLIENT_H

#include <QMainWindow>
#include <basicobject.h>

namespace Ui {
class ViewClient;
}

class ViewClient : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ViewClient(QWidget *parent = 0);
    ~ViewClient();

signals:
    void resizeSignal();

protected:
    virtual void resizeEvent(QResizeEvent *event);
    
private:
    Ui::ViewClient *ui;
};

#endif // VIEWCLIENT_H
