#ifndef VERSEDELEGATE_H
#define VERSEDELEGATE_H

#include <QStyledItemDelegate>
#include <QModelIndex>
#include <QStandardItemModel>

class VerseDelegete : public QStyledItemDelegate
{
	Q_OBJECT
signals:

public:
    explicit VerseDelegete(QObject* parent = nullptr);

	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const Q_DECL_OVERRIDE;
	QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const Q_DECL_OVERRIDE;

    ~VerseDelegete();
};

#endif // VERSEDELEGATE_H
