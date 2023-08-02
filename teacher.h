#pragma once
#include <iostream>
#include "identity.h"

// 教师类
class Teacher : public Identity {
 public:
  int empId; // 职工号

  Teacher();
  // 有参构造
  Teacher(int empId, std::string name, std::string pwd);
  // 菜单界面
  virtual void operMenu();
  // 查看所有预约
  void showAllOrders();
  // 审核预约
  void vailOrder();
};

Teacher::Teacher() {}

// 有参构造
Teacher::Teacher(int empId, std::string name, std::string pwd) {
  this->empId = empId;
  this->name = name;
  this->pwd = pwd;
}

// 菜单界面
void Teacher::operMenu() {
  std::cout << "欢迎教师: " << this->name << "登录!" << std::endl;
  std::cout << "\t|-----------------------------|" << std::endl;
  std::cout << "\t|          1. 查看所有预约      |" << std::endl;
  std::cout << "\t|          2. 审核预约          |" << std::endl;
  std::cout << "\t|          0. 注销登录          |" << std::endl;
  std::cout << "\t|-----------------------------|" << std::endl;
  std::cout << "请输入您的操作：" << std::endl;
}

// 查看所有预约
void Teacher::showAllOrders() {
  OrderFile order_file;
  if (order_file.o_size == 0) {
    std::cout << "暂无预约!" << std::endl;
    system("pause");
    return;
  }

  for (int i = 0; i < order_file.o_size; ++i) {
    std::cout << i + 1 << "、 ";
    std::cout << "预约日期：周" << order_file.orderData[i]["date"];
    std::cout << "  时间段：" << (order_file.orderData[i]["interval"] == "1" ? "上午" : "下午");
    std::cout << "  学号：" << order_file.orderData[i]["stuId"];
    std::cout << "  姓名：" << order_file.orderData[i]["stuName"];
    std::cout << "  机房编号：" << order_file.orderData[i]["roomId"];
    std::string status = "  状态："; // 1. 审核中  2. 已预约  -1. 预约失败  0. 取消预约
    if (order_file.orderData[i]["status"] == "1") {
      status += "审核中";
    } else if (order_file.orderData[i]["status"] == "2") {
      status += "已预约";
    } else if (order_file.orderData[i]["status"] == "-1") {
      status += "预约失败，审核未通过";
    } else if (order_file.orderData[i]["status"] == "0") {
      status += "预约已取消";
    }
    std::cout << status << std::endl;
  }

  system("pause");
}

// 审核预约
void Teacher::vailOrder() {
  OrderFile order_file;
  if (order_file.o_size == 0) {
    std::cout << "暂无预约!" << std::endl;
    system("pause");
    return;
  }

  std::cout << "待审核预约的记录如下：" << std::endl;

  std::vector<int> v;
  int index = 1;
  for (int i = 0; i < order_file.o_size; ++i) {
    // 先判断是否自身学号
    if (order_file.orderData[i]["status"] == "1") {
      v.push_back(i);
      std::cout << index++ << "、";
      std::cout << "预约日期：周" << order_file.orderData[i]["date"];
      std::cout << "  时间段：" << (order_file.orderData[i]["interval"] == "1" ? "上午" : "下午");
      std::cout << "  学号：" << order_file.orderData[i]["stuId"];
      std::cout << "  姓名：" << order_file.orderData[i]["stuName"];
      std::cout << "  机房编号：" << order_file.orderData[i]["roomId"];
      std::string status = "  状态：审核中";
      std::cout << status << std::endl;
    }
  }

  int select = 0; // 接收用户选择的预约记录
  int result = 0; // 接受预约结果记录
  while (true) {
    std::cout << "请输入审核的记录，0 - 返回" << std::endl;
    std::cin >> select;

    if (select >= 0 && select <= v.size()) {
      if (select != 0) {
        std::cout << "请输入审核结果：" << std::endl;
        std::cout << "1. 通过" << std::endl;
        std::cout << "2. 不通过" << std::endl;
        std::cin >> result;

        if (result == 1) {
          order_file.orderData[v[select - 1]]["status"] = "2";
        } else {
          order_file.orderData[v[select - 1]]["status"] = "-1";
        }
        order_file.updateOrder(); // 更新预约记录
        std::cout << "审核完毕" << std::endl;
      }
      break;
    }
    std::cout << "输入有误!" << std::endl;
  }

  system("pause");
}
