# 桥接模式

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