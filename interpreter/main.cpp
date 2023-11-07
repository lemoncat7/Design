/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-11-07 10:45:12
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-11-07 11:17:30
 */
#include "Interpreter.hpp"


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