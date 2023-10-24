/*
 * @Description:
 * @version:
 * @Author: 莫邪
 * @Date: 2023-10-24 10:18:44
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-24 11:05:01
 */
#include <iostream>
#include <memory>
class WeatherAbstract;
//观察者基类
class Observer {
 public:
  virtual ~Observer() = default;
  virtual void update(WeatherAbstract *weather) = 0;
};

enum Weather {
  SUNNY,
  CLOUDY,
  RAINY,
  SNOWY,
};
// 天气预报基类
class WeatherAbstract {
 public:
  virtual void measurementsChanged() = 0;
  virtual int GetTemperature() = 0;
  virtual int GetHumidity() = 0;
  virtual Weather GetWeather() = 0;
  virtual std::vector<int> GetPreWeather() = 0;
  virtual void RegisterObserver(std::shared_ptr<Observer> observer) = 0;
};
// 天气类实现
class WeatherConcrete : public WeatherAbstract {
 public:
  WeatherConcrete() = default;
  virtual ~WeatherConcrete() = default;
  int GetTemperature() override { return temperature_; }
  int GetHumidity() override { return humidity_; }
  Weather GetWeather() override { return weather_; }
  std::vector<int> GetPreWeather() override { return pre_weather_; }
  void RegisterObserver(std::shared_ptr<Observer> observer) override {
    observers_.push_back(observer);
  }
  void setMeasurements(int temperature, int humidity, Weather weather,
                       std::vector<int> pre_weather) {
    temperature_ = temperature;
    humidity_ = humidity;
    weather_ = weather;
    pre_weather_ = pre_weather;
    measurementsChanged();
  }
  void measurementsChanged() override { notifyObservers(); }

 private:
  void notifyObservers() {
    for (auto &observer : observers_) {
      observer->update(this);
    }
  }
  // 温度
  int temperature_;
  // 天气预测
  std::vector<int> pre_weather_;
  // 湿度
  int humidity_;
  // 天气
  Weather weather_;
  // 观察者
  std::vector<std::shared_ptr<Observer>> observers_;
};

// 手机
class Smartphone : public Observer {
 public:
  Smartphone() = default;
  virtual ~Smartphone() = default;
  void update(WeatherAbstract *weather) override {
    std::cout << "Smartphone: 当前温度" << weather->GetTemperature() << "℃ " << std::endl;
    std::string pre_we;
    for (auto &pre_weather : weather->GetPreWeather()) {
      pre_we += std::to_string(pre_weather) + "℃ ";
    }
    std::cout << "            未来天气预测" << pre_we << std::endl;
  }
};

//电视
class TV : public Observer {
 public:
  TV() = default;
  virtual ~TV() = default;
  void update(WeatherAbstract *weather) override {
    std::cout << "TV: 当前温度" << weather->GetTemperature() << "℃ " << std::endl;
    std::cout << "    当前湿度" << weather->GetHumidity() << "% " << std::endl;
  }
};

//房屋智能
class SmartHouse : public Observer {
 public:
  SmartHouse() = default;
  virtual ~SmartHouse() = default;
  void update(WeatherAbstract *weather) override {
    if (weather->GetTemperature() < 22) {
      std::cout << "SmartHouse: 当前温度" << weather->GetTemperature() << "℃ , 提高空调温度 10%" << std::endl;
    } else if(weather->GetTemperature() > 30){
      std::cout << "SmartHouse: 当前温度" << weather->GetTemperature() << "℃ , 降低空调温度 10%" << std::endl;
    }
    if (weather->GetHumidity() < 20) {
      std::cout << "            当前湿度" << weather->GetHumidity() << "% , 打开加湿器" << std::endl;
    } else if(weather->GetHumidity() > 30){
      std::cout << "            当前湿度" << weather->GetHumidity() << "% , 关闭加湿器" << std::endl;
    }
  }
};

//智能衣柜
class SmartDresser : public Observer {
 public:
  SmartDresser() = default;
  virtual ~SmartDresser() = default;
  void update(WeatherAbstract *weather) override {
    switch(weather->GetWeather()) {
      case Weather::CLOUDY:
        std::cout << "SmartDresser: 当前天气阴天，建议带外套" << std::endl;
        break;
      case Weather::SUNNY:
        std::cout << "SmartDresser: 当前天气晴朗，建议穿短袖" << std::endl;
        break;
      case Weather::RAINY:
        std::cout << "SmartDresser: 当前天气下雨，建议穿雨伞" << std::endl;
        break;
      case Weather::SNOWY:
        std::cout << "SmartDresser: 当前天气下雪，建议穿棉衣" << std::endl;
        break;
    }
  }
};