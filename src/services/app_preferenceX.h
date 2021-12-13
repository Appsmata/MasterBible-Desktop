#include <QtCore>

#include "../utils/preference_utils.h"

class prefAppUser
{
public:
    static QString get()
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesAppUser() + "_find");
        QString preferenceValue = appDb->getValueOrDefault(
            PrefUtils::preferencesAppUser(),
            PrefDefaults::preferencesAppUser()
        );
        appDb->connectionClose(PrefUtils::preferencesAppUser() + "_find");
        return preferenceValue;
    }

    static void set(QString value)
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesAppUser() + "_change");
        appDb->updateValue(PrefUtils::preferencesAppUser(), value);
        appDb->connectionClose(PrefUtils::preferencesAppUser() + "_change");
    }
};

class prefDarkMode
{
public:
    static bool get()
    {
        bool preferenceValue = false;
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesDarkMode() + "_find");
        QString prefValue = appDb->getValueOrDefault(
            PrefUtils::preferencesDarkMode(),
            PrefDefaults::preferencesDarkMode()
        );
        appDb->connectionClose(PrefUtils::preferencesDarkMode() + "_find");
        if (prefValue == 1) preferenceValue = true;
        return preferenceValue;
    }

    static void set(bool value)
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesDarkMode() + "_change");
        appDb->updateValue(PrefUtils::preferencesDarkMode(), value ? "1" : "0");
        appDb->connectionClose(PrefUtils::preferencesDarkMode() + "_change");
    }
};

class prefEditMode
{
public:
    static bool get()
    {
        bool preferenceValue = false;
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesEditMode() + "_find");
        QString prefValue = appDb->getValueOrDefault(
            PrefUtils::preferencesEditMode(),
            PrefDefaults::preferencesEditMode()
        );
        appDb->connectionClose(PrefUtils::preferencesEditMode() + "_find");
        if (prefValue == 1) preferenceValue = true;
        return preferenceValue;
    }

    static void set(QString value)
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesEditMode() + "_change");
        appDb->updateValue(PrefUtils::preferencesEditMode(), value);
        appDb->connectionClose(PrefUtils::preferencesEditMode() + "_change");
    }
};

class prefInstalledDate
{
public:
    static QString get()
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesInstalledDate() + "_find");
        QString preferenceValue = appDb->getValueOrDefault(
            PrefUtils::preferencesInstalledDate(),
            PrefDefaults::preferencesInstalledDate()
        );
        appDb->connectionClose(PrefUtils::preferencesInstalledDate() + "_find");
        return preferenceValue;
    }

    static void set(bool value)
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesInstalledDate() + "_change");
        appDb->updateValue(PrefUtils::preferencesInstalledDate(), value ? "1" : "0");
        appDb->connectionClose(PrefUtils::preferencesInstalledDate() + "_change");
    }
};

class prefGeneralFontBold
{
public:
    static bool get()
    {
        bool preferenceValue = false;
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesGeneralFontBold() + "_find");
        QString prefValue = appDb->getValueOrDefault(
            PrefUtils::preferencesGeneralFontBold(),
            PrefDefaults::preferencesGeneralFontBold()
        );
        appDb->connectionClose(PrefUtils::preferencesGeneralFontBold() + "_find");
        if (prefValue == 1) preferenceValue = true;
        return preferenceValue;
    }

    static void set(bool value)
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesGeneralFontBold() + "_change");
        appDb->updateValue(PrefUtils::preferencesGeneralFontBold(), value ? "1" : "0");
        appDb->connectionClose(PrefUtils::preferencesGeneralFontBold() + "_change");
    }
};

class prefGeneralFontSize
{
public:
    static int get()
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesGeneralFontSize() + "_find");
        QString preferenceValue = appDb->getValueOrDefault(
            PrefUtils::preferencesGeneralFontSize(),
            PrefDefaults::preferencesGeneralFontSize()
        );
        appDb->connectionClose(PrefUtils::preferencesGeneralFontSize() + "_find");
        return preferenceValue.toInt();
    }

    static void set(int value)
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesGeneralFontSize() + "_change");
        appDb->updateValue(PrefUtils::preferencesGeneralFontSize(), QString::number(value));
        appDb->connectionClose(PrefUtils::preferencesGeneralFontSize() + "_change");
    }
};

