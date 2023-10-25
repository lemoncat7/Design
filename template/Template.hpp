/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-25 09:57:45
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-25 11:17:20
 */
#include <iostream>
using namespace std;
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