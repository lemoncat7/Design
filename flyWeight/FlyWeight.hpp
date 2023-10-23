/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-23 11:08:05
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-23 11:17:18
 */
#include <iostream>
#include <string>
#include <unordered_map>
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
// 棋子对象(不同部分之一 - 棋子类型)
struct ChessPieceUnit {
  ChessPiece* piece;
  int positionX; // 棋子位置(不同部分之二)
  int positionY;
  void print() {
    std::cout << piece->render() << " " << positionX << " " << positionY << std::endl;
  }
};
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

