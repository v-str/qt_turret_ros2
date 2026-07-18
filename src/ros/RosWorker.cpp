#include "RosWorker.h"
#include "constants.h"

RosWorker::RosWorker(QObject *parent)
    : QObject(parent)
{
}

RosWorker::~RosWorker()
{
    stop();
}

void RosWorker::start()
{
    rclcpp::init(0, nullptr);
    node_ = std::make_shared<rclcpp::Node>(qt_turret::node_name);

    publisher_ = node_->create_publisher<proto_turret_interfaces::msg::TurretCommand>(
        qt_turret::cmd_turret_topic, qt_turret::qos_depth);

    subscriber_ = node_->create_subscription<proto_turret_interfaces::msg::TurretCommand>(
        qt_turret::heartbeat_topic, qt_turret::qos_depth,
        [this](const proto_turret_interfaces::msg::TurretCommand::SharedPtr msg) {
            emit stateUpdated(msg->pan_pos, msg->tilt_pos, msg->laser_enable);
        });

    rclcpp::spin(node_);

    node_.reset();
    emit finished();
}

void RosWorker::stop()
{
    rclcpp::shutdown();
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
