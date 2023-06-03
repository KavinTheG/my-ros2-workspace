from launch import LaunchDescription 
from launch_ros.actions import Node 

def generate_launch_description(): 
     
    return LaunchDescription([ 
        Node(
            package='motor_control_pkg', 
            executable='test_publisher_node', 
            #output='display' 
        ) 
    ]
) 