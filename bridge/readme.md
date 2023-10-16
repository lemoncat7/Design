## 介绍

桥接模式应该是比较难理解的模式之一, 但是代码的实现相对简单.

对于这个模式可能有两种不同的理解方式

在GoF的《设计模式》一书中，桥接模式是这么定义的：

`“Decouple an abstraction from its implementation so that the two can vary independently。”`

翻译成中文就是：

`“将抽象和实现解耦，让它们可以独立变化。”`

另外一种理解方式：

`“一个类存在两个（或多个）独立变化的维度，我们通过组合的方式，让这两个（或多个）维度可以独立进行扩展。”`

通过组合关系来替代继承关系, 避免继承层次的指数级爆炸. 这种理解方式非常类似于`组合优于继承`设计原则. 

## 原理

就以手机, 和游戏进行举例

手机可以有多个品牌, 可以有华为, 小米, 苹果….

游戏有多个种类, 射击, 冒险, 闯关…

华为可以玩 射击, 冒险,  小米可以玩 冒险, 闯关… 可以有很多种组合

**游戏基类**

```cpp
class Game {
  std::string name;

 public:
  Game(std::string name) : name(name) {}
  virtual ~Game() = default;
  virtual void Play() = 0;
  void print() { std::cout << name << std::endl; }
};
```

**实现**

```cpp
class RunningGame : public Game {
 public:
  RunningGame() : Game("Running") {}
  void Play() override { std::cout << "Play Running Game." << std::endl; }
};

class ShootingGame : public Game {
 public:
  ShootingGame() : Game("Shooting") {}
  void Play() override { std::cout << "Play Shooting Game." << std::endl; }
};
```

**手机基类**

```cpp
class Phone {
  std::shared_ptr<Game> game;

 public:
  Phone() {}
  virtual ~Phone() = default;
  virtual void Download(std::shared_ptr<Game> game) = 0;
  virtual void Open() = 0;
};
```

**实现**

```cpp
class iPhone : public Phone {
  std::shared_ptr<Game> game;

 public:
  void Download(std::shared_ptr<Game> game) override {
    std::cout << "iPhone. download ";
    game->print();
    this->game = game;
  }
  void Open() override {
    std::cout << "iPhone. start ";
    game->Play();
  }
};

class Samsung : public Phone {
  std::shared_ptr<Game> game;

 public:
  void Download(std::shared_ptr<Game> game) override {
    std::cout << "Samsung. download ";
    game->print();
    this->game = game;
  }
  void Open() override {
    std::cout << "Samsung. start ";
    game->Play();
  }
};
```

## 调用方式

```cpp
//有两个游戏
auto running = std::make_shared<RunningGame>();
auto shooting = std::make_shared<ShootingGame>();
//两个手机
auto iphone = std::make_shared<iPhone>();
auto samsung = std::make_shared<Samsung>();
//下载游戏
iphone->Download(running);
samsung->Download(shooting);
//运行游戏
iphone->Open();
samsung->Open();
//换个游戏
samsung->Download(running);
//运行游戏
samsung->Open();
```

## **效果**

```cpp
./bin/design/Bridge
iPhone. download Running
Samsung. download Shooting
iPhone. start Play Running Game.
Samsung. start Play Shooting Game.
Samsung. download Running
Samsung. start Play Running Game.
```

## 结论

通过桥接模式，我们可以灵活地组合不同品牌的手机和不同名字的游戏，而不需要为每一种组合编写新的代码。这提供了更好的可维护性和扩展性，允许我们在不修改现有类的情况下添加新的手机品牌和游戏。

优点：

1. 分离抽象接口及其实现部分。使得抽象和实现可以沿着各自的维度来变化，也就是说抽象和实现不再在同一个继承层次结构中，而是“子类化”它们，使它们各自都具有自己的子类，以便任何组合子类，从而获得多维度组合对象。
2. 在很多情况下，桥接模式可以取代多层继承方案，多层继承方案违背了“单一职责原则”，复用性较差，且类的个数非常多，桥接模式是比多层继承方案更好的解决方法，它极大减少了子类的个数。

桥接模式**提高了系统的可扩展性**，在两个变化维度中任意扩展一个维度，都不需要修改原有系统，符合“开闭原则”

缺点：

1. 桥接模式的使用会增加系统的理解与设计难度，由于关联关系建立在抽象层，要求开发者一开始就针对抽象层进行设计与编程。
2. 桥接模式要求正确识别出系统中两个独立变化的维度，因此其**使用范围具有一定的局限性**，如何正确识别两个独立维度也需要一定的经验积累。