
(cl:in-package :asdf)

(defsystem "kinect_detect_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "ObjectPose" :depends-on ("_package_ObjectPose"))
    (:file "_package_ObjectPose" :depends-on ("_package"))
    (:file "ObjectIDs" :depends-on ("_package_ObjectIDs"))
    (:file "_package_ObjectIDs" :depends-on ("_package"))
    (:file "ObjectPoses" :depends-on ("_package_ObjectPoses"))
    (:file "_package_ObjectPoses" :depends-on ("_package"))
  ))