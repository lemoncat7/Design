/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-08 10:53:47
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-08 11:07:48
 */

#include <iostream>
#include <memory>

class AbstractBall {
public:
    virtual void get() = 0;
    virtual void play() = 0;
    virtual ~AbstractBall() = default;
};

class FootBall : public AbstractBall {
public:
    void get() override { std::cout << "get footBall" << std::endl; }
    void play() override { std::cout << "play footBall" << std::endl;}
};

class BasketBall : public AbstractBall {
public:
    void get() override { std::cout << "get basketBall" << std::endl; }
    void play() override { std::cout << "play basketBall" << std::endl;}
};

class Volleyball : public AbstractBall {
public:
    void get() override { std::cout << "get volleyball" << std::endl; }
    void play() override { std::cout << "play volleyball" << std::endl;}
};

enum Type {
    FootBallType = 1,
    BasketBallType = 2,
    VolleyballType = 3
    };

class SimpleFactory {
public:
    std::shared_ptr<AbstractBall> createBall(Type type) {
        switch (type) {
            case 1:
                return std::make_shared<FootBall>();
            case 2:
                return std::make_shared<BasketBall>();
            case 3:
                return std::make_shared<Volleyball>();
            default:
                return nullptr;
        }
    }
};