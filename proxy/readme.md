# 代理模式

简单回顾下创建型模式

1. 单例模式用来创建全局唯一的对象
2. 工厂模式用来创建不同但是相关类型的对象(继承同一父类或者接口的一组子类), 由给定的参数来决定创建哪种类型的对象
3. 建造者模式是用来创建复杂对象, 可以通过设置不同的可选参数, “定制化”地创建不同的对象
4. 原型模式针对创建成本比较大的对象, 利用对已有对象进行复制的方式进行创建, 以达到节省创建时间的目的

接下来就是结构型模型

结构型模式包括：代理模式、桥接模式、装饰器模式、适配器模式、门面模式、组合模式、享元模式

## 原理

在不改变原始类（或叫被代理类）代码的情况下, 通过引入代理类来给原始类附加功能.

下述有个业务接口.

```cpp
// 接口虚类
class Subject {
 public:
  virtual void method() = 0;
  virtual void print() = 0;
};
//业务实现类
class RealSubject : public Subject {
 public:
  void method() { print(); }
  void print() { std::cout << "real method" << std::endl; }
};
```

若我想在这个业务上加个功能, 访问时间, 执行时长 或者其他的扩展业务

1. 扩展代码侵入业务代码, 跟业务代码高度耦合, 而且以后需要替换成其他扩展成本比较大
2. 扩展代码跟业务代码无关, 不应该放一起. 一个类最好职责单一, 只需要关心业务的处理

假设我这边需要简单加个日期打印

```cpp
// Log类
class Log {
 public:
  Log() {}
  std::string getTime() {
    time_t t = time(NULL);
    char ch[64] = {0};
    // 年-月-日 时:分:秒
    strftime(ch, sizeof(ch) - 1, "%Y-%m-%d %H:%M:%S", localtime(&t));
    return ch;
  }
};
```

下面通过代理模式添加时间日志输出

```cpp
//代理类
class StaticProxy : public Subject {
 public:
  StaticProxy() {
    subject = new RealSubject();
    log = new Log();
  }
  ~StaticProxy() {
    delete subject;
    delete log;
  }
  void method() {
    std::cout << log->getTime() << ": "
              << "static proxy start" << std::endl;
    subject->method();
    std::cout << log->getTime() << ": "
              << "static proxy end" << std::endl;
  }
  void print() {}

 private:
  RealSubject* subject;
  Log* log;
};
```

调用方式

```cpp
std::shared_ptr<Subject> sub = nullptr;
std::cout << "-----Orgin print-----" << std::endl;
sub = std::make_shared<RealSubject>();
sub->method();
std::cout << "-----Proxy Pattern-----" << std::endl;
sub = std::make_shared<StaticProxy>();
sub->method();
```

效果

```cpp
./bin/design/Proxy
-----Orgin print-----
real method
-----Proxy Pattern-----
2023-10-13 10:08:37: static proxy start
real method
2023-10-13 10:08:37: static proxy end
```

这样就可以在不入侵原有业务代码的基础上扩展功能

但是 代码实现还是有点问题

1. 我们需要在代理类中，将原始类中的所有的接口，都重新实现一遍，并且为每个方法都附加相似的代码逻辑. 
2. 如果要添加的附加功能的类有不止一个，我们需要针对每个类都创建一个代理类。

我们可以使用**动态代理**来解决这个问题

就是我们不事先为每个原始类编写代理类，而是在运行的时候，动态地创建原始类对应的代理类，然后在系统中用代理类替换掉原始类。

业务2接口

```cpp
// 接口虚类2
class Subject2 {
 public:
  virtual void method2() = 0;
  virtual void print2() = 0;
};
// 业务实现类2
class RealSubject2 : public Subject2 {
 public:
  void method2() { print2(); }
  void print2() { std::cout << "real2 method" << std::endl; } 
};
```

代理类

```cpp
template <class T>
class DynamicProxy : public T {
 public:
  DynamicProxy(std::function<void()> func) : func(func), log(new Log) {}
  ~DynamicProxy() { delete log; }
  void extend() {
    std::cout << log->getTime() << ": "
              << "dynamic proxy start" << std::endl;
    func();
    std::cout << log->getTime() << ": "
              << "dynamic proxy end" << std::endl;
  }
  void method() { extend(); }
  void method2() { extend(); }

 private:
  std::function<void()> func;
  Log* log;
};
```

调用方式

```cpp
std::cout << "-----Dynamic Proxy Pattern-----" << std::endl;
auto sub = std::make_shared<DynamicProxy<Subject>>(std::bind(&RealSubject::method, RealSubject()));
sub->method();
auto sub2 = std::make_shared<DynamicProxy<Subject2>>(std::bind(&RealSubject2::method, RealSubject2()));
sub->method();
```

效果

```cpp
./bin/design/Proxy
-----Dynamic Proxy Pattern-----
2023-10-13 10:34:48: dynamic proxy start
real method
2023-10-13 10:34:48: dynamic proxy end
2023-10-13 10:34:48: dynamic proxy start
real method
2023-10-13 10:34:48: dynamic proxy end
```

通过动态代理方式(模版增加通用性) 

1. 可以通过绑定函数的方式动态添加需要增加扩展的业务函数接口
2. 只需要实现增加扩展的接口, 不需要全部实现基类所以接口

## 适用

代理模式常用在业务系统中开发一些非功能性需求，比如：监控、统计、鉴权、限流、事务、幂等、日志。

我们将这些附加功能与业务功能解耦，放到代理类统一处理，让程序员只需要关注业务方面的开发。