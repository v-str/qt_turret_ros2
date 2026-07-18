#include "mainwindow.h"
#include "ros/RosWorker.h"

#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QThread ros_thread;
    RosWorker ros_worker;
    ros_worker.moveToThread(&ros_thread);

    MainWindow w;

    QObject::connect(&ros_thread, &QThread::started,
                     &ros_worker, &RosWorker::start);

    QObject::connect(&ros_worker, &RosWorker::finished,
                     &ros_thread, &QThread::quit);

    ros_thread.start();
    w.show();

    int ret = a.exec();
    ros_worker.stop();
    ros_thread.quit();
    ros_thread.wait();
    return ret;
}
