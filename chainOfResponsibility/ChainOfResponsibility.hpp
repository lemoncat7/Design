/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-27 10:42:09
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-27 10:52:23
 */
#include <iostream>
#include <memory>
#include <map>
using namespace std;
// 抽象处理者
class Handler {
public:
  virtual void handleRequest(string request) = 0;
  void setNext(shared_ptr<Handler> handler) {
    nextHandler = handler; 
  }
protected:
  shared_ptr<Handler> nextHandler;
};
// 检查库存
class StockChecker : public Handler {
  map<string, int> stock;
public:
  StockChecker() {
    stock = {{"goods1", 100}, {"goods2", 10}, {"goods3", 1000}};
  }
  void handleRequest(string request) override {
    if (/* 检查库存 */stock[request] > 10) {
      cout << "库存检查通过" << endl;
    } else {
      cout << "商品库存不足" << endl; 
      return;
    }
    // 传递给下一处理者
    if (nextHandler) nextHandler->handleRequest(request);
  }
};
// 校验价格
class PriceValidator : public Handler {
  map<string, int> price;
public:
  PriceValidator() {
    price = {{"goods1", 100}, {"goods2", 10}, {"goods3", 1000}};
  }
  void handleRequest(string request) override {
    if (/* 校验价格 */price[request] > 100) {
      cout << "价格校验通过" << endl;
    } else {
      cout << "商品价格错误" << endl;
      return;
    }
    if (nextHandler) nextHandler->handleRequest(request);
  }
};
// 其他具体处理者 
// ...
