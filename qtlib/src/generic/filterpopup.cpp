#include "filterpopup.h"

#include <QKeyEvent>

#include "qtutils.h"


FilterPopup::FilterPopup(QWidget* parent, QStandardItemModel& model) : QMenu(nullptr) {
    mTreeView.setModel(&model);
    setLayout(&mLayout);
    mLayout.setContentsMargins(0, 0, 0, 0);
    mLayout.addWidget(&mTreeView);
    mTreeView.getTreeView().setHeaderHidden(true);
    mTreeView.getLineEdit().setFocusPolicy(Qt::StrongFocus);
    mTreeView.setIsItemSelector(true);
    connect(&mTreeView.getTreeView(), &QTreeView::doubleClicked, this, &FilterPopup::confirm);
}

void FilterPopup::showEvent(QShowEvent* event) {
    QMenu::showEvent(event);
    mTreeView.getLineEdit().setFocus();
}


void FilterPopup::keyPressEvent(QKeyEvent* event) {
    QMenu::keyPressEvent(event);

    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        confirm();
    else if (event->key() == Qt::Key_Up)
        moveSelection(-1);
    else if (event->key() == Qt::Key_Down)
        moveSelection(1);
}

void FilterPopup::moveSelection(int dir) {
    auto selectedIndexes = mTreeView.getSelectionModel()->selection().indexes();
    if (selectedIndexes.empty())
        return;

    int row = selectedIndexes.at(0).row();
    int newRow = clamp(row + dir, 0, mTreeView.getModel()->rowCount() - 1);

    if (row == newRow)
        return;

    auto newIndex = mTreeView.getModel()->index(newRow, 0);
    mTreeView.getSelectionModel()->setCurrentIndex(newIndex, QItemSelectionModel::SelectCurrent);
    mTreeView.update();
}


void FilterPopup::confirm() {
    mWasAccepted = true;
    close();
}

QSize FilterPopup::sizeHint() const {
    return mSize;
}



