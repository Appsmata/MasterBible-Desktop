#ifndef SONGDELEGATE_H
#define SONGDELEGATE_H

#include <QStyledItemDelegate>
#include <QModelIndex>
#include <QStandardItemModel>

class SongDelegate : public QStyledItemDelegate
{
	Q_OBJECT
signals:

public:
	explicit SongDelegate(QObject* parent = nullptr);

	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const Q_DECL_OVERRIDE;
	QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const Q_DECL_OVERRIDE;

	~SongDelegate();
};

#endif // SONGDELEGATE_H