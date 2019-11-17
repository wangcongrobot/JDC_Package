/* DO NOT EDIT or check into source control
 * Generated code for wrapping a ros message Pub/Sub in ecto
 *
 * package : object_recognition_msgs
 * msg : RecognizedObjectArray
 */
#include <ecto_ros/wrap_sub.hpp>
#include <ecto_ros/wrap_pub.hpp>
#include <ecto_ros/wrap_bag.hpp>


#include <object_recognition_msgs/RecognizedObjectArray.h>

namespace ecto_object_recognition_msgs
{
    struct Subscriber_RecognizedObjectArray : ecto_ros::Subscriber<object_recognition_msgs::RecognizedObjectArray> {};
    struct Publisher_RecognizedObjectArray : ecto_ros::Publisher<object_recognition_msgs::RecognizedObjectArray> {};
    struct Bagger_RecognizedObjectArray : ecto_ros::Bagger<object_recognition_msgs::RecognizedObjectArray> {};
}

ECTO_CELL(ecto_object_recognition_msgs, ecto_object_recognition_msgs::Subscriber_RecognizedObjectArray,"Subscriber_RecognizedObjectArray", "Subscribes to a object_recognition_msgs::RecognizedObjectArray.");
ECTO_CELL(ecto_object_recognition_msgs, ecto_object_recognition_msgs::Publisher_RecognizedObjectArray,"Publisher_RecognizedObjectArray", "Publishes a object_recognition_msgs::RecognizedObjectArray.");
ECTO_CELL(ecto_object_recognition_msgs, ecto_object_recognition_msgs::Bagger_RecognizedObjectArray,"Bagger_RecognizedObjectArray", "A bagger for messages of a given type. Can enable read/write to ros bags.");
