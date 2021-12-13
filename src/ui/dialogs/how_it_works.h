#ifndef HOW_IT_WORKS_H
#define HOW_IT_WORKS_H

#include <QDialog>

namespace Ui {
class HowItWorks;
}

class HowItWorks : public QDialog
{
    Q_OBJECT

public:
    explicit HowItWorks(QWidget *parent = nullptr);
    ~HowItWorks();

private:
    Ui::HowItWorks *ui;
};

#endif // HOW_IT_WORKS_H
