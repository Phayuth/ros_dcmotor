# DC Motor ROS Package
This package is written for Simulation and Hardware Implementation of DC motor control in ROS Melodic. Using the Method of Lumped Parameter Modelling of DC motor and PID controller Design with ROOT LOCUS and 2nd Order Standard Differential Equation. [For Mom!]


### Requirement
- ROS Melodic
- rosserial


### Installation
#### Install Project
Create workspace ➡ Clone project ➡ Compile ➡ Source .bashrc
```
mkdir -p ws_dcmotor/src
cd ws_dcmotor/src
git clone https://github.com/Phayuth/ros_dcmotor.git
cd ..
catkin_make
source ~/ws_dcmotor/devel/setup.bash
```


#### Install rosserial (MAKE SURE TO SOURCE PROJECT, SO THAT THE CUSTOM MSG CAN COMPILE FOR ROSSERIAL)
```
sudo apt-get install ros-melodic-rosserial-arduino
sudo apt-get install ros-melodic-rosserial
```
```
cd ~/Arduino/libraries
rm -rf ros_lib
rosrun rosserial_arduino make_libraries.py .
```


### Simulation
- Run node `rosrun ros_dcmotor motor_linear_node` for Linear Model
- Run node `rosrun ros_dcmotor motor_nonlinear_node` for Nonlinear Model
- Use rqt to publish `/voltage` to get rotation velocity


### Hardware
- Change Lumped Parameter model `a,b,c` in arduino file
- For Motor Driver with PWM pin and Direction pin type : Upload `ros_dcmotor_hw/arduino/arduino_direct.ino` code to Arduino
- For Motor Driver with both PWM pins type (IBT2) : Upload `ros_dcmotor_hw/arduino/arduino_ibt.ino` code to Arduino
- Bringup Node `roslaunch ros_dcmotor_hw bringup.launch`
- Publish Desired Velocity on `/motor_desired` topic


### Reference
- Lumped Parameter Estimation of a Low Cost DC Motor for Position Controller Design : https://ieeexplore.ieee.org/document/9807810 
- PD Controller and Dynamic Compensation Design for a DC Motor based on Estimated Parameters : https://ieeexplore.ieee.org/document/9807796
- rosserial setup : http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup