#ifndef PREFDELEGATE_H
#define PREFDELEGATE_H

#include <QStyledItemDelegate>
#include <QModelIndex>
#include <QStandardItemModel>

class PrefDelegate : public QStyledItemDelegate
{
    Q_OBJECT
signals:

public:
    explicit PrefDelegate(QObject* parent = nullptr);

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const Q_DECL_OVERRIDE;

    ~PrefDelegate();
};

#endif // PREFDELEGATE_H
