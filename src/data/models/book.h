#ifndef BOOK_H
#define BOOK_H

#include <QMetaType>

struct Book {
    int bookid;
    int testament;
    QString code;
    QString title;
    int chapters;
    QString swahili;
};

Q_DECLARE_METATYPE(Book)

#endif // BOOK_H
