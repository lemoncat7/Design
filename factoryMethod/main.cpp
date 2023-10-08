/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-08 14:47:54
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-08 14:54:44
 */
#include "FactoryMethod.hpp"

int main() {
  std::shared_ptr<AbstractFactory> factory = nullptr;
  std::shared_ptr<AbstractProduct> product = nullptr;
  factory = std::make_shared<MachineryFactory>();
  product = factory->getProduct();
  factory = std::make_shared<MagicFactory>();
  product = factory->getProduct();
  factory = std::make_shared<Greenfactory>();
  product = factory->getProduct();
  return 0;
}