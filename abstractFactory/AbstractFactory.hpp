/*
 * @Description:
 * @version:
 * @Author: 莫邪
 * @Date: 2023-10-09 09:30:04
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-09 09:49:43
 */
#include <iostream>
#include <memory>

class AbstractBall {
 public:
  virtual ~AbstractBall() = default;
  virtual void play() = 0;
};

class BasketBall : public AbstractBall {
 public:
  BasketBall() { play(); }
  void play() override { std::cout << "play basketball" << std::endl; }
};

class Football : public AbstractBall {
 public:
  Football() { play(); }
  void play() override { std::cout << "play football" << std::endl; }
};

class Volleyball : public AbstractBall {
 public:
  Volleyball() { play(); }
  void play() override { std::cout << "play volleyball" << std::endl; }
};

class AbstractShirt {
 public:
  virtual ~AbstractShirt() = default;
  virtual void wear() = 0;
};

class BasketShirt : public AbstractShirt {
 public:
  BasketShirt() { wear();}
  void wear() override { std::cout << "wear basketShirt" << std::endl;}
};

class FootballShirt : public AbstractShirt {
 public:
  FootballShirt() { wear();}
  void wear() override { std::cout << "wear footballShirt" << std::endl;}
};

class VolleyballShirt : public AbstractShirt {
 public:
  VolleyballShirt() { wear();}
  void wear() override { std::cout << "wear volleyballShirt" << std::endl;}
};

class AbstractFactory {
 public:
  virtual ~AbstractFactory() = default;
  virtual std::shared_ptr<AbstractBall> createBall() = 0;
  virtual std::shared_ptr<AbstractShirt> createShirt() = 0;
};

class BasketballFactory : public AbstractFactory {
 public:
  std::shared_ptr<AbstractBall> createBall() override { return std::make_shared<BasketBall>(); }
  std::shared_ptr<AbstractShirt> createShirt() override { return std::make_shared<BasketShirt>();}
};

class FootballFactory : public AbstractFactory {
 public:
  std::shared_ptr<AbstractBall> createBall() override { return std::make_shared<Football>(); }
  std::shared_ptr<AbstractShirt> createShirt() override { return std::make_shared<FootballShirt>();}
};

class VolleyballFactory : public AbstractFactory {
 public:
  std::shared_ptr<AbstractBall> createBall() override { return std::make_shared<Volleyball>(); }
  std::shared_ptr<AbstractShirt> createShirt() override { return std::make_shared<VolleyballShirt>();}
};