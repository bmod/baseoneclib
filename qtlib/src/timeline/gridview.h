#pragma once

#include <QtWidgets/QGraphicsView>
#include <QGraphicsRectItem>


class GridView : public QGraphicsView {
Q_OBJECT
    enum class ZoomMode {
        IgnoreAspectRatio, KeepAspectRatio, Horizontal, Vertical
    };

    enum class PanMode {
        Horizontal, Vertical, Parallax
    };

    enum class RulerFormat {
        Float, SMPTE
    };

public:
    GridView();

    ~GridView() {}

    void pan(const QPointF& delta);

    void zoom(const QPointF& delta, const QPointF& pivot);

    void centerView();

    void frameAll(bool horizontal, bool vertical, QMargins margins = QMargins(20, 20, 20, 20));

    void frameSelected(bool horizontal, bool vertical, QMargins margins = QMargins(20, 20, 20, 20));

    void frameView(const QRectF& rect, bool horizontal, bool vertical, QMargins margins = QMargins(20, 20, 20, 20));

    void fitInView(const QRectF& rect, const QMargins& margins, bool horizontal, bool vertical);

    void setVerticalScroll(int value);

    void setGridEnabled(bool enabled);

    const QPoint& mousePressedPos() const { return mMousePressPos; }

    const QPoint& mouseLastPos() const { return mMouseLastPos; }

    const QPoint& mouseDelta() const { return mMouseDelta; }

Q_SIGNALS:

    void viewTransformed();

protected:
    void drawBackground(QPainter* painter, const QRectF& rect) override;

    void mousePressEvent(QMouseEvent* event) override;

    void mouseMoveEvent(QMouseEvent* event) override;

    void mouseReleaseEvent(QMouseEvent* event) override;

    void wheelEvent(QWheelEvent* event) override;

    void keyPressEvent(QKeyEvent* event) override;

    void keyReleaseEvent(QKeyEvent* event) override;

    QPoint mMousePressPos;
private:
    QRectF selectedItemsBoundingRect() const;

    const QPointF viewScale() const;

    const QPointF viewPos() const;

    QPoint mMouseLastPos;
    QPoint mMouseDelta;
    QSize mViewSize;
    QFont mRulerFont;
    bool mGridEnabled = true;

    ZoomMode mZoomMode = ZoomMode::Horizontal;
    PanMode mPanMode = PanMode::Horizontal;
    RulerFormat mRulerFormat = RulerFormat::SMPTE;
    qreal mFramerate = 30;

    qreal calcGridStep(qreal desiredSpacing, qreal viewWidth, qreal sceneRectWidth) const;

    qreal calcGridStepTime(qreal desiredSpacing, qreal viewWidth, qreal sceneRectWidth, qreal minStepSize) const;
};
