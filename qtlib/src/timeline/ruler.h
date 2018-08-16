#pragma once

#include <QWidget>
#include <QStylePainter>
#include "timelinemodel.h"
#include "timedisplay.h"
#include <memory>

class Ruler : public QWidget {
public:
    Ruler(QWidget* parent = 0);

    void setRange(const Range& range);

    void setHeight(int height);

    void setTimeDisplay(std::shared_ptr<TimeDisplay> timeDisplay);

protected:

    void resizeEvent(QResizeEvent* event) override;

    void paintEvent(QPaintEvent* event) override;

    void drawHatches(QPainter& painter, int hatchLength, qreal minStepSize,
                     bool drawLabels = false) const;

private:
    void setHatchFont(const QFont& font);

    Range mRange;
    int mMinorHatchLength = 4;
    int mMajorHatchLength = 12;
    std::shared_ptr<TimeDisplay> mTimeConfig;
    QFont mFont;
    int mTextHeight;
    QPoint mLabelOffset = {4, 0};
};
