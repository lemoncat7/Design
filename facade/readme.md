<!--
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-19 10:02:41
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-19 10:02:42
-->
# 门面模式

平常开发过程中是否会遇到接口颗粒的问题. 

一般情况下, 我门为了保证接口的可复用性, 会讲接口设计的细一些, 保证职责单一.

但是如果颗粒太小, 在业务开发中可能会调用 n多个细颗粒的接口. 

但是如果颗粒太大, 一个接口有n多个事情要做,返回n多个数据, 就会导致接口复用性不够好, 不够通用. 

## 介绍

`门面模式为子系统提供一组统一的接口，定义一组高层接口让子系统更易用。`

一下举个例子说明

假设有a, b, c, d 四个细颗粒接口, 业务需要使用a, b, d, 那就可以使用 门面模式将a, b, d包裹起来对外提供一个门面接口 x直接给业务调用. 

那么为什么不直接使用三个接口, 而是又封装一层呢?

假设系统调用接口通过网络通信获取数据, 一般网络通信耗时比较多, 为了提高响应速度, 我们要尽量减少系统间的网络通信次数. 

如果完成一个业务需要依次调用a, b, d三个接口, 且不支持并发操作, 有可能会导致接口调用次数过多的网络通信, 导致系统响应过慢.

## 定义

以这个需求作为示例

我需要一种方式来通过手机控制家庭的多个智能设备，如灯光、空调、音响等，而无需每次都与每个设备互动。

四个子系统

```cpp
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
```

定义门面系统包裹四个接口

```cpp
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
```

## 调用

```cpp
FacadeSystem facade;
facade.on();
facade.off();
```

## 效果

```cpp
./bin/design/Facade        
Turn On The Light
Turn On The Air Conditioner
Turn On The Television
Turn On The Stereo System
All systems are turned on
Turn Off The Light
Turn Off The Air Conditioner
Turn Off The Television
Turn Off The Stereo System
```

## 回顾

类、模块、系统之间的“通信”, 一般都是通过接口调用来完成的. 接口设计的好坏, 直接影响到类、模块、系统是否好用.

接口粒度设计得太大, 太小都不好. 太大会导致接口不可复用, 太小会导致接口不易用. 在实际的开发中, 接口的可复用性和易用性需要“微妙”的权衡. 针对这个问题. 基本的处理原则是, **尽量保持接口的可复用性, 但针对特殊情况, 允许提供冗余的门面接口, 来提供更易用的接口**。

“门面模式让子系统更加易用”, 实际上, 它除了解决易用性问题之外, 还能解决其他很多方面的问题.

强调一下，门面模式定义中的**“子系统（subsystem）”**也可以有多种理解方式。它既可以是一个完整的系统，也可以是更细粒度的类或者模块。

## 应用场景

门面模式适用于以下情况：

1. 简化复杂系统： 当你需要与一个复杂子系统进行交互，而子系统内部包含多个组件、类或服务，门面模式能够将这些复杂性封装起来，提供一个更简单的接口供客户端使用。
2. 隐藏子系统的复杂性： 当客户端不需要了解子系统的内部工作原理，只关心如何与子系统交互时，门面模式非常有用。门面提供了抽象接口，隐藏了内部的复杂性，让客户端更容易使用。
3. 降低耦合度： 门面模式可以减少客户端与子系统之间的耦合。这使得系统更加灵活，因为子系统的改变不会影响客户端代码。
4. 提供一个单一入口点： 当你希望为系统提供一个单一的入口点，以便执行多个操作或任务时，门面模式非常有用。客户端只需与门面互动，而不必关心系统中的多个部分。
5. 简化接口： 当多个接口和方法需要协同工作以执行一个任务时，门面模式可以将这些操作封装在一个单一接口中，从而减少客户端需要处理的细节。
6. 遗留系统集成： 在将新系统与遗留系统集成时，门面模式可以充当接口，使新系统与遗留系统进行通信更容易。
7. 性能优化： 在某些情况下，门面模式可以用于优化性能，例如缓存复杂操作的结果，以减少计算的重复执行。