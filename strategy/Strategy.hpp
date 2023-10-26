/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-26 11:12:14
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-26 11:15:05
 */
#include <iostream>
// 栽种策略接口
class PlantStrategy {
public:
  virtual void plant() = 0; 
};

// 小麦栽种策略  
class WheatPlantStrategy : public PlantStrategy {
public:
  void plant() override {
    // 小麦栽种逻辑
    std::cout << "小麦栽种逻辑" << std::endl;
  }
};

// 稻米栽种策略
class RicePlantStrategy : public PlantStrategy {
public:
  void plant() override {
    // 稻米栽种逻辑
    std::cout << "稻米栽种逻辑" << std::endl;
  }  
};

// 农场类
class Farm {
private:
  PlantStrategy* strategy; 

public:
  void setStrategy(PlantStrategy* strategy) {
    this->strategy = strategy;
  }

  void plantCrop() {
    strategy->plant(); 
  }
};
