#include <memory>
#include <QModelIndex>
#include <QListView>
#include <QDialog>
#include <QDialogButtonBox>
#include <QListView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QFile>
#include <QGraphicsDropShadowEffect>

#include "home_window.h"
#include "ui_home_window.h"
#include "../data/delegates/verse_delegate.h"
#include "../ui/dialogs/app_options.h"
#include "../ui/dialogs/book_select.h"
#include "../ui/presentor_window.h"
#include "../utils/app_utils.h"
#include "../utils/pref_utils.h"

int previewFontSize, previewFontType, selectedbook, chapters;
bool appReady, editMode, searchAll, darkMode, previewFontBold;
QFont previewFontHome, generalFontHome;

std::vector<Book> books;
std::vector<Verse> verses, filters;
std::vector<QString> histories, list_items, list_titles;
QString search_term, set_language, set_book, set_chapter, set_verse;

QStandardItemModel* VerseModel = new QStandardItemModel();

QSettings homePrefs(AppUtils::appName(), AppUtils::orgDomain());

HomeWindow::HomeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HomeWindow)
{
    ui->setupUi(this);
    appReady = false;
    ui->splitterMain->setStretchFactor(1, 3);

    QString appNameUser = QCoreApplication::applicationName() + " " + AppUtils::appVersion();
    appNameUser.append(" | " + homePrefs.value(PrefUtils::prefsAppUser()).toString());
    this->setWindowTitle(appNameUser);

    ui->cmbLanguages->addItem("English");
    ui->cmbLanguages->addItem("Swahili");

    loadSettings();
    loadControls();
    requestData();
}

void HomeWindow::changeStyle(int type)
{
    QString fileName = "";
    switch ( type )
    {
        case 1:
            fileName = "black.qss";
            break;
        default:
            fileName = "brown.qss";
            break;
    }

    QFile file(":/themes/"+ fileName);

    if ( file.open(QFile::ReadOnly) )
    {
        QString qss = QLatin1String(file.readAll());
        this->setStyleSheet(qss);
        file.close();
    }
}

void HomeWindow::requestData()
{
    appReady = false;
    searchBible("");
    openReading();

    for (int c = 1; c < chapters + 1; c++)
        ui->cmbChapter->addItem(QString::number(c));
    appReady = true;

}

void HomeWindow::loadSettings()
{
    darkMode = homePrefs.value(PrefUtils::prefsDarkMode()).toBool();
    editMode = homePrefs.value(PrefUtils::prefsEditMode()).toBool();
    searchAll = homePrefs.value(PrefUtils::prefsSearchAllbooks()).toBool();

    generalFontHome.setFamily(PrefUtils::preferencesFontTypes()[homePrefs.value(PrefUtils::prefsGeneralFontType()).toInt()]);
    generalFontHome.setPointSize(homePrefs.value(PrefUtils::prefsGeneralFontSize()).toInt());
    generalFontHome.setBold(homePrefs.value(PrefUtils::prefsGeneralFontBold()).toBool());

    previewFontBold = homePrefs.value(PrefUtils::prefsPreviewFontBold()).toBool();
    previewFontSize = homePrefs.value(PrefUtils::prefsPreviewFontSize()).toInt();
    previewFontType = homePrefs.value(PrefUtils::prefsPreviewFontType()).toInt();

    previewFontHome.setFamily(PrefUtils::preferencesFontTypes()[previewFontType]);
    previewFontHome.setPointSize(previewFontSize);
    previewFontHome.setBold(previewFontBold);
}

void HomeWindow::loadControls()
{
    /*ui->chkSearchCriteria->setChecked(searchAll);
    ui->menuSearchAll->setChecked(searchAll);
    ui->actionDarkMode->setChecked(darkMode);
    ui->menuDarkMode->setChecked(darkMode);

    ui->txtSearch->setFont(generalFontHome);
    ui->cmbBooks->setFont(generalFontHome);
    ui->chkSearchCriteria->setFont(generalFontHome);

    ui->txtTitle->setFont(previewFontHome);
    ui->txtContent->setFont(previewFontHome);
    ui->txtAlias->setFont(previewFontHome);*/

    if (darkMode)
        changeStyle(1);
    else
        changeStyle(0);
}

// Changing of font of the Verse preview
void HomeWindow::fontChange()
{
    switch (previewFontType)
    {
    case 12:
        previewFontType = 1;
        break;

    default:
        previewFontType = previewFontType + 1;
        break;
    }
    homePrefs.setValue(PrefUtils::prefsPreviewFontType(), previewFontType);
    loadSettings();
    loadControls();
}

