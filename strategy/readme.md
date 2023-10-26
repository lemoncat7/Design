<!--
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-26 11:18:52
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-26 11:18:53
-->
## 介绍

策略模式(Strategy Pattern)是一种软件设计模式,属于行为型模式。它定义了一系列算法,将每个算法封装起来,并让它们可以相互替换。策略模式可以让算法独立于使用它的客户而变化,从而使得系统更容易扩展。

工厂模式是解耦对象的创建和使用，观察者模式是解耦观察者和被观察者。策略模式跟两者类似，也能起到解耦的作用，不过，它解耦的是策略的定义、创建、使用这三部分。

策略模式的主要 PARTICIPANT 如下:

`Context` - 环境类,持有一个 Strategy 对象,通过调用 Strategy 来执行算法。

`Strategy` - 抽象策略类,定义了一个公共接口,各种不同的算法以不同的 Strategy 类实现这些接口。`ConcreteStrategy` - 具体策略类,实现了 Strategy 定义的接口,提供具体的算法实现。

客户通过 `Context` 访问不同的 `ConcreteStrategy`,从而动态改变 `Context` 执行的算法。

`Context` 和各个 `ConcreteStrategy` 之间松耦合,使得算法可以灵活替换。

策略模式的优点:

- 算法可以独立于使用它的客户而变化,避免频繁改动客户代码。
- 可以方便地增加新的算法而不影响已有代码。
- 遵循开闭原则,对扩展开放,对修改关闭。

策略模式的缺点:

- 客户必须明确地知道不同 Strategies 的区别,以便选择恰当的算法。
- 增加新的策略类会增加系统的复杂度。

策略模式通常适用于一个系统需要动态地在多个算法中选择一种算法的情况。由于算法之间低耦合,策略模式经常被用在可以通过配置文件进行选择的情况。

## 定义

假设我们要开发一个农场管理游戏,玩家可以种不同的庄稼。不同的庄稼需要采用不同的栽种策略,例如小麦需要晴天播种,稻米需要浇水栽种。

这个时候我们就可以使用策略模式:定义一个栽种策略接口,具体的小麦栽种策略、稻米栽种策略来实现这个接口。游戏中的农场可以组合不同的栽种策略来适应不同的庄稼。

当游戏需要新增庄稼种类时,我们只需要增加一个新的栽种策略类,而不需要修改农场类的代码。所以这里的可变的是栽种策略,我们通过策略模式来封装这些可变的算法,使农场类逻辑不受栽种策略变化的影响。

定义一个策略基类

```cpp
// 栽种策略接口
class PlantStrategy {
public:
  virtual void plant() = 0; 
};
```

实现不同的策略接口

```cpp
// 小麦栽种策略  
class WheatPlantStrategy : public PlantStrategy {
public:
  void plant() override {
    // 小麦栽种逻辑
    std::cout << "小麦栽种逻辑" << std::endl;
  }
};

// 稻米栽种策略
class RicePlantStrategy : public PlantStrategy {
public:
  void plant() override {
    // 稻米栽种逻辑
    std::cout << "稻米栽种逻辑" << std::endl;
  }  
};
```

农场实行不同策略

```cpp
// 农场类
class Farm {
private:
  PlantStrategy* strategy; 

public:
  void setStrategy(PlantStrategy* strategy) {
    this->strategy = strategy;
  }

  void plantCrop() {
    strategy->plant(); 
  }
};
```

## 调用

```cpp
// 使用
Farm* farm = new Farm();
farm->setStrategy(new WheatPlantStrategy());
farm->plantCrop();  // 调用小麦栽种逻辑

farm->setStrategy(new RicePlantStrategy());
farm->plantCrop();  // 调用稻米栽种逻辑
```

## 效果

```cpp
./bin/design/strategy
小麦栽种逻辑
稻米栽种逻辑
```

## 回顾

策略模式定义一族算法类，将每个算法分别封装起来，让它们可以互相替换。策略模式可以使算法的变化独立于使用它们的客户端（这里的客户端代指使用算法的代码）。

策略模式用来解耦策略的定义、创建、使用。实际上，一个完整的策略模式就是由这三个部分组成的。

- 策略类的定义比较简单，包含一个策略接口和一组实现这个接口的策略类。
- 策略的创建由工厂类来完成，封装策略创建的细节。
- 策略模式包含一组策略可选，客户端代码如何选择使用哪个策略，有两种确定方法：编译时静态确定和运行时动态确定。其中，“运行时动态确定”才是策略模式最典型的应用场景。

除此之外，我们还可以通过策略模式来移除if-else分支判断。实际上，这得益于策略工厂类，更本质上点讲，是借助“查表法”，根据type查表替代根据type分支判断。