<!--
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-18 11:06:07
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-18 11:06:08
-->
# 适配器模式

代理、桥接、装饰器、适配器，这4种模式是比较常用的结构型设计模式.

它们之间的区别。

- **代理模式：**代理模式在不改变原始类接口的条件下，为原始类定义一个代理类，主要目的是控制访问，而非加强功能，这是它跟装饰器模式最大的不同。
- **桥接模式：**桥接模式的目的是将接口部分和实现部分分离，从而让它们可以较为容易、也相对独立地加以改变。
- **装饰器模式：**装饰者模式在不改变原始类接口的情况下，对原始类功能进行增强，并且支持多个装饰器的嵌套使用。
- **适配器模式：**适配器模式是一种事后的补救策略。适配器提供跟原始类不同的接口，而代理模式、装饰器模式提供的都是跟原始类相同的接口。

## 介绍

适配器模式**（Adapter Pattern）,** 也称为包装器模式**（Wrapper Pattern）,** 是一种结构型设计模式。该模式允许对象的接口与客户端的期望接口不匹配时协同工作. 适配器模式创建一个包装类, 该包装类包含了原始类的实例, 并实现了客户端所期望的接口. 通过这种方式, 适配器模式允许原始类与客户端协同工作, 尽管它们的接口不一致.

强调一个类的接口适配成另一个类的接口, 使原本不兼容的类能够协同工作.

通常有两种主要类型:

类适配器, 使用多继承或接口实现来适配接口.

对象适配器, 使用组合来包装原始类的实例, 以实现新的接口.

## 定义

想象你有一部新的手机，它使用USB-C充电接口，但你在家里只有一个旧的手机充电器，它使用Micro-USB接口。你不想购买一个新的充电器，而是想找到一种方法，使旧的充电器与你的新手机兼容。这就是适配器模式的应用。

在这个例子中：

1. **问题：** 你有一个新的手机和一个旧的充电器，它们的接口不匹配，但你想要充电。
2. **解决方案（适配器）：** 你可以获得一个USB-C到Micro-USB适配器。这个适配器连接到你的新手机的USB-C接口，并允许你将旧的Micro-USB充电器连接到它。
3. **效果：** 现在，你可以使用旧的充电器来为新手机充电，而无需购买新的充电器。适配器充当一个中间层，使不兼容的部分协同工作。

使用usb-c的手机

```cpp
class USB_CPhone{
public:
  const std::string chargeWithUSB_C() {
    return "Charging with USB-C";
  }
};
```

旧手机充电线

```cpp
class MicroUSBCharger {
public:
  const std::string chargeWithMicroUSB() {
    return "Charging with Micro-USB";
  }
};
```

适配器

```cpp
//对象适配器
class ObjectChargeAdapter: public USB_CPhone {
  MicroUSBCharger microUSBCharger;
public:
  const std::string chargeWithUSB_C() {
    return microUSBCharger.chargeWithMicroUSB();
  }
};

//类适配器
class ClassChargeAdapter: public MicroUSBCharger ,private USB_CPhone {
public:
  const std::string chargeWithUSB_C() {
    return chargeWithMicroUSB();
  }
};
```

## 调用

```cpp
ObjectChargeAdapter new_phone;
std::cout << new_phone.chargeWithUSB_C() << std::endl;
ClassChargeAdapter new_phone1;
std::cout << new_phone1.chargeWithUSB_C() << std::endl;
```

## 效果

```cpp
./bin/design/Adapter
Charging with Micro-USB
Charging with Micro-USB
```

## 适用

1. **接口不匹配：** 当你需要使用一个已经存在的类，但它的接口与你的需求不匹配时，适配器模式很有用。这可以是由于新旧系统之间接口不一致，或者是由于第三方库的接口与你的代码不兼容。
2. **代码复用：** 适配器模式有助于重用现有的类，而不必对其进行修改。这对于避免修改稳定的代码或依赖于外部库的代码非常有用。
3. **无法修改源代码：** 当你不能修改原始类的源代码，但需要使其与其他类协同工作时，适配器模式是一种有效的解决方案。
4. **兼容性：** 当你希望让不同接口的类在一起工作，以提高系统的整体兼容性时，适配器模式非常有帮助。
5. **新旧系统集成：** 在迁移到新系统时，你可能需要将旧系统的组件与新系统集成。适配器模式可以帮助你连接新旧系统的组件，以确保它们能够协同工作。
6. **接口的抽象：** 适配器模式可以用来创建更抽象的接口，使得客户端代码更灵活和独立于具体类的实现。

总之，适配器模式在需要将不兼容的接口进行协调工作、重用现有代码、维护代码的稳定性和提高系统的可扩展性时非常有用。它有助于降低代码的耦合度，并使不同组件能够相互协同工作，同时保持代码的整洁和易于维护。

那在实际的开发中，什么情况下才会出现接口不兼容呢?

- 封装有缺陷的接口设计
- 统一多个类的接口设计
- 替换依赖的外部系统
- 兼容老版本接口
- 适配不同格式的数据