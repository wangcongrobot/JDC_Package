; Auto-generated. Do not edit!


(cl:in-package kinect_detect_msgs-msg)


;//! \htmlinclude ObjectPoses.msg.html

(cl:defclass <ObjectPoses> (roslisp-msg-protocol:ros-message)
  ((object_poses
    :reader object_poses
    :initarg :object_poses
    :type (cl:vector kinect_detect_msgs-msg:ObjectPose)
   :initform (cl:make-array 0 :element-type 'kinect_detect_msgs-msg:ObjectPose :initial-element (cl:make-instance 'kinect_detect_msgs-msg:ObjectPose))))
)

(cl:defclass ObjectPoses (<ObjectPoses>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ObjectPoses>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ObjectPoses)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name kinect_detect_msgs-msg:<ObjectPoses> is deprecated: use kinect_detect_msgs-msg:ObjectPoses instead.")))

(cl:ensure-generic-function 'object_poses-val :lambda-list '(m))
(cl:defmethod object_poses-val ((m <ObjectPoses>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kinect_detect_msgs-msg:object_poses-val is deprecated.  Use kinect_detect_msgs-msg:object_poses instead.")
  (object_poses m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ObjectPoses>) ostream)
  "Serializes a message object of type '<ObjectPoses>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'object_poses))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'object_poses))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ObjectPoses>) istream)
  "Deserializes a message object of type '<ObjectPoses>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'object_poses) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'object_poses)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'kinect_detect_msgs-msg:ObjectPose))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ObjectPoses>)))
  "Returns string type for a message object of type '<ObjectPoses>"
  "kinect_detect_msgs/ObjectPoses")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ObjectPoses)))
  "Returns string type for a message object of type 'ObjectPoses"
  "kinect_detect_msgs/ObjectPoses")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ObjectPoses>)))
  "Returns md5sum for a message object of type '<ObjectPoses>"
  "dea7b0d2a30c999d7206bf1518da1588")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ObjectPoses)))
  "Returns md5sum for a message object of type 'ObjectPoses"
  "dea7b0d2a30c999d7206bf1518da1588")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ObjectPoses>)))
  "Returns full string definition for message of type '<ObjectPoses>"
  (cl:format cl:nil "ObjectPose[] object_poses~%~%================================================================================~%MSG: kinect_detect_msgs/ObjectPose~%uint8 class_id~%float64 confidence~%uint32[4] rect~%float64[3] center~%float64[4] quaternation~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ObjectPoses)))
  "Returns full string definition for message of type 'ObjectPoses"
  (cl:format cl:nil "ObjectPose[] object_poses~%~%================================================================================~%MSG: kinect_detect_msgs/ObjectPose~%uint8 class_id~%float64 confidence~%uint32[4] rect~%float64[3] center~%float64[4] quaternation~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ObjectPoses>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'object_poses) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ObjectPoses>))
  "Converts a ROS message object to a list"
  (cl:list 'ObjectPoses
    (cl:cons ':object_poses (object_poses msg))
))
