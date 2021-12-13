#ifndef APP_HINTS_H
#define APP_HINTS_H

#include <QDialog>

namespace Ui {
class AppHints;
}

class AppHints : public QDialog
{
    Q_OBJECT

public:
    explicit AppHints(QWidget *parent = nullptr);
    ~AppHints();

private:
    Ui::AppHints *ui;
};

#endif // APP_HINTS_H
