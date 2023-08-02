#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "identity.h"
#include "globalFile.h"
#include "computerRoom.h"

// 管理员类
class Manager : public Identity {
 public:
  // 学生容器
  std::vector<Student> vStu;
  // 教师容器
  std::vector<Teacher> vTea;
  // 机房信息
  std::vector<ComputerRoom> vCom;

  Manager();
  // 有参构造
  Manager(std::string name, std::string pwd);
  // 初始化容器
  void initVector();
  // 菜单界面
  virtual void operMenu();
  // 添加账号
  void addPerson();
  // 查看账号
  void showPerson();
  // 添加机房
  void addComputerRoom();
  // 查看机房信息
  void showComputer();
  // 清空预约
  void clearFile();
  // 检测重复参数 id
  bool checkRepeat(int id, int type);
};

Manager::Manager() {}

// 有参构造
Manager::Manager(std::string name, std::string pwd) {
  this->name = name;
  this->pwd = pwd;
  // 初始化文件 获取文件学生、教师、机房信息
  this->initVector();
}

// 初始化容器
void Manager::initVector() {
  // 清空容器
  vStu.clear();
  vTea.clear();
  vCom.clear();

  // 读取信息 - 学生
  std::ifstream ifs(SRUDENT_FILE, std::ios::in);

  if (!ifs.is_open()) {
    std::cout << "文件读取失败!" << std::endl;
    return;
  }

  Student s;
  while (ifs >> s.id && ifs >> s.name && ifs >> s.pwd) {
    vStu.push_back(s);
  }

//  std::cout << "当前学生数量为: " << vStu.size() << std::endl;
  ifs.close();

  // 读取信息 - 教师
  std::ifstream ifs2(TEACHER_FILE, std::ios::in);

  if (!ifs2.is_open()) {
    std::cout << "文件读取失败!" << std::endl;
    return;
  }

  Teacher t;
  while (ifs2 >> t.empId && ifs2 >> t.name && ifs2 >> t.pwd) {
    vTea.push_back(t);
  }

//  std::cout << "当前教师数量为: " << vTea.size() << std::endl;
  ifs2.close();

  // 读取化机房
  std::ifstream ifs3(COMPUTER_FILE, std::ios::in);

  if (!ifs3.is_open()) {
    std::cout << "文件读取失败!" << std::endl;
    return;
  }

  ComputerRoom com;
  while (ifs3 >> com.comId && ifs3 >> com.maxNum) {
    vCom.push_back(com);
  }

  ifs3.close();
}

// 菜单界面
void Manager::operMenu() {
  std::cout << "欢迎管理员: " << this->name << "登录!" << std::endl;
  std::cout << "\t|-----------------------------|" << std::endl;
  std::cout << "\t|          1. 添加账号          |" << std::endl;
  std::cout << "\t|          2. 查看账号          |" << std::endl;
  std::cout << "\t|          3. 添加机房          |" << std::endl;
  std::cout << "\t|          4. 查看机房          |" << std::endl;
  std::cout << "\t|          5. 清空预约          |" << std::endl;
  std::cout << "\t|          0. 注销预约          |" << std::endl;
  std::cout << "\t|-----------------------------|" << std::endl;
  std::cout << "请输入您的操作：" << std::endl;
}

