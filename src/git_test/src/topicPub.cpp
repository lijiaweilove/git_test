#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class PubNode : public rclcpp::Node
{
public:
    PubNode(std::string name) : Node(name)
    {
        RCLCPP_INFO(this->get_logger(),"我是V2topic%s",name.c_str());
        pub = this->create_publisher<std_msgs::msg::String>("command",10);
        timer = this->create_wall_timer(std::chrono::seconds(1),std::bind(&PubNode::timer_callback,this));
    }
private:
    void timer_callback(){
        std_msgs::msg::String msg;
        msg.data = "foward";
        RCLCPP_INFO(this->get_logger(),"pub:%s",msg.data.c_str());
        pub->publish(msg);
    }
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub;
    rclcpp::TimerBase::SharedPtr timer;
};    

int main(int argc, char **argv)
{
    rclcpp::init(argc,argv);
    auto pubNode = std::make_shared<PubNode>("pub_node");
    rclcpp::spin(pubNode);
    rclcpp::shutdown();
    return 0;
}
