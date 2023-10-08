<!--
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-08 10:37:55
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-08 11:22:11
-->
设计模式是一种通用的、可重复利用的解决特定问题的软件设计方法。设计模式提供了在开发中常见问题的解决方案，它们是经过验证的最佳实践，有助于提高代码的可维护性、可读性和可扩展性。

使用设计模式有以下好处：

可维护性：设计模式可以使代码更易于理解和维护。由于它们是经过广泛验证的解决方案，其他开发人员可以更容易地理解您的代码，从而减少了错误和bug的可能性。
可重用性：设计模式鼓励将代码分解成小块，这些小块可以在不同的项目中重复使用。这降低了代码重复的风险，提高了开发效率。
扩展性：设计模式有助于使代码更容易扩展，以满足未来的需求变化。您可以通过添加新的模式或扩展现有的模式来支持新功能。
降低耦合度：设计模式有助于降低代码中不同部分之间的紧密耦合度，使其更容易进行单元测试和模块化开发。
共享最佳实践：设计模式代表了许多经验丰富的开发人员在不同项目中的共享经验，这有助于确保您的代码遵循行业标准和最佳实践。
总之，使用设计模式可以提高软件的质量，减少错误，提高开发效率，并使代码更容易维护和扩展。设计模式是编程的强大工具，值得在软件开发中加以利用。

面向对象的设计原则 遵循可维护性 可复用性

高内聚：内聚是对软件系统中元素职责相关性和集中度的度量。如果元素具有高度相关的职责，除了这些职责内的任务，没有其它过多的工作，那么该元素就具有高内聚性；反之则成为低内聚性。

低耦合：耦合是软件结构中各模块之间相互连接的一种度量，耦合强弱取决于模块间接口的复杂程度、进入或访问一个模块的点以及通过接口的数据

1 单一职责 一个对象应该只包含单一的职责，并且该职责被完整地封装在一个类中 就一个类而言，应该仅有一个引起它变化的原因

2 开闭原则 软件实体应对扩展开放，对修改关闭

3 里氏代换原则 所有引用基类的地方必须能透明地使用其子类的对象

4 依赖倒转原则 高层模块不应该依赖低层模块，它们都应该依赖抽象 抽象不应该依赖于细节，细节应该依赖于抽象

5 接口隔离原则 客户端不应该依赖那些它不需要的接口

6 合成复用原则 优先使用对象组合，而不是通过继承来达到复用的目的

7 迪米特法则 每一个软件单位对其他单位都只有最少的知识，而且局限于那些与本单位密切相关的软件单位