<!--
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-27 10:59:34
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-27 10:59:35
-->
# 职责链模式

## 介绍

职责链模式是一种行为设计模式,其主要思想是:

1.  避免请求的发送者与接收者耦合在一起,让多个对象都有可能接收请求。
2. 将这些接收者对象连接成一条链,并且沿着这条链传递请求,直到有对象处理它为止。

职责链模式的主要角色包括:

- 抽象处理者(Handler):定义了一个处理请求的接口,包含对后继者的引用以及一个抽象处理方法。
- 具体处理者(Concrete Handler):实现了抽象处理者的处理方法,判断是否有能力处理该请求,如果可以处理则处理,否则将请求传给后继者。
- 客户类(Client):创建处理链,并向链头的具体处理者对象提交请求,不关心实际的处理者。

职责链模式的主要优点:

1. 降低了发送者和接收者之间的耦合关系。
2. 增强了系统的可扩展性,可以通过增加或者修改链中的处理者来扩展系统。
3. 增强了给对象指派职责的灵活性。

职责链模式适用于有多个对象可以处理同一个请求的场景,例如多级请求审批、异常监控等。通过职责链模式,请求发送者只需要将请求发送到链上,无需关心由谁来处理,实现了请求者和处理者的松耦合。

## 定义

假设有一个购物网站,当用户下单时,订单数据需要经过以下多个处理步骤:

1. 检查库存:检查用户购买的商品是否有现货
2. 校验价格:校验订单中商品的价格是否正确
3. 计算运费:根据收货地址计算运费
4. 生成订单:生成订单信息
5. 发送邮件:给用户发送订单确认邮件

定义职责链基类

```cpp
// 抽象处理者
class Handler {
public:
  virtual void handleRequest(string request) = 0;
  void setNext(shared_ptr<Handler> handler) {
    nextHandler = handler; 
  }
protected:
  shared_ptr<Handler> nextHandler;
};
```

实现具体实现类

```cpp
// 检查库存
class StockChecker : public Handler {
  map<string, int> stock;
public:
  StockChecker() {
    stock = {{"goods1", 100}, {"goods2", 10}, {"goods3", 1000}};
  }
  void handleRequest(string request) override {
    if (/* 检查库存 */stock[request] > 10) {
      cout << "库存检查通过" << endl;
    } else {
      cout << "商品库存不足" << endl; 
      return;
    }
    // 传递给下一处理者
    if (nextHandler) nextHandler->handleRequest(request);
  }
};
// 校验价格
class PriceValidator : public Handler {
  map<string, int> price;
public:
  PriceValidator() {
    price = {{"goods1", 100}, {"goods2", 10}, {"goods3", 1000}};
  }
  void handleRequest(string request) override {
    if (/* 校验价格 */price[request] > 100) {
      cout << "价格校验通过" << endl;
    } else {
      cout << "商品价格错误" << endl;
      return;
    }
    if (nextHandler) nextHandler->handleRequest(request);
  }
};
// 其他具体处理者 
// ...
```

## 调用

```cpp
// 初始化责任链
std::shared_ptr<Handler> stockChecker = std::make_shared<StockChecker>();
std::shared_ptr<Handler> priceValidator = std::make_shared<PriceValidator>();
stockChecker->setNext(priceValidator);
// 提交请求
string request = "goods1";
stockChecker->handleRequest(request);
std::cout << "=========================================" << std::endl;
// 提交请求
request = "goods2";
stockChecker->handleRequest(request);
std::cout << "=========================================" << std::endl;
// 提交请求
request = "goods3";
stockChecker->handleRequest(request);
```

## 效果

```cpp
./bin/design/chainOfResponsibility
库存检查通过
商品价格错误
=========================================
商品库存不足
=========================================
库存检查通过
价格校验通过
```

传统的方式是逐一调用这些处理对象的方法。使用职责链模式后,可以将这些对象接成一条链,请求从链头传递到链尾,每个处理对象判断是否需要处理该请求,如果需要则处理后再传递给下一个对象,直到请求被处理完毕。

这种方式提高了请求处理的灵活性,客户端只需要将请求发送到链头,而不需要关心链的结构,新增或者删除处理对象也方便,只需要修改链的结构即可。此外,职责链模式还提高了每个处理对象的独立性,责任单一。

## 回顾

模板模式、策略模式、在职责链模式

这三种模式具有相同的作用：**复用**和**扩展**，在实际的项目开发中比较常用，特别是框架开发中，我们可以利用它们来提供框架的扩展点，能够让框架的使用者在不修改框架源码的情况下，基于扩展点定制化框架的功能。

在职责链模式中，多个处理器依次处理同一个请求。一个请求先经过A处理器处理，然后再把请求传递给B处理器，B处理器处理完后再传递给C处理器，以此类推，形成一个链条。链条上的每个处理器各自承担各自的处理职责，所以叫作职责链模式。

在GoF的定义中，一旦某个处理器能处理这个请求，就不会继续将请求传递给后续的处理器了。当然，在实际的开发中，也存在对这个模式的变体，那就是请求不会中途终止传递，而是会被所有的处理器都处理一遍。

职责链模式有两种常用的实现。一种是使用链表来存储处理器，另一种是使用数组来存储处理器，后面一种实现方式更加简单。