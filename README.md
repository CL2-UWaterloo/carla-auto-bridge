# CARLA and Autoware.Auto ROS 2 bridge

## Environment 
|Ubuntu|ROS 2|Autoware|Nvidia Driver|CUDA Version|
|:---:|:---:|:---:|:---:|:---:|
|20.04|galactic|auto/(source installation)|470.63.01|11.4+|

## Minimum Hardware Requirements 
|CPU|RAM|GPU|
|:---:|:---:|:---:|
|8 cores|16 GB|NVIDIA 4GB RAM|

### GPU is not required to run basic functionality, it is mandatory to enable the following neural network related functions:
* LiDAR based object detection
* Camera based object detection
* Traffic light detection and classification
## Installation steps
1) Autoware.Auto source installation (https://autowarefoundation.gitlab.io/autoware.auto/AutowareAuto/installation-no-ade.html)
2) CARLA 0.9.13 source installation (debian, https://carla.readthedocs.io/en/latest/start_quickstart/)
3) carla-auto-bridge (this repository)
  ```bash
  mkdir -p ros2_ws/src
  cd ros2_ws/src
  git clone git@github.com:CL2-UWaterloo/carla-auto-bridge.git --recursive
  ```
## Build
```bash
cd ros2_ws
colcon build --symlink-install
```
## Quick Start
1. Run CARLA, load a map
```bash
/opt/carla-simulator/CarlaUE4.sh
python3 /opt/carla-simulator/PythonAPI/util/config.py -m Town01
```
2. Launch carla_ros_bridge, autoware.auto bridge
```bash
ros2 launch carla_ros_bridge carla_ros_bridge_with_example_ego_vehicle.launch.py
ros2 launch autoware_bridge autoware_bridge_launch.xml 
ros2 launch autoware_bridge autoware_launch.xml map_path:=<path-to-map-dir>/Town01 vehicle_model:=sample_vehicle sensor_model:=sample_sensor_kit
```
3. Set initial pose
4. Set goal position
5. Wait for planning
6. Engage (use web interface or Rviz plugin (AutowareStatePanel))
