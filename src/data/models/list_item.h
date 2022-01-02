#ifndef LIST_ITEM_H
#define LIST_ITEM_H

#include <QMetaType>

typedef enum {
    S_RED,
    S_BLUE,
    S_YELLOW,
} ItemStatus;

struct ListItem {
    QString image;
    QString title;
    QString content;
};

Q_DECLARE_METATYPE(ListItem)

#endif // LIST_ITEM_H
