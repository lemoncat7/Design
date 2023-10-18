/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-18 10:46:40
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-18 10:59:21
 */
#include <iostream>
#include <memory>

//micro-usb类
class MicroUSBCharger {
public:
  const std::string chargeWithMicroUSB() {
    return "Charging with Micro-USB";
  }
};

//usb-c类
class USB_CPhone{
public:
  const std::string chargeWithUSB_C() {
    return "Charging with USB-C";
  }
};

//对象适配器
class ObjectChargeAdapter: public USB_CPhone {
  MicroUSBCharger microUSBCharger;
public:
  const std::string chargeWithUSB_C() {
    return microUSBCharger.chargeWithMicroUSB();
  }
};

//类适配器
class ClassChargeAdapter: public MicroUSBCharger ,private USB_CPhone {
public:
  const std::string chargeWithUSB_C() {
    return chargeWithMicroUSB();
  }
};
