/* DO NOT EDIT or check into source control
 * Generated code for wrapping a ros message Pub/Sub in ecto
 *
 * package : object_recognition_msgs
 * msg : ObjectInformation
 */
#include <ecto_ros/wrap_sub.hpp>
#include <ecto_ros/wrap_pub.hpp>
#include <ecto_ros/wrap_bag.hpp>


#include <object_recognition_msgs/ObjectInformation.h>

namespace ecto_object_recognition_msgs
{
    struct Subscriber_ObjectInformation : ecto_ros::Subscriber<object_recognition_msgs::ObjectInformation> {};
    struct Publisher_ObjectInformation : ecto_ros::Publisher<object_recognition_msgs::ObjectInformation> {};
    struct Bagger_ObjectInformation : ecto_ros::Bagger<object_recognition_msgs::ObjectInformation> {};
}

ECTO_CELL(ecto_object_recognition_msgs, ecto_object_recognition_msgs::Subscriber_ObjectInformation,"Subscriber_ObjectInformation", "Subscribes to a object_recognition_msgs::ObjectInformation.");
ECTO_CELL(ecto_object_recognition_msgs, ecto_object_recognition_msgs::Publisher_ObjectInformation,"Publisher_ObjectInformation", "Publishes a object_recognition_msgs::ObjectInformation.");
ECTO_CELL(ecto_object_recognition_msgs, ecto_object_recognition_msgs::Bagger_ObjectInformation,"Bagger_ObjectInformation", "A bagger for messages of a given type. Can enable read/write to ros bags.");
