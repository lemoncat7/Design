<!--
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-17 10:26:18
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-17 10:26:18
-->
# 装饰器模式

装饰器模式的代码结构跟桥接模式非常相似, 但是两者针对的问题却并不相同

## 介绍：

  `装饰器模式允许你附加新的行为到对象实例上，同时保持对象类的完整性。装饰器模式通常用于通过递归组合方式，使类能够包含更多的责任，同时保持系统中的每个类小而简单。`

装饰器模式用于在运行时动态添加功能，而桥接模式用于将抽象和实现分离以处理多维度的变化。

他们可以由以下几点区分:

1. **主要目的**：
    - 装饰器模式的主要目的是动态地为对象添加行为，而不修改其原始类。它用于在运行时包装对象，以添加新的功能，例如添加额外的操作或状态。装饰器模式关注对象的功能扩展。
    - 桥接模式的主要目的是将抽象和实现分离，使它们可以独立变化。它用于处理多维度的变化，例如在多个维度上有多个实现，然后通过组合在不同维度上选择不同的实现。桥接模式关注不同维度的独立变化。
2. **结构差异**：
    - 装饰器模式包括抽象组件、具体组件、装饰器抽象类和具体装饰器。它通过递归性地包装对象来添加功能，具体装饰器可以在运行时添加额外的功能。
    - 桥接模式包括抽象类、具体类、抽象实现类和具体实现类。它通过将抽象类和实现类分离来处理多维度的变化，允许它们独立变化。
3. **应用场景**：
    - 装饰器模式适用于需要在不修改原始类的情况下动态添加功能的场景。它通常用于需要包装核心对象以添加功能，例如输入/输出流、窗口控件等。
    - 桥接模式适用于多个维度上有多个实现，并且需要将这些维度进行解耦的场景。它通常用于处理多维度的变化，例如操作系统平台和文件系统的组合。
4. **关注点**：
    - 装饰器模式的关注点在于在现有对象上添加功能。
    - 桥接模式的关注点在于将抽象和实现分离，以处理多维度的变化。

## 定义

**场景**：假设你是一个冰淇淋店的经营者，你有各种类型的冰淇淋，如巧克力冰淇淋、草莓冰淇淋、香草冰淇淋等。你想允许顾客根据自己的口味选择各种配料，如巧克力酱、坚果、草莓酱等，以定制他们的冰淇淋。

抽象冰激凌类

```cpp
// 冰激凌抽象类
class AbstractIceCream {
 public:
  virtual ~AbstractIceCream() = default;
  virtual const std::string MakeIceCream() = 0;
};
```

实现具体冰激凌

```cpp
// 草莓冰激凌
class StrawberryIceCream : public AbstractIceCream {
 public:
  const std::string MakeIceCream() override { return "草莓冰激凌"; }
};

// 巧克力冰激凌
class ChocolateIceCream : public AbstractIceCream {
 public:
  const std::string MakeIceCream() override { return "巧克力冰激凌"; }
};
```

抽象装饰器

```cpp
// 装饰器抽象类
class AbstractDecorator : public AbstractIceCream {
 public:
  virtual ~AbstractDecorator() = default;
  virtual const std::string MakeIceCream() = 0;
  virtual void SetIceCream(std::shared_ptr<AbstractIceCream> iceCream) {
    iceCream_ = iceCream;
  }
  virtual std::shared_ptr<AbstractIceCream> GetIceCream() { return iceCream_; }

 protected:
  std::shared_ptr<AbstractIceCream> iceCream_;
};
```

实现具体的装饰器

```cpp
//巧克力酱装饰器
class ChocolateIceCreamChunk : public AbstractDecorator {
 public:
  const std::string MakeIceCream() override {
    return GetIceCream()->MakeIceCream() + AddChocolateChips();
  }
  const std::string AddChocolateChips() {
    return "撒上巧克力豆";
  }
};

//坚果装饰器
class NutsIceCreamChunk : public AbstractDecorator {
 public:
  const std::string MakeIceCream() override {
    return GetIceCream()->MakeIceCream() + AddNuts();
  }
  const std::string AddNuts() {
    return "撒上一把坚果";
  }
};

//布丁装饰器
class PuddingIceCreamChunk : public AbstractDecorator {
 public:
  const std::string MakeIceCream() override {
    return GetIceCream()->MakeIceCream() + AddPudding();
  }
  const std::string AddPudding() {
    return "撒上一块布丁";
  }
};
```

## 调用

```cpp
//想要制作一个巧克力冰激凌
auto chocolate = std::make_shared<ChocolateIceCream>();
//加上布丁
auto pudding = std::make_shared<PuddingIceCreamChunk>();
pudding->SetIceCream(chocolate);
//加上坚果
auto nuts = std::make_shared<NutsIceCreamChunk>();
nuts->SetIceCream(pudding);
//制作
std::cout << nuts->MakeIceCream() << std::endl;
//想要制作一个草莓冰激凌
auto strawberry = std::make_shared<StrawberryIceCream>();
//加上巧克力豆
auto chocolate_beans = std::make_shared<ChocolateIceCreamChunk>();
chocolate_beans->SetIceCream(strawberry);
//加上布丁
auto pudding_beans = std::make_shared<PuddingIceCreamChunk>();
pudding_beans->SetIceCream(chocolate_beans);
//制作
std::cout << pudding_beans->MakeIceCream() << std::endl;
```

## 效果

```cpp
./bin/design/Decorator
巧克力冰激凌撒上一块布丁撒上一把坚果
草莓冰激凌撒上巧克力豆撒上一块布丁
```

## **优点**：

允许动态地添加功能，避免使用继承，保持对象类的简单性，符合开放-封闭原则（对扩展开放，对修改关闭）。

## **缺点**：

可能会导致类的数量增加，以及复杂的对象层次结构。

装饰器模式允许您在运行时包装对象并以递归方式添加功能，这在需要动态地修改对象行为而不影响其原始类的情况下非常有用。它是一种强大的模式，用于扩展对象的功能，同时保持代码的灵活性和可维护性。

**适用情况**：当需要在不修改现有对象类的情况下，动态地添加功能或职责时，使用装饰器模式。