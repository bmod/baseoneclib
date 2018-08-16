
#include "generic/basewindow.h"
#include "timeline/timelinepanel.h"

class MainWindow : public BaseWindow {
public:
    MainWindow() {
        addDock("Timeline", &mTimelinePanel);
    }

private:
    TimelinePanel mTimelinePanel;
    Timeline mTimeline;
};


int main(int argc, char* argv[]) {
    QApplication::setApplicationName("baseoneclib_test");
    QApplication::setOrganizationName("CoreSmith");
    QApplication app(argc, argv);

    MainWindow win;
    win.show();

    app.exec();
}