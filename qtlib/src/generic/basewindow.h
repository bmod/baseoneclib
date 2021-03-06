#pragma once

#include <QDockWidget>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QtCore/QSettings>


/**
 * Extension of QMainWindow, automatically saves and restores many windowsettings.
 */
class BaseWindow : public QMainWindow {
public:
    /**
     * Constructor
     */
    BaseWindow();

    /**
     * Destructor
     */
    virtual ~BaseWindow() {
    }

    /**
     * @return The QMenu that contains the list of available windows
     */
    QMenu* getWindowMenu() {
        return mWindowMenu;
    }

    /**
     * Add a QWidget to this window, display it as a dockwidget and add a toggle menuitem to the menubar
     * @param name The name and title of the specified widget.
     * @param widget The widget to be added as a dockwidget.
     * @param area The initial area to stick the the dock into.
     */
    QDockWidget* addDock(const QString& name, QWidget* widget, Qt::DockWidgetArea area = Qt::TopDockWidgetArea);

protected:
    /**
     * Override from QMainWindow
     */
    void showEvent(QShowEvent* event) override;

    /**
     * Override from QMainWindow
     */
    void closeEvent(QCloseEvent* event) override;

    /**
     * Save the user-level application settings
     * @param settings The QSettings object to use
     */
    void saveSettings(QSettings& settings);

    /**
     * Restore the user-level application settings
     * @param settings The QSettings object to use
     */
    void restoreSettings(QSettings& settings);

private:
    QMenu* mWindowMenu;
};
