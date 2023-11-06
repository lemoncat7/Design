<!--
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-11-06 11:08:04
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-11-06 11:08:05
-->
## 介绍

命令模式是一种设计模式,它将请求封装成对象,以便使用不同的请求、队列或者日志来参数化其他对象。命令模式也允许支持撤销操作。

主要解决的是调用者与接收者之间的耦合关系。

命令模式的主要角色有:

1. 接收者(Receiver) - 执行命令对应的操作,即命令要执行的具体操作。
2. 命令(Command) - 声明执行操作的接口,拥有执行命令的抽象方法execute()。
3. 具体命令(ConcreteCommand) - 实现了Command接口,它拥有接收者,并通过调用接收者的功能来完成命令要执行的操作。
4. 调用者(Invoker) - 要求命令对象执行请求,通常会持有命令对象。
5. 客户端(Client) - 创建具体命令对象,并绑定接收者。

command模式的优点:

1. 解耦了调用操作的对象和实现操作的对象。
2. 可以实现命令的排队和日志,也可以方便地实现撤销和重做操作。
3. 扩展性好,可以易于增加新的命令类,满足扩展的需求。

总结:命令模式将请求封装成对象,这可以用来参数化其他对象,实现命令的排队和日志,也可以方便地实现撤销/重做操作。它通过解耦调用者和接收者来实现更松耦合的代码。

## 定义

假设我们在做一个游戏,游戏中有不同的角色,每个角色都可以执行不同的技能。需求如下:

1. 游戏中有多种角色,如武士、法师、猎人等。
2. 每个角色都有自己独特的技能,如武士可以横扫千军,法师可以释放火球术等。
3. 玩家可以控制角色去释放技能攻击敌人。
4. 需要记录每个技能的使用日志,如火球术使用了多少次。
5. 需要有一个技能冷却系统,每个技能不能连续释放,需要冷却一段时间。
6. 未来需要不断新增角色和技能。

使用命令模式可以很好地满足需求:

1. 每个技能都封装为一个命令类,实现执行技能的方法。
2. 命令类记录自己的执行日志。
3. 命令类具有冷却功能,可以避免连续释放。
4. 新增角色时,只需要给该角色绑定它的技能命令即可。
5. 新增技能也只需要新增一个命令类。
6. 角色和技能解耦,两者之间通过命令进行交互。

技能

```cpp
// 技能接口
class Skill {
public:
  virtual ~Skill() {}
  //返回冷却时间
  virtual long Use() = 0;
};
// 具体技能类
class SpecificSkills: public Skill {
private:
  std::string name_;
  int cooldown_;
public:
  SpecificSkills(const std::string& name, const int& cooldown) : name_(name), cooldown_(cooldown) {
  }
  long Use() override {
    std::cout << name_ << " used!" << std::endl; 
    return cooldown_; // 冷却时间
  }
};
```

命令

```cpp
// 命令接口  
class Command {
public:
  virtual ~Command() {}
  //返回使用次数
  virtual int Execute() = 0;
};
// 具体命令类
class SkillCommand : public Command {
private:
  Skill* skill_;
  time_t coll_down_;
  int usage;
public:
  explicit SkillCommand(Skill* skill) : skill_(skill), coll_down_(0), usage(0) {}
  int Execute() override {
    if (time(0) < coll_down_) {
      std::cout << "Skill is cooling down!" << std::endl;
    } else {
      coll_down_ = time(0) + skill_->Use();
      usage++;
    }
    return usage;
  }
};
```

角色调用

```cpp
// 客户端/调用者
class Invoker {
private:
  std::unordered_map<std::string, Command*> commands_;
public:
  ~Invoker() {
    for (auto& it : commands_) {
      delete it.second;
    }
  }
  void SetCommand(const std::string& name, Command* cmd) {
    commands_[name] = cmd;
  }
  void Execute(const std::string& name) {
    if (commands_.find(name) != commands_.end()) {
      auto usage = commands_[name]->Execute(); 
      std::cout << name << " is used " << usage << " times !" << std::endl;
    } else {
      std::cout << name << " is invalid!" << std::endl;
    }
  }
};
```

## 调用

```cpp
int main() {
  Skill* fireBall = new SpecificSkills("Fire Ball", 3);
  Skill* Flash = new SpecificSkills("Flash", 1);
  Invoker* invoker = new Invoker();
  invoker->SetCommand("fire", new SkillCommand(fireBall));
  invoker->SetCommand("flash", new SkillCommand(Flash));
  invoker->Execute("fire");
  invoker->Execute("fire");
  sleep(3);
  invoker->Execute("flash");
  invoker->Execute("fire");
  delete invoker;
  return 0;
}
```

## 效果

```cpp
./bin/design/command
Fire Ball used!
fire is used 1 times !
Skill is cooling down!
fire is used 1 times !
Flash used!
flash is used 1 times !
Fire Ball used!
fire is used 2 times !
```

这个示例中:

- SpecificSkills类是技能,实现了释放火球术的功能
- SkillCommand是具体的命令类,封装了对Wizard的调用
- Invoker是调用者,通过invoke方法触发命令

这样可以实现调用者和接收者的解耦,并可以方便地扩展新的命令和接收者,满足游戏的灵活需求。

## 回顾

命令模式在平时工作中并不常用，你稍微了解一下就可以。今天，我重点讲解了它的设计意图，也就是能解决什么问题。

落实到编码实现，命令模式用到最核心的实现手段，就是将函数封装成对象。我们知道，在大部分编程语言中，函数是没法作为参数传递给其他函数的，也没法赋值给变量。借助命令模式，我们将函数封装成对象，这样就可以实现把函数像对象一样使用。

命令模式的主要作用和应用场景，是用来控制命令的执行，比如，异步、延迟、排队执行命令、撤销重做命令、存储命令、给命令记录日志等等，这才是命令模式能发挥独一无二作用的地方。