/*
 * @Description:
 * @version:
 * @Author: 莫邪
 * @Date: 2023-10-17 09:43:14
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-17 10:13:30
 */
#include <iostream>
#include <memory>

// 冰激凌抽象类
class AbstractIceCream {
 public:
  virtual ~AbstractIceCream() = default;
  virtual const std::string MakeIceCream() = 0;
};

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