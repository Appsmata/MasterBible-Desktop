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
#include "../data/delegates/song_delegate.h"
#include "../ui/dialogs/app_options.h"
#include "../ui/dialogs/book_select.h"
#include "../ui/presentor_window.h"
#include "../utils/app_utils.h"
#include "../utils/pref_utils.h"

int previewFontSize, previewFontType, selectedbook;
bool appReady, editMode, searchAll, darkMode, previewFontBold;
QFont previewFontHome, generalFontHome;

std::vector<Book> books;
std::vector<Song> songs, filters;
QString selected_book, selected_song, search_term;
QStandardItemModel* songModel = new QStandardItemModel();

QSettings homePrefs(AppUtils::appName(), AppUtils::orgDomain());

HomeWindow::HomeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HomeWindow)
{
    ui->setupUi(this);
    appReady = false;
    ui->SplitterMain->setStretchFactor(1, 3);

    QString appNameUser = QCoreApplication::applicationName() + " " + QCoreApplication::applicationVersion();
    appNameUser.append(" | " + homePrefs.value(PrefUtils::prefsAppUser()).toString());
    this->setWindowTitle(appNameUser);

    loadSettings();
    loadControls();
    requestData();
    appReady = true;
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
    /*if (appDb->isDataLoaded()) {

    }
    else {
        BookSelect bookSelect(this);
        bookSelect.exec();
        //loadData();
    }*/
    if (populateSongbooks())
    {
        if (ui->cmbSongbooks->count() > 0)
        {
            appDb->connectionOpen("songs");
            songs = appDb->fetchSongs();
            appDb->connectionClose("songs");
            populateSongLists(0);
            appReady = true;
        }
        else
        {
            //AsBase::WriteLogs("Data", "Database is empty, resorting to user actions", "", "");
        }
    }
    else {
        QMessageBox::warning(this, qApp->applicationName(), tr("Oops! vSongBook could not generate view due to unknown error at the moment"));
    }
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
    ui->chkSearchCriteria->setChecked(searchAll);
    ui->menuSearchAll->setChecked(searchAll);
    ui->actionDarkMode->setChecked(darkMode);
    ui->menuDarkMode->setChecked(darkMode);

    ui->txtSearch->setFont(generalFontHome);
    ui->cmbSongbooks->setFont(generalFontHome);
    ui->chkSearchCriteria->setFont(generalFontHome);

    ui->txtTitle->setFont(previewFontHome);
    ui->txtContent->setFont(previewFontHome);
    ui->txtAlias->setFont(previewFontHome);

    if (darkMode)
        changeStyle(1);
    else
        changeStyle(0);
}

// Changing of font of the song preview
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

bool HomeWindow::populateSongbooks()
{
    bool retval = false;

    appDb->connectionOpen("books");
    books = appDb->fetchBooks();
    appDb->connectionClose("books");

    if (books.size() != 0)
    {
        for (size_t i = 0; i < books.size(); i++)
        {
            ui->cmbSongbooks->addItem(books[i].title);
        }
        retval = true;
    }
    return true;
}

void HomeWindow::populateSongLists(size_t book)
{
    if (book == 0 || book < books.size())
    {
        if (songs.size() != 0)
        {

            filters.clear();
            songModel->clear();

            for (size_t i = 0; i < songs.size(); i++)
            {
                if (songs[i].categoryid == books[book].categoryid)
                {
                    filters.push_back(songs[i]);
                    QStandardItem* songItem = new QStandardItem;
                    songItem->setData(QVariant::fromValue(songs[i]), Qt::UserRole + 1);
                    songModel->appendRow(songItem);
                }
            }
            filterSonglists();
        }
    }
}

void HomeWindow::populateSongSearch(QString SearchStr)
{
    if (SearchStr.size() > 0)
    {
        if (songs.size() != 0)
        {
            filters.clear();
            songModel->clear();

            if (SearchStr.size() < 5)
            {
                if (SearchStr.toInt() != 0)
                {
                    for (size_t i = 0; i < songs.size(); i++)
                    {
                        if (songs[i].number == SearchStr.toInt())
                        {
                            filters.push_back(songs[i]);
                            QStandardItem* songItem = new QStandardItem;
                            songItem->setData(QVariant::fromValue(songs[i]), Qt::UserRole + 1);
                            songModel->appendRow(songItem);
                        }
                    }
                }
                else searchSonglists(SearchStr);
            }
            else searchSonglists(SearchStr);
            filterSonglists();
        }
    }
}

