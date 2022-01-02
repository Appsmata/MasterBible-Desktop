#include <QtWidgets>
#include <QStandardItemModel>
#include <QObject>
#include <QGroupBox>
#include <QComboBox>
#include <QRadioButton>
#include <QscrollArea>
#include <QPushButton>
#include <QSlider>

#include "app_options.h"
#include "ui_app_options.h"
#include "data/delegates/pref_delegate.h"
#include "data/models/preference.h"
#include "utils/app_utils.h"
#include "utils/pref_utils.h"

QString setUserName;
int setGeneralFontSize, setGeneralFontType, setPreviewFontSize, setPreviewFontType, setPresentFontSize, setPresentFontType;
int setPresentTheme, setAppLanguage;
bool isReady, setDarkMode, setEditMode, setSearchAll, setTabletMode, setGeneralFontBold, setPreviewFontBold, setPresentFontBold;
QFont setGeneralFont, setGeneralFontText, setPreviewFont, setPresentFont;
std::vector<QString> languages, pref_sets, navigations, pref_fonts;

PrefDelegate* prefDelegate;
Preference* preference;
QScrollArea* scrollArea;
QWidget* scrollPane;
QVBoxLayout* lstSettings;
std::vector<Preference> pages, preflist, filtered;
QStandardItemModel* prefModel = new QStandardItemModel();

QSettings allappPrefs(AppUtils::appName(), AppUtils::orgDomain());

AppOptions::AppOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppOptions)
{
    ui->setupUi(this);

    isReady = false;
    setupStuff();
    loadSettings();
    loadControls();
    loadNavigation();
    isReady = true;
}

void AppOptions::setupStuff()
{
    ui->btnTheme1->setText("Black\nand\nWhite");
    ui->btnTheme1->setStyleSheet("* { background-color: #000000; color: #FFFFFF; }");

    ui->btnTheme2->setText("White\nand\nBlack");
    ui->btnTheme2->setStyleSheet("* { background-color: #FFFFFF; color: #000000; }");

    ui->btnTheme3->setText("Grey\nand\nBlack");
    ui->btnTheme3->setStyleSheet("* { background-color: #A9A9A9; color: #000000; }");

    ui->btnTheme4->setText("Black\nand\nGrey");
    ui->btnTheme4->setStyleSheet("* { background-color: #000000; color: #A9A9A9; }");

    ui->btnTheme5->setText("Blue\nand\nWhite");
    ui->btnTheme5->setStyleSheet("* { background-color: #0000FF; color: #FFFFFF; }");

    ui->btnTheme6->setText("White\nand\nBlue");
    ui->btnTheme6->setStyleSheet("* { background-color: #FFFFFF; color: #0000FF; }");

    ui->btnTheme7->setText("Green\nand\nWhite");
    ui->btnTheme7->setStyleSheet("* { background-color: #006400; color: #FFFFFF; }");

    ui->btnTheme8->setText("White\nand\nGreen");
    ui->btnTheme8->setStyleSheet("* { background-color: #FFFFFF; color: #006400; }");

    ui->btnTheme9->setText("Orange\nand\nBlack");
    ui->btnTheme9->setStyleSheet("* { background-color: #FFA500; color: #000000; }");

    ui->btnTheme10->setText("Black\nand\nOrange");
    ui->btnTheme10->setStyleSheet("* { background-color: #000000; color: #FFA500; }");

    ui->btnTheme11->setText("Red\nand\nWhite");
    ui->btnTheme11->setStyleSheet("* { background-color: #FF0000; color: #FFFFFF; }");

    ui->btnTheme12->setText("White\nand\nRed");
    ui->btnTheme12->setStyleSheet("* { background-color: #FFFFFF; color: #FF0000; }");

    ui->btnTheme13->setText("Black\nand\nYellow");
    ui->btnTheme13->setStyleSheet("* { background-color: #000000; color: #FFFF00; }");

    ui->btnTheme14->setText("Yellow\nand\nBlack");
    ui->btnTheme14->setStyleSheet("* { background-color: #FFFF00; color: #000000; }");

    ui->btnTheme15->setText("Custom\n\nTheme");
    ui->btnTheme15->setStyleSheet("* { background-color: #000000; color: #FFFFFF; }");

}

