<!--
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-09 09:30:39
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-09 10:05:05
-->
# 抽象工厂模式

回顾其他两个工厂模式

**简易工厂**将所有逻辑都封装在一个工厂类中, 工厂依据客户提供的名字创建对应的产品

**工厂方法**将产品创建过程封装到一个具体的工厂类中, 每一个工厂可以创建一个具体的产品, 所以需要创建很多工厂

## 介绍

一个工厂不止可以建造一个产品, 他可以建造多个. 比如一个关于运动工厂, 他可以建造篮球, 足球 … 

总之，一个工厂可以提供创建多种相关产品的接口，而无需像工厂方法一样，为每一个产品都提供一个具体工厂。

## 定义

抽象工厂模式结构与工厂方法模式结构类似，不同之处在于，一个具体工厂可以生产多种同类相关的产品：

抽象工厂（AbstractFactory）：所有生产具体产品的工厂类的基类，提供工厂类的公共方法；
具体工厂（ConcreteFactory）：生产具体的产品
抽象产品（AbstractProduct）：所有产品的基类，提供产品类的公共方法
具体产品（ConcreteProduct）：具体的产品类

## 流程

• 抽象产品类AbstractBall, 球类的基类，定义抽象方法play

```cpp
class AbstractBall {
 public:
  virtual ~AbstractBall() = default;
  virtual void play() = 0;
};
```

• 具体产品类， 分别为Basketball、Football、Volleyball，具体实现方法play

```cpp
class BasketBall : public AbstractBall {
 public:
  BasketBall() { play(); }
  void play() override { std::cout << "play basketball" << std::endl; }
};

class Football : public AbstractBall {
 public:
  Football() { play(); }
  void play() override { std::cout << "play football" << std::endl; }
};

class Volleyball : public AbstractBall {
 public:
  Volleyball() { play(); }
  void play() override { std::cout << "play volleyball" << std::endl; }
};
```

• 抽象产品类AbstractShirt：球衣类的基类，定义抽象方法wear

```cpp
class AbstractShirt {
 public:
  virtual ~AbstractShirt() = default;
  virtual void wear() = 0;
};
```

具体产品类BasketballShirt、FootballShirt、VolleyballShirt，具体实现方法wear

```cpp
class BasketShirt : public AbstractShirt {
 public:
  BasketShirt() { wear();}
  void wear() override { std::cout << "wear basketShirt" << std::endl;}
};

class FootballShirt : public AbstractShirt {
 public:
  FootballShirt() { wear();}
  void wear() override { std::cout << "wear footballShirt" << std::endl;}
};

class VolleyballShirt : public AbstractShirt {
 public:
  VolleyballShirt() { wear();}
  void wear() override { std::cout << "wear volleyballShirt" << std::endl;}
};
```

• 定义抽象工厂AbstractFactory，声明两个方法createBall 和 createShirt

```cpp
class AbstractFactory {
 public:
  virtual ~AbstractFactory() = default;
  virtual std::shared_ptr<AbstractBall> createBall() = 0;
  virtual std::shared_ptr<AbstractShirt> createShirt() = 0;
};
```

• 定义具体工厂，重新具体实现两个方法

```cpp
class BasketballFactory : public AbstractFactory {
 public:
  std::shared_ptr<AbstractBall> createBall() override { return std::make_shared<BasketBall>(); }
  std::shared_ptr<AbstractShirt> createShirt() override { return std::make_shared<BasketShirt>();}
};

class FootballFactory : public AbstractFactory {
 public:
  std::shared_ptr<AbstractBall> createBall() override { return std::make_shared<Football>(); }
  std::shared_ptr<AbstractShirt> createShirt() override { return std::make_shared<FootballShirt>();}
};

class VolleyballFactory : public AbstractFactory {
 public:
  std::shared_ptr<AbstractBall> createBall() override { return std::make_shared<Volleyball>(); }
  std::shared_ptr<AbstractShirt> createShirt() override { return std::make_shared<VolleyballShirt>();}
};
```

• 客户使用方式

```cpp
int main() {
  std::shared_ptr<AbstractFactory> factory = nullptr;
  factory = std::make_shared<BasketballFactory>();
  factory->createBall();
  factory->createShirt();
  factory = std::make_shared<FootballFactory>();
  factory->createBall();
  factory->createShirt();
  factory = std::make_shared<VolleyballFactory>();
  factory->createBall();
  factory->createShirt();
  return 0;
}
```

## 效果

```cpp
./bin/design/AbstractFactory
play basketball
wear basketShirt
play football
wear footballShirt
play volleyball
wear volleyballShirt
```

## 总结

抽象工厂在增加一个系列的产品时 只需要增加一个对应产品的工厂就ok了.

但是在已有的具体产品中如果需要新增一类产品, 比如需要一个袜子, 鞋子就需要增加对应的接口和修改对应的工厂类.

## 优点:

- 工厂方法用于创建客户所需产品，同时向客户隐藏某个具体产品类将被实例化的细节，用户只需关心所需产品对应的工厂；
- 新加入产品系列时，无需修改原有系统，增强了系统的可扩展性，符合开闭原则。

## 缺点:

- 在已有产品系列中添加新产品时需要修改抽象层代码，对原有系统改动较大，违背开闭原则

## 适用

- 一系列/一族产品需要被同时使用时，适合使用抽象工厂模式；
- 产品结构稳定，设计完成之后不会向系统中新增或剔除某个产品

三种工厂模式中，简单工厂和工厂方法比较常用，抽象工厂的应用场景比较特殊，所以很少用到.

工厂模式，它的作用无外乎下面这四个。这也是判断要不要使用工厂模式的最本质的参考标准。

- 封装变化：创建逻辑有可能变化，封装成工厂类之后，创建逻辑的变更对调用者透明。
- 代码复用：创建代码抽离到独立的工厂类之后可以复用。
- 隔离复杂性：封装复杂的创建逻辑，调用者无需了解如何创建对象。
- 控制复杂度：将创建代码抽离出来，让原本的函数或类职责更单一，代码更简洁。