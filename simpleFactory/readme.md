<!--
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-08 10:47:02
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-08 11:21:32
-->

# 简单工厂模式

## 介绍

创建型模式主要关注对象创建的过程, 论述是如何将对象的创建和使用进行分离, 让用户在使用对象时无须关心创建对象的细节, 从而降低系统的耦合度.

简单工厂 作为最基础的设计模式之一, 并不属于gof 的23 个设计模式, 但也是其余创建型模式的基础

## 简单工厂的基本流程

- 设计一个抽象产品类，它包含一些公共方法的实现；

```cpp
class AbstractBall {
public:
    virtual void get() = 0;
    virtual void play() = 0;
    virtual ~AbstractBall() = default;
};
```

- 从抽象产品类中派生出多个具体产品类，如篮球类、足球类、排球类，具体产品类中实现具体产品生产的相关代码；

```
class FootBall : public AbstractBall {
public:
    void get() override { std::cout << "get footBall" << std::endl; }
    void play() override { std::cout << "play footBall" << std::endl;}
};

class BasketBall : public AbstractBall {
public:
    void get() override { std::cout << "get basketBall" << std::endl; }
    void play() override { std::cout << "play basketBall" << std::endl;}
};

class Volleyball : public AbstractBall {
public:
    void get() override { std::cout << "get volleyball" << std::endl; }
    void play() override { std::cout << "play volleyball" << std::endl;}
};
```

- 设计一个工厂类，工厂类中提供一个生产各种产品的工厂方法，该方法根据传入参数（产品名称）创建不同的具体产品类对象；

```cpp
enum Type {
    FootBallType = 1,
    BasketBallType = 2,
    VolleyballType = 3
    };

class SimpleFactory {
public:
    std::shared_ptr<AbstractBall> createBall(Type type) {
        switch (type) {
            case 1:
                return std::make_shared<FootBall>();
            case 2:
                return std::make_shared<BasketBall>();
            case 3:
                return std::make_shared<Volleyball>();
            default:
                return nullptr;
        }
    }
};
```

- 客户只需调用工厂类的工厂方法，并传入具体产品参数，即可得到一个具体产品对象。

```cpp
SimpleFactory s;
  auto ball1 = s.createBall(Type::BasketBallType);
  ball1->get();
  ball1->play();
  auto ball2 = s.createBall(Type::FootBallType);
  ball2->get();
  ball2->play();
  auto ball3 = s.createBall(Type::VolleyballType);
  ball3->get();
  ball3->play();
```

## 定义

- **工厂（Factory）**：根据客户提供的具体产品类的参数，创建具体产品实例；
- **抽象产品（AbstractProduct）**：具体产品类的基类，包含创建产品的公共方法；
- **具体产品（ConcreteProduct）**：抽象产品的派生类，包含具体产s品特有的实现方法，是简单工厂模式的创建目标。

## 效果

```cpp
//执行可执行文件
./SimpleFactory
//输出
get basketBall
play basketBall
get footBall
play footBall
get volleyball
play volleyball
```

## 总结

简单工厂模式的优点在于：

- 工厂类提供创建具体产品的方法，并包含一定判断逻辑，客户不必参与产品的创建过程；
- 客户只需要知道对应产品的参数即可，参数一般简单好记，如数字、字符或者字符串等。

但是 存在明显的不足

如果想玩其他的球了, 一方面再继承实现, 另一方面还需要再工厂添加对应的类型. 但是这违背了开闭原则

另一方面，简单工厂模式所有的判断逻辑都在工厂类中实现，一旦工厂类设计故障，则整个系统都受之影响！