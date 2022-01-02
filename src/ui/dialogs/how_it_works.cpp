#include "how_it_works.h"
#include "ui_how_it_works.h"

HowItWorks::HowItWorks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HowItWorks)
{
    ui->setupUi(this);
}

HowItWorks::~HowItWorks()
{
    delete ui;
}
