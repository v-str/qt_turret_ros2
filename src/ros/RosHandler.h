#ifndef ROSHANDLER_H
#define ROSHANDLER_H

#include <functional>
#include <proto_turret_interfaces/msg/turret_command.hpp>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float32.hpp>

using TurretCommand = proto_turret_interfaces::msg::TurretCommand;
using Node = rclcpp::Node;
using Pub = rclcpp::Publisher<TurretCommand>::SharedPtr;
using Sub = rclcpp::Subscription<TurretCommand>::SharedPtr;
using Float32Sub = rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr;

class RosHandler
{
public:
    using StatusCallback = std::function<void(float pan, float tilt, bool laser)>;
    using TemperatureCallback = std::function<void(float temperature)>;

    ~RosHandler();

    void init();
    void run();
    void stop();

    void publishCommand(float pan, float tilt, float pan_vel, float tilt_vel, bool laser);
    void setStatusCallback(StatusCallback cb);
    void setTemperatureCallback(TemperatureCallback cb);

private:
    Node::SharedPtr m_node;
    Pub              m_publisher;
    Sub              m_subscriber;
    Float32Sub       m_temperatureSub;
    StatusCallback   m_onStatus;
    TemperatureCallback m_onTemperature;

    using Executor = rclcpp::executors::SingleThreadedExecutor;
    std::shared_ptr<Executor> m_executor;
};

#endif // ROSHANDLER_H