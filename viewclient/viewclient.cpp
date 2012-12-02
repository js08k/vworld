#include "viewclient.h"
#include "ui_viewclient.h"
#include "basicobjectview.h"
#include "scene.h"
#include "clearcontainer.h"

ViewClient::ViewClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewClient)
{
    ui->setupUi(this);

    Scene *scene = new Scene( this );
    connect( this, SIGNAL(resizeSignal()), scene, SLOT(resize()) );

    ClearContainer *design = new ClearContainer( scene );
    design->setMaximumWidth( 60 );
}

ViewClient::~ViewClient()
{
    delete ui;
}

void ViewClient::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent( event );
    emit resizeSignal();
}
