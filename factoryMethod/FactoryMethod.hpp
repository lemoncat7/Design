/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-08 14:46:44
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-08 14:59:02
 */
#include <memory>
#include <iostream>

class AbstractProduct {		//抽象产品
public:
	AbstractProduct() {}
	virtual void print() = 0;
	virtual void play() = 0;
};

class PowerArmor : public AbstractProduct {
public:
	PowerArmor() {
		print();
		play();
	}
	void print() {
		std::cout << "得到一个动力装甲" << std::endl;
	}
	void play() {
		std::cout << "动力装甲因太过脆弱而被损坏" << std::endl;
	}
};

class FlyingPowder : public AbstractProduct {
public:
	FlyingPowder() {
		print();
		play();
	}
	void print() {
		std::cout << "得到一个飞路粉" << std::endl;
	}
	void play() {
		std::cout << "飞路粉太香招来苍蝇" << std::endl;
	}
};

class Goblins : public AbstractProduct {
public:
	Goblins() {
		print();
		play();
	}
	void print() {
		std::cout << "得到一个哥布林" << std::endl;
	}
	void play() {
		std::cout << "暴躁的哥布林发起了进攻" << std::endl;
	}
};

class AbstractFactory {
public :
	AbstractFactory() {}
	virtual std::shared_ptr<AbstractProduct> getProduct() = 0;
};

class MachineryFactory : public AbstractFactory{
public : 
	MachineryFactory() {}
	std::shared_ptr<AbstractProduct> getProduct() {
		return std::make_shared<PowerArmor>();
	}
};

class MagicFactory : public AbstractFactory {
public:
	MagicFactory() {}
	std::shared_ptr<AbstractProduct> getProduct() {
		return std::make_shared<FlyingPowder>();
	}
};

class Greenfactory : public AbstractFactory {
public:
	Greenfactory() {}
	std::shared_ptr<AbstractProduct> getProduct() {
		return std::make_shared<Goblins>();
	}
};