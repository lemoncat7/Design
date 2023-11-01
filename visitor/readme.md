<!--
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-11-01 10:17:00
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-11-01 10:17:00
-->
算是23种经典设计模式中最难理解的几个之一。因为它难理解、难实现，应用它会导致代码的可读性、可维护性变差，所以，访问者模式在实际的软件开发中很少被用到，在没有特别必要的情况下，建议你不要使用访问者模式。

## 介绍

访问者模式是一种对象行为型设计模式,它允许在不改变元素类的前提下定义作用于元素类的新操作。

主要解决的是对象结构相对稳定,但经常需要在此对象结构上定义新的操作的问题。访问者模式可以将相关的行为局部化到一个访问者类中,而不是将这些行为分散到这个对象结构的所有类中。

访问者模式的主要角色包括:

- 访问者(Visitor)角色:定义作用于元素对象的操作,它存储遍历元素对象的算法。访问者可以为每个 ConcreteElement 增加新的操作。
- 元素(Element)角色:定义接受访问者访问的操作接口,其中包含一个 accept() 方法,它以一个访问者为参数。
- 具体元素(ConcreteElement)角色:实现了元素角色提供的 accept() 操作。
- 对象结构(Object Structure)角色:是一个包含元素角色的容器,提供让访问者对象遍历容器中的所有元素的方法。

其实质是将算法与对象结构分离,把相关的行为局部化封装在访问者中,而不是分散在一个个对象中。这样既容易增加新的操作,也容易增加新的元素类,它符合“开闭原则”。

举个例子,可以利用访问者模式对一个敌我对象集合进行遍历,执行不同的行为,而不需要修改每个敌我对象的类。

## 定义

假设我们从网站上爬取了很多资源文件，它们的格式有三种：PDF、PPT、Word。我们现在要开发一个工具来处理这批资源文件。这个工具的其中一个功能是，把这些资源文件中的文本内容抽取出来放到txt文件中。

当然, 实现方法很多, 我这边实现一种实现方式

通过抽象, 让PDF、PPT、Word 三个子类分别继承实现 ContentToTxt 函数

```cpp
// 继承重写
class ReaderAbstraction {
  std::string file_path_;
public:
  ReaderAbstraction(std::string file_path) : file_path_(file_path) {}
  virtual void ContentToTxt() = 0;
};
//PDF、PPT、Word
class PDFReader : public ReaderAbstraction {
public:
  PDFReader(std::string file_path) : ReaderAbstraction(file_path) {}
  void ContentToTxt() override { std::cout << "PDF to txt" << std::endl; }
};
class PPTReader : public ReaderAbstraction {
public:
  PPTReader(std::string file_path) : ReaderAbstraction(file_path) {}
  void ContentToTxt() override { std::cout << "PPT to txt" << std::endl; }
};
class WordReader : public ReaderAbstraction {
public:
  WordReader(std::string file_path) : ReaderAbstraction(file_path) {}
  void ContentToTxt() override { std::cout << "Word to txt" << std::endl; }
};
```

通过工程去去创建和抽取功能

```cpp
//工厂
class ReaderFactory {
public:
  static std::unique_ptr<ReaderAbstraction> CreateReader(const std::string &type, 
                                                         const std::string &file_path) {
    if (type == "PDF") {
      return std::make_unique<PDFReader>(file_path);
    } else if (type == "PPT") {
      return std::make_unique<PPTReader>(file_path);
    } else if (type == "Word") {
      return std::make_unique<WordReader>(file_path);
    }
    return nullptr;
  }
};
```

如果工具的功能不停地扩展，不仅要能抽取文本内容，还要支持压缩、提取文件元信息（文件名、大小、更新时间等等）构建索引等一系列的功能，那如果我们继续按照上面的实现思路，就会存在这样几个问题：

- 违背开闭原则，添加一个新的功能，所有类的代码都要修改
- 虽然功能增多，每个类的代码都不断膨胀，可读性和可维护性都变差了
- 把所有比较上层的业务逻辑都耦合到PdfFile、PPTFile、WordFile类中，导致这些类的职责不够单一

针对上面的问题，我们常用的解决方法就是拆分解耦，把业务操作跟具体的数据结构解耦，设计成独立的类。这里我们按照访问者模式的演进思路来对上面的代码进行重构。

