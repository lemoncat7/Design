<!--
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-11-07 11:23:10
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-11-07 11:23:11
-->
# 解释器模式

## 介绍

解释器模式(Interpreter Pattern)是一种行为型设计模式,它能够对语言中的语法或表达式进行解释,并定义语言的文法表示。

它的主要作用是:

- 定义语言的文法表示
- 解释该语言中的句子

在解释器模式中,通常包含以下主要角色:

- AbstractExpression(抽象表达式):声明解释器的接口,为所有的终结符声明一个解释操作。
- TerminalExpression(终结符表达式):实现与文法中的每个终结符相关的解释操作。
- NonterminalExpression(非终结符表达式):为文法中的每一条规则实现解释操作。
- Context(上下文):包含解释器之外的一些全局信息。
- Client(客户):构建表示文法所需的抽象语法树,并调用解释操作。

客户可以根据需要引入不同的规则,使用解释器模式可以避免对语法的编码。解释器模式常用于SQL解析、符号处理引擎等需要对表达式语法进行解释的场景。

比如抽象语法树、编译器、表达式计算等都大量运用了解释器模式,它是实现多种复杂语法解析的简洁高效方式。

## 定义

我们需要开发一个简单的表达式计算程序,支持加减乘除四种算术运算,以及括号内的优先运算。

需求如下:

1. 程序需要解析输入的算术表达式字符串,识别其中的数字、运算符、括号等组成部分
2. 表达式中允许使用的运算符为:+ - * / ,对应的优先级依次降低
3. 括号内表达式需要优先计算,遵循合理的括号匹配规则
4. 需要正确解析表达式,构建抽象语法树(Abstract Syntax Tree, AST)
5. 程序根据构建的AST计算表达式的值,并输出结果
6. 需要能够处理错误情况,如非法表达式、缺少操作数等,并给出提示信息
7. 需要提供简单的API或接口,外部程序可以通过该接口传入表达式并获取计算结果

以上是该表达式解释器和计算程序的主要需求。用户输入算术表达式字符串,程序内部需要解析表达式语法,转换为抽象语法树,然后进行运算求值,最后返回结果。需要能够正确处理运算符优先级和括号,并解析报错情况。

AST 节点定义

```cpp
// Token types
enum TokenType {
  NUMBER,
  OP_ADD, 
  OP_SUB,
  OP_MUL,
  OP_DIV,
  LPAREN,
  RPAREN
};
// Token struct
struct Token {
  TokenType type;
  string value;
};
// Expression AST node
struct ASTNode {
  TokenType op;
  double num;
  ASTNode* left;
  ASTNode* right;
  ASTNode(TokenType op, double num) : op(op), num(num), left(nullptr), right(nullptr) {}
  ASTNode(TokenType op, ASTNode* left, ASTNode* right) : op(op), left(left), right(right) {}
};
```

解析表达式 生成toke

```cpp
// Parse input expression into tokens
vector<Token> tokenize(const string& input) {

  vector<Token> result;
  stack<char> op_stack;
  
  for(int i = 0; i < input.size(); i++) {

    char c = input[i];

    // 处理数字
    if(isdigit(c)) {
      double num = 0;
      while(i < input.size() && isdigit(input[i])) {
        num = num * 10 + (input[i] - '0');
        i++;
      }
      i--;
      // 添加数字token
      result.push_back({NUMBER, to_string(num)});
      // 将op_stack中的所有运算符弹出生成token  
      while(!op_stack.empty()) {
        char op = op_stack.top();
        op_stack.pop();
        
        if(op == '+') {
          result.push_back({OP_ADD, "+"});
        } else if(op == '-') {
          result.push_back({OP_SUB, "-"}); 
        } else if(op == '*') {
          result.push_back({OP_MUL, "*"});
        } else if(op == '/') {
          result.push_back({OP_DIV, "/"});
        }
      }
    }
    
    // 处理加减乘除运算符
    else if(c == '+' || c == '-' || c == '*' || c == '/') {
      op_stack.push(c);
    }

    // 遇到左括号清空运算符栈
    else if(c == '(') {
      op_stack = stack<char>();
    }

    // 右括号将栈内所有运算符弹出生成token
    else if(c == ')') {
      while(!op_stack.empty()) {
        char op = op_stack.top();
        op_stack.pop();
        if(op == '+') {
          result.push_back({OP_ADD, "+"});
        } else if(op == '-') {
          result.push_back({OP_SUB, "-"});
        } else if(op == '*') {
          result.push_back({OP_MUL, "*"});
        } else if(op == '/') {
          result.push_back({OP_DIV, "/"}); 
        }
      }
    }
  }
  return result;
}
// Build
```

根据token 生产 AST

```cpp
// Build AST from tokens
ASTNode* buildAST(const vector<Token>& tokens) {
  stack<ASTNode*> s;
  for (auto t : tokens) {
    if (t.type == NUMBER) {
      s.push(new ASTNode(t.type, stod(t.value))); 
    } else if (t.type == OP_ADD || t.type == OP_SUB ||
               t.type == OP_MUL || t.type == OP_DIV) {
      ASTNode* right = s.top(); s.pop();
      ASTNode* left = s.top(); s.pop();
      s.push(new ASTNode(t.type, left, right));
    } else if (t.type == RPAREN) {
      ASTNode* node = s.top(); s.pop();
      while (s.top()->op != LPAREN) {
        ASTNode* left = s.top(); s.pop();
        node = new ASTNode(s.top()->op, left, node);
        s.pop(); 
      }
      s.pop(); // Pop LPAREN
      s.push(node);
    } else {
      s.push(new ASTNode(t.type, 0)); // LPAREN
    }
  }
  return s.top();
}
```

计算节点

```cpp
// Evaluate the AST
double eval(ASTNode* node) {
  if (node->op == NUMBER) return node->num;
  if (node->op == OP_ADD) return eval(node->left) + eval(node->right);
  if (node->op == OP_SUB) return eval(node->left) - eval(node->right);
  if (node->op == OP_MUL) return eval(node->left) * eval(node->right);
  if (node->op == OP_DIV) return eval(node->left) / eval(node->right);
  return 0; // Won't reach here
}
```

## 调用

```cpp
int main() {
  string input;
  cout << "Enter an expression: ";
  // input = "1 + 1";
  getline(cin, input);
  vector<Token> tokens = tokenize(input);
  ASTNode* ast = buildAST(tokens);
  double result = eval(ast);
  cout << "Result: " << result << endl;
  return 0;
}
```

## 效果

```cpp
./bin/design/interpreter
Enter an expression: 1+1
Result: 2
./bin/design/interpreter
Enter an expression: 1+1/2
Result: 1
./bin/design/interpreter
Enter an expression: 1+(1/2)
Result: 0.5
```

## 回顾

解释器模式为某个语言定义它的语法（或者叫文法）表示，并定义一个解释器用来处理这个语法。实际上，这里的“语言”不仅仅指我们平时说的中、英、日、法等各种语言。从广义上来讲，只要是能承载信息的载体，我们都可以称之为“语言”，比如，古代的结绳记事、盲文、哑语、摩斯密码等。

要想了解“语言”要表达的信息，我们就必须定义相应的语法规则。这样，书写者就可以根据语法规则来书写“句子”（专业点的叫法应该是“表达式”），阅读者根据语法规则来阅读“句子”，这样才能做到信息的正确传递。而我们要讲的解释器模式，其实就是用来实现根据语法规则解读“句子”的解释器。