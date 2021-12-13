#include "app_about.h"
#include "ui_app_about.h"

AppAbout::AppAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppAbout)
{
    ui->setupUi(this);
}

AppAbout::~AppAbout()
{
    delete ui;
}
