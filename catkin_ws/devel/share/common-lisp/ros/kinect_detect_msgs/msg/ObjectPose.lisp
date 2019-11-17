; Auto-generated. Do not edit!


(cl:in-package kinect_detect_msgs-msg)


;//! \htmlinclude ObjectPose.msg.html

(cl:defclass <ObjectPose> (roslisp-msg-protocol:ros-message)
  ((class_id
    :reader class_id
    :initarg :class_id
    :type cl:fixnum
    :initform 0)
   (confidence
    :reader confidence
    :initarg :confidence
    :type cl:float
    :initform 0.0)
   (rect
    :reader rect
    :initarg :rect
    :type (cl:vector cl:integer)
   :initform (cl:make-array 4 :element-type 'cl:integer :initial-element 0))
   (center
    :reader center
    :initarg :center
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0))
   (quaternation
    :reader quaternation
    :initarg :quaternation
    :type (cl:vector cl:float)
   :initform (cl:make-array 4 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass ObjectPose (<ObjectPose>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ObjectPose>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ObjectPose)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name kinect_detect_msgs-msg:<ObjectPose> is deprecated: use kinect_detect_msgs-msg:ObjectPose instead.")))

(cl:ensure-generic-function 'class_id-val :lambda-list '(m))
(cl:defmethod class_id-val ((m <ObjectPose>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kinect_detect_msgs-msg:class_id-val is deprecated.  Use kinect_detect_msgs-msg:class_id instead.")
  (class_id m))

(cl:ensure-generic-function 'confidence-val :lambda-list '(m))
(cl:defmethod confidence-val ((m <ObjectPose>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kinect_detect_msgs-msg:confidence-val is deprecated.  Use kinect_detect_msgs-msg:confidence instead.")
  (confidence m))

(cl:ensure-generic-function 'rect-val :lambda-list '(m))
(cl:defmethod rect-val ((m <ObjectPose>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kinect_detect_msgs-msg:rect-val is deprecated.  Use kinect_detect_msgs-msg:rect instead.")
  (rect m))

(cl:ensure-generic-function 'center-val :lambda-list '(m))
(cl:defmethod center-val ((m <ObjectPose>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kinect_detect_msgs-msg:center-val is deprecated.  Use kinect_detect_msgs-msg:center instead.")
  (center m))

(cl:ensure-generic-function 'quaternation-val :lambda-list '(m))
(cl:defmethod quaternation-val ((m <ObjectPose>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kinect_detect_msgs-msg:quaternation-val is deprecated.  Use kinect_detect_msgs-msg:quaternation instead.")
  (quaternation m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ObjectPose>) ostream)
  "Serializes a message object of type '<ObjectPose>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'class_id)) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'confidence))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) ele) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) ele) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) ele) ostream))
   (cl:slot-value msg 'rect))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'center))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'quaternation))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ObjectPose>) istream)
  "Deserializes a message object of type '<ObjectPose>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'class_id)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'confidence) (roslisp-utils:decode-double-float-bits bits)))
  (cl:setf (cl:slot-value msg 'rect) (cl:make-array 4))
  (cl:let ((vals (cl:slot-value msg 'rect)))
    (cl:dotimes (i 4)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:aref vals i)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:aref vals i)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:aref vals i)) (cl:read-byte istream))))
  (cl:setf (cl:slot-value msg 'center) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'center)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'quaternation) (cl:make-array 4))
  (cl:let ((vals (cl:slot-value msg 'quaternation)))
    (cl:dotimes (i 4)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ObjectPose>)))
  "Returns string type for a message object of type '<ObjectPose>"
  "kinect_detect_msgs/ObjectPose")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ObjectPose)))
  "Returns string type for a message object of type 'ObjectPose"
  "kinect_detect_msgs/ObjectPose")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ObjectPose>)))
  "Returns md5sum for a message object of type '<ObjectPose>"
  "e68ffe39821162630486382c2d079836")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ObjectPose)))
  "Returns md5sum for a message object of type 'ObjectPose"
  "e68ffe39821162630486382c2d079836")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ObjectPose>)))
  "Returns full string definition for message of type '<ObjectPose>"
  (cl:format cl:nil "uint8 class_id~%float64 confidence~%uint32[4] rect~%float64[3] center~%float64[4] quaternation~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ObjectPose)))
  "Returns full string definition for message of type 'ObjectPose"
  (cl:format cl:nil "uint8 class_id~%float64 confidence~%uint32[4] rect~%float64[3] center~%float64[4] quaternation~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ObjectPose>))
  (cl:+ 0
     1
     8
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'rect) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'center) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'quaternation) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ObjectPose>))
  "Converts a ROS message object to a list"
  (cl:list 'ObjectPose
    (cl:cons ':class_id (class_id msg))
    (cl:cons ':confidence (confidence msg))
    (cl:cons ':rect (rect msg))
    (cl:cons ':center (center msg))
    (cl:cons ':quaternation (quaternation msg))
))
