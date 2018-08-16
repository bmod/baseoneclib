#include "errordialog.h"
#include <QPushButton>

ErrorDialog::ErrorDialog(QWidget* parent) : QDialog(parent), mButtonBox(QDialogButtonBox::Close) {
    setWindowTitle("Error");
    setLayout(&mLayout);

    setWindowFlag(Qt::WindowCloseButtonHint, false);

    mLayout.addWidget(&mText);
    mLayout.addWidget(&mButtonBox);

    setWindowModality(Qt::ApplicationModal);

    auto btClose = mButtonBox.button(QDialogButtonBox::Close);
    connect(btClose, &QPushButton::clicked, [this]() {
        close();
    });
}

void ErrorDialog::addMessage(LogMessage message) {
    mText.append(message.text() + "\n");
}

void ErrorDialog::closeEvent(QCloseEvent* event) {
    mText.clear();
    QDialog::closeEvent(event);
}

QSize ErrorDialog::sizeHint() const {
    return {600, 300};
}

void ErrorDialog::showEvent(QShowEvent* event) {
    QDialog::showEvent(event);
}

