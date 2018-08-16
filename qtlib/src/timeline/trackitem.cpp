#include "trackitem.h"

TrackItem::TrackItem(QGraphicsItem* parent, Track& track)
        : mTrack(track), QGraphicsItemGroup(parent) {
    setHandlesChildEvents(false);
}
