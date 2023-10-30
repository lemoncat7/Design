/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-30 14:06:00
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-30 15:04:23
 */
#pragma once
#include <iostream>
#include <memory>
#include <string>
using namespace std;

class State;

// Book class 
class Book {
public:
  Book(string title);
  ~Book() ;
  void setState(std::shared_ptr<State> state) ;
  void borrow() ;
  void returnBook() ;
  void reserve() ;
  void getTitle() ;
  string title_;
private:
  std::shared_ptr<State> state_;
};

class State {
public:
  virtual void borrow(Book& book) = 0;
  virtual void returnBook(Book& book) = 0;
  virtual void reserve(Book& book) = 0;
  virtual void getTitle(Book& book) = 0;
};

// Concrete state classes
class Available : public State {
public:
  void borrow(Book& book) override ;
  void returnBook(Book& book) override ;
  void reserve(Book& book) override ;
  void getTitle(Book& book) override ;
};
class Borrowed : public State {
public:
  void returnBook(Book& book) override ;
  void borrow(Book& book) override ;
  void reserve(Book& book) override ;
  void getTitle(Book& book) override ;
  void checkOverdue(Book& book) ;
};
class Reserved : public State {
public:
  void borrow(Book& book) override ;
  void returnBook(Book& book) override ;
  void reserve(Book& book) override ;
  void getTitle(Book& book) override ;
};
class Expired : public State {
public:
  void borrow(Book& book) override ;
  void returnBook(Book& book) override ;
  void reserve(Book& book) override ;
  void getTitle(Book& book) override ;
};

