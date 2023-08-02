#pragma once
#include <iostream>
#include <vector>
#include "identity.h"
#include "computerRoom.h"
#include "orderFile.h"

// 学生类
class Student : public Identity {
 public:
  int id; // 学生学号
  std::vector<ComputerRoom> vCom; // 存放机房信息

  Student();
  // 有参构造
  Student(int id, std::string name, std::string pwd);
  // 初始化信息
  void initStudent();
  // 菜单页面
  virtual void operMenu();
  // 申请预约
  void applyOrder();
  // 查看自身预约
  void showSelfOrder();
  // 查看所有预约
  void showAllOrders();
  // 取消预约
  void cancelOrder();
};

Student::Student() {}

// 有参构造
Student::Student(int id, std::string name, std::string pwd) {
  this->id = id;
  this->name = name;
  this->pwd = pwd;

  // 初始化
  this->initStudent();
}

// 初始化信息
void Student::initStudent() {
  std::ifstream ifs(COMPUTER_FILE, std::ios::in);

  ComputerRoom com;
  while (ifs >> com.comId && ifs >> com.maxNum) {
    // 将读取信息放入到容器中
    vCom.push_back(com);
  }

  ifs.close();
}

// 菜单页面
void Student::operMenu() {
  std::cout << "欢迎学生: " << this->name << "登录!" << std::endl;
  std::cout << "\t|-----------------------------|" << std::endl;
  std::cout << "\t|          1. 申请预约          |" << std::endl;
  std::cout << "\t|          2. 查看自身预约       |" << std::endl;
  std::cout << "\t|          3. 查看所有预约       |" << std::endl;
  std::cout << "\t|          4. 取消预约          |" << std::endl;
  std::cout << "\t|          0. 注销登录          |" << std::endl;
  std::cout << "\t|-----------------------------|" << std::endl;
  std::cout << "请输入您的操作：" << std::endl;
}

// 申请预约
void Student::applyOrder() {
  std::cout << "机房开放时间为周一至周五!" << std::endl;
  std::cout << "请选择申请预约时间：" << std::endl;
  std::cout << "1. 周一" << std::endl;
  std::cout << "2. 周二" << std::endl;
  std::cout << "3. 周三" << std::endl;
  std::cout << "4. 周四" << std::endl;
  std::cout << "5. 周五" << std::endl;

  int date = 0; // 日期
  int interval = 0; // 时间段
  int room = 0; // 机房编号

  while (true) {
    std::cin >> date;
    if (date >= 1 && date <= 5) {
      break;
    }
    std::cout << "输入有误，请重新选择..." << std::endl;
  }

  std::cout << "请选择申请预约时间段：" << std::endl;
  std::cout << "1. 上午" << std::endl;
  std::cout << "2. 下午" << std::endl;
  while (true) {
    std::cin >> interval;
    if (interval == 1 || interval == 2) {
      break;
    }
    std::cout << "输入有误，请重新选择..." << std::endl;
  }

  std::cout << "请选择机房：" << std::endl;
  for (auto it : vCom) {
    std::cout << it.comId << "号机房容量为：" << it.maxNum << std::endl;
  }

  while (true) {
    std::cin >> room;
    // 改进
    if (room >= 1 && room <= this->vCom.size()) {
      break;
    }
    std::cout << "输入有误，请重新选择..." << std::endl;
  }

  std::cout << "预约成功!审核中..." << std::endl;

  // 写入数据
  std::ofstream ofs(ORDER_FILE, std::ios::app);
  if (!ofs.is_open()) {
    std::cout << "文件打开失败!" << std::endl;
    ofs.close();
    return;
  }

  ofs << "date:" << date << " ";
  ofs << "interval:" << interval << " ";
  ofs << "stuId:" << this->id << " ";
  ofs << "stuName:" << this->name << " ";
  ofs << "roomId:" << room << " ";
  ofs << "status:" << 1 << std::endl;

  ofs.close();
  system("pause");
}

// 查看自身预约
void Student::showSelfOrder() {
  OrderFile order_file;
  if (order_file.o_size == 0) {
    std::cout << "无预约记录!" << std::endl;
    system("pause");
    return;
  }

  for (int i = 0; i < order_file.o_size; ++i) {
    // 如何 string -> int
    // string 利用 .c_str() 转 const char *
    // 利用 atoi(const char *) 转 int
    if (this->id == atoi(order_file.orderData[i]["stuId"].c_str())) {
      // 找到自身预约
      std::cout << "预约日期：周" << order_file.orderData[i]["date"];
      std::cout << "  时间段：" << (order_file.orderData[i]["interval"] == "1" ? "上午" : "下午");
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
  }

  system("pause");
}

// 查看所有预约
void Student::showAllOrders() {
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

// 取消预约
void Student::cancelOrder() {
  OrderFile order_file;
  if (order_file.o_size == 0) {
    std::cout << "暂无预约!" << std::endl;
    system("pause");
    return;
  }

  std::cout << "审核中或预约成功的记录可以取消，请输入取消的记录：" << std::endl;

  std::vector<int> v; // 存放在最大容器中的下标编号
  int index = 1;
  for (int i = 0; i < order_file.o_size; ++i) {
    // 先判断是否自身学号
    if (this->id == (atoi(order_file.orderData[i]["stuId"].c_str()))) {
      // 在筛选状态， 审核中或预约成功的记录
      if (order_file.orderData[i]["status"] == "1" || order_file.orderData[i]["status"] == "2") {
        v.push_back(i);
        std::cout << index++ << "、";
        std::cout << "预约日期：周" << order_file.orderData[i]["date"];
        std::cout << "  时间段：" << (order_file.orderData[i]["interval"] == "1" ? "上午" : "下午");
        std::cout << "  机房编号：" << order_file.orderData[i]["roomId"];
        std::string status = "  状态："; // 1. 审核中  2. 已预约
        if (order_file.orderData[i]["status"] == "1") {
          status += "审核中";
        } else if (order_file.orderData[i]["status"] == "2") {
          status += "预约成功";
        }
        std::cout << status << std::endl;
      }
    }
  }

  int select = 0;
  while (true) {
    std::cout << "请输入取消的记录，0 - 返回" << std::endl;
    std::cin >> select;

    if (select >= 0 && select <= v.size()) {
      if (select != 0) {
        order_file.orderData[v[select - 1]]["status"] = "0";

        order_file.updateOrder();
        std::cout << "已取消预约" << std::endl;
      }
      break;
    }
    std::cout << "输入有误!" << std::endl;
  }

  system("pause");
}
