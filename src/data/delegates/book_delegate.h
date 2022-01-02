#ifndef BOOKDELEGATE_H
#define BOOKDELEGATE_H

#include <QObject>

class BookDelegate : public QObject
{
    Q_OBJECT
public:
    explicit BookDelegate(QObject *parent = nullptr);

signals:

};

#endif // BOOKDELEGATE_H
