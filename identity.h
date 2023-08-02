#pragma once
#include <iostream>
#include <string>

// 身份抽象类
class Identity {
 public:
  std::string name; // 用户名
  std::string pwd; // 密码

  // 操作菜单 纯虚函数
  virtual void operMenu() = 0;
};