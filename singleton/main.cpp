/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-11 10:27:54
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-11 12:07:57
 */
#include "Singleton.hpp"

int main() {
  HungryManSingleton::getInstance();
  HungryManSingleton::getInstance();
  HungryManCallOneSingleton::getInstance();
  HungryManCallOneSingleton::getInstance();
  LazyManSingleton::getInstance();
  LazyManSingleton::getInstance();
  StaticLazyManSingleton::getInstance();
  StaticLazyManSingleton::getInstance();
  return 0;
}