class prefGeneralFontType
{
public:
    static int get()
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesGeneralFontType() + "_find");
        QString preferenceValue = appDb->getValueOrDefault(
            PrefUtils::preferencesGeneralFontType(),
            PrefDefaults::preferencesGeneralFontType()
        );
        appDb->connectionClose(PrefUtils::preferencesGeneralFontType() + "_find");
        return preferenceValue.toInt();
    }

    static void set(int value)
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesGeneralFontType() + "_change");
        appDb->updateValue(PrefUtils::preferencesGeneralFontType(), QString::number(value));
        appDb->connectionClose(PrefUtils::preferencesGeneralFontType() + "_change");
    }
};

class prefLanguage
{
public:
    static QString get()
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesLanguage() + "_find");
        QString preferenceValue = appDb->getValueOrDefault(
            PrefUtils::preferencesLanguage(),
            PrefDefaults::preferencesLanguage()
        );
        appDb->connectionClose(PrefUtils::preferencesLanguage() + "_find");
        return preferenceValue;
    }

    static void set(QString value)
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesLanguage() + "_change");
        appDb->updateValue(PrefUtils::preferencesLanguage(), value);
        appDb->connectionClose(PrefUtils::preferencesLanguage() + "_change");
    }
};

class prefLastWindowStartup
{
public:
    static int get()
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesLastWindowStartup() + "_find");
        QString preferenceValue = appDb->getValueOrDefault(
            PrefUtils::preferencesLastWindowStartup(),
            PrefDefaults::preferencesLastWindowStartup()
        );
        appDb->connectionClose(PrefUtils::preferencesLastWindowStartup() + "_find");
        return preferenceValue.toInt();
    }

    static void set(int value)
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesLastWindowStartup() + "_change");
        appDb->updateValue(PrefUtils::preferencesLastWindowStartup(), QString::number(value));
        appDb->connectionClose(PrefUtils::preferencesLastWindowStartup() + "_change");
    }
};

class prefLastWindowWidth
{
public:
    static int get()
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesLastWindowWidth() + "_find");
        QString preferenceValue = appDb->getValueOrDefault(
            PrefUtils::preferencesLastWindowWidth(),
            PrefDefaults::preferencesLastWindowWidth()
        );
        appDb->connectionClose(PrefUtils::preferencesLastWindowWidth() + "_find");
        return preferenceValue.toInt();
    }

    static void set(int value)
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesLastWindowWidth() + "_change");
        appDb->updateValue(PrefUtils::preferencesLastWindowWidth(), QString::number(value));
        appDb->connectionClose(PrefUtils::preferencesLastWindowWidth() + "_change");
    }
};

class prefListFontBold
{
public:
    static bool get()
    {
        bool preferenceValue = false;
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesListFontBold() + "_find");
        QString prefValue = appDb->getValueOrDefault(
            PrefUtils::preferencesListFontBold(),
            PrefDefaults::preferencesListFontBold()
        );
        appDb->connectionClose(PrefUtils::preferencesListFontBold() + "_find");
        if (prefValue == 1) preferenceValue = true;
        return preferenceValue;
    }

    static void set(bool value)
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesListFontBold() + "_change");
        appDb->updateValue(PrefUtils::preferencesListFontBold(), value ? "1" : "0");
        appDb->connectionClose(PrefUtils::preferencesListFontBold() + "_change");
    }
};

class prefPresentFontBold
{
public:
    static bool get()
    {
        bool preferenceValue = false;
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesPresentFontBold() + "_find");
        QString prefValue = appDb->getValueOrDefault(
            PrefUtils::preferencesPresentFontBold(),
            PrefDefaults::preferencesPresentFontBold()
        );
        appDb->connectionClose(PrefUtils::preferencesPresentFontBold() + "_find");
        if (prefValue == 1) preferenceValue = true;
        return preferenceValue;
    }

    static void set(bool value)
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesPresentFontBold() + "_change");
        appDb->updateValue(PrefUtils::preferencesPresentFontBold(), value ? "1" : "0");
        appDb->connectionClose(PrefUtils::preferencesPresentFontBold() + "_change");
    }
};

