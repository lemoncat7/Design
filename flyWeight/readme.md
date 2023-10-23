# 享元模式

## 介绍

所谓“享元”, 顾名思义就是被共享的单元. 享元模式的意图是复用对象, 节省内存, 前提是享元对象是不可变对象.

它使用共享的对象来有效地支持大量细粒度的对象. 具体来说,享元模式尽量减少内存使用,方法是共享相同数据的对象,避免重复创建相同的对象.

具体来讲, 当一个系统中存在大量重复对象的时候, 如果这些重复的对象是不可变对象, 我们就可以利用享元模式将对象设计成享元, 在内存中只保留一份实例, 供多处代码引用. 这样可以减少内存中对象的数量, 起到节省内存的目的.

## 定义

假设我们要开发一个国际象棋游戏,chessboard 上一共有32个棋子。如果对每个棋子都创建一个对象,那会产生大量相似的对象并浪费内存。

使用享元模式,可以把棋子分为两类状态:

内部状态:棋子的名称(king, queen, pawn 等),颜色(黑色或白色)。这部分对每种棋子只需要创建一次。

外部状态:棋子的当前位置。这需要每个棋子都单独保存。

那么我们可以创建一个 ChessPiece 类代表内部状态,里面有棋子的名称和颜色属性。然后创建一个 ChessPieceUnit 类代表每个棋子,里面包含一个 ChessPiece 引用和当前位置坐标。

在游戏中,每次需要一个棋子时,可以从 ChessPiece 缓存池中获得,避免重复创建内部状态相同的 ChessPiece,然后绑定其外部状态,如当前位置。

这样就可以大量节省内存,只需要创建很少的内部状态对象,而复用它们来代表具体的每个棋子。

**共同部分 设定好就不再改变**

```cpp
// ChessPiece为棋子对象的基类(共同部分)
class ChessPiece {
public:
  virtual ~ChessPiece() {}
  virtual std::string render() = 0; 
};
// 具体棋子类,继承自ChessPiece基类(共同部分)
class Queen : public ChessPiece {
public:
  std::string render() override {
    return "渲染Queen";
  }
};
class King : public ChessPiece {
public:
  std::string render() override {
    return "渲染King" ;
  }
};
```

**不同部分**

```cpp
// 棋子对象(不同部分之一 - 棋子类型)
struct ChessPieceUnit {
  ChessPiece* piece;
  int positionX; // 棋子位置(不同部分之二)
  int positionY;
  void print() {
    std::cout << piece->render() << " " << positionX << " " << positionY << std::endl;
  }
};
```

```cpp
// 享元工厂类,使用单例模式
class ChessPieceFactory {
public:
  static ChessPieceFactory* getInstance() {
    static ChessPieceFactory instance;
    return &instance;
  }
  
  ChessPiece* getChessPiece(std::string type) {
    if (!pieces.count(type)) {
      if (type == "Queen")
        pieces[type] = new Queen(); 
      else if (type == "King")
        pieces[type] = new King();
    }
    return pieces[type];
  }

private:
  std::unordered_map<std::string, ChessPiece*> pieces;
  
  ChessPieceFactory() {}
};
```

调用

```cpp
// 创建棋子对象
ChessPieceUnit queen1; 
auto factory = ChessPieceFactory::getInstance();
queen1.piece = factory->getChessPiece("Queen");
queen1.positionX = 3;
queen1.positionY = 5;
ChessPieceUnit king1;
king1.piece = factory->getChessPiece("King");
king1.positionX = 4;
king1.positionY = 8;  
// 渲染棋子
queen1.print();
king1.print();
// 修改位置
queen1.positionX = 2;
queen1.positionY = 8;
king1.positionX = 5;
king1.positionY = 2; 
// 渲染棋子
queen1.print();
king1.print();
```

## 效果

```cpp
./bin/design/flyWeight
渲染Queen 3 5
渲染King 4 8
渲染Queen 2 8
渲染King 5 2
```

说明:

- ChessPiece类中定义渲染接口是棋子的共同功能
- Queen和King类继承自ChessPiece,是具体棋子类型的不同之处
- ChessPieceUnit结构体中包含具体棋子对象和位置坐标,是每个棋子不同的状态

这样通过共享内存中相同的ChessPiece对象,避免重复创建,即实现了享元模式。

## 回顾

**1.享元模式的原理**

所谓“享元”，顾名思义就是被共享的单元。享元模式的意图是复用对象，节省内存，前提是享元对象是不可变对象。具体来讲，当一个系统中存在大量重复对象的时候，我们就可以利用享元模式，将对象设计成享元，在内存中只保留一份实例，供多处代码引用，这样可以减少内存中对象的数量，以起到节省内存的目的。实际上，不仅仅相同对象可以设计成享元，对于相似对象，我们也可以将这些对象中相同的部分（字段），提取出来设计成享元，让这些大量相似对象引用这些享元。

**2.享元模式的实现**

享元模式的代码实现非常简单，主要是通过工厂模式，在工厂类中，通过一个Map或者List来缓存已经创建好的享元对象，以达到复用的目的。

使用享元模式的好处:

- 减少内存占用,降低系统资源消耗
- 提高系统性能
- 适用于系统有大量相似对象的情况

其缺点是增加了系统的复杂度,需要区分内部状态和外部状态,这使得程序的逻辑复杂化。