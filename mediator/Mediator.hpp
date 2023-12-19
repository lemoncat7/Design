/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-12-19 10:30:56
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-12-19 10:30:57
 */
#pragma once

#include <iostream>
#include <string>
#include <vector>

// 抽象中介者
class Mediator {
public:
    virtual void sendMessage(const std::string& message, class Colleague* colleague) = 0;
};

// 抽象同事类
class Colleague {
public:
    Colleague(Mediator* mediator, const std::string& name) : mediator(mediator), name(name) {}

    virtual void sendMessage(const std::string& message) = 0;
    virtual void receiveMessage(const std::string& message) = 0;

protected:
    Mediator* mediator;
    std::string name;
};

// 具体中介者
class ConcreteMediator : public Mediator {
public:
    void addColleague(Colleague* colleague) {
        colleagues.push_back(colleague);
    }

    virtual void sendMessage(const std::string& message, Colleague* colleague) override {
        for (Colleague* c : colleagues) {
            if (c != colleague) {
                c->receiveMessage(message);
            }
        }
    }

private:
    std::vector<Colleague*> colleagues;
};

// 具体同事类
class ConcreteColleague : public Colleague {
public:
    ConcreteColleague(Mediator* mediator, const std::string& name) : Colleague(mediator, name) {}

    virtual void sendMessage(const std::string& message) override {
        std::cout << name << " 发送消息: " << message << std::endl;
        mediator->sendMessage(message, this);
    }

    virtual void receiveMessage(const std::string& message) override {
        std::cout << name << " 收到消息: " << message << std::endl;
    }
};
