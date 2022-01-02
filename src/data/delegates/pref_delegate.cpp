#include <QPainterPath>
#include <QPainter>
#include <QStyledItemDelegate>
#include <QStyle>
#include <QEvent>
#include <QDebug>

#include "pref_delegate.h"
#include "data/models/preference.h"

PrefDelegate::PrefDelegate(QObject* parent) : QStyledItemDelegate(parent) { }

PrefDelegate::~PrefDelegate()
{

}

void PrefDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (index.isValid()) {
        painter->save();
        QVariant var = index.data(Qt::UserRole + 1);
        Preference pref = var.value<Preference>();

        // item Rectangular area
        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth(option.rect.width() - 1);
        rect.setHeight(option.rect.height() - 1);

        QPainterPath path;
        path.moveTo(rect.topRight());
        path.lineTo(rect.topLeft());
        path.quadTo(rect.topLeft(), rect.topLeft());
        path.lineTo(rect.bottomLeft());
        path.quadTo(rect.bottomLeft(), rect.bottomLeft());
        path.lineTo(rect.bottomRight());
        path.quadTo(rect.bottomRight(), rect.bottomRight());
        path.lineTo(rect.topRight());
        path.quadTo(rect.topRight(), rect.topRight());

        // Change background color when hovering or selecting
        if (option.state.testFlag(QStyle::State_MouseOver)) {
            painter->setPen(QPen(QColor("#FF4500")));
            painter->setBrush(QColor("#FF4500"));
            painter->drawPath(path);
        }
        else if (option.state.testFlag(QStyle::State_Selected)) {
            painter->setPen(QPen(QColor("#FF7C00")));
            painter->setBrush(QColor("#FF7C00"));
            painter->drawPath(path);
        }
        else {
            painter->setPen(QPen(QColor("#FFFFFF")));
            painter->setBrush(QColor("#FFFFFF"));
            painter->drawPath(path);
        }

        QRectF iconRect, itemText1, itemText2;

        itemText1 = QRect(5, rect.top(), rect.width() - 10, 25);
        itemText2 = QRect(itemText1.left(), itemText1.bottom(), rect.width() - 10 - iconRect.width(), 20);

        painter->setPen(QPen(QColor(Qt::black)));
        painter->setFont(QFont("Trebuchet MS", 14, QFont::Bold));
        painter->drawText(itemText1, pref.title);

        painter->setPen(QPen(Qt::black));
        painter->setFont(QFont("Trebuchet MS", 12, 0));
        painter->drawText(itemText2, pref.content);

        painter->restore();
    }
}

QSize PrefDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Q_UNUSED(index)
        return QSize(option.rect.width(), 50);
}
