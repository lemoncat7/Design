/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-24 10:18:48
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-24 11:22:15
 */
#include "Observer.hpp"

int main() {
  std::shared_ptr<WeatherConcrete> weather = std::make_shared<WeatherConcrete>();
  weather->RegisterObserver(std::make_shared<Smartphone>());
  weather->RegisterObserver(std::make_shared<SmartHouse>());
  weather->RegisterObserver(std::make_shared<SmartDresser>());
  weather->RegisterObserver(std::make_shared<TV>());
  weather->setMeasurements(18, 20, Weather::CLOUDY, {23,24,24,24,23,21});
  weather->setMeasurements(35, 40, Weather::SUNNY, {35,55,40,35,32,30});
}