/* DO NOT EDIT or check into source control
 * Generated code for wrapping a ros message Pub/Sub in ecto
 *
 * package : object_recognition_msgs
 * msg : ObjectType
 */
#include <ecto_ros/wrap_sub.hpp>
#include <ecto_ros/wrap_pub.hpp>
#include <ecto_ros/wrap_bag.hpp>


#include <object_recognition_msgs/ObjectType.h>

namespace ecto_object_recognition_msgs
{
    struct Subscriber_ObjectType : ecto_ros::Subscriber<object_recognition_msgs::ObjectType> {};
    struct Publisher_ObjectType : ecto_ros::Publisher<object_recognition_msgs::ObjectType> {};
    struct Bagger_ObjectType : ecto_ros::Bagger<object_recognition_msgs::ObjectType> {};
}

ECTO_CELL(ecto_object_recognition_msgs, ecto_object_recognition_msgs::Subscriber_ObjectType,"Subscriber_ObjectType", "Subscribes to a object_recognition_msgs::ObjectType.");
ECTO_CELL(ecto_object_recognition_msgs, ecto_object_recognition_msgs::Publisher_ObjectType,"Publisher_ObjectType", "Publishes a object_recognition_msgs::ObjectType.");
ECTO_CELL(ecto_object_recognition_msgs, ecto_object_recognition_msgs::Bagger_ObjectType,"Bagger_ObjectType", "A bagger for messages of a given type. Can enable read/write to ros bags.");
