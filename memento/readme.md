<!--
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-11-02 10:14:26
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-11-02 10:14:27
-->
# 备忘录模式

备忘录模式。这个模式理解、掌握起来不难，代码实现比较灵活，应用场景也比较明确和有限，主要是用来防丢失、撤销、恢复等。

## 介绍

备忘录模式(Memento Pattern)是一种软件设计模式,它提供了一种捕获对象内部状态的方法,并在需要时外部化该状态,以便可以恢复到之前的状态。

这个模式涉及到三个角色:

发起人(Originator):要被保存状态的对象。它可以创建一个备忘录,用来记录当前时刻的内部状态,并可使用备忘录恢复到之前保存的状态。

备忘录(Memento):存储发起人对象的内部状态的类。备忘录的交互限定在发起人与管理者之间。

管理者(Caretaker):负责保存备忘录的对象。不检查备忘录内容,仅负责存储和提供备忘录。

主要步骤如下:

1. 发起人在需要保存状态时,创建一个备忘录对象,将需要保存的信息导入,并将备忘录对象传递给管理者进行保存。
2. 当需要恢复到之前保存的状态时,管理者返回相应的备忘录对象给发起人。
3. 发起人使用备忘录对象记录的状态信息,恢复到之前保存的状态。

这样可以在不违反封装的情况下,实现对象状态的保存和恢复。备忘录模式提供了一种状态恢复的灵活机制,可以使用多条生命线的对象状态进行恢复。

## 定义

假设有一个文本编辑器软件,它允许用户进行文本编辑,同时也包含了撤销操作功能,可以让用户撤销之前的编辑操作,恢复到之前的内容状态

所以完整的需求是:

1. 当用户编辑文本时,文本内容会随之改变。
2. 文本内容需要在特定时间点(比如用户保存时)创建一个备忘录,存储当前的文本状态。
3. 用户可以请求撤销操作。
4. 撤销管理器提供之前创建的备忘录给文本内容。
5. 文本内容使用备忘录中的状态进行恢复。
6. 这样就实现了撤销操作,可以回退到之前保存的文本状态。

编辑器

```cpp
// 编辑器
class TextEdit {
  std::string text_;
 public:
  void AddText(const std::string &text);
  const std::string& GetText();
  std::shared_ptr<TextMemento> CreateMemento() ;
  void RestoreMemento(std::shared_ptr<TextMemento> memento) ;
};

// 编辑器
void TextEdit::AddText(const std::string &text) { text_ += text; }
const std::string &TextEdit::GetText() { return text_; }
std::shared_ptr<TextMemento> TextEdit::CreateMemento() {
  return std::make_shared<TextMemento>(*this);
}
void TextEdit::RestoreMemento(std::shared_ptr<TextMemento> memento) {
  text_ = memento->GetText();
}
```

备忘录

```cpp
// 备忘录(快照)
class TextMemento {
  std::string text_;
 public:
  TextMemento(TextEdit &textEdit);
  std::string GetText() ;
};

// 备忘录(快照)

TextMemento::TextMemento(TextEdit &textEdit) { text_ = textEdit.GetText(); }
std::string TextMemento::GetText() { return text_; }
```

管理

```cpp
// 快照管理
class MementoManager {
  std::vector<std::shared_ptr<TextMemento>> memento_list_;
public:
  void AddMemento(std::shared_ptr<TextMemento> memento) ;
  std::shared_ptr<TextMemento> GetLastMemento() ;
  void Undo() ;
};

// 快照管理

void MementoManager::AddMemento(std::shared_ptr<TextMemento> memento) {
  memento_list_.push_back(memento);
}
std::shared_ptr<TextMemento> MementoManager::GetLastMemento() {
  // if (memento_list_.empty()) return std::make_shared<TextMemento>(TextEdit());
  auto mem = memento_list_.back();
  Undo();
  return mem;
}
void MementoManager::Undo() { memento_list_.pop_back(); }
```

## 调用

```cpp
int main() {
  TextEdit edit; 
  MementoManager mgr;
  edit.AddText("Hello World!");
  mgr.AddMemento(edit.CreateMemento());
  edit.AddText("bro !?");
  mgr.AddMemento(edit.CreateMemento());
  edit.AddText("I'm fine, thanks!");
  mgr.AddMemento(edit.CreateMemento());
  std::cout << edit.GetText() << std::endl;
  edit.RestoreMemento(mgr.GetLastMemento());
  std::cout << edit.GetText() << std::endl;
  edit.RestoreMemento(mgr.GetLastMemento());
  std::cout << edit.GetText() << std::endl;
  edit.RestoreMemento(mgr.GetLastMemento());
  std::cout << edit.GetText() << std::endl;
  return 0;
}
```

## 效果

```cpp
./bin/design/memento 
Hello World!bro !?I'm fine, thanks!
Hello World!bro !?I'm fine, thanks!
Hello World!bro !?
Hello World!
```

## 回顾

备忘录模式也叫快照模式，具体来说，就是在不违背封装原则的前提下，捕获一个对象的内部状态，并在该对象之外保存这个状态，以便之后恢复对象为先前的状态。这个模式的定义表达了两部分内容：一部分是，存储副本以便后期恢复；另一部分是，要在不违背封装原则的前提下，进行对象的备份和恢复。

备忘录模式的应用场景也比较明确和有限，主要是用来防丢失、撤销、恢复等。它跟平时我们常说的“备份”很相似。两者的主要区别在于，备忘录模式更侧重于代码的设计和实现，备份更侧重架构设计或产品设计。

对于大对象的备份来说，备份占用的存储空间会比较大，备份和恢复的耗时会比较长。针对这个问题，不同的业务场景有不同的处理方式。比如，只备份必要的恢复信息，结合最新的数据来恢复；再比如，全量备份和增量备份相结合，低频全量备份，高频增量备份，两者结合来做恢复。

## 扩展

如果要备份的对象数据比较大，备份频率又比较高，那快照占用的内存会比较大，备份和恢复的耗时会比较长。这个问题该如何解决呢？

用上面这个例子, 可以通过只记录每次改变的长度, 而不是完整的信息

我们再举一个例子。假设每当有数据改动，我们都需要生成一个备份，以备之后恢复。如果需要备份的数据很大，这样高频率的备份，不管是对存储（内存或者硬盘）的消耗，还是对时间的消耗，都可能是无法接受的。想要解决这个问题，我们一般会采用“低频率全量备份”和“高频率增量备份”相结合的方法。

全量备份就不用讲了，它跟我们上面的例子类似，就是把所有的数据“拍个快照”保存下来。所谓“增量备份”，指的是记录每次操作或数据变动。

当我们需要恢复到某一时间点的备份的时候，如果这一时间点有做全量备份，我们直接拿来恢复就可以了。如果这一时间点没有对应的全量备份，我们就先找到最近的一次全量备份，然后用它来恢复，之后执行此次全量备份跟这一时间点之间的所有增量备份，也就是对应的操作或者数据变动。这样就能减少全量备份的数量和频率，减少对时间、内存的消耗。