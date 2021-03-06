#include "eventitem.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QtGui/QtGui>

EventItem::EventItem(QGraphicsItem* parent, Event& event)
        : mEvent(event), QObject(), QGraphicsRectItem(parent) {
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    mBrush = QBrush(QColor("#89A"));
    mBrushSelected = QBrush(QColor("#9AB"));

    mPenBorder = QPen(Qt::black, 1);
    mPenBorder.setCosmetic(true);
    mPenBorderSelected = QPen(Qt::white, 1);
    mPenBorderSelected.setCosmetic(true);

    onEventChanged(event);

    event.connect(&event, &Event::changed, this, &EventItem::onEventChanged);

}

void EventItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    // Inverse scale
    auto mtx = painter->matrix();
    qreal sx = mtx.m11();
    qreal sy = mtx.m22();
    qreal px = mtx.dx();
    qreal py = mtx.dy();
    qreal pw = rect().width() * sx;
    qreal ph = rect().height() * sy;
    QRectF viewRect(px, py, pw, ph);

    painter->setPen(isSelected() ? mPenBorderSelected : mPenBorder);
    painter->setBrush(isSelected() ? mBrushSelected : mBrush);


    painter->save();

    painter->drawRect(rect().adjusted(0, 0, -1 / sx, -1 / sy));

    painter->resetTransform();

    QRectF textRect = viewRect.adjusted(3, 3, -3, -3);

    auto text = painter->fontMetrics().elidedText(mEvent.name(), Qt::ElideRight, textRect.width());


//	painter->drawText(textMargin.x(), rect().height() - textMargin.y(), text);
    painter->drawText(textRect, text);

    painter->restore();
}

void EventItem::onEventChanged(Event& event) {
    setRect(0, 0, event.length(), event.track().height());
}

QRectF EventItem::boundingRect() const {
    qreal penWidth = pen().width();
    return rect();
}

