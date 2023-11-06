/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-11-06 09:57:18
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-11-06 10:29:41
 */
#include "Command.hpp"
#include <unistd.h> 

int main() {
  Skill* fireBall = new SpecificSkills("Fire Ball", 3);
  Skill* Flash = new SpecificSkills("Flash", 1);
  Invoker* invoker = new Invoker();
  invoker->SetCommand("fire", new SkillCommand(fireBall));
  invoker->SetCommand("flash", new SkillCommand(Flash));
  invoker->Execute("fire");
  invoker->Execute("fire");
  sleep(3);
  invoker->Execute("flash");
  invoker->Execute("fire");
  delete invoker;
  return 0;
}