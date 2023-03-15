#include <micro_ros_arduino.h>

#include <stdio.h>
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/string.h>

#include <type_traits>

rcl_subscription_t subscriber;
std_msgs__msg__String msg;
rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rcl_timer_t timer;

#define LED_PIN 13

#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}

void error_loop(){
  while(1){
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(10000);
  }  
}

String msg_data;

void subscription_callback(const void * msgin)
{  
  const std_msgs__msg__String * message = (const std_msgs__msg__String *)msgin;
  msg_data = message->data.data;
}

void setup() {
  //Serial.begin(115200);
  set_microros_transports();
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);  
  
  delay(2000);

  allocator = rcl_get_default_allocator();

  //create init_options
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

  // create node
  RCCHECK(rclc_node_init_default(&node, "micro_ros_arduino_node", "", &support));

  // create subscriber
  RCCHECK(rclc_subscription_init_default(
    &subscriber,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String),
    "data_topic"));

  // create executor
  RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
  RCCHECK(rclc_executor_add_subscription(&executor, &subscriber, &msg, &subscription_callback, ON_NEW_DATA));
  msg.data.data=(char *) malloc(100 * sizeof(char));
  msg.data.size = 0;
  msg.data.capacity = 100;
}

void loop() {
  delay(100);
  
  if (msg_data.equals("HIGH")) {
    digitalWrite(LED_PIN, HIGH);
    //delay(1000);
  } else if (msg_data.equals("LOW")) {
    digitalWrite(LED_PIN, LOW);
  }
  


  RCCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
}
