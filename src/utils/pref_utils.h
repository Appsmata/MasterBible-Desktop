#include <QtCore>

#include "app_utils.h"
#include "../data/models/preference.h"

class PrefUtils
{
public:
    static QString prefsAppUser() { return "general/app_user"; }
    static QString prefsDarkMode() { return "general/dark_mode"; }
    static QString prefsEditMode() { return "general/edit_mode"; }
    static QString prefsFirstInstall() { return "general/first_install"; }
    static QString prefsGeneralFontBold() { return "general/font_bold"; }
    static QString prefsGeneralFontSize() { return "general/font_size"; }
    static QString prefsGeneralFontType() { return "general/font_type"; }
    static QString prefsInstalledDate() { return "general/installed_date"; }
    static QString prefsLanguage() { return "general/app_language"; }
    static QString prefsLastWindowStartup() { return "general/last_window_startup"; }
    static QString prefsLastWindowWidth() { return "general/last_window_width"; }
    static QString prefsListFontBold() { return "general/list_font_bold"; }
    static QString prefsPresentFontBold() { return "present/font_bold"; }
    static QString prefsPresentFontSize() { return "present/font_size"; }
    static QString prefsPresentFontType() { return "present/font_type"; }
    static QString prefsPresentTheme() { return "present/present_theme"; }
    static QString prefsPreviewFontBold() { return "preview/font_bold"; }
    static QString prefsPreviewFontSize() { return "preview/font_size"; }
    static QString prefsPreviewFontType() { return "preview/font_type"; }
    static QString prefsSearchAllbooks() { return "general/search_all_books"; }
    static QString prefsSelectedBook() { return "general/selected_book"; }
    static QString prefsSelectedSong() { return "general/selected_song"; }
    static QString prefsShowHelpFirst() { return "general/show_help_first"; }
    static QString prefsShowStartpage() { return "general/show_startpage"; }
    static QString prefsTabletMode() { return "general/tablet_mode"; }

    static std::vector<QString> preferencesLanguages()
    {
        std::vector<QString> languages;

        languages.push_back("English");
        languages.push_back("Swahili");
        languages.push_back("French");

        return languages;
    }

    static std::vector<QString> preferencesFontTypes()
    {
        std::vector<QString> fonts;

        fonts.push_back("Arial");
        fonts.push_back("Calibri");
        fonts.push_back("Century Gothic");
        fonts.push_back("Comic Sans MS");
        fonts.push_back("Corbel");
        fonts.push_back("Courier New");
        fonts.push_back("Palatino");
        fonts.push_back("Linotype");
        fonts.push_back("Tahoma");
        fonts.push_back("Tempus Sans ITC");
        fonts.push_back("Times New Roman");
        fonts.push_back("Trebuchet MS");
        fonts.push_back("Verdana");

        return fonts;
    }

    static std::vector<Preference> preferencePages()
    {
        std::vector<Preference> pages;
        Preference page1, page2, page3;

        page1.category = 1;
        page1.title = "General Options";
        page1.content = "Essential preferences";

        page2.category = 2;
        page2.title = "App Font Options";
        page2.content = "Font management";

        page3.category = 3;
        page3.title = "Presentation Themes";
        page3.content = "Set your preffered theme";

        pages.push_back(page1);
        pages.push_back(page2);
        pages.push_back(page3);
        return pages;
    }

    static std::vector<Preference> preferenceList()
    {
        std::vector<Preference> prefs;
        Preference pref1, pref2, pref3, pref4, pref5, pref6, pref7, pref8, pref9, pref10;

        pref1.category = 1;
        pref1.preferenceid = 1;
        pref1.title = "Tablet Mode";
        pref1.content = "Use touchscreen mode";
        pref1.key = "preferences_tablet_mode";

        pref2.category = 1;
        pref2.preferenceid = 2;
        pref2.title = "Search Criteria";
        pref2.content = "Search all songbooks";
        pref2.key = "preferences_search_all_books";

        pref3.category = 1;
        pref3.preferenceid = 3;
        pref3.title = "Preffered Language";
        pref3.content = "Choose app language";
        pref3.key = "preferences_language";

        pref4.category = 1;
        pref4.preferenceid = 4;
        pref4.title = "Dark Mode";
        pref4.content = "Enable dark mode";
        pref4.key = "preferences_dark_mode";

        pref5.category = 1;
        pref5.preferenceid = 5;
        pref5.title = "Your Name/Name of your Church";
        pref5.content = "App User Name";
        pref5.key = "preferences_app_user";

        pref6.category = 1;
        pref6.preferenceid = 6;
        pref6.title = "Song Edit Mode";
        pref6.content = "Enable etitting of songs";
        pref6.key = "preferences_edit_mode";

        pref7.category = 2;
        pref7.preferenceid = 7;
        pref7.title = "General App font";
        pref7.content = "";
        pref7.key = "preferences_general_font";

        pref8.category = 2;
        pref8.preferenceid = 8;
        pref8.title = "Song Preview Font";
        pref8.content = "";
        pref8.key = "preferences_preview_font";

        pref9.category = 1;
        pref9.preferenceid = 9;
        pref9.title = "Song Present Font";
        pref9.content = "";
        pref9.key = "preferences_present_font";

        pref10.category = 1;
        pref10.preferenceid = 10;
        pref10.title = "Presentation Themes";
        pref10.content = "";
        pref10.key = "preferences_theme";

        prefs.push_back(pref1);
        prefs.push_back(pref2);
        prefs.push_back(pref3);
        prefs.push_back(pref4);
        prefs.push_back(pref5);
        prefs.push_back(pref6);
        prefs.push_back(pref7);
        prefs.push_back(pref8);
        prefs.push_back(pref9);
        prefs.push_back(pref10);
        return prefs;
    }

    static QString appUserDefault() { return "App User"; }

    static bool defaultPrefs() {
        QSettings defaultPrefs(AppUtils::appName(), AppUtils::orgDomain());

        defaultPrefs.setValue(PrefUtils::prefsTabletMode(), false);
        defaultPrefs.setValue(PrefUtils::prefsDarkMode(), false);
        defaultPrefs.setValue(PrefUtils::prefsEditMode(), false);
        defaultPrefs.setValue(PrefUtils::prefsSearchAllbooks(), true);

        defaultPrefs.setValue(PrefUtils::prefsLanguage(), 0);
        defaultPrefs.setValue(PrefUtils::prefsAppUser(), PrefUtils::appUserDefault());

        defaultPrefs.setValue(PrefUtils::prefsGeneralFontType(), 11);
        defaultPrefs.setValue(PrefUtils::prefsGeneralFontSize(), 12);
        defaultPrefs.setValue(PrefUtils::prefsGeneralFontBold(), false);

        defaultPrefs.setValue(PrefUtils::prefsPreviewFontType(), 11);
        defaultPrefs.setValue(PrefUtils::prefsPreviewFontSize(), 18);
        defaultPrefs.setValue(PrefUtils::prefsPreviewFontBold(), false);

        defaultPrefs.setValue(PrefUtils::prefsPresentFontType(), 11);
        defaultPrefs.setValue(PrefUtils::prefsPresentFontSize(), 30);
        defaultPrefs.setValue(PrefUtils::prefsPresentFontBold(), true);

        defaultPrefs.setValue(PrefUtils::prefsPresentTheme(), 0);

        defaultPrefs.setValue(PrefUtils::prefsFirstInstall(), true);

        return true;
    }

};
