#pragma once

#include <QtWidgets/QDialog>
#include "filtertreeview.h"

/**
 * General purpose popup dialog showing a filterable tree.
 */
class FilterPopup : public QMenu {
public:
    explicit FilterPopup(QWidget* parent, QStandardItemModel& model);

public:

    /**
     * Override to provide a reasonable size
     */
    QSize sizeHint() const override;

    /**
     * @return true if the user choice was confirmed, false if the dialog was dismissed
     */
    bool wasAccepted() const { return mWasAccepted; }

protected:
    /**
     * Set focus etc
     */
    void showEvent(QShowEvent* event) override;

    /**
     * Capture keyboard for confirmation etc
     */
    void keyPressEvent(QKeyEvent* event) override;

private:
    void moveSelection(int dir);

    void confirm();

    bool mWasAccepted = false;
    FilterTreeView mTreeView;
    QVBoxLayout mLayout;
    QSize mSize = {400, 400};

};
