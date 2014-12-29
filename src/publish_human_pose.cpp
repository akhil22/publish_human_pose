#include<ros/ros.h>
#include<visualization_msgs/MarkerArray.h>
#include<visualization_msgs/Marker.h>
#include<geometry_msgs/Pose.h>
int main(int argc, char** argv){
	ros::init(argc, argv, "human_pose_publisher");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<visualization_msgs::MarkerArray>("human_pose",1);
	ros::Rate looprate(2);
	double x = 0;
	double y = 0;
	uint32_t shape = visualization_msgs::Marker::CUBE;
	while(ros::ok()){
		visualization_msgs::MarkerArray markerarray;
		visualization_msgs::Marker marker;
		// Set the frame ID and timestamp.  See the TF tutorials for information on these.
		marker.header.frame_id = "/map";
		marker.header.stamp = ros::Time::now();

		// Set the namespace and id for this marker.  This serves to create a unique ID
		// Any marker sent with the same namespace and id will overwrite the old one
		marker.ns = "basic_shapes";
		marker.id = 0;

		// Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
		marker.type = shape;

		// Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
		marker.action = visualization_msgs::Marker::ADD;

		// Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
		marker.pose.position.x = x;
		marker.pose.position.y = y;
		marker.pose.position.z = 0.3;
		marker.pose.orientation.x = 0;
		marker.pose.orientation.y = 0;
		marker.pose.orientation.z = 0;
		marker.pose.orientation.w = 1;

		// Set the scale of the marker -- 1x1x1 here means 1m on a side
		marker.scale.x = 0.4;
		marker.scale.y = 0.4;
		marker.scale.z = 0.4;

		// Set the color -- be sure to set alpha to something non-zero!
		marker.color.r = 0.0f;
		marker.color.g = 1.0f;
		marker.color.b = 0.0f;
		marker.color.a = 1.0;

		marker.lifetime = ros::Duration();
		markerarray.markers.push_back(marker);
		// Publish the marker
	/*	while (pub.getNumSubscribers() < 1)
		{
			if (!ros::ok())
			{
				return 0;
			}
			ROS_WARN_ONCE("Please create a subscriber to the marker");
			sleep(1);
		}*/
		pub.publish(markerarray);
		y = y+0.5;
		x = x+0.5;
		if(x >= 8){
			ros::Rate r(0.2);
			r.sleep();
			x = 0;
			y = 0;
		}
		looprate.sleep();
	}
}
