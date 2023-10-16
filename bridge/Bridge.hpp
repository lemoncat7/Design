/*
 * @Description:
 * @version:
 * @Author: 莫邪
 * @Date: 2023-10-16 09:43:55
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-16 11:12:45
 */
#include <iostream>
#include <memory>

class Game {
  std::string name;

 public:
  Game(std::string name) : name(name) {}
  virtual ~Game() = default;
  virtual void Play() = 0;
  void print() { std::cout << name << std::endl; }
};

class RunningGame : public Game {
 public:
  RunningGame() : Game("Running") {}
  void Play() override { std::cout << "Play Running Game." << std::endl; }
};

class ShootingGame : public Game {
 public:
  ShootingGame() : Game("Shooting") {}
  void Play() override { std::cout << "Play Shooting Game." << std::endl; }
};

class Phone {
  std::shared_ptr<Game> game;

 public:
  Phone() {}
  virtual ~Phone() = default;
  virtual void Download(std::shared_ptr<Game> game) = 0;
  virtual void Open() = 0;
};

class iPhone : public Phone {
  std::shared_ptr<Game> game;

 public:
  void Download(std::shared_ptr<Game> game) override {
    std::cout << "iPhone. download ";
    game->print();
    this->game = game;
  }
  void Open() override {
    std::cout << "iPhone. start ";
    game->Play();
  }
};

class Samsung : public Phone {
  std::shared_ptr<Game> game;

 public:
  void Download(std::shared_ptr<Game> game) override {
    std::cout << "Samsung. download ";
    game->print();
    this->game = game;
  }
  void Open() override {
    std::cout << "Samsung. start ";
    game->Play();
  }
};