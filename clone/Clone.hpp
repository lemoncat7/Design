/*
 * @Description:
 * @version:
 * @Author: 莫邪
 * @Date: 2023-10-12 09:40:13
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-12 10:14:11
 */
#include <iostream>
class Homework {
 public:
  int id;
  std::string name;
  std::string answer;
  Homework(int id, std::string name, std::string answer)
      : id(id), name(name), answer(answer) {}
  void print() {
    std::cout << "id: " << id << " name: " << name << " answer: " << answer
              << std::endl;
  }
};

class ShallowStudent {
 public:
  Homework* homework;
  ShallowStudent(Homework* homework) : homework(homework) {}
  void print() {
    homework->print();
  }
};

class DeepStudent {
 public:
  Homework* homework;
  DeepStudent(Homework* homework) : homework(homework) {}
  void print() {
    homework->print();
  }
  void CloneHomework(const Homework* homework) {
    this->homework = new Homework(*homework);
  }
  DeepStudent(const DeepStudent& other) {
    CloneHomework(other.homework);
  }
  DeepStudent& operator=(const DeepStudent& other) {
    CloneHomework(other.homework);
    return *this;
  }

};