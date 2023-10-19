/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-19 09:44:15
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-19 09:51:56
 */
#include <iostream>
#include <memory>

//子系统 灯光
class Light{
public:
    void TurnOnTheLight() {
      std::cout << "Turn On The Light" << std::endl;
    }
    void TurnOffTheLight() {
      std::cout << "Turn Off The Light" << std::endl;
    }
};

//子系统 空调
class AirConditioner{
public:
    void TurnOnTheAirConditioner() {
      std::cout << "Turn On The Air Conditioner" << std::endl;
    }
    void TurnOffTheAirConditioner() {
      std::cout << "Turn Off The Air Conditioner" << std::endl;
    }
};

//子系统 电视
class Television{
public:
    void TurnOnTheTelevision() {
      std::cout << "Turn On The Television" << std::endl;
    }
    void TurnOffTheTelevision() {
      std::cout << "Turn Off The Television" << std::endl;
    }
};

//子系统 音响
class StereoSystem{
public:
    void TurnOnTheStereoSystem() {
      std::cout << "Turn On The Stereo System" << std::endl;
    }
    void TurnOffTheStereoSystem() {
      std::cout << "Turn Off The Stereo System" << std::endl;
    }
};

//门面系统
class FacadeSystem{
  Light light;
  AirConditioner airConditioner;
  Television television;
  StereoSystem stereoSystem;

public:
    void on() {
      light.TurnOnTheLight();
      airConditioner.TurnOnTheAirConditioner();
      television.TurnOnTheTelevision();
      stereoSystem.TurnOnTheStereoSystem();
      std::cout << "All systems are turned on" << std::endl;
    }
    void off() {
      light.TurnOffTheLight();
      airConditioner.TurnOffTheAirConditioner();
      television.TurnOffTheTelevision();
      stereoSystem.TurnOffTheStereoSystem();
      std::cout << "All systems are turned off" << std::endl;
    }
};