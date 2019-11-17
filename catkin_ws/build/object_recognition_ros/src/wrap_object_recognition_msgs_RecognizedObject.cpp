/* DO NOT EDIT or check into source control
 * Generated code for wrapping a ros message Pub/Sub in ecto
 *
 * package : object_recognition_msgs
 * msg : RecognizedObject
 */
#include <ecto_ros/wrap_sub.hpp>
#include <ecto_ros/wrap_pub.hpp>
#include <ecto_ros/wrap_bag.hpp>


#include <object_recognition_msgs/RecognizedObject.h>

namespace ecto_object_recognition_msgs
{
    struct Subscriber_RecognizedObject : ecto_ros::Subscriber<object_recognition_msgs::RecognizedObject> {};
    struct Publisher_RecognizedObject : ecto_ros::Publisher<object_recognition_msgs::RecognizedObject> {};
    struct Bagger_RecognizedObject : ecto_ros::Bagger<object_recognition_msgs::RecognizedObject> {};
}

ECTO_CELL(ecto_object_recognition_msgs, ecto_object_recognition_msgs::Subscriber_RecognizedObject,"Subscriber_RecognizedObject", "Subscribes to a object_recognition_msgs::RecognizedObject.");
ECTO_CELL(ecto_object_recognition_msgs, ecto_object_recognition_msgs::Publisher_RecognizedObject,"Publisher_RecognizedObject", "Publishes a object_recognition_msgs::RecognizedObject.");
ECTO_CELL(ecto_object_recognition_msgs, ecto_object_recognition_msgs::Bagger_RecognizedObject,"Bagger_RecognizedObject", "A bagger for messages of a given type. Can enable read/write to ros bags.");
