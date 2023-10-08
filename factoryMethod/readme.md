<!--
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-08 14:38:14
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-08 15:08:51
-->
# 工厂方法模式

在GoF的《设计模式》一书中，它将简单工厂模式看作是工厂方法模式的一种特例，所以工厂模式只被分成了工厂方法和抽象工厂两类。实际上，前面一种分类方法更加常见.

## 介绍

简单工厂每次增加一个产品都需要修改工厂代码内部的逻辑, 为了遵循**开闭原则**, 工厂方法将不在使用一个工厂统一进行所有产品的生产, 而是每一个产品都由一个工厂进行生产. 

## 定义

- **抽象工厂（AbstractFactory）**：所有生产具体产品的工厂类的基类，提供工厂类的公共方法；
- **具体工厂（ConcreteFactory）**：生产具体的产品
- **抽象产品（AbstractProduct）**：所有产品的基类，提供产品类的公共方法
- **具体产品（ConcreteProduct）**：具体的产品类

## 流程

- 定义抽象产品类, 不提供实现方法

```cpp
class AbstractProduct {		//抽象产品
public:
	AbstractProduct() {}
	virtual void print() = 0;
	virtual void play() = 0;
};
```

- 定义三个具体产品类

```cpp
class PowerArmor : public AbstractProduct {
public:
	PowerArmor() {
		print();
		play();
	}
	void print() {
		std::cout << "得到一个动力装甲" << std::endl;
	}
	void play() {
		std::cout << "动力装甲因太过脆弱而被损坏" << std::endl;
	}
};

class FlyingPowder : public AbstractProduct {
public:
	FlyingPowder() {
		print();
		play();
	}
	void print() {
		std::cout << "得到一个飞路粉" << std::endl;
	}
	void play() {
		std::cout << "飞路粉太香招来苍蝇" << std::endl;
	}
};

class Goblins : public AbstractProduct {
public:
	Goblins() {
		print();
		play();
	}
	void print() {
		std::cout << "得到一个哥布林" << std::endl;
	}
	void play() {
		std::cout << "暴躁的哥布林发起了进攻" << std::endl;
	}
};
```

- 定义抽象工厂, 纯虚类

```cpp
class AbstractFactory {
public :
	AbstractFactory() {}
	virtual std::shared_ptr<AbstractProduct> getProduct() = 0;
};
```

- 定义三个具体方法工厂

```cpp
class MachineryFactory : public AbstractFactory{
public : 
	MachineryFactory() {}
	std::shared_ptr<AbstractProduct> getProduct() {
		return std::make_shared<PowerArmor>();
	}
};

class MagicFactory : public AbstractFactory {
public:
	MagicFactory() {}
	std::shared_ptr<AbstractProduct> getProduct() {
		return std::make_shared<FlyingPowder>();
	}
};

class Greenfactory : public AbstractFactory {
public:
	Greenfactory() {}
	std::shared_ptr<AbstractProduct> getProduct() {
		return std::make_shared<Goblins>();
	}
};
```

- 用户使用方法

```cpp
#include "FactoryMethod.hpp"

int main() {
  std::shared_ptr<AbstractFactory> factory = nullptr;
  std::shared_ptr<AbstractProduct> product = nullptr;
  factory = std::make_shared<MachineryFactory>();
  product = factory->getProduct();
  factory = std::make_shared<MagicFactory>();
  product = factory->getProduct();
  factory = std::make_shared<Greenfactory>();
  product = factory->getProduct();
  return 0;
}
```

- 效果

```cpp
./bin/design/FactoryMethod

得到一个动力装甲
动力装甲因太过脆弱而被损坏
得到一个飞路粉
飞路粉太香招来苍蝇
得到一个哥布林
暴躁的哥布林发起了进攻
```

## 总结

如果 想要新增一个产品只需要增加对应的产品和生产产品的工厂, 此方式不会修改或影响到之前已存在的产品代码. 由此可见, 相对于简单工厂更加符合 **开闭原则**, 工厂方法是使用频率最高的设计模式之一，是很多开源框架和API类库的核心模式.

## 优点:

- 工厂方法用于创建客户所需产品，同时向客户隐藏某个具体产品类将被实例化的细节，用户只需关心所需产品对应的工厂；
- 工厂自主决定创建何种产品，并且创建过程封装在具体工厂对象内部，多态性设计是工厂方法模式的关键；
- 新加入产品时，无需修改原有代码，增强了系统的可扩展性，符合开闭原则。

## 缺点:

- 添加新产品时需要同时添加新的产品工厂，系统中类的数量成对增加，增加了系统的复杂度，更多的类需要编译和运行，增加了系统的额外开销；
- 工厂和产品都引入了抽象层，客户端代码中均使用的抽象层（AbstractFactory和AbstractSportProduct ），增加了系统的抽象层次和理解难度。

## 适用:

- 客户端不需要知道它所需要创建的对象的类；
- 抽象工厂类通过其子类来指定创建哪个对象（运用多态性设计和里氏代换原则）

**那什么时候该用工厂方法模式，而非简单工厂模式呢？**

之所以将某个代码块剥离出来，独立为函数或者类，原因是这个代码块的逻辑过于复杂，剥离之后能让代码更加清晰，更加可读、可维护。但是，如果代码块本身并不复杂，就几行代码而已，我们完全没必要将它拆分成单独的函数或者类。

基于这个设计思想，当对象的创建逻辑比较复杂，不只是简单的new一下就可以，而是要组合其他类对象，做各种初始化操作的时候，我们推荐使用工厂方法模式，将复杂的创建逻辑拆分到多个工厂类中，让每个工厂类都不至于过于复杂。而使用简单工厂模式，将所有的创建逻辑都放到一个工厂类中，会导致这个工厂类变得很复杂。

除此之外，在某些场景下，如果对象不可复用，那工厂类每次都要返回不同的对象。如果我们使用简单工厂模式来实现，就只能选择第一种包含if分支逻辑的实现方式。如果我们还想避免烦人的if-else分支逻辑，这个时候，我们就推荐使用工厂方法模式。