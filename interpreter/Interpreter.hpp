/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-11-07 10:45:08
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-11-07 11:17:04
 */
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
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
// Evaluate the AST
double eval(ASTNode* node) {
  if (node->op == NUMBER) return node->num;
  if (node->op == OP_ADD) return eval(node->left) + eval(node->right);
  if (node->op == OP_SUB) return eval(node->left) - eval(node->right);
  if (node->op == OP_MUL) return eval(node->left) * eval(node->right);
  if (node->op == OP_DIV) return eval(node->left) / eval(node->right);
  return 0; // Won't reach here
}