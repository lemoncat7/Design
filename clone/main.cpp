/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-12 09:40:19
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-12 10:04:57
 */
#include "Clone.hpp"

int main() {
  auto A = ShallowStudent(new Homework(1, "小杰", "小杰作业"));
  auto B = ShallowStudent(A);
  B.homework->id = 2;
  B.homework->name = "小李";
  A.print();
  B.print();

  auto C = DeepStudent(new Homework(3, "小迓", "小迓作业"));
  auto D = DeepStudent(C);
  D.homework->id = 4;
  D.homework->name = "小王";
  auto E = C;
  E.homework->id = 5;
  E.homework->name = "小张";
  C.print();
  D.print();
  E.print();
  return 0;
}