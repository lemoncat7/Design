/*
 * @Description:
 * @version:
 * @Author: 莫邪
 * @Date: 2023-10-13 09:49:13
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-13 11:03:28
 */
#include <iostream>

// 接口虚类
class Subject {
 public:
  virtual void method() = 0;
};
// 接口虚类2
class Subject2 {
 public:
  virtual void method2() = 0;
};
// 业务实现类
class RealSubject : public Subject {
 public:
  void method() { std::cout << "real method" << std::endl; }
};
// 业务实现类2
class RealSubject2 : public Subject2{
 public:
  void method2() { std::cout << "real2 method" << std::endl; }
};
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
    std::cout << log->getTime() << ": " << "static proxy start" << std::endl;
    subject->method();
    std::cout << log->getTime() << ": " << "static proxy end" << std::endl;
  }
private:
  RealSubject* subject;
  Log* log;
};

template <class T>
class DynamicProxy : public T {
public:
  DynamicProxy(std::function<void()> func) : func(func), log(new Log) {}
  ~DynamicProxy() { delete log; }
  void extend() {
    std::cout << log->getTime() << ": " << "dynamic proxy start" << std::endl;
    func();
    std::cout << log->getTime() << ": " << "dynamic proxy end" << std::endl;
  }
  void method() {
    extend();
  }
  void method2() {
    extend();
  }
private:
  std::function<void()> func;
  Log* log;
};