#ifndef APP_OPTIONS_H
#define APP_OPTIONS_H

#include <QDialog>

class QStandardItemModel;

namespace Ui {
class AppOptions;
}

class AppOptions : public QDialog
{
    Q_OBJECT

public:
    explicit AppOptions(QWidget *parent = nullptr);
    ~AppOptions();

private slots:
    void setupStuff();
    void loadNavigation();
    void loadControls();
    void loadSettings();
    void loadPreferenceItems(int page, QString searchstr);
    
    void on_lstNavigation_clicked(const QModelIndex &index);
    void on_lstNavigation_doubleClicked(const QModelIndex &index);
    void on_txtSearch_textChanged(const QString &arg1);
    void on_btnTabletMode_clicked(bool checked);
    void on_btnSearchCritria_clicked(bool checked);
    void on_cmbLanguage_currentIndexChanged(int index);
    void on_txtUserName_textChanged(const QString &arg1);


    void on_sldFontGeneral_valueChanged(int value);
    void on_cmbFontGeneral_currentIndexChanged(int index);
    void on_btnFontGeneral_clicked(bool checked);

    void on_sldFontPreview_valueChanged(int value);
    void on_cmbFontPreview_currentIndexChanged(int index);
    void on_btnFontPreview_clicked(bool checked);

    void on_sldFontPresent_valueChanged(int value);
    void on_cmbFontPresent_currentIndexChanged(int index);
    void on_btnFontPresent_clicked(bool checked);

    void on_btnTheme1_clicked();
    void on_btnTheme2_clicked();
    void on_btnTheme3_clicked();
    void on_btnTheme4_clicked();
    void on_btnTheme5_clicked();
    void on_btnTheme6_clicked();
    void on_btnTheme7_clicked();
    void on_btnTheme8_clicked();
    void on_btnTheme9_clicked();
    void on_btnTheme10_clicked();
    void on_btnTheme11_clicked();
    void on_btnTheme12_clicked();
    void on_btnTheme13_clicked();
    void on_btnTheme14_clicked();
    void on_btnTheme15_clicked();

    void on_btnReset_clicked();

private:
    Ui::AppOptions *ui;
};

#endif // APP_OPTIONS_H
