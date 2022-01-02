#include <QApplication>
#include <QFile>
#include <QSplashScreen>
#include <QThread>

#include "data/app_database.h"
#include "utils/app_utils.h"
#include "utils/pref_utils.h"
#include "ui/home_window.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QPixmap pixmap("res/images/splash.png");
    QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);
    splash.show();

    app.thread()->sleep(3);
    app.processEvents();
    splash.close();

    //Check if database exists otherwise create it
    AppDatabase* appDb = new AppDatabase();
    appDb->checkDatabase();

    QSettings preferences(AppUtils::appName(), AppUtils::orgDomain());

    if (!preferences.value(PrefUtils::prefsFirstInstall()).toBool())
    {
        QCoreApplication::setApplicationName(AppUtils::appName());
        QCoreApplication::setApplicationVersion(AppUtils::appVersion());
        QCoreApplication::setOrganizationName(AppUtils::orgName());
        QCoreApplication::setOrganizationDomain(AppUtils::orgDomain());

        PrefUtils::defaultPrefs();
    }

    HomeWindow home;
    home.showMaximized();
    return app.exec();
}
