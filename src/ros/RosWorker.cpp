#include "RosWorker.h"
#include <chrono>
#include <thread>

RosWorker::RosWorker(QObject *parent)
    : QObject(parent)
    , running_(false)
{
}

RosWorker::~RosWorker()
{
    stop();
}

void RosWorker::start()
{
    rclcpp::init(0, nullptr);
    node_ = std::make_shared<rclcpp::Node>("turret_qt_controller");

    publisher_ = node_->create_publisher<proto_turret_interfaces::msg::TurretCommand>(
        "/cmd_turret", 10);

    subscriber_ = node_->create_subscription<proto_turret_interfaces::msg::TurretCommand>(
        "/proto_turret_publisher", 10,
        [this](const proto_turret_interfaces::msg::TurretCommand::SharedPtr msg) {
            emit stateUpdated(msg->pan_pos, msg->tilt_pos, msg->laser_enable);
        });

    executor_ = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
    executor_->add_node(node_);

    running_ = true;
    while (running_ && rclcpp::ok()) {
        executor_->spin_some();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    executor_->remove_node(node_);
    executor_.reset();
    node_.reset();
    if (rclcpp::ok())
        rclcpp::shutdown();
    emit finished();
}

void RosWorker::stop()
{
    running_ = false;
}

void RosWorker::publishCommand(float pan, float tilt, float pan_vel, float tilt_vel, bool laser)
{
    if (!publisher_) return;
    auto msg = proto_turret_interfaces::msg::TurretCommand();
    msg.pan_pos = pan;
    msg.tilt_pos = tilt;
    msg.pan_vel = pan_vel;
    msg.tilt_vel = tilt_vel;
    msg.laser_enable = laser;
    publisher_->publish(msg);
}
