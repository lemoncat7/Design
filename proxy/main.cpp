/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-13 09:49:20
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-13 10:33:00
 */
#include "Proxy.hpp"
#include <memory>

int main() {
  std::cout << "-----Orgin print-----" << std::endl;
  std::shared_ptr<Subject> sub = std::make_shared<RealSubject>();
  sub->method();
  std::cout << "-----Proxy Pattern-----" << std::endl;
  sub = std::make_shared<StaticProxy>();
  sub->method();
  std::cout << "-----Dynamic Proxy Pattern-----" << std::endl;
  sub = std::make_shared<DynamicProxy<Subject>>(std::bind(&RealSubject::method, RealSubject()));
  sub->method();
  auto sub2 = std::make_shared<DynamicProxy<Subject2>>(std::bind(&RealSubject2::method, RealSubject2()));
  sub->method();
  return 0;
}