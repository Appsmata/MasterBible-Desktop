#ifndef PREFERENCE_H
#define PREFERENCE_H

#include <QMetaType>

struct Preference {
    int preferenceid;
    int category;
    QString title;
    QString content;
    QString key;
    QString created;
    QString updated;
};

Q_DECLARE_METATYPE(Preference)

#endif // PREFERENCE_H
