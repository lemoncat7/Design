/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-08 10:53:34
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-08 11:10:50
 */
#include "SimpleFactor.hpp"

int main() {
  SimpleFactory s;
  auto ball1 = s.createBall(Type::BasketBallType);
  ball1->get();
  ball1->play();
  auto ball2 = s.createBall(Type::FootBallType);
  ball2->get();
  ball2->play();
  auto ball3 = s.createBall(Type::VolleyballType);
  ball3->get();
  ball3->play();
  return 0;
}