#include "mainwindow.h"
#include "ros/QtRosWorker.h"

#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QThread ros_thread;
    QtRosWorker ros_worker;
    ros_worker.moveToThread(&ros_thread);

    MainWindow w;
    w.setRosWorker(&ros_worker);

    QObject::connect(&ros_thread, &QThread::started,
                     &ros_worker, &QtRosWorker::start);

    ros_thread.start();
    w.show();

    int ret = a.exec();
    ros_worker.stop();
    ros_thread.quit();
    ros_thread.wait();
    return ret;
}
