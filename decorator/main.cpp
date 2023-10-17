/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-17 09:43:18
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-17 10:18:36
 */
#include "Decorator.hpp"

int main() {
  //想要制作一个巧克力冰激凌
  auto chocolate = std::make_shared<ChocolateIceCream>();
  //加上布丁
  auto pudding = std::make_shared<PuddingIceCreamChunk>();
  pudding->SetIceCream(chocolate);
  //加上坚果
  auto nuts = std::make_shared<NutsIceCreamChunk>();
  nuts->SetIceCream(pudding);
  //制作
  std::cout << nuts->MakeIceCream() << std::endl;
  //想要制作一个草莓冰激凌
  auto strawberry = std::make_shared<StrawberryIceCream>();
  //加上巧克力豆
  auto chocolate_beans = std::make_shared<ChocolateIceCreamChunk>();
  chocolate_beans->SetIceCream(strawberry);
  //加上布丁
  auto pudding_beans = std::make_shared<PuddingIceCreamChunk>();
  pudding_beans->SetIceCream(chocolate_beans);
  //制作
  std::cout << pudding_beans->MakeIceCream() << std::endl;
  return 0;
}