#ifndef ROSHANDLER_H
#define ROSHANDLER_H

#include <functional>
#include <rclcpp/rclcpp.hpp>
#include <proto_turret_interfaces/msg/turret_command.hpp>

using TurretCommand = proto_turret_interfaces::msg::TurretCommand;
using Node = rclcpp::Node;
using Pub = rclcpp::Publisher<TurretCommand>::SharedPtr;
using Sub = rclcpp::Subscription<TurretCommand>::SharedPtr;

class RosHandler
{
public:
    using StatusCallback = std::function<void(float pan, float tilt, bool laser)>;

    ~RosHandler();

    void init();
    void run();
    void stop();

    void publishCommand(float pan, float tilt, float pan_vel, float tilt_vel, bool laser);
    void setStatusCallback(StatusCallback cb);

private:
    Node::SharedPtr  m_node;
    Pub              m_publisher;
    Sub              m_subscriber;
    StatusCallback   m_onStatus;

    using Executor = rclcpp::executors::SingleThreadedExecutor;
    std::shared_ptr<Executor> m_executor;
};

#endif // ROSHANDLER_H