文件类

```cpp
class FileAbstraction {
  std::string file_path_;
public:
  FileAbstraction(const std::string &file_path) : file_path_(file_path) {}
  std::string& FilePath() { return file_path_; }
  virtual void Accept(Visitor &visitor) = 0;
};
class PDFFile : public FileAbstraction {
public:
  PDFFile(const std::string &file_path) : FileAbstraction(file_path) {}
  void Accept(Visitor &visitor) override;
};
class PPTFile : public FileAbstraction {
public:
  PPTFile(const std::string &file_path) : FileAbstraction(file_path) {}
  void Accept(Visitor &visitor) override;
};
class WordFile : public FileAbstraction {
public:
  WordFile(const std::string &file_path) : FileAbstraction(file_path) {}
  void Accept(Visitor &visitor) override;
};
```

实现

```cpp
void PDFFile::Accept(Visitor &visitor) {
  visitor.VisitPDFFile(*this);
}
void PPTFile::Accept(Visitor &visitor) {
  visitor.VisitPPTFile(*this);
}
void WordFile::Accept(Visitor &visitor) {
  visitor.VisitWordFile(*this);
}
```

访问者

```cpp
class Visitor {
public:
  virtual void VisitPDFFile(PDFFile &file) {};
  virtual void VisitPPTFile(PPTFile &file) {};
  virtual void VisitWordFile(WordFile &file) {};
};
//阅读
class ReaderVisitor : public Visitor {
public:
  void VisitPDFFile(PDFFile &file) override;
  void VisitPPTFile(PPTFile &file) override;
  void VisitWordFile(WordFile &file) override;
};
//压缩
class CompressorVisitor : public Visitor {
public:
  void VisitPDFFile(PDFFile &file) override;
  void VisitPPTFile(PPTFile &file) override;
  void VisitWordFile(WordFile &file) override;
};
```

实现

```cpp
/ 阅读
void ReaderVisitor::VisitPDFFile(PDFFile &file) {
  std::cout << file.FilePath() << "阅读PDF文件" << std::endl;
}
void ReaderVisitor::VisitPPTFile(PPTFile &file) {
  std::cout << file.FilePath() << "阅读PPT文件" << std::endl;
}
void ReaderVisitor::VisitWordFile(WordFile &file) {
  std::cout << file.FilePath() << "阅读Word文件" << std::endl;
}
// 压缩

void CompressorVisitor::VisitPDFFile(PDFFile &file) {
  std::cout << file.FilePath() << "压缩PDF文件" << std::endl;
}
void CompressorVisitor::VisitPPTFile(PPTFile &file) {
  std::cout << file.FilePath() << "压缩PPT文件" << std::endl;
}
void CompressorVisitor::VisitWordFile(WordFile &file) {
  std::cout << file.FilePath() << "压缩Word文件" << std::endl;
}
```

## 调用

```cpp
int main() {
  ReaderVisitor reader;
  CompressorVisitor compressor;
  PDFFile pdf("a.pdf");
  pdf.Accept(reader);
  pdf.Accept(compressor);
  PPTFile ppt("a.ppt");
  ppt.Accept(reader);
  ppt.Accept(compressor);
  WordFile word("a.doc");
  word.Accept(reader);
  word.Accept(compressor);
  return 0;
}
```

## 效果

```cpp
./bin/design/visitor
a.pdf阅读PDF文件
a.pdf压缩PDF文件
a.ppt阅读PPT文件
a.ppt压缩PPT文件
a.doc阅读Word文件
a.doc压缩Word文件
```

## 回顾

访问者模式允许一个或者多个操作应用到一组对象上，设计意图是解耦操作和对象本身，保持类职责单一、满足开闭原则以及应对代码的复杂性。

对于访问者模式，学习的主要难点在代码实现。而代码实现比较复杂的主要原因是，函数重载在大部分面向对象编程语言中是静态绑定的。也就是说，调用类的哪个重载函数，是在编译期间，由参数的声明类型决定的，而非运行时，根据参数的实际类型决定的。

正是因为代码实现难理解，所以，在项目中应用这种模式，会导致代码的可读性比较差。如果你的同事不了解这种设计模式，可能就会读不懂、维护不了你写的代码。所以，除非不得已，不要使用这种模式。