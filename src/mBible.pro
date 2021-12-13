QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    data/app_database.cpp \
    data/delegates/book_delegate.cpp \
    data/delegates/listdelegate.cpp \
    data/delegates/pref_delegate.cpp \
    data/delegates/song_delegate.cpp \
    main.cpp \
    ui/dialogs/app_about.cpp \
    ui/dialogs/app_hints.cpp \
    ui/dialogs/app_options.cpp \
    ui/dialogs/book_select.cpp \
    ui/dialogs/how_it_works.cpp \
    ui/home_window.cpp \
    ui/presentor_window.cpp

HEADERS += \
    data/app_database.h \
    data/delegates/book_delegate.h \
    data/delegates/listdelegate.h \
    data/delegates/pref_delegate.h \
    data/delegates/song_delegate.h \
    data/models/book.h \
    data/models/history.h \
    data/models/list_item.h \
    data/models/preference.h \
    data/models/search.h \
    data/models/song.h \
    services/app_preference.h \
    services/exception.h \
    services/task.h \
    ui/dialogs/app_about.h \
    ui/dialogs/app_hints.h \
    ui/dialogs/app_options.h \
    ui/dialogs/book_select.h \
    ui/dialogs/how_it_works.h \
    ui/home_window.h \
    ui/presentor_window.h \
    utils/api_utils.h \
    utils/app_utils.h \
    utils/db_utils.h \
    utils/pref_utils.h

FORMS += \
    ui/dialogs/app_about.ui \
    ui/dialogs/app_hints.ui \
    ui/dialogs/app_options.ui \
    ui/dialogs/book_select.ui \
    ui/dialogs/how_it_works.ui \
    ui/home_window.ui \
    ui/presentor_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res/icons.qrc \
    res/images.qrc \
    res/themes.qrc

DISTFILES += \
    ui/home_window.ui.bak

win32:RC_ICONS += res\icons\appicon.ico
