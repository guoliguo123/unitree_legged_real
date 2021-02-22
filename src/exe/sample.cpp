void chatterCallback(const std_msgs::String::ConstPtr& msg)
   {
     ROS_INFO("I heard: [%s]", msg->data.c_str());
   }
int main(int argc, char **argv)
   {
	ros::init(argc, argv, "listener");
	ros::NodeHandle n;
        /*告诉master我们要订阅chatter topic上的消息。当有消息到达topic时，ROS就会调用

chatterCallback()函数。第二个参数是队列大小，以防我们处理消息的速度不够快，在缓存了1000个

消息后，再有新的消息到来就将开始丢弃先前接收的消息。*/


	ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
/*NodeHandle::subscribe()返回ros::Subscriber对象,你必须让它处于活动状态直到你不再想订阅该

消息。当这个对象销毁时，它将自动退订 上的消息。*/

	ros::spin();
/*ros::spin()进入自循环，可以尽可能快的调用消息回调函数。如果没有消息到达，它不会占用很多

CPU，所以不用担心。一旦ros::ok()返回FALSE，ros::spin()就会立刻跳出自循环。这有可能是

ros::shutdown()被调用，或者是用户按下了Ctrl-C，使得master告诉节点要shutdown。也有可能是节

点被人为的关闭。*/
	return 0;
    }