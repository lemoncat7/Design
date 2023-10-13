/*
 * @Description:
 * @version:
 * @Author: 莫邪
 * @Date: 2023-10-13 09:49:20
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-13 10:59:48
 */
#include <memory>

#include "Proxy.hpp"

int main() {
  std::cout << "-----Orgin print-----" << std::endl;
  std::shared_ptr<Subject> sub = std::make_shared<RealSubject>();
  sub->method();
  std::cout << "-----Proxy Pattern-----" << std::endl;
  sub = std::make_shared<StaticProxy>();
  sub->method();
  std::cout << "-----Dynamic Proxy Pattern-----" << std::endl;
  std::shared_ptr<Subject> sub1 = std::make_shared<DynamicProxy<RealSubject>>(
      std::bind(&RealSubject::method, RealSubject()));
  sub1->method();
  std::shared_ptr<Subject2> sub2 = std::make_shared<DynamicProxy<RealSubject2>>(
      std::bind(&RealSubject2::method2, RealSubject2()));
  sub2->method2();
  return 0;
}