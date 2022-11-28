# DC Motor ROS1 Package
This package is written for Simulation and Hardware Implementation of DC motor control in ROS 1. Using the Method of Lumped Parameter Modelling of DC motor and PID controller Design with ROOT LOCUS and 2nd Order Standard Differential Equation. [For Mom!]

### Require
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
cd ~/Arduino/libraries
rm -rf ros_lib
rosrun rosserial_arduino make_libraries.py .
```

#### Upload .Ino code to Arduino `ros_dcmotor_hw/arduino.ino`

### Usage
Bringup Node
```
roslaunch ros_dcmotor_hw bringup.launch
```

### Reference
- Lumped Parameter Estimation of a Low Cost DC Motor for Position Controller Design : https://ieeexplore.ieee.org/document/9807810 
- PD Controller and Dynamic Compensation Design for a DC Motor based on Estimated Parameters : https://ieeexplore.ieee.org/document/9807796
- rosserial setup : http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup