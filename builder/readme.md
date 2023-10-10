<!--
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-10 12:00:18
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-10 12:00:19
-->
# 建造者模式

**Builder模式,** 中文翻译为**建造者模式**或者**构建者模式,** 也有人叫它**生成器模式.** 也是比较常用的创建型设计模式.

本身代码的原理和实现掌握起来不难, 难点在于他的应用场景. 

下面可以围绕这两个问题进行了解

1. 既然可以直接用构造函数 或者使用set函数设置参数进行构建对象, 为什么还需要使用建造者进行对象的构建
2. 建造者模式和工厂模式都可以创建对象，那它们两个的区别在哪里

## 介绍

建造者模式将包含多个部件的对象的构建过程进行剥离, 客户只需要给出他需要的部件类型, 不用关心如何构建, 以及构建的细节.

比如你,我都需要造一间房子, 造房子的过程无非是从打地基, 筑墙, 装修等过程, 但是最后你, 我期望的房子的风格肯定是不一样的,  最终建造的房子肯定呈现不同风格.

## 问题1. 为什么使用建造者

平常开发中, 最常用new 构造出一个对象. 

假设 这里有个一个类 House

```cpp
#define DEFAULT_ROOF "default roof"
#define DEFAULT_WALL "default wall"
#define DEFAULT_FLOOR "default floor"
class House {
private:
  std::string roof_;
  std::string wall_;
  std::string floor_;
public:
  House(std::string roof, std::string wall, std::string floor) {
    if (roof.empty()) {
      roof = DEFAULT_ROOF;
    }
    if (wall.empty()) {
      wall = DEFAULT_WALL;
    }
    if (floor.empty()) {
      floor = DEFAULT_FLOOR;
    }
    roof_ = roof;
    wall_ = wall;
    floor_ = floor;
  }
};
```

给空字符串表示使用默认风格的装饰. 现在只有三个选项, 但如果需要增加其他的装修什么吊灯, 沙发啥的… 参数逐渐增多，变成了8个、10个，甚至更多. 如果继续沿用现在的风格, 构造函数只会变得更长, 可读性和易用性就会变差. 

这个时候就会想到定义set变量的函数, 你需要用哪个就自己设这个变量

```cpp
#define DEFAULT_ROOF "default roof"
#define DEFAULT_WALL "default wall"
#define DEFAULT_FLOOR "default floor"

class House {
private:
  std::string roof_;
  std::string wall_;
  std::string floor_;
public:
  House() {}
  void setRoof(std::string roof) { roof_ = roof;}
  void setWall(std::string wall) { wall_ = wall;}
  void setFloor(std::string floor) { floor_ = floor;}
};
```

到现在仍未使用 建造者模式, 但可以再想下以下场景是否能够适配

1. 假设有一些必填项, 比如大小, 空间, 占地, 门牌… 这些需要放到构造函数中强制填入, 那参数列表又会很长. 但如果使用set 函数, 没地方进行校验.
2. 假设大小, 占地这些参数有关联和约束, 也没有地方进行校验.
3. 假设房子造完了, 我不期望他的属性进行修改, 那就不能暴露他的 set函数

这时候可以使用建造者 

我们可以把校验逻辑放置到Builder类中，先创建建造者，并且通过set()方法设置建造者的变量值，然后在使用build()方法真正创建对象之前，做集中的校验，校验通过之后才会创建对象。

当然我们也可以将Builder类设计成独立的非内部类

以下代码隐藏了 house的set 函数, 并在House::Builder::build中进行了校验

```cpp
#define DEFAULT_ROOF "default roof"
#define DEFAULT_WALL "default wall"
#define DEFAULT_FLOOR "default floor"

class House {
private:
  std::string roof_;
  std::string wall_;
  std::string floor_;
  House() {}
  void setRoof(std::string roof) { roof_ = roof;}
  void setWall(std::string wall) { wall_ = wall;}
  void setFloor(std::string floor) { floor_ = floor;}
public:
  void print()  {
    std::cout << "roof : " << roof_ << std::endl;
    std::cout << "wall : " << wall_ << std::endl;
    std::cout << "floor : " << floor_ << std::endl;
  }
  class Builder {
  private:
    std::string roof_;
    std::string wall_;
    std::string floor_;
  public:
    Builder() {}
    ~Builder() {}
    void setRoof(std::string roof) { roof_ = roof; }
    void setWall(std::string wall) { wall_ = wall; }
    void setFloor(std::string floor) { floor_ = floor; }
    House* build() {
      if (roof_.empty()) {
        roof_ = DEFAULT_ROOF;
      }
      if (wall_.empty()) {
        wall_ = DEFAULT_WALL;
      }
      if (floor_.empty()) {
        floor_ = DEFAULT_FLOOR;
      }
      House *house_ = new House();
      house_->setRoof(roof_);
      house_->setWall(wall_);
      house_->setFloor(floor_);
      return house_;
    }
  };
};
```

客户使用方式

```cpp
int main() {
  House::Builder builder;
  builder.setFloor("red floor");
  auto* house = builder.build();
  house->print();
  return 0;
}
```

效果

```cpp
./bin/design/Builder
roof : default roof
wall : default wall
floor : red floor
```

## 问题2. 与工厂模式有何区别？

工厂模式是用来创建不同但是相关类型的对象, 由给定的参数来决定创建哪种类型的对象. 建造者模式是用来创建一种类型的复杂对象, 通过设置不同的可选参数, “定制化”地创建不同的对象.

网上有一个经典的例子很好地解释了两者的区别.

顾客走进一家餐馆点餐, 我们利用工厂模式, 根据用户不同的选择, 来制作不同的食物, 比如披萨、汉堡、沙拉. 对于披萨来说, 用户又有各种配料可以定制, 比如奶酪、西红柿、起司，我们通过建造者模式根据用户选择的不同配料来制作披萨.

## 优点

1. 将构建过程进行剥离, 客户无需关心建造的细节. 使用同样的建造过程创建不同风格的对象. 
2. 如果将建造者放到类外实现, 可以实现多个建造者建造不同风格的house, 这些建造者相互独立, 无依赖. 

## 缺点

1. 创建的产品一般具有较多的共同点, 如果产品之间的差异性很大，则不适合使用建造者模式，因此其使用范围受到一定的限制。

### 适用

- 需要生成的产品对象有复杂的内部结构（通常包含多个成员变量）；
- 产品对象内部属性有一定的生成顺序；
- 同一个创建流程适用于多种不同的产品。