#include "app_hints.h"
#include "ui_app_hints.h"

AppHints::AppHints(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppHints)
{
    ui->setupUi(this);
}

AppHints::~AppHints()
{
    delete ui;
}
