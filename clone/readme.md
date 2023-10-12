创建型模式: 单例模式、工厂模式、建造者模式、原型模式

## 定义

通过一个已有对象, 获得更多相同或相似的对象. 

`使用原型实例指定待创建对象的类型，并且通过复制这个原型来创建新的对象。`

## 为什么使用原型模式

如果对象的创建成本比较大, 然后同一个类的对象之间的差别不大. 这时候就可以使用已有对象通过拷贝的方式进行创建新的对象. 以达到节省创建时间的效果

## 什么时候会产生较大成本的对象创建

实际上, 为对象申请内存, 给成员赋值并不会产生多大的性能和时间. 但如果在创建的过程中需要进行复杂的计算(排序, 哈希…), 亦或者是文本系统, 数据库, 网络…的读取,.

这个时候可以通过拷贝构造创建对象可以减少这些消耗性能时间的操作.

## 原型模式的两种方式 **浅拷贝** 和 **深拷贝**

深拷贝（Deep Copy）和浅拷贝（Shallow Copy）是与对象复制相关的两种不同方式，它们有着重要的区别：

1. **浅拷贝（Shallow Copy）**：
    - 浅拷贝是一种简单的复制操作，它只复制对象的成员变量的值。
    - 浅拷贝创建一个新对象，然后将原对象的成员变量的值复制到新对象中。
    - 如果对象包含指针类型的成员变量，浅拷贝只会复制指针的值，而不会复制指针指向的数据。这可能导致多个对象共享相同的内存位置，即浅拷贝对象和原对象之间的数据共享，如果一个对象修改了共享的数据，其他对象也会受到影响。
2. **深拷贝（Deep Copy）**：
    - 深拷贝是一种更复杂的复制操作，它不仅复制对象的成员变量的值，还会递归复制指针指向的数据。
    - 深拷贝会为新对象创建新的内存空间，并将原对象的数据递归复制到新的内存位置。
    - 这确保了每个对象都有自己的独立数据副本，修改一个对象的数据不会影响其他对象。

C++默认提供了拷贝构造函数

 默认拷贝构造函数会自动被编译器生成，除非你自定义了拷贝构造函数，否则将使用默认的合成拷贝构造函数。

而默认的拷贝函数属于浅拷贝.

下面以同学拷贝作业为例🥸

有个作业类包含 学号, 姓名, 答案

```cpp
class Homework {
 public:
  int id;
  std::string name;
  std::string answer;
  Homework(int id, std::string name, std::string answer)
      : id(id), name(name), answer(answer) {}
  void print() {
    std::cout << "id: " << id << " name: " << name << " answer: " << answer
              << std::endl;
  }
};
```

## 浅拷贝

```cpp
class ShallowStudent {
 public:
  Homework* homework;
  ShallowStudent(Homework* homework) : homework(homework) {}
  void print() {
    homework->print();
  }
};
```

这里不实现拷贝构造和赋值构造, 都是用默认的

调用方式

```cpp
auto A = ShallowStudent(new Homework(1, "小杰", "小杰作业"));
auto B = ShallowStudent(A);
B.homework->id = 2;
B.homework->name = "小李";
A.print();
B.print();
```

得到的效果

```cpp
./bin/design/Clone
id: 2 name: 小李 answer: 小杰作业
id: 2 name: 小李 answer: 小杰作业
```

这里看到 同学B 拷贝完作业后修改名字, 把原来同学A的姓名也修改掉了, 这明显不是我们想要的效果. 

## 深拷贝

下边我们手动实现拷贝构造和 赋值构造函数

```cpp
class DeepStudent {
 public:
  Homework* homework;
  DeepStudent(Homework* homework) : homework(homework) {}
  void print() {
    homework->print();
  }
  void CloneHomework(const Homework* homework) {
    this->homework = new Homework(*homework);
  }
  DeepStudent(const DeepStudent& other) {
    CloneHomework(other.homework);
  }
  DeepStudent& operator=(const DeepStudent& other) {
    CloneHomework(other.homework);
    return *this;
  }

};
```

调用方式

```cpp
auto C = DeepStudent(new Homework(3, "小迓", "小迓作业"));
  auto D = DeepStudent(C);
  D.homework->id = 4;
  D.homework->name = "小王";
  auto E = C;
  E.homework->id = 5;
  E.homework->name = "小张";
  C.print();
  D.print();
  E.print();
```

得到的效果

```cpp
./bin/design/Clone
id: 3 name: 小迓 answer: 小迓作业
id: 4 name: 小王 answer: 小迓作业
id: 5 name: 小张 answer: 小迓作业
```

从效果得到 同学D, E 修改完学号姓名 不会对 同学C原有的试卷有任何影响

## 结论

(1)编译器会自动生成拷贝构造函数

```cpp
class 类名{
	//拷贝构造函数形式：   一定要有&  const某些情况下可以省略  但不建议！！
	类名(const 类名& o){
	}
};
```

(2)默认生成的拷贝构造函数的实现是按照 字节复制 的形式进行拷贝

(3)哪些时候会调用拷贝构造函数： 用已经实例化的对象来构造一个新的对象

```cpp
class Emp{
    Emp(){}
    Emp(int,string,int){}
}
void func(Emp e){}
void bar(Emp& e){}
Emp e;
Emp e1(e); //拷贝构造
Emp e2 = e;//拷贝构造
Emp e3; 
e3 = e;    //不是拷贝构造
func(e);   //拷贝构造
bar(e);    //不会拷贝
 
func(Emp());//匿名对象作为实参时不会调用拷贝构造
func(Emp(1,"",0));//匿名对象
 
Emp e4 = func();//有可能会调用拷贝构造
返回一个全局的 或者 *this 或者引用对象时 会调用拷贝构造
返回匿名对象 或者 函数内存声明的函数时  不会调用拷贝构造
```

(4)什么情况下需要手动实现拷贝构造函数？

默认的拷贝构造函数都是进行字节复制，即浅拷贝

如果需要实现深拷贝则需要自己手动实现拷贝构造函数

深拷贝：

对于指针类型的成员变量，不是拷贝指针变量本身的值，而拷贝指针所指向内存区域的数据

(5)默认的拷贝构造函数会调用类类型成员的拷贝构造

手动实现时需要在 初始化列表中 调用类类型成员的拷贝构造

### 优点:

- 当创建新的对象实例较为复杂时，原型模式可以简化创建过程，提高创建对象的效率；
- 可扩展：模式中提供了抽象原型类，具体原型类可适当扩展；

### 缺点:

- 深克隆代码可能会较为复杂；
- 每一个类都得配备一个clone方法，且该方法位于类的内部，修改时违背开闭原则；

### 适用

- 当创建新的对象实例较为复杂时，原型模式可以简化创建过程；