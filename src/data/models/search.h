#ifndef SEARCH_H
#define SEARCH_H

#include <QMetaType>

struct Search {
    int historyid;
    int type;
    int item;
    QString title;
    QString extra;
    QString created;
};

Q_DECLARE_METATYPE(Search)

#endif // SEARCH_H
