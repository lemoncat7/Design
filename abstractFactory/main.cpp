/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-09 09:30:34
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-09 09:44:27
 */

#include "AbstractFactory.hpp"

int main() {
  std::shared_ptr<AbstractFactory> factory = nullptr;
  factory = std::make_shared<BasketballFactory>();
  factory->createBall();
  factory->createShirt();
  factory = std::make_shared<FootballFactory>();
  factory->createBall();
  factory->createShirt();
  factory = std::make_shared<VolleyballFactory>();
  factory->createBall();
  factory->createShirt();
  return 0;
}