// Reduce Preview Font Size
void HomeWindow::fontSmaller()
{
    if ((previewFontSize - 2) > 9)
    {
        previewFontSize = previewFontSize - 2;
        previewFontHome.setPointSize(previewFontSize);
        homePrefs.setValue(PrefUtils::prefsPreviewFontSize(), previewFontSize);
        loadSettings();
        loadControls();
    }
}

void HomeWindow::fontBigger()
{
    if ((previewFontSize + 2) < 51)
    {
        previewFontSize = previewFontSize + 2;
        homePrefs.setValue(PrefUtils::prefsPreviewFontSize(), previewFontSize);
        loadSettings();
        loadControls();
    }
}

// Open the presentor window
void HomeWindow::openPresenter()
{
    //PresentorWindow* present = new PresentorWindow();
    //present->showFullScreen();
}

void HomeWindow::on_txtSearch_textChanged(const QString & searchStr)
{
    searchBible(searchStr);
}

void HomeWindow::on_txtSearch_returnPressed()
{
    searchBible(ui->txtSearch->text());
}

void HomeWindow::on_cmbLanguages_currentIndexChanged(const QString& arg1)
{
    set_language = arg1.toLower();
    homePrefs.setValue(PrefUtils::prefsSelectedLanguage(), set_language);
    if (appReady) gotoReading();
}

void HomeWindow::on_lstResults_clicked(const QModelIndex& index)
{
    getReading(index);
}

void HomeWindow::on_lstResults_doubleClicked(const QModelIndex& index)
{
    //openVersePreview(index);
    //openPresenter();
}

void HomeWindow::on_cmbChapter_currentIndexChanged(const QString& arg1)
{
    if (appReady) gotoReading();
}

void HomeWindow::on_chkNewTestament_stateChanged(int arg1)
{
    searchBible(ui->txtSearch->text());
}

void HomeWindow::on_chkOldTestament_stateChanged(int arg1)
{
    searchBible(ui->txtSearch->text());
}

void HomeWindow::searchBible(QString SearchStr)
{
    QStringList strList;
    QStandardItemModel* listModel = new QStandardItemModel();
    bool SearchOT, SearchNT;

    int bookcount = 0, versecount = 0;

    SearchOT = ui->chkOldTestament->isChecked();
    SearchNT = ui->chkNewTestament->isChecked();
    ui->lblResult->hide();

    QString Results = "";

    if (list_items.size() > 0)
    {
        list_items.clear();
        list_titles.clear();
    }

    /*sqlite3* db;
    char* err_msg = NULL, ** qryResult = NULL;
    int row, col, rc = sqlite3_open_v2(AsUtils::DbNameChar(), &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

    QByteArray bar1 = AsUtils::BookSearchSql(SearchStr, SearchOT, SearchNT).toLocal8Bit();
    char* sqlQuery1 = bar1.data();

    //ui->TxtContent->setPlainText(AsUtils::BookSearchSql(SearchStr, SearchOT, SearchNT));

    if (rc == SQLITE_OK)
    {
        rc = sqlite3_get_table(db, sqlQuery1, &qryResult, &row, &col, &err_msg);

        if (rc == SQLITE_OK)
        {
            for (int i = 1; i < row + 1; i++)
            {
                QString bookid = *(qryResult + i * col + 0);

                QStandardItem* listItem = new QStandardItem;
                AsItem listing;
                //listing.image = "res/settings.png";
                QString testament = "OT";
                QString tstStr = *(qryResult + i * col + 1);
                QString title1 = *(qryResult + i * col + 3);
                QString title2 = *(qryResult + i * col + 5);

                list_items.push_back(bookid);
                list_titles.push_back(title1 + " 1");

                if (tstStr == "1") testament = "OT";
                else if (tstStr == "2") testament = "NT";

                listing.title = bookid + "# " + title1.toUpper() + " (" + *(qryResult + i * col + 2) + ")";
                listing.content = testament + "; " + title2 + " (SW); " + *(qryResult + i * col + 4) + " Chapters;";

                listItem->setData(QVariant::fromValue(listing), Qt::UserRole + 1);
                listModel->appendRow(listItem);
                bookcount++;
            }

            if (SearchOT && !SearchNT) Results = QString::number(bookcount) + " books in the Old Testament";
            else if (!SearchOT && SearchNT) Results = QString::number(bookcount) + " books in the New Testament";
            else Results = QString::number(bookcount) + " books in the Bible";

            if (!SearchStr.isEmpty())
            {
                QByteArray bar2 = AsUtils::VerseSearchSql(SearchStr, language).toLocal8Bit();

                char* sqlQuery2 = bar2.data();

                rc = sqlite3_get_table(db, sqlQuery2, &qryResult, &row, &col, &err_msg);

                for (int k = 1; k < row + 1; k++)
                {
                    QString verseid = *(qryResult + k * col + 0);

                    QStandardItem* listItem = new QStandardItem;
                    AsItem listing;
                    QString title = *(qryResult + k * col + 1);
                    QString content = *(qryResult + k * col + 2);

                    list_items.push_back(verseid);
                    list_titles.push_back(title);

                    listing.title = title.toUpper();
                    listing.content = content;

                    listItem->setData(QVariant::fromValue(listing), Qt::UserRole + 1);
                    listModel->appendRow(listItem);
                    versecount++;
                }

            }

            AsDelegate* homeDelegate = new AsDelegate(this);
            ui->LstResults->setItemDelegate(homeDelegate);
            ui->LstResults->setModel(listModel);
            ui->LstResults->setSpacing(1);

            sqlite3_free_table(qryResult);
            sqlite3_close(db);

            ui->LblResult->setText(Results);
            if (bookcount > 0 || versecount > 0)
            {
                ui->LstResults->setCurrentIndex(listModel->index(0, 0));
            }
        }
    }*/
}

