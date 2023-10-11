/*
 * @Description:
 * @version:
 * @Author: 莫邪
 * @Date: 2023-10-11 10:23:14
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-11 12:07:47
 */
#include <iostream>
#include <memory>
#include <mutex>
class HungryManSingleton {
 public:
  static HungryManSingleton& getInstance() {
    // 静态成员变量确保只有一个实例
    static HungryManSingleton instance;
    return instance;
  }
  ~HungryManSingleton() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  // 其他成员函数和数据成员

 private:
  // 私有构造函数，防止外部实例化
  HungryManSingleton() {
    // 初始化单例对象
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
  // 禁用拷贝构造函数
  HungryManSingleton(const HungryManSingleton&) = delete;

  // 禁用赋值操作符
  HungryManSingleton& operator=(const HungryManSingleton&) = delete;
};

class HungryManCallOneSingleton {
 public:
  static std::shared_ptr<HungryManCallOneSingleton> getInstance();

  ~HungryManCallOneSingleton() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

 private:
  HungryManCallOneSingleton() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  // 禁用拷贝构造函数
  HungryManCallOneSingleton(const HungryManCallOneSingleton&) = delete;

  // 禁用赋值操作符
  HungryManCallOneSingleton& operator=(const HungryManCallOneSingleton&) =
      delete;
};

static std::shared_ptr<HungryManCallOneSingleton> singleton = nullptr;
static std::once_flag singletonFlag;

std::shared_ptr<HungryManCallOneSingleton>
HungryManCallOneSingleton::getInstance() {
  std::call_once(singletonFlag, [&] {
    singleton = std::shared_ptr<HungryManCallOneSingleton>(
        new HungryManCallOneSingleton());
  });
  return singleton;
}

class LazyManSingleton {
 public:
  static std::shared_ptr<LazyManSingleton> getInstance();

  // 禁用拷贝构造函数
  LazyManSingleton(const LazyManSingleton&) = delete;

  // 禁用赋值操作符
  LazyManSingleton& operator=(const LazyManSingleton&) = delete;

  ~LazyManSingleton() { std::cout << __PRETTY_FUNCTION__ << std::endl; }

 private:
  LazyManSingleton() { std::cout << __PRETTY_FUNCTION__ << std::endl; }

  static std::shared_ptr<LazyManSingleton> instance;
  static std::mutex mutex;
};

std::shared_ptr<LazyManSingleton> LazyManSingleton::instance = nullptr;
std::mutex LazyManSingleton::mutex;
std::shared_ptr<LazyManSingleton> LazyManSingleton::getInstance() {
  // 使用互斥锁确保线程安全
  std::lock_guard<std::mutex> lock(mutex);

  if (!instance) {
    instance = std::shared_ptr<LazyManSingleton>(new LazyManSingleton());
  }
  return instance;
}

class StaticLazyManSingleton {
public:
    static StaticLazyManSingleton& getInstance() {
        static StaticLazyManSingleton instance; // 静态局部变量确保线程安全且延迟加载
        return instance;
    }

    // 禁用拷贝构造函数
    StaticLazyManSingleton(const StaticLazyManSingleton&) = delete;

    // 禁用赋值操作符
    StaticLazyManSingleton& operator=(const StaticLazyManSingleton&) = delete;

private:
    StaticLazyManSingleton() {
        std::cout << __PRETTY_FUNCTION__  << std::endl;
    }

    ~StaticLazyManSingleton() {
        std::cout << __PRETTY_FUNCTION__  << std::endl;
    }
};