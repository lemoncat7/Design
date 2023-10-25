/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-25 09:57:49
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-25 11:17:31
 */

#include "Template.hpp"

int main() {
  Reimbursement* r1 = new DepartmentReimbursement();
  r1->process();
  Reimbursement* r2 = new FinanceDepartmentReimbursement();
  r2->process();
  return 0;
}