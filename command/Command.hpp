/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-11-06 09:57:13
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-11-06 10:26:49
 */
#include <iostream>
#include <memory>
#include <unordered_map>
#include <time.h>

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