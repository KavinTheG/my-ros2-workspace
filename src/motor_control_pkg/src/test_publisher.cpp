#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class TestPublisher : public rclcpp::Node
{
public:
    // Constructor for the class
    TestPublisher()
        : Node("test_publisher"), count_(0)
    { // Instantiating the publisher and timer (defined in the private section)
        publisher_ = this->create_publisher<std_msgs::msg::String>("motor_cmd", 10);
        timer_ = this->create_wall_timer(
            500ms, std::bind(&TestPublisher::timer_callback, this));
    }

private:
    // Increases the count variable
    void timer_callback()
    {
        auto message = std_msgs::msg::String();
        message.data = "testing" + std::to_string(count_++);
        publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TestPublisher>());
    rclcpp::shutdown();
    return 0;
}