// Get the settings navigation
void AppOptions::loadNavigation()
{
    pages = PrefUtils::preferencePages();
    preflist = PrefUtils::preferenceList();
    
    if (pages.size() != 0)
    {
        prefModel->clear();
        for (size_t i = 0; i < pages.size(); i++)
        {
            QStandardItem* prefItem = new QStandardItem;
            prefItem->setData(QVariant::fromValue(pages[i]), Qt::UserRole + 1);
            prefModel->appendRow(prefItem);
        }
        
        PrefDelegate* prefDelegate = new PrefDelegate(this);
        ui->lstNavigation->setItemDelegate(prefDelegate);
        ui->lstNavigation->setModel(prefModel);
        ui->lstNavigation->setSpacing(1);
        ui->lstNavigation->setCurrentIndex(prefModel->index(0, 0));
        loadPreferenceItems(1, "");
    }

}

void AppOptions::loadPreferenceItems(int page, QString searchStr)
{
    if (preflist.size() != 0)
    {
        if (searchStr.length() < 2)
        {
            ui->grpTabletMode->hide();
            ui->grpDarkMode->hide();
            ui->grpSearchCriteria->hide();
            ui->grpLanguage->hide();
            ui->grpUserName->hide();
            ui->grpSampleText->hide();
            ui->grpFontGeneral->hide();
            ui->grpFontPreview->hide();
            ui->grpFontPresent->hide();
            ui->grpThemes->hide();

            switch (page)
            {
                case 1:
                    ui->grpTabletMode->show();
                    ui->grpTabletMode->setFocus();
                    ui->grpDarkMode->show();
                    ui->grpSearchCriteria->show();
                    ui->grpLanguage->show();
                    ui->grpUserName->show();
                    break;

                case 2:
                    ui->grpSampleText->show();
                    ui->grpSampleText->setFocus();
                    ui->grpFontGeneral->show();
                    ui->grpFontPreview->show();
                    ui->grpFontPresent->show();
                    break;

                case 3:
                    ui->grpThemes->show();
                    ui->grpThemes->setFocus();
                    break;
            }
        }
        else
        {
            filtered.clear();
            ui->grpTabletMode->hide();
            ui->grpDarkMode->hide();
            ui->grpSearchCriteria->hide();
            ui->grpLanguage->hide();
            ui->grpUserName->hide();
            ui->grpSampleText->hide();
            ui->grpFontGeneral->hide();
            ui->grpFontPreview->hide();
            ui->grpFontPresent->hide();
            ui->grpThemes->hide();

            for (size_t i = 0; i < preflist.size(); i++)
            {
                if (preflist[i].title.contains(searchStr) || preflist[i].content.contains(searchStr))
                {
                    filtered.push_back(preflist[i]); 
                    
                    switch (preflist[i].preferenceid)
                    {
                        case 1:
                            ui->grpTabletMode->show();
                            break;

                        case 2:
                            ui->grpDarkMode->show();
                            break;

                        case 3:
                            ui->grpSearchCriteria->show();
                            break;

                        case 4:
                            ui->grpLanguage->show();
                            break;

                        case 5:
                            ui->grpUserName->show();
                            break;

                        case 7:
                            ui->grpSampleText->show();
                            ui->grpFontGeneral->show();
                            break;

                        case 8:
                            ui->grpSampleText->show();
                            ui->grpFontGeneral->show();
                            break;

                        case 9:
                            ui->grpSampleText->show();
                            ui->grpFontGeneral->show();
                            break;

                        case 10:
                            ui->grpThemes->show();
                            break;

                    }
                }
            }
        }
    }

}

