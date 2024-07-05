#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class SubNode : public rclcpp::Node
{
public:
    SubNode(std::string name) : Node(name){
        RCLCPP_INFO(this->get_logger(),"我是topic：%s",name.c_str());
        sub = this->create_subscription<std_msgs::msg::String>("command",10,
            std::bind(&SubNode::subInfo,this,std::placeholders::_1));
    }
private:
    void subInfo(const std_msgs::msg::String::SharedPtr msg){
        double rate = 0.0f;
        if(msg->data == "foward")
            rate = 0.2f;
        RCLCPP_INFO(this->get_logger(),"指令[%s],发送速度[%f]",msg->data.c_str(),rate);
    }
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub;
};

int main(int argc, char const *argv[])
{
    rclcpp::init(argc,argv);
    auto sub = std::make_shared<SubNode>("sub_node");
    rclcpp::spin(sub);
    rclcpp::shutdown();
    return 0;
}
