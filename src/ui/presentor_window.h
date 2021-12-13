#ifndef PRESENTOR_WINDOW_H
#define PRESENTOR_WINDOW_H

#include <QMainWindow>

#include "../data/app_database.h"
#include "../data/models/book.h"
#include "../data/models/song.h"

namespace Ui {
class PresentorWindow;
}

class PresentorWindow : public QMainWindow
{
    Q_OBJECT

public:
    AppDatabase* appDb = new AppDatabase();
    explicit PresentorWindow(QWidget *parent = nullptr);
    void requestData();
    ~PresentorWindow();

private slots:
    void setUpStuff();
    void loadTheme();
    void loadButtonIcons(bool light);
    void loadControls();
    void loadSettings();

    void themeChange();
    void fontChange();
    void fontSmaller();
    void fontBigger();
    void fontBold();

    void previousVerse();
    void nextVerse();

    void presentSong();
    void setPresentation();

    void on_btnClose_clicked();
    void on_actionClose_triggered();
    void on_actionFont_triggered();
    void on_actionBold_triggered();
    void on_actionSmaller_triggered();
    void on_actionBigger_triggered();
    void on_actionDown_triggered();
    void on_actionUp_triggered();
    void on_actionTheme_triggered();

    void on_btnBold_clicked();
    void on_btnFont_clicked();
    void on_btnBigger_clicked();
    void on_btnSmaller_clicked();
    void on_btnUp_clicked();
    void on_btnDown_clicked();
    void on_btnTheme_clicked();

private:
    Ui::PresentorWindow *ui;
};

#endif // PRESENTOR_WINDOW_H
