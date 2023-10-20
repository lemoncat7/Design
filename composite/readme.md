<!--
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-20 11:14:52
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-20 11:14:53
-->
组合模式相较于我们对象设计中的组合关系是两个不同的概念:

1. 组合模式(Composite Pattern)是一种设计模式,它将对象组合成树形结构来表示部分-整体层次结构。组合模式允许客户端统一地使用个别对象和组合对象。
2. 组合关系(Composition)是对象之间的一种强关联关系,表示部分和整体的关系,部分对象无法脱离整体对象独立存在。这种部分与整体的关系不同于关联关系和聚合关系。

主要区别:

- 组合模式是一种设计模式,重点在于统一处理个别对象和组合对象。
- 组合关系是描述类之间关系的一种关联方式,强调部分与整体之间不可分的强依赖性。
- 组合模式使用了组合关系,即组合对象与部分对象之间形成了强依赖,部分对象不能脱离组合对象独立存在。
- 但是实现组合模式不一定需要使用组合关系,也可以通过关联关系来实现。

总之,组合模式是一种设计模式,利用组合关系或者关联关系来统一对待部分和整体对象。组合关系是描述部分和整体间强依赖关联的一种方式。

## 介绍

组合模式(Composite Pattern)是一种结构型设计模式,用于将对象组合成树形结构以表示“部分-整体”的层次关系。

组合模式的定义:将对象组合成树形结构以表示部分-整体层次结构。组合模式使得用户对单个对象和组合对象的使用具有一致性。

组合模式的主要角色:

- Component:组合中的对象声明接口,在适当的情况下,实现所有类共有接口的默认行为。
- Leaf:叶子构件,叶子对象没有子对象,定义叶子对象的行为。
- Composite:容器构件,存储子部件,在Component接口中实现子部件管理的相关操作,如添加和删除等。

组合模式的适用场景:表示对象的部分-整体层次结构(树形结构)。

## 定义

我们要构建一个文件系统,它包含文件和文件夹。文件和文件夹有一些共同的操作,比如获取名称、获取大小等。但是它们也有一些不同的操作,例如文件可以读取内容,文件夹可以添加子文件和子文件夹。

基类 含有共同属性

```cpp
class Entry {
  string name;
  int size;

 public:
  Entry(string name) { this->name = name; }
  void setSize(int size) { this->size = size; }
  string getName() { return name; }
  int getSize() { return size; }
  virtual void read(std::string space = " ") = 0;
};
```

文件 包含内容

```cpp
class File : public Entry {
  string content;

 public:
  File(string name, string content) : Entry(name) {
    this->content = content;
    setSize(content.size());
  }
  void read(std::string space = " ") override {
    std::cout << space;
    std::cout << "File : " << getName() << " size [" << getSize()
              << "] content[" << content << "]" << std::endl;
  }
};
```

文件夹 可包含多个文件以及文件夹

```cpp
class Folder : public Entry {
  vector<std::shared_ptr<Entry>> children;

 public:
  Folder(string name) : Entry(name) { setSize(0); }
  void addEntry(std::shared_ptr<Entry> entry) {
    children.push_back(entry);
    setSize(getSize() + entry->getSize());
  }
  void read(std::string space = " ") override {
    std::cout << space;
    std::cout << "Folder : " << getName() << " size[" << getSize() << "]"
              << std::endl;
    for (auto child : children) {
      child->read(space + " ");
    }
  }
};
```

## 调用

```cpp
std::shared_ptr<Folder> root = std::make_shared<Folder>("root");
std::shared_ptr<Folder> second = std::make_shared<Folder>("sec");
second->addEntry(std::make_shared<File>("sex.md", "this is a girl"));
root->addEntry(std::make_shared<File>("readme.md", "for test"));
root->addEntry(second);
root->addEntry(std::make_shared<File>("readme2.md", "for test2"));
root->read();
```

## 效果

```cpp
./bin/design/composite
 Folder : root size[31]
  File : readme.md size [8] content[for test]
  Folder : sec size[14]
   File : sex.md size [14] content[this is a girl]
  File : readme2.md size [9] content[for test2]
```

## 回顾

组合模式的设计思路，与其说是一种设计模式，倒不如说是对业务场景的一种数据结构和算法的抽象。其中，数据可以表示成树这种数据结构，业务需求可以通过在树上的递归遍历算法来实现。

组合模式，将一组对象组织成树形结构，将单个对象和组合对象都看做树中的节点，以统一处理逻辑，并且它利用树形结构的特点，递归地处理每个子树，依次简化代码实现。使用组合模式的前提在于，你的业务场景必须能够表示成树形结构。所以，组合模式的应用场景也比较局限，它并不是一种很常用的设计模式。