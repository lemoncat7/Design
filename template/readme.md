<!--
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-25 11:22:31
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-25 11:22:32
-->
# 模版模式

模板模式主要是用来解决复用和扩展两个问题。

## 介绍

模板方法(Template Method)是一种设计模式,属于行为型设计模式。

其核心思想是:

在抽象父类中定义了一个算法的骨架,里面有一些抽象的方法。子类继承这个抽象类,需要重写这些抽象方法来完成算法中某些步骤。子类不需要重写整个算法流程,就可以重定义算法中的某些部分。

模板方法模式的主要优点:

- 封装不变部分,扩展可变部分。把相同流程封装到抽象父类模板方法中,将可变部分留给子类实现。
- 复用代码。子类可以复用抽象类中封装的算法流程代码。
- 符合开闭原则。通过扩展子类而非修改父类模板方法来改变算法。

模板方法模式适用于:

- 多个子类有着相同的算法流程,且其中某些实现不同。
- 需要复用一个算法的框架,但其中某些步骤将在子类中实现。
- 当不想子类修改算法流程时,可以将其定义为final方法。

模板方法模式的核心在于正确识别出算法中的稳定流程和可变部分,继而将其封装为模板方法和抽象方法。这样可以实现代码复用和扩展解耦。

## 定义

我们需要开发一个 报销系统,用于企业员工报销费用。报销系统要实现以下基本流程:

1. 员工提交报销申请
2. 负责人进行初审
3. 财务人员进行终审
4. 支付报销费用

其中,不同部门的报销流程主要差异在于:

1. 初审和终审的审批标准不同
2. 部分部门可能需要部门经理额外审批
3. 报销总额超过一定限额需要财务总监审批

要求:

1. 抽象出报销申请的基本流程作为模板方法
2. 使用不同的部门类继承基本报销流程类,重写可变部分的步骤
3. 部门类只关注自己的审批逻辑,不需要重复编写基本流程

## 报销基类

实现共通的流程

```cpp
// 报销基类
class Reimbursement {
public:
  void process() {
    submit();
    firstReview(); 
    finalReview();
    pay();
  }
  virtual void submit() {
    cout << "提交报销申请" << endl;
  }
  virtual void firstReview() = 0;
  virtual void finalReview() = 0;
  virtual void pay() {
    cout << "支付报销费用" << endl; 
  }
};
```

各个部门实现自己的报销逻辑

```cpp
// 部门报销类
class DepartmentReimbursement : public Reimbursement {
public:
  void firstReview() override {
    cout << "部门特定的初审流程" << endl;
  }
  void finalReview() override {
   cout << "部门特定的终审流程" << endl;  
  }
};
// 财务部门报销类
class FinanceDepartmentReimbursement : public Reimbursement {
public:
  void firstReview() override {
    cout << "财务部门特定的初审流程" << endl;
  }
  void finalReview() override {
    cout << "财务部门特定的终审流程" << endl;
  }
};
```

## 调用

```cpp
Reimbursement* r1 = new DepartmentReimbursement();
r1->process();
Reimbursement* r2 = new FinanceDepartmentReimbursement();
r2->process();
```

## 效果

```cpp
./bin/design/template 
提交报销申请
部门特定的初审流程
部门特定的终审流程
支付报销费用
提交报销申请
财务部门特定的初审流程
财务部门特定的终审流程
支付报销费用
```

## 回顾

模板方法模式在一个方法中定义一个算法骨架，并将某些步骤推迟到子类中实现。模板方法模式可以让子类在不改变算法整体结构的情况下，重新定义算法中的某些步骤。这里的“算法”，我们可以理解为广义上的“业务逻辑”，并不特指数据结构和算法中的“算法”。这里的算法骨架就是“模板”，包含算法骨架的方法就是“模板方法”，这也是模板方法模式名字的由来。

模板模式有两大作用：复用和扩展。其中，复用指的是，所有的子类可以复用父类中提供的模板方法的代码。扩展指的是，框架通过模板模式提供功能扩展点，让框架用户可以在不修改框架源码的情况下，基于扩展点定制化框架的功能。