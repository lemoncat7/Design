# 状态模式

## 介绍

状态模式(State Pattern)是一种设计模式,其主要思想是:

当一个对象的内在状态改变时,允许其改变对外界的行为,这个对象看起来像是改变了其类。

状态模式的用法主要有:

1. 行为随状态改变而改变的场景一个对象的行为取决于它的状态,并且它必须在运行时刻根据状态改变它的行为的时候,就可以考虑使用状态模式。比如订单流程、工作流等。
2. 状态切换的条件语句过多如果一个对象拥有大量处理不同状态的条件语句,可以使用状态模式把这些判断提取出来,放到不同的状态类中。提高可维护性。
3. 状态切换业务逻辑复杂将复杂的状态转换逻辑提取到不同的状态类中,可以提高程序的可维护性和扩展性。
4. 状态依赖条件多变化大当一个对象的状态转换与其他对象关系密切,对象状态转换的条件多变化大时,可以使用状态模式提高灵活性。
5. 需要状态历史记录状态历史或恢复状态时可以考虑状态模式。

总而言之,状态模式通过将不同状态抽象成不同类,实现了状态逻辑与对象行为的分离,提高了程序的灵活性和可维护性。它在状态转换条件复杂时比较合适。

## 定义

一个图书管理系统,需要实现图书的借阅流程。图书有以下状态:

可借阅(Available):可被借阅
已借出(Borrowed):已被用户借走
预定(Reserved):有用户进行了预定
过期(Expired):借阅期过期
状态与行为:

可借阅:可以借阅,可以预定
已借出:可以还书
预定:等待借阅,可以取消预定
过期:需要收罚金,强制还书

图书类

```cpp
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
```

实现

```cpp
Book::Book(string title) : title_(title) {
  state_ = std::make_shared<Available>();
}
Book::~Book() {}
void Book::setState(std::shared_ptr<State> state) { this->state_ = state; }
void Book::borrow() { state_->borrow(*this); }
void Book::returnBook() { state_->returnBook(*this); }
void Book::reserve() { state_->reserve(*this); }
void Book::getTitle() { state_->getTitle(*this); }
```

各个状态

```cpp
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
```

实现

```cpp
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
```

## 调用

```cpp
int main() {
  Book book("Design Patterns");
  book.borrow();
  book.getTitle();
  book.returnBook();
  book.getTitle();
  return 0;
}
```

## 效果

```cpp
./bin/design/state   
Design Patterns is borrowed
Book title: Design Patterns, borrowed
Design Patterns is expired
Book title: Design Patterns, expired
```

## 回顾

今天我们讲解了状态模式。虽然网上有各种状态模式的定义，但是你只要记住状态模式是状态机的一种实现方式即可。状态机又叫有限状态机，它有3个部分组成：状态、事件、动作。其中，事件也称为转移条件。事件触发状态的转移及动作的执行。不过，动作不是必须的，也可能只转移状态，不执行任何动作。