void HomeWindow::searchSonglists(QString SearchStr)
{
    for (size_t i = 0; i < songs.size(); i++)
    {
        if (songs[i].title.toLower().contains(SearchStr.toLower()) ||
                songs[i].alias.toLower().contains(SearchStr.toLower()) ||
                songs[i].content.toLower().contains(SearchStr.toLower()))
        {
            filters.push_back(songs[i]);
            QStandardItem* songItem = new QStandardItem;
            songItem->setData(QVariant::fromValue(songs[i]), Qt::UserRole + 1);
            songModel->appendRow(songItem);
        }
    }
}

void HomeWindow::filterSonglists()
{
    if (filters.size() != 0)
    {
        SongDelegate* songDelegate = new SongDelegate(this);
        ui->lstResults->setItemDelegate(songDelegate);
        ui->lstResults->setModel(songModel);
        ui->lstResults->setSpacing(1);
        ui->lstResults->setCurrentIndex(songModel->index(0, 0));
        openSongPreview(songModel->index(0, 0));
    }
}

void HomeWindow::openSongPreview(const QModelIndex& index)
{
    int song = index.row();
    QString songTitle = AppUtils::replaceView(filters[song].title);
    QString songAlias = AppUtils::replaceView(filters[song].alias);
    QString songContent = AppUtils::replaceView(filters[song].content);

    homePrefs.setValue(PrefUtils::prefsSelectedSong(), filters[song].songid);

    ui->txtTitle->setText(songTitle);
    ui->txtContent->setPlainText(songContent);

    if (songAlias.length() < 3)
    {
        ui->txtAlias->hide();
    }
    else
    {
        ui->txtAlias->show();
        ui->txtAlias->setText(songAlias);
    }
}

// Open the presentor window
void HomeWindow::openPresenter()
{
    PresentorWindow* present = new PresentorWindow();
    present->showFullScreen();
}

void HomeWindow::on_txtSearch_textChanged(const QString &arg1)
{
    populateSongSearch(arg1);
}

void HomeWindow::on_txtSearch_returnPressed()
{
    populateSongSearch(ui->txtSearch->text());
}

void HomeWindow::on_cmbSongbooks_currentIndexChanged(int index)
{
    if (appReady)
        populateSongLists(index);
}

void HomeWindow::on_lstResults_clicked(const QModelIndex &index)
{
    openSongPreview(index);
}

void HomeWindow::on_lstResults_doubleClicked(const QModelIndex &index)
{
    openSongPreview(index);
    openPresenter();
}

void HomeWindow::on_menuPrint_triggered()
{

}

void HomeWindow::on_menuExit_triggered()
{
    close();
}

void HomeWindow::on_menuNewSong_triggered()
{

}

void HomeWindow::on_menuEditSong_triggered()
{

}

void HomeWindow::on_menuBooks_triggered()
{

}

void HomeWindow::on_menuPresent_triggered()
{
    openPresenter();
}

void HomeWindow::on_menuManageSettings_triggered()
{
    on_toolbarSettings_triggered();
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
    openPresenter();
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
        ui->toolbarBold->setChecked(previewFontBold);

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
        ui->menuDarkMode->setChecked(darkMode);
        ui->actionDarkMode->setChecked(darkMode);
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
        ui->menuDarkMode->setChecked(darkMode);
        ui->actionDarkMode->setChecked(darkMode);
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

        ui->chkSearchCriteria->setChecked(searchAll);
        ui->menuSearchAll->setChecked(searchAll);
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

        ui->chkSearchCriteria->setChecked(searchAll);
        ui->menuSearchAll->setChecked(searchAll);
        homePrefs.setValue(PrefUtils::prefsSearchAllbooks(), searchAll);
    }
}

HomeWindow::~HomeWindow()
{
    delete ui;
}
