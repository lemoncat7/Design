/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-10 11:38:36
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-10 11:42:23
 */
#include "Builder.hpp"

int main() {
  House::Builder builder;
  builder.setFloor("floor");
  auto* house = builder.build();
  house->print();
  return 0;
}