void AppOptions::loadSettings()
{
    setTabletMode = allappPrefs.value(PrefUtils::prefsTabletMode()).toBool();
    setDarkMode = allappPrefs.value(PrefUtils::prefsDarkMode()).toBool();
    setEditMode = allappPrefs.value(PrefUtils::prefsEditMode()).toBool();
    setSearchAll = allappPrefs.value(PrefUtils::prefsSearchAllbooks()).toBool();

    setAppLanguage = allappPrefs.value(PrefUtils::prefsLanguage()).toInt();
    setUserName = allappPrefs.value(PrefUtils::prefsAppUser()).toString();

    setGeneralFontBold = allappPrefs.value(PrefUtils::prefsGeneralFontBold()).toBool();
    setGeneralFontSize = allappPrefs.value(PrefUtils::prefsGeneralFontSize()).toInt();
    setGeneralFontType = allappPrefs.value(PrefUtils::prefsGeneralFontType()).toInt();

    setGeneralFont.setFamily(PrefUtils::preferencesFontTypes()[setGeneralFontType]);
    setGeneralFont.setPointSize(setGeneralFontSize * 0.9);
    setGeneralFont.setBold(true);

    setGeneralFontText.setFamily(PrefUtils::preferencesFontTypes()[setGeneralFontType]);
    setGeneralFontText.setPointSize(setGeneralFontSize);
    setGeneralFontText.setBold(setGeneralFontBold);

    setPreviewFontBold = allappPrefs.value(PrefUtils::prefsPreviewFontBold()).toBool();
    setPreviewFontSize = allappPrefs.value(PrefUtils::prefsPreviewFontSize()).toInt();
    setPreviewFontType = allappPrefs.value(PrefUtils::prefsPreviewFontType()).toInt();

    setPreviewFont.setFamily(PrefUtils::preferencesFontTypes()[setPreviewFontType]);
    setPreviewFont.setPointSize(setPreviewFontSize);
    setPreviewFont.setBold(setPreviewFontBold);

    setPresentFontBold = allappPrefs.value(PrefUtils::prefsPresentFontBold()).toBool();
    setPresentFontSize = allappPrefs.value(PrefUtils::prefsPresentFontSize()).toInt();
    setPresentFontType = allappPrefs.value(PrefUtils::prefsPresentFontType()).toInt();

    setPresentFont.setFamily(PrefUtils::preferencesFontTypes()[setPresentFontType]);
    setPresentFont.setPointSize(setPresentFontSize);
    setPresentFont.setBold(setPresentFontBold);

    setPresentTheme = allappPrefs.value(PrefUtils::prefsPresentTheme()).toInt();
}

void AppOptions::loadControls()
{
    for (size_t i = 0; i < PrefUtils::preferencesLanguages().size(); i++)
    {
        ui->cmbLanguage->addItem(PrefUtils::preferencesLanguages()[i]);
    }
    ui->cmbLanguage->setCurrentIndex(setAppLanguage);

    for (size_t i = 0; i < PrefUtils::preferencesFontTypes().size(); i++)
    {
        ui->cmbFontGeneral->addItem(PrefUtils::preferencesFontTypes()[i]);
    }
    ui->cmbFontGeneral->setCurrentIndex(setGeneralFontType);

    for (size_t i = 0; i < PrefUtils::preferencesFontTypes().size(); i++)
    {
        ui->cmbFontPreview->addItem(PrefUtils::preferencesFontTypes()[i]);
    }
    ui->cmbFontPreview->setCurrentIndex(setPreviewFontType);

    for (size_t i = 0; i < PrefUtils::preferencesFontTypes().size(); i++)
    {
        ui->cmbFontPresent->addItem(PrefUtils::preferencesFontTypes()[i]);
    }
    ui->cmbFontPresent->setCurrentIndex(setPresentFontType);

    ui->btnTabletMode->setChecked(setTabletMode);
    ui->btnDarkMode->setChecked(setDarkMode);
    ui->btnSearchCritria->setChecked(setSearchAll);
    ui->txtUserName->setText(setUserName);

    ui->lblFontGeneral->setText(QString::number(setGeneralFontSize));
    ui->sldFontGeneral->setValue(setGeneralFontSize);
    ui->btnFontGeneral->setChecked(setGeneralFontBold);

    ui->lblFontPreview->setText(QString::number(setPreviewFontSize));
    ui->sldFontPreview->setValue(setPreviewFontSize);
    ui->btnFontPreview->setChecked(setPreviewFontBold);

    ui->lblFontPresent->setText(QString::number(setPresentFontSize));
    ui->sldFontPresent->setValue(setPresentFontSize);
    ui->btnFontPresent->setChecked(setPresentFontBold);

    ui->grpTabletMode->setFont(setGeneralFont);
    ui->btnTabletMode->setFont(setGeneralFontText);

    ui->grpDarkMode->setFont(setGeneralFont);
    ui->btnDarkMode->setFont(setGeneralFontText);

    ui->grpSearchCriteria->setFont(setGeneralFont);
    ui->btnSearchCritria->setFont(setGeneralFontText);

    ui->grpLanguage->setFont(setGeneralFont);
    ui->lblLanguage->setFont(setGeneralFontText);
    ui->cmbLanguage->setFont(setGeneralFontText);

    ui->grpUserName->setFont(setGeneralFont);
    ui->txtUserName->setFont(setGeneralFontText);

    ui->grpSampleText->setFont(setGeneralFont);
    ui->txtSampleText->setFont(setGeneralFontText);

    ui->grpFontGeneral->setFont(setGeneralFont);
    ui->lblFontGeneral->setFont(setGeneralFontText);
    ui->sldFontGeneral->setFont(setGeneralFontText);
    ui->cmbFontGeneral->setFont(setGeneralFontText);
    ui->btnFontGeneral->setFont(setGeneralFontText);

    ui->grpFontPreview->setFont(setGeneralFont);
    ui->lblFontPreview->setFont(setGeneralFontText);
    ui->sldFontPreview->setFont(setGeneralFontText);
    ui->cmbFontPreview->setFont(setGeneralFontText);
    ui->btnFontPreview->setFont(setGeneralFontText);

    ui->grpFontPresent->setFont(setGeneralFont);
    ui->lblFontPresent->setFont(setGeneralFontText);
    ui->sldFontPresent->setFont(setGeneralFontText);
    ui->cmbFontPresent->setFont(setGeneralFontText);
    ui->btnFontPresent->setFont(setGeneralFontText);

    ui->grpThemes->setFont(setGeneralFont);
    ui->btnTheme1->setFont(setGeneralFontText);
    ui->btnTheme2->setFont(setGeneralFontText);
    ui->btnTheme3->setFont(setGeneralFontText);
    ui->btnTheme4->setFont(setGeneralFontText);
    ui->btnTheme5->setFont(setGeneralFontText);
    ui->btnTheme6->setFont(setGeneralFontText);
    ui->btnTheme7->setFont(setGeneralFontText);
    ui->btnTheme8->setFont(setGeneralFontText);
    ui->btnTheme9->setFont(setGeneralFontText);
    ui->btnTheme10->setFont(setGeneralFontText);
    ui->btnTheme11->setFont(setGeneralFontText);
    ui->btnTheme12->setFont(setGeneralFontText);
    ui->btnTheme13->setFont(setGeneralFontText);
    ui->btnTheme14->setFont(setGeneralFontText);
    ui->btnTheme15->setFont(setGeneralFontText);
}

