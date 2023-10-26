/*
 * @Description:
 * @version:
 * @Author: 莫邪
 * @Date: 2023-10-26 11:12:18
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-26 11:13:43
 */
#include "Strategy.hpp"

int main() {
  // 使用
  Farm* farm = new Farm();
  farm->setStrategy(new WheatPlantStrategy());
  farm->plantCrop();  // 调用小麦栽种逻辑

  farm->setStrategy(new RicePlantStrategy());
  farm->plantCrop();  // 调用稻米栽种逻辑
}