void HomeWindow::getReading(const QModelIndex& index)
{
    appReady = false;
    int item = index.row();
    QString item_title = list_titles[item];

    homePrefs.setValue(PrefUtils::prefsSelectedBook(), item_title);
    homePrefs.setValue(PrefUtils::prefsSelectedChapter(), item_title);

    QStringList bookstr = item_title.split(" ");

    switch (bookstr.size())
    {
    case 2:
        set_book = bookstr[0];
        set_chapter = bookstr[1];
        break;

    case 3:
        set_book = bookstr[0] + " " + bookstr[1];
        set_chapter = bookstr[2];
        break;

    case 4:
        set_book = bookstr[0] + " " + bookstr[1] + " " + bookstr[2];
        set_chapter = bookstr[3];
        break;

    default:
        set_book = item_title;
        set_chapter = "1";
        break;
    }

    homePrefs.setValue(PrefUtils::prefsSelectedBook(), set_book);
    homePrefs.setValue(PrefUtils::prefsSelectedChapter(), set_chapter);

    ui->txtTitle->setText(set_book + " " + set_chapter);

    ui->cmbChapter->clear();
    ui->cmbVerse->clear();

    openReading();
    for (int c = 1; c < chapters + 1; c++) ui->cmbChapter->addItem(QString::number(c));
    appReady = true;
}

void HomeWindow::gotoReading()
{
    //chapter = ui->CmbChapter->currentText();
    //verse = "1";
    //ui->TxtTitle->setText(book + " " + chapter);
    openReading();
}

void HomeWindow::openReading()
{
    /*sqlite3* db;
    char* err_msg = NULL, ** qryResult = NULL;
    int row, col, rc = sqlite3_open_v2(AsUtils::DbNameChar(), &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

    if (rc == SQLITE_OK)
    {
        QByteArray bar2 = AsUtils::VerseReadingSql(book, chapter, language).toLocal8Bit();
        char* sqlQuery2 = bar2.data();

        //ui->TxtContent->setPlainText(AsUtils::VerseReadingSql(book, chapter, language));
        rc = sqlite3_get_table(db, sqlQuery2, &qryResult, &row, &col, &err_msg);

        QString Scripture = "";
        int rows = row + 1;

        if (rc == SQLITE_OK)
        {
            for (int r = 1; r < rows; r++)
            {
                QString verseid = *(qryResult + r * col + 0);
                QString reading = *(qryResult + r * col + 2);

                if (r != rows) Scripture.append(reading + "\n");

                ui->CmbVerse->addItem(QString::number(r));
            }
            ui->txtContent->setPlainText(Scripture);

            QString book_chapters = *(qryResult + 1 * col + 3);
            QString book_swahili = *(qryResult + 1 * col + 4);

            if (language == "swahili")
            {
                ui->TxtTitle->setText(book_swahili + " " + chapter);
            }
            chapters = book_chapters.toInt();

            sqlite3_free_table(qryResult);
            sqlite3_close(db);
        }
    }*/
}

void HomeWindow::nextChapter()
{
    if (appReady && ui->cmbChapter->currentIndex() > 0)
    {
        ui->cmbChapter->setCurrentIndex(ui->cmbChapter->currentIndex() - 1);
        gotoReading();
    }
}