// 添加账号
void Manager::addPerson() {
  int select = 0;
  while (true) {
    std::cout << "请选择添加账号类型" << std::endl;
    std::cout << "1.添加学生" << std::endl;
    std::cout << "2.添加教师" << std::endl;
    std::cin >> select;
    if (select == 1 || select == 2) {
      break;
    }
  }

  std::string fileName; // 操作文件名
  std::string tip; // 提示id号
  std::string errorTip; // 重复错误提示
  std::ofstream ofs; // 操作文件对象

  if (select == 1) {
    fileName = SRUDENT_FILE;
    tip = "请输入学号：";
    errorTip = "学号重复，请重新输入";
  } else {
    fileName = TEACHER_FILE;
    tip = "请输入职工号：";
    errorTip = "职工号重复，请重新输入";
  }

  // 利用追加的方式写文件
  ofs.open(fileName, std::ios::out | std::ios::app);

  int id;
  std::string name;
  std::string pwd;

  while (true) {
    std::cout << tip << std::endl;
    std::cin >> id;
    bool result = this->checkRepeat(id, select);
    if (result) {
      std::cout << errorTip << std::endl;
    } else { break; }
  }

  while (true) {
    std::cout << "请输入姓名：" << std::endl;
    std::cin >> name;
    std::cout << "请输入密码：" << std::endl;
    std::cin >> pwd;

    if (!name.empty() && !pwd.empty()) {
      break;
    }
  }

  // 向文件添加数据
  ofs << id << " " << name << " " << pwd << " " << std::endl;
  std::cout << "添加成功!" << std::endl;
  system("pause");

  ofs.close();

  // 调用接口，重新初始化
  this->initVector();
}

void printStudent(Student &s) {
  std::cout << "学号：" << s.id << " 姓名：" << s.name << " 密码：" << s.pwd << std::endl;
}
void printTeacher(Teacher &t) {
  std::cout << "职工号：" << t.empId << " 姓名：" << t.name << " 密码：" << t.pwd << std::endl;
}
// 查看账号
void Manager::showPerson() {
  std::cout << "请选择查看内容：" << std::endl;
  std::cout << "1.查看所有学生" << std::endl;
  std::cout << "2.查看所有教师" << std::endl;

  int select = 0;
  std::cin >> select;

  if (select == 1) {
    std::cout << "所有学生信息如下：" << std::endl;
    std::for_each(vStu.begin(), vStu.end(), printStudent);
  } else {
    std::cout << "所有教师信息如下：" << std::endl;
    std::for_each(vTea.begin(), vTea.end(), printTeacher);
  }
  std::cout << std::endl;
}

// 添加机房
void Manager::addComputerRoom() {
  std::ofstream ofs(COMPUTER_FILE, std::ios::out | std::ios::app);

  if (!ofs.is_open()) {
    std::cout << "文件打开失败!" << std::endl;
    ofs.close();
    return;
  }
  int id;
  int num;

  while (true) {
    std::cout << "请输入机房号：" << std::endl;
    std::cin >> id;
    bool result = this->checkRepeat(id, 3);
    if (result) {
      std::cout << "该机房号已存在!" << std::endl;
    } else { break; }
  }

  std::cout << "请输入机房最大容量：" << std::endl;
  std::cin >> num;
  num = num > 0 ? num : 0;

  // 向文件添加数据
  ofs << id << " " << num << " " << std::endl;
  std::cout << "添加成功!" << std::endl;
  system("pause");

  ofs.close();

  // 调用接口，重新初始化
  this->initVector();
}

// 查看机房信息
void Manager::showComputer() {
  std::cout << "机房信息如下：" << std::endl;
  for (auto it : vCom) {
    std::cout << "机房编号：" << it.comId << " 机房最大容量：" << it.maxNum << std::endl;
  }
  std::cout << std::endl;
  system("pause");
}

// 清空预约
void Manager::clearFile() {
  std::cout << "是否清空预约：" << std::endl;
  std::cout << "1.是" << std::endl;
  std::cout << "2.否" << std::endl;

  int select = 0;
  std::cin >> select;
  if (select == 1) {
    std::ofstream ofs(ORDER_FILE, std::ios::trunc);
    ofs.close();
    std::cout << "清空成功!" << std::endl;
  }
  system("pause");
}

// 检测重复参数 id
bool Manager::checkRepeat(int id, int type) {
  if (type == 1) {
    // 检测学生
    for (auto it : vStu) {
      if (id == it.id) {
        return true;
      }
    }
  } else if (type == 2) {
    // 检测教师
    for (auto it : vTea) {
      if (id == it.empId) {
        return true;
      }
    }
  } else if (type == 3) {
    // 检测机房
    for (auto it : vCom) {
      if (id == it.comId) {
        return true;
      }
    }
  }

  return false;
}