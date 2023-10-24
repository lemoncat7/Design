<!--
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-24 11:16:37
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-24 11:16:40
-->
# 观察者模式

从今天起, 开始学习行为型设计模式. 

我们常把23种经典的设计模式分为三类: 创建型、结构型、行为型.

创建型设计模式主要解决“对象的创建”问题. 

结构型设计模式主要解决“类或对象的组合或组装”问题, 

行为型设计模式主要解决的就是“类或对象之间的交互”问题.

## 介绍

观察者模式(Observer Pattern),它定义对象之间的一种一对多的依赖关系,以便当一个对象的状态发生改变时,所有依赖于它的对象都得到通知并被自动更新.

其工作原理如下:

1. 主题将所有观察它的对象保存在一个集合中。
2. 当主题状态发生改变时,会遍历所有观察者,调用它们的更新方法。
3. 观察者收到通知后会执行相应的更新逻辑。

观察者模式可以实现对象之间的松耦合,当主题状态发生改变时,可以通知多个观察者对象,而无需每个观察者都了解主题的具体实现. 适用于需要维护对象之间一致性的系统.

根据应用场景的不同,观察者模式会对应不同的代码实现方式: 有同步阻塞的实现方式, 也有异步非阻塞的实现方式; 有进程内的实现方式, 也有跨进程的实现方式.

## 定义

这里用一个简单的天气预报系统来说明观察者模式:

假设有一个天气预报站,它可以实时监测城市的温度、湿度、气压等数据。

然后有以下几类观察者:

1. 手机软件:需要实时显示当前天气数据,以及未来24小时预测。
2. 电视新闻:需要定期擦拭最新的温度和空气质量,报道天气概况。
3. 房屋智能控制系统:根据温湿度调整空调、加湿器等家电。
4. 衣柜智能推荐系统:根据天气选择推荐的服装。

这样当天气预报站的数据更新时,就会实时通知所有的观察者,各观察者接收到更新后,做出各自的响应:

1. 手机软件实时更新显示信息。
2. 新闻在下一个时段报道最新天气。
3. 智能控制系统调整家电参数。
4. 智能衣柜修改推荐列表。

天气预报

```cpp
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
```

观察者

```cpp
//观察者基类
class Observer {
 public:
  virtual ~Observer() = default;
  virtual void update(WeatherAbstract *weather) = 0;
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
```

## 调用

```cpp
std::shared_ptr<WeatherConcrete> weather = std::make_shared<WeatherConcrete>();
weather->RegisterObserver(std::make_shared<Smartphone>());
weather->RegisterObserver(std::make_shared<SmartDresser>());
weather->RegisterObserver(std::make_shared<SmartDresser>());
weather->RegisterObserver(std::make_shared<TV>());
weather->setMeasurements(18, 20, Weather::CLOUDY, {23,24,24,24,23,21});
weather->setMeasurements(35, 40, Weather::SUNNY, {35,55,40,35,32,30});
```

## 效果

```cpp
./bin/design/observer 
Smartphone: 当前温度18℃ 
            未来天气预测23℃ 24℃ 24℃ 24℃ 23℃ 21℃ 
SmartDresser: 当前天气阴天，建议带外套
SmartDresser: 当前天气阴天，建议带外套
TV: 当前温度18℃ 
    当前湿度20% 
Smartphone: 当前温度35℃ 
            未来天气预测35℃ 55℃ 40℃ 35℃ 32℃ 30℃ 
SmartDresser: 当前天气晴朗，建议穿短袖
SmartDresser: 当前天气晴朗，建议穿短袖
TV: 当前温度35℃ 
    当前湿度40%
```

## 回顾

设计模式要干的事情就是解耦

创建型模式是将创建和使用代码解耦

结构型模式是将不同功能代码解耦

行为型模式是将不同的行为代码解耦

具体到观察者模式, 它将观察者和被观察者代码解耦。

观察者模式的应用场景非常广泛, 小到代码层面的解耦, 大到架构层面的系统解耦, 再或者一些产品的设计思路, 都有这种模式的影子, 比如, 邮件订阅, RSS Feeds, 本质上都是观察者模式, 不同的应用场景和需求下, 这个模式也有截然不同的实现方式, 有同步阻塞的实现方式, 也有异步非阻塞的实现方式; 有进程内的实现方式, 也有跨进程的实现方式.