class prefPresentFontSize
{
public:
    static int get()
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesPresentFontSize() + "_find");
        QString preferenceValue = appDb->getValueOrDefault(
            PrefUtils::preferencesPresentFontSize(),
            PrefDefaults::preferencesPresentFontSize()
        );
        appDb->connectionClose(PrefUtils::preferencesPresentFontSize() + "_find");
        return preferenceValue.toInt();
    }

    static void set(int value)
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesPresentFontSize() + "_change");
        appDb->updateValue(PrefUtils::preferencesPresentFontSize(), QString::number(value));
        appDb->connectionClose(PrefUtils::preferencesPresentFontSize() + "_change");
    }
};

class prefPresentFontType
{
public:
    static int get()
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesPresentFontType() + "_find");
        QString preferenceValue = appDb->getValueOrDefault(
            PrefUtils::preferencesPresentFontType(),
            PrefDefaults::preferencesPresentFontType()
        );
        appDb->connectionClose(PrefUtils::preferencesPresentFontType() + "_find");
        return preferenceValue.toInt();
    }

    static void set(int value)
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesPresentFontType() + "_change");
        appDb->updateValue(PrefUtils::preferencesPresentFontType(), QString::number(value));
        appDb->connectionClose(PrefUtils::preferencesPresentFontType() + "_change");
    }
};

class prefPreviewFontSize
{
public:
    static int get()
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesPreviewFontSize() + "_find");
        QString preferenceValue = appDb->getValueOrDefault(
            PrefUtils::preferencesPreviewFontSize(),
            PrefDefaults::preferencesPreviewFontSize()
        );
        appDb->connectionClose(PrefUtils::preferencesPreviewFontSize() + "_find");
        return preferenceValue.toInt();
    }

    static void set(int value)
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesPreviewFontSize() + "_change");
        appDb->updateValue(PrefUtils::preferencesPreviewFontSize(), QString::number(value));
        appDb->connectionClose(PrefUtils::preferencesPreviewFontSize() + "_change");
    }
};

class prefPreviewFontBold
{
public:
    static bool get()
    {
        bool preferenceValue = false;
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesPreviewFontBold() + "_find");
        QString prefValue = appDb->getValueOrDefault(
            PrefUtils::preferencesPreviewFontBold(),
            PrefDefaults::preferencesPreviewFontBold()
        );
        appDb->connectionClose(PrefUtils::preferencesPreviewFontBold() + "_find");
        if (prefValue == 1) preferenceValue = true;
        return preferenceValue;
    }

    static void set(bool value)
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesPreviewFontBold() + "_change");
        appDb->updateValue(PrefUtils::preferencesPreviewFontBold(), value ? "1" : "0");
        appDb->connectionClose(PrefUtils::preferencesPreviewFontBold() + "_change");
    }
};

class prefPreviewFontType
{
public:
    static int get()
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesPreviewFontType() + "_find");
        QString preferenceValue = appDb->getValueOrDefault(
            PrefUtils::preferencesPreviewFontType(),
            PrefDefaults::preferencesPreviewFontType()
        );
        appDb->connectionClose(PrefUtils::preferencesPreviewFontType() + "_find");
        return preferenceValue.toInt();
    }

    static void set(int value)
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesPreviewFontType() + "_change");
        appDb->updateValue(PrefUtils::preferencesPreviewFontType(), QString::number(value));
        appDb->connectionClose(PrefUtils::preferencesPreviewFontType() + "_change");
    }
};

class prefSearchAllbooks
{
public:
    static bool get()
    {
        bool preferenceValue = false;
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesSearchAllbooks() + "_find");
        QString prefValue = appDb->getValueOrDefault(
            PrefUtils::preferencesSearchAllbooks(),
            PrefDefaults::preferencesSearchAllbooks()
        );
        appDb->connectionClose(PrefUtils::preferencesSearchAllbooks() + "_find");
        if (prefValue == 1) preferenceValue = true;
        return preferenceValue;
    }

    static void set(bool value)
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesSearchAllbooks() + "_change");
        appDb->updateValue(PrefUtils::preferencesSearchAllbooks(), value ? "1" : "0");
        appDb->connectionClose(PrefUtils::preferencesSearchAllbooks() + "_change");
    }
};

