<!--
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-11 12:10:53
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-11 12:10:54
-->
# 单例模式

## 介绍

单例模式理解起来比较简单, 就是一个类 它只允许创建一个对象或者实例, 那这个类就是单例类. 

## 用处

在业务上, 有些数据只需要保存一份, 比如系统信息, 配置信息

1. 可以节省空间、资源
2. 方便控制, 避免多对象引起复杂操作

单例有下面两种经典的实现方式。

## 饿汉式 (线程安全)

它在程序启动时立即创建单例对象，而不是在首次访问时才创建。

这确保了线程安全，因为在多线程环境下，单例对象已经在程序启动阶段被创建，不需要考虑竞态条件。

使用普通静态变量方式

```cpp
class HungryManSingleton {
public:
    static HungryManSingleton& getInstance() {
        // 静态成员变量确保只有一个实例
        static HungryManSingleton instance;
        return instance;
    }
    ~HungryManSingleton() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
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
```

使用c++11 `std::call_one` 方式, 是 C++ 标准库提供的一个多线程同步工具，用于确保某个函数只会在多线程环境下执行一次。通常，它与 **`std::once_flag`** 一起使用

```cpp
class HungryManCallOneSingleton {
public:
  static std::shared_ptr<HungryManCallOneSingleton> getInstance() ;

  ~HungryManCallOneSingleton() {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
private:
    
  HungryManCallOneSingleton() {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
    // 禁用拷贝构造函数
  HungryManCallOneSingleton(const HungryManCallOneSingleton&) = delete;
  
  // 禁用赋值操作符
  HungryManCallOneSingleton& operator=(const HungryManCallOneSingleton&) = delete;
  
};

static std::shared_ptr<HungryManCallOneSingleton> singleton = nullptr;
static std::once_flag singletonFlag;

std::shared_ptr<HungryManCallOneSingleton> HungryManCallOneSingleton::getInstance() {
  std::call_once(singletonFlag, [&] {
    singleton = std::shared_ptr<HungryManCallOneSingleton>(new HungryManCallOneSingleton());
  });
  return singleton;
}
```

## 懒汉式

普通懒汉式单例（线程不安全）

使用互斥锁保证线程安全 (线程安全)

```cpp
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
```

静态局部变量 (线程安全)

```cpp
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
```

在C++11及更高版本中，使用静态局部变量来实现单例模式通常是线程安全的，这是因为C++11引入了线程安全的静态局部变量初始化机制。这种机制确保了只有一个线程能够初始化静态局部变量，避免了竞态条件

## 特点

- 构造函数为私有类型，目的是禁止外部构造。
- 拷贝构造函数和赋值构造函数是私有类型，目的是禁止外部拷贝和赋值，确保实例的唯一性。
- 类中有一个获取实例的静态方法，可以全局访问。