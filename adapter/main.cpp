/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-18 10:46:43
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-18 10:59:33
 */
#include "Adapter.hpp"

int main() {
  ObjectChargeAdapter new_phone;
  std::cout << new_phone.chargeWithUSB_C() << std::endl;
  ClassChargeAdapter new_phone1;
  std::cout << new_phone1.chargeWithUSB_C() << std::endl;
  return 0;
}