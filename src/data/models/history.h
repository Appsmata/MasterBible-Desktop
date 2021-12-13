#ifndef HISTORY_H
#define HISTORY_H

#include <QMetaType>

struct History {
    int historyid;
    int type;
    int item;
    QString title;
    QString extra;
    QString created;
};

Q_DECLARE_METATYPE(History)

#endif // HISTORY_H
