/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-23 11:08:09
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-23 11:21:37
 */
#include "FlyWeight.hpp"

int main() {
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
  return 0;
}