/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-30 14:06:04
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-30 14:55:10
 */
#include "State.hpp"
int main() {
  Book book("Design Patterns");
  book.borrow();
  book.getTitle();
  book.returnBook();
  book.getTitle();
  return 0;
}