class prefSelectedBook
{
public:
    static int get()
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesSelectedBook() + "_find");
        QString preferenceValue = appDb->getValueOrDefault(
            PrefUtils::preferencesSelectedBook(),
            PrefDefaults::preferencesSelectedBook()
        );
        appDb->connectionClose(PrefUtils::preferencesSelectedBook() + "_find");
        return preferenceValue.toInt();
    }

    static void set(int value)
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesSelectedBook() + "_change");
        appDb->updateValue(PrefUtils::preferencesSelectedBook(), QString::number(value));
        appDb->connectionClose(PrefUtils::preferencesSelectedBook() + "_change");
    }
};

class prefSelectedSong
{
public:
    static int get()
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesSelectedSong() + "_find");
        QString preferenceValue = appDb->getValueOrDefault(
            PrefUtils::preferencesSelectedSong(),
            PrefDefaults::preferencesSelectedSong()
        );
        appDb->connectionClose(PrefUtils::preferencesSelectedSong() + "_find");
        return preferenceValue.toInt();
    }

    static void set(int value)
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesSelectedSong() + "_change");
        appDb->updateValue(PrefUtils::preferencesSelectedSong(), QString::number(value));
        appDb->connectionClose(PrefUtils::preferencesSelectedSong() + "_change");
    }
};

class prefShowHelpFirst
{
public:
    static bool get()
    {
        bool preferenceValue = false;
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesShowHelpFirst() + "_find");
        QString prefValue = appDb->getValueOrDefault(
            PrefUtils::preferencesShowHelpFirst(),
            PrefDefaults::preferencesShowHelpFirst()
        );
        appDb->connectionClose(PrefUtils::preferencesShowHelpFirst() + "_find");
        if (prefValue == 1) preferenceValue = true;
        return preferenceValue;
    }

    static void set(bool value)
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesShowHelpFirst() + "_change");
        appDb->updateValue(PrefUtils::preferencesShowHelpFirst(), value ? "1" : "0");
        appDb->connectionClose(PrefUtils::preferencesShowHelpFirst() + "_change");
    }
};

class prefShowStartpage
{
public:
    static bool get()
    {
        bool preferenceValue = false;
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesShowStartpage() + "_find");
        QString prefValue = appDb->getValueOrDefault(
            PrefUtils::preferencesShowStartpage(),
            PrefDefaults::preferencesShowStartpage()
        );
        appDb->connectionClose(PrefUtils::preferencesShowStartpage() + "_find");
        if (prefValue == 1) preferenceValue = true;
        return preferenceValue;
    }

    static void set(bool value)
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesShowStartpage() + "_change");
        appDb->updateValue(PrefUtils::preferencesShowStartpage(), value ? "1" : "0");
        appDb->connectionClose(PrefUtils::preferencesShowStartpage() + "_change");
    }
};

class prefTabletMode
{
public:
    static bool get()
    {
        bool preferenceValue = false;
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesTabletMode() + "_find");
        QString prefValue = appDb->getValueOrDefault(
            PrefUtils::preferencesTabletMode(),
            PrefDefaults::preferencesTabletMode()
        );
        appDb->connectionClose(PrefUtils::preferencesTabletMode() + "_find");
        if (prefValue == 1) preferenceValue = true;
        return preferenceValue;
    }

    static void set(bool value)
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesTabletMode() + "_change");
        appDb->updateValue(PrefUtils::preferencesTabletMode(), value ? "1" : "0");
        appDb->connectionClose(PrefUtils::preferencesTabletMode() + "_change");
    }
};

class prefTheme
{
public:
    static int get()
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesTheme() + "_find");
        QString preferenceValue = appDb->getValueOrDefault(
            PrefUtils::preferencesTheme(),
            PrefDefaults::preferencesTheme()
        );
        appDb->connectionClose(PrefUtils::preferencesTheme() + "_find");
        return preferenceValue.toInt();
    }

    static void set(int value)
    {
        AppDatabase* appDb = new AppDatabase();
        appDb->connectionOpen(PrefUtils::preferencesTheme() + "_change");
        appDb->updateValue(PrefUtils::preferencesTheme(), QString::number(value));
        appDb->connectionClose(PrefUtils::preferencesTheme() + "_change");
    }
};
