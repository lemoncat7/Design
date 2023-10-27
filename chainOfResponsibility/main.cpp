/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-27 10:42:13
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-27 10:53:58
 */

#include "ChainOfResponsibility.hpp"

int main() {
  // 初始化责任链
  std::shared_ptr<Handler> stockChecker = std::make_shared<StockChecker>();
  std::shared_ptr<Handler> priceValidator = std::make_shared<PriceValidator>();
  stockChecker->setNext(priceValidator);
  // 提交请求
  string request = "goods1";
  stockChecker->handleRequest(request);
  std::cout << "=========================================" << std::endl;
  // 提交请求
  request = "goods2";
  stockChecker->handleRequest(request);
  std::cout << "=========================================" << std::endl;
  // 提交请求
  request = "goods3";
  stockChecker->handleRequest(request);
  return 0;
}