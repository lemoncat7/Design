/*
 * @Description:
 * @version:
 * @Author: 莫邪
 * @Date: 2023-10-30 14:57:29
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-30 15:04:10
 */
#include "State.hpp"
// Book class
Book::Book(string title) : title_(title) {
  state_ = std::make_shared<Available>();
}
Book::~Book() {}
void Book::setState(std::shared_ptr<State> state) { this->state_ = state; }
void Book::borrow() { state_->borrow(*this); }
void Book::returnBook() { state_->returnBook(*this); }
void Book::reserve() { state_->reserve(*this); }
void Book::getTitle() { state_->getTitle(*this); }

void Available::borrow(Book& book) {
  cout << book.title_ << " is borrowed" << endl;
  book.setState(std::make_shared<Borrowed>());
}
void Available::returnBook(Book& book) {
  cout << "Book is already available" << endl;
}
void Available::reserve(Book& book) {
  cout << book.title_ << " is reserved" << endl;
  book.setState(std::make_shared<Reserved>());
}
void Available::getTitle(Book& book) {
  cout << "Book title: " << book.title_ << ", available" << endl;
}

void Borrowed::returnBook(Book& book) { checkOverdue(book); }
void Borrowed::borrow(Book& book) {
  cout << "Book is already borrowed" << endl;
}
void Borrowed::reserve(Book& book) {
  cout << book.title_ << " is reserved" << endl;
  book.setState(std::make_shared<Reserved>());
}
void Borrowed::getTitle(Book& book) {
  cout << "Book title: " << book.title_ << ", borrowed" << endl;
}
void Borrowed::checkOverdue(Book& book) {
  if (true) {  // 检查过期状态
    cout << book.title_ << " is expired" << endl;
    book.setState(std::make_shared<Expired>());
  } else {
    cout << book.title_ << " is returned" << endl;
    book.setState(std::make_shared<Available>());
  }
}

void Reserved::borrow(Book& book) {
  cout << book.title_ << " is borrowed" << endl;
  book.setState(std::make_shared<Borrowed>());
}
void Reserved::returnBook(Book& book) {
  cout << book.title_ << " is reserved" << endl;
  book.setState(std::make_shared<Reserved>());
}
void Reserved::reserve(Book& book) {
  cout << "Book is already reserved" << endl;
}
void Reserved::getTitle(Book& book) {
  cout << "Book title: " << book.title_ << ", reserved" << endl;
}

void Expired::borrow(Book& book) {
  cout << "Cannot borrow " << book.title_ << ", it is expired" << endl;
}
void Expired::returnBook(Book& book) {
  cout << book.title_ << " is returned with fine" << endl;
  book.setState(std::make_shared<Available>());
}
void Expired::reserve(Book& book) {
  cout << "Cannot reserve " << book.title_ << ", it is expired" << endl;
}
void Expired::getTitle(Book& book) {
  cout << "Book title: " << book.title_ << ", expired" << endl;
}