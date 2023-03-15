#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

class IntegerPublisher : public rclcpp::Node
{
public:
    IntegerPublisher() : Node("send_data")
    {
        publisher_ = this->create_publisher<std_msgs::msg::Int32>("data_topic", 10);

        timer_ = this->create_wall_timer(std::chrono::seconds(1),
                                         std::bind(&IntegerPublisher::publishData, this));
    }

private:
    void publishData()
    {
        auto msg = std_msgs::msg::Int32();
        
        // Send random number, either 0 or 1
        msg.data = rand() % 2;
        RCLCPP_INFO(this->get_logger(), "%i", msg.data);
        publisher_->publish(msg);
    }

    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;

    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<IntegerPublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}