void AppOptions::on_lstNavigation_clicked(const QModelIndex &index)
{
    int item = index.row();
    loadPreferenceItems(pages[item].category, "");
}

void AppOptions::on_lstNavigation_doubleClicked(const QModelIndex &index)
{
    int item = index.row();
    loadPreferenceItems(pages[item].category, "");
}

void AppOptions::on_txtSearch_textChanged(const QString &query)
{
    loadPreferenceItems(0, query);
}

void AppOptions::on_btnTabletMode_clicked(bool checked)
{
    if (isReady)
        allappPrefs.setValue(PrefUtils::prefsTabletMode(), checked);
}

void AppOptions::on_btnSearchCritria_clicked(bool searched)
{
    if (isReady)
        allappPrefs.setValue(PrefUtils::prefsSearchAllbooks(), searched);
}

void AppOptions::on_cmbLanguage_currentIndexChanged(int language)
{
    if (isReady)
        allappPrefs.setValue(PrefUtils::prefsLanguage(), language);
}

void AppOptions::on_txtUserName_textChanged(const QString &username)
{
    if (isReady)
        allappPrefs.setValue(PrefUtils::prefsAppUser(), username);
}

void AppOptions::on_sldFontGeneral_valueChanged(int fontsize)
{
    if (isReady) {
        allappPrefs.setValue(PrefUtils::prefsGeneralFontSize(), fontsize);
        loadSettings();
        ui->txtSampleText->setFont(setGeneralFont);
        ui->lblFontGeneral->setText(QString::number(fontsize));
    }
}

void AppOptions::on_cmbFontGeneral_currentIndexChanged(int fonttype)
{
    if (isReady) {
        allappPrefs.setValue(PrefUtils::prefsGeneralFontType(), fonttype);
        loadSettings();
        ui->txtSampleText->setFont(setGeneralFont);
    }
}

void AppOptions::on_btnFontGeneral_clicked(bool fontbold)
{
    if (isReady) {
        allappPrefs.setValue(PrefUtils::prefsGeneralFontBold(), fontbold);
        loadSettings();
        ui->txtSampleText->setFont(setGeneralFont);
    }
}

void AppOptions::on_sldFontPreview_valueChanged(int fontsize)
{
    if (isReady) {
        allappPrefs.setValue(PrefUtils::prefsPreviewFontSize(), fontsize);
        loadSettings();
        ui->txtSampleText->setFont(setPreviewFont);
        ui->lblFontPreview->setText(QString::number(fontsize));
    }
}

void AppOptions::on_cmbFontPreview_currentIndexChanged(int fonttype)
{
    if (isReady) {
        allappPrefs.setValue(PrefUtils::prefsPreviewFontType(), fonttype);
        loadSettings();
        ui->txtSampleText->setFont(setPreviewFont);
    }
}

