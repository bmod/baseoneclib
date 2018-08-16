#pragma once

#include <QtWidgets/QGraphicsItem>
#include <QtGui/QBrush>
#include <QPen>
#include "timelinemodel.h"


class TrackItem : public QGraphicsItemGroup {
public:
    explicit TrackItem(QGraphicsItem* parent, Track& track);

    Track& track() const { return mTrack; }

private:
    Track& mTrack;

};
