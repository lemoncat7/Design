/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-16 09:43:58
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-16 11:08:17
 */
#include "Bridge.hpp"

int main() {
  //有两个游戏
  auto running = std::make_shared<RunningGame>();
  auto shooting = std::make_shared<ShootingGame>();
  //两个手机
  auto iphone = std::make_shared<iPhone>();
  auto samsung = std::make_shared<Samsung>();
  //下载游戏
  iphone->Download(running);
  samsung->Download(shooting);
  //运行游戏
  iphone->Open();
  samsung->Open();
  //换个游戏
  samsung->Download(running);
  //运行游戏
  samsung->Open();
  return 0;
}