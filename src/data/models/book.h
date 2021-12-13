#ifndef BOOK_H
#define BOOK_H

#include <QMetaType>

struct Book {
    int bookid;
    int categoryid;
    int enabled;
    QString title;
    QString tags;
    int qcount;
    int position;
    QString content;
    QString backpath;
    QString created;
    QString updated;
};

Q_DECLARE_METATYPE(Book)

#endif // BOOK_H
