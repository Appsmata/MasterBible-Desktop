#ifndef HOME_WINDOW_H
#define HOME_WINDOW_H

#include <QMainWindow>

#include "../data/app_database.h"
#include "../data/models/book.h"
#include "../data/models/verse.h"

namespace Ui {
class HomeWindow;
}

class HomeWindow : public QMainWindow
{
    Q_OBJECT

public:
    AppDatabase* appDb = new AppDatabase();
    explicit HomeWindow(QWidget* parent = nullptr);
    void requestData();
    void changeStyle(int type);
    ~HomeWindow();

private slots:
    void loadControls();
    void loadSettings();

    void fontChange();
    void fontSmaller();
    void fontBigger();

    void on_txtSearch_textChanged(const QString& arg1);
    void on_txtSearch_returnPressed();
    void on_cmbLanguages_currentIndexChanged(const QString& arg1);
    void on_lstResults_clicked(const QModelIndex& index);
    void on_lstResults_doubleClicked(const QModelIndex& index);
    void on_chkNewTestament_stateChanged(int arg1);
    void on_chkOldTestament_stateChanged(int arg1);
    void on_cmbChapter_currentIndexChanged(const QString& arg1);

    void nextChapter();
    void previousChapter();
    void searchBible(QString Searchstr);
    void gotoReading();
    void getReading(const QModelIndex& selected);
    void openReading();

    void on_menuPrint_triggered();
    void on_menuExit_triggered();
    void on_menuNewVerse_triggered();
    void on_menuEditVerse_triggered();
    void on_menuBooks_triggered();
    void on_menuPresent_triggered();
    void on_menuManageSettings_triggered();
    void on_menuResetSettings_triggered();
    void on_menuHowItWorks_triggered();
    void on_menuContactUs_triggered();
    void on_menuAboutThisApp_triggered();

    void on_toolbarPresent_triggered();
    void on_toolbarEdit_triggered();
    void on_toolbarPrevious_triggered();
    void on_toolbarNext_triggered();
    void on_toolbarBigger_triggered();
    void on_toolbarSmaller_triggered();
    void on_toolbarBold_triggered();
    void on_toolbarSettings_triggered();
    void on_menuDarkMode_triggered();
    void on_actionDarkMode_triggered();
    void on_menuSearchAll_triggered();
    void on_chkSearchCriteria_stateChanged(int arg1);

    void openPresenter();
private:
    Ui::HomeWindow *ui;
};

#endif // HOME_WINDOW_H
