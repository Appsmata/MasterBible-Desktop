#ifndef LISTDELEGATE_H
#define LISTDELEGATE_H

#include <QObject>

class ListDelegate : public QObject
{
    Q_OBJECT
public:
    explicit ListDelegate(QObject *parent = nullptr);

signals:

};

#endif // LISTDELEGATE_H