void AppOptions::on_btnFontPreview_clicked(bool fontbold)
{
    if (isReady) {
        allappPrefs.setValue(PrefUtils::prefsPreviewFontBold(), fontbold);
        loadSettings();
        ui->txtSampleText->setFont(setPreviewFont);
    }
}

void AppOptions::on_sldFontPresent_valueChanged(int fontsize)
{
    if (isReady) {
        allappPrefs.setValue(PrefUtils::prefsPresentFontSize(), fontsize);
        loadSettings();
        ui->txtSampleText->setFont(setPresentFont);
        ui->lblFontPresent->setText(QString::number(fontsize));
    }
}

void AppOptions::on_cmbFontPresent_currentIndexChanged(int fonttype)
{
    if (isReady) {
        allappPrefs.setValue(PrefUtils::prefsPresentFontType(), fonttype);
        loadSettings();
        ui->txtSampleText->setFont(setPresentFont);
    }
}

void AppOptions::on_btnFontPresent_clicked(bool fontbold)
{
    if (isReady) {
        allappPrefs.setValue(PrefUtils::prefsPresentFontBold(), fontbold);
        loadSettings();
        ui->txtSampleText->setFont(setPresentFont);
    }
}

void AppOptions::on_btnTheme1_clicked()
{
    if (isReady)
        allappPrefs.setValue(PrefUtils::prefsPresentTheme(), 1);
}

void AppOptions::on_btnTheme2_clicked()
{
    if (isReady)
        allappPrefs.setValue(PrefUtils::prefsPresentTheme(), 2);
}

void AppOptions::on_btnTheme3_clicked()
{
    if (isReady)
        allappPrefs.setValue(PrefUtils::prefsPresentTheme(), 3);
}

void AppOptions::on_btnTheme4_clicked()
{
    if (isReady)
        allappPrefs.setValue(PrefUtils::prefsPresentTheme(), 4);
}

void AppOptions::on_btnTheme5_clicked()
{
    if (isReady)
        allappPrefs.setValue(PrefUtils::prefsPresentTheme(), 5);
}

void AppOptions::on_btnTheme6_clicked()
{
    if (isReady)
        allappPrefs.setValue(PrefUtils::prefsPresentTheme(), 6);
}

void AppOptions::on_btnTheme7_clicked()
{
    if (isReady)
        allappPrefs.setValue(PrefUtils::prefsPresentTheme(), 7);
}

void AppOptions::on_btnTheme8_clicked()
{
    if (isReady)
        allappPrefs.setValue(PrefUtils::prefsPresentTheme(), 8);
}

void AppOptions::on_btnTheme9_clicked()
{
    if (isReady)
        allappPrefs.setValue(PrefUtils::prefsPresentTheme(), 9);
}

void AppOptions::on_btnTheme10_clicked()
{
    if (isReady)
        allappPrefs.setValue(PrefUtils::prefsPresentTheme(), 10);
}

void AppOptions::on_btnTheme11_clicked()
{
    if (isReady)
        allappPrefs.setValue(PrefUtils::prefsPresentTheme(), 11);
}

void AppOptions::on_btnTheme12_clicked()
{
    if (isReady)
        allappPrefs.setValue(PrefUtils::prefsPresentTheme(), 12);
}

void AppOptions::on_btnTheme13_clicked()
{
    if (isReady)
        allappPrefs.setValue(PrefUtils::prefsPresentTheme(), 13);
}

void AppOptions::on_btnTheme14_clicked()
{
    if (isReady)
        allappPrefs.setValue(PrefUtils::prefsPresentTheme(), 14);
}

void AppOptions::on_btnTheme15_clicked()
{
    if (isReady)
        allappPrefs.setValue(PrefUtils::prefsPresentTheme(), 15);
}

void AppOptions::on_btnReset_clicked()
{
    QMessageBox msgBox;

    msgBox.setWindowTitle("Just a minute ...");
    QIcon icon;
    icon.addFile(QStringLiteral(":/icons/icons/appicon.ico"), QSize(), QIcon::Normal, QIcon::Off);
    msgBox.setWindowIcon(icon);

    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText("Are you sure you want to reset your app settings?");
    
    //msgBox.setInformativeText(selectedones);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    int ret = msgBox.exec();
    switch (ret) {
        case QMessageBox::Yes:
            PrefUtils::defaultPrefs();
            close();
            break;

        default:
            // should never be reached
            break;
    }
}

AppOptions::~AppOptions()
{
    delete ui;
}

