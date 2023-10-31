<!--
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-31 09:00:24
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-31 09:00:25
-->
# 迭代器模式

## 介绍

迭代器模式是一种设计模式,它提供一种方法访问一个容器对象中各个元素,而不需要暴露该对象的内部表示。

迭代器模式的主要目的是:

1. 提供一种方法顺序访问一个聚合对象中的各个元素,而又不暴露其内部的表示。
2. 为遍历不同的集合结构提供一个统一的接口(即迭代器接口)。

迭代器模式的主要 PARTICIPANT 包括:

Iterator 抽象迭代器接口:定义访问和遍历元素的方法。

ConcreteIterator 具体迭代器实现:实现抽象迭代器接口中定义的方法。

Aggregate 抽象容器接口:定义创建相应迭代器对象的方法。

ConcreteAggregate 具体容器实现:实现创建具体迭代器的方法。

客户端可以通过迭代器来遍历容器中的所有元素,而不需要了解容器的内部结构。迭代器简化了聚合类的接口和聚合类的遍历。

迭代器模式在提供一个统一遍历接口的同时,封装了集合的内部结构,使客户端代码与集合的存储结构解耦。

## 定义

假设我们有一个图书管理系统,需要管理图书馆中的所有图书。图书馆有打印版图书和电子版图书,打印版图书存储在书架上,电子版存储在服务器上。

我们希望提供一个统一的界面来遍历所有图书,而不管是打印版还是电子版。

需求如下:

1. 图书馆有一个所有图书的列表,包括打印版和电子版图书。
2. 图书馆可以提供一个迭代器接口,用来遍历所有图书。
3. 打印版图书存储在书架上,需要提供具体的书架迭代器来遍历书架上的图书。
4. 电子版图书存储在服务器上,需要提供具体的服务器迭代器来遍历服务器上的电子图书。
5. 使用图书馆提供的迭代器接口,可以一致地遍历所有图书,而不需要关心图书的存储形式是打印版还是电子版。

图书接口

```cpp
// Book接口
class Book {
public:
  virtual string getName() = 0;
};
// 具体书类
class DesignPatternsBook : public Book {
public:
  string getName() override ;
};
// 具体书类 
class RefactoringBook : public Book {
public:
   string getName() override ;
};
```

具体实现

```cpp
// 具体书类
string DesignPatternsBook::getName() { return "Design Patterns"; }
// 具体书类
string RefactoringBook::getName() { return "Refactoring"; }
```

图书聚合类

```cpp
// BookShelf类,实现Aggregate接口
class BookShelf {
private:
  vector<Book*> books;
public:
  vector<Book*>& Books() ;
  void addBook(Book* book) ;
  // 创建迭代器
  Iterator* createIterator() ;
};
```

实现

```cpp
vector<Book*>& BookShelf::Books() { return books; }
void BookShelf::addBook(Book* book) { books.push_back(book); }
// 创建迭代器
Iterator* BookShelf::createIterator() { return new BookShelfIterator(this); }
```

迭代器接口

```cpp
// 迭代器接口
class Iterator {
public:
  virtual bool hasNext() = 0;
  virtual Book* next() = 0;
};
// 具体迭代器
class BookShelfIterator : public Iterator {
private:
  BookShelf* bookShelf;
  int index;
public:
  BookShelfIterator(BookShelf* bookShelf) ;
  bool hasNext() override ;
  Book* next() override ;
};
```

实现

```cpp
// 具体迭代器
BookShelfIterator::BookShelfIterator(BookShelf* bookShelf) {
  this->bookShelf = bookShelf;
  this->index = 0;
}
bool BookShelfIterator::hasNext() {
  if (index < bookShelf->Books().size()) {
    return true;
  }
  return false;
}
Book* BookShelfIterator::next() {
  Book* book = bookShelf->Books()[index];
  index++;
  return book;
}
```

## 调用

```
// 客户端代码
int main() {
  BookShelf* bookShelf = new BookShelf();
  bookShelf->addBook(new DesignPatternsBook());
  bookShelf->addBook(new RefactoringBook());
  Iterator* it = bookShelf->createIterator();
  while (it->hasNext()) {
    Book* book = it->next();
    cout << book->getName() << endl; 
  }
  return 0;
}
```

## 效果

```cpp
./bin/design/iterator 
Design Patterns
Refactoring
```

## 回顾

迭代器模式，也叫游标模式。它用来遍历集合对象。这里说的“集合对象”，我们也可以叫“容器”“聚合对象”，实际上就是包含一组对象的对象，比如，数组、链表、树、图、跳表。

一个完整的迭代器模式，一般会涉及容器和容器迭代器两部分内容。为了达到基于接口而非实现编程的目的，容器又包含容器接口、容器实现类，迭代器又包含迭代器接口、迭代器实现类。容器中需要定义iterator()方法，用来创建迭代器。

遍历集合一般有三种方式：for循环、迭代器遍历。相对于for循环遍历，利用迭代器来遍历有下面三个优势：

- 迭代器模式封装集合内部的复杂数据结构，开发者不需要了解如何遍历，直接使用容器提供的迭代器即可；
- 迭代器模式将集合对象的遍历操作从集合类中拆分出来，放到迭代器类中，让两者的职责更加单一；
- 迭代器模式让添加新的遍历算法更加容易，更符合开闭原则。除此之外，因为迭代器都实现自相同的接口，在开发中，基于接口而非实现编程，替换迭代器也变得更加容易。