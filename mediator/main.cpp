/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-12-19 10:31:02
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-12-19 10:31:03
 */
#include "Mediator.hpp"

int main() {
    ConcreteMediator mediator;

    ConcreteColleague user1(&mediator, "User 1");
    ConcreteColleague user2(&mediator, "User 2");
    ConcreteColleague user3(&mediator, "User 3");

    mediator.addColleague(&user1);
    mediator.addColleague(&user2);
    mediator.addColleague(&user3);

    user1.sendMessage("Hello, everyone!");
    user2.sendMessage("Hi there!");
    user3.sendMessage("Greetings!");

    return 0;
}