void HomeWindow::previousChapter()
{
    if (appReady && ui->cmbChapter->currentIndex() < chapters)
    {
        ui->cmbChapter->setCurrentIndex(ui->cmbChapter->currentIndex() + 1);
        gotoReading();
    }
}

void HomeWindow::on_menuPrint_triggered()
{

}

void HomeWindow::on_menuExit_triggered()
{
    close();
}

void HomeWindow::on_menuNewVerse_triggered()
{

}

void HomeWindow::on_menuEditVerse_triggered()
{

}

void HomeWindow::on_menuBooks_triggered()
{

}

void HomeWindow::on_menuPresent_triggered()
{
    //openPresenter();
}

void HomeWindow::on_menuManageSettings_triggered()
{
    //on_toolbarSettings_triggered();
}

void HomeWindow::on_menuResetSettings_triggered()
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
            loadSettings();
            loadControls();
            break;

        default:
            // should never be reached
            break;
    }
}

void HomeWindow::on_menuHowItWorks_triggered()
{

}

void HomeWindow::on_menuContactUs_triggered()
{

}

void HomeWindow::on_menuAboutThisApp_triggered()
{

}

void HomeWindow::on_toolbarPresent_triggered()
{
    //openPresenter();
}

void HomeWindow::on_toolbarEdit_triggered()
{

}

void HomeWindow::on_toolbarPrevious_triggered()
{

}

void HomeWindow::on_toolbarNext_triggered()
{

}

void HomeWindow::on_toolbarSmaller_triggered()
{
    if (appReady) {
        if ((previewFontSize - 2) > 9)
        {
            previewFontSize = previewFontSize - 2;
            homePrefs.setValue(PrefUtils::prefsPreviewFontSize(), previewFontSize);
            loadSettings();
            loadControls();
        }
    }
}

void HomeWindow::on_toolbarBigger_triggered()
{
    if (appReady) {
        if ((previewFontSize + 2) < 51)
        {
            previewFontSize = previewFontSize + 2;
            homePrefs.setValue(PrefUtils::prefsPreviewFontSize(), previewFontSize);
            loadSettings();
            loadControls();
        }
    }    
}

void HomeWindow::on_toolbarSettings_triggered()
{
    AppOptions preferences(this);
    preferences.exec();
    loadSettings();
    loadControls();
}

void HomeWindow::on_toolbarBold_triggered()
{
    if (appReady) {
        if (previewFontBold)
            previewFontBold = false;
        else
            previewFontBold = true;
        //ui->toolbarBold->setChecked(previewFontBold);

        homePrefs.setValue(PrefUtils::prefsPreviewFontBold(), previewFontBold);
        loadSettings();
        loadControls();
    }    
}

void HomeWindow::on_menuDarkMode_triggered()
{
    if (appReady) {
        if (darkMode)
            darkMode = false;
        else
            darkMode = true;
        //ui->menuDarkMode->setChecked(darkMode);
        //ui->actionDarkMode->setChecked(darkMode);
        homePrefs.setValue(PrefUtils::prefsDarkMode(), darkMode);
        loadSettings();
        loadControls();
    }    
}


void HomeWindow::on_actionDarkMode_triggered()
{
    if (appReady) {
        if (darkMode)
            darkMode = false;
        else
            darkMode = true;
        //ui->menuDarkMode->setChecked(darkMode);
        //ui->actionDarkMode->setChecked(darkMode);
        homePrefs.setValue(PrefUtils::prefsDarkMode(), darkMode);
        loadSettings();
        loadControls();
    }
}

void HomeWindow::on_chkSearchCriteria_stateChanged(int value)
{
    if (appReady) {
        if (searchAll)
            searchAll = false;
        else
            searchAll = true;

        //ui->chkSearchCriteria->setChecked(searchAll);
        //ui->menuSearchAll->setChecked(searchAll);
        homePrefs.setValue(PrefUtils::prefsSearchAllbooks(), searchAll);
    }
}

void HomeWindow::on_menuSearchAll_triggered()
{
    if (appReady) {
        if (searchAll)
            searchAll = false;
        else
            searchAll = true;

        //ui->chkSearchCriteria->setChecked(searchAll);
        //ui->menuSearchAll->setChecked(searchAll);
        homePrefs.setValue(PrefUtils::prefsSearchAllbooks(), searchAll);
    }
}

HomeWindow::~HomeWindow()
{
    delete ui;
}
