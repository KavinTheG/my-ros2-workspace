#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class StringPublisher : public rclcpp::Node
{
public:
    StringPublisher() : Node("send_data")
    {
        publisher_ = this->create_publisher<std_msgs::msg::String>("data_topic", 10);

        timer_ = this->create_wall_timer(std::chrono::seconds(1),
                                         std::bind(&StringPublisher::publishData, this));
    }

private:
    void publishData()
    {
        auto msg = std_msgs::msg::String();
        
        int x = rand() % 2;

        msg.data = x == 0 ? std::string("HIGH") : std::string("LOW");
        
        RCLCPP_INFO(this->get_logger(), msg.data.c_str());

        publisher_->publish(msg);
    }

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;

    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<StringPublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}