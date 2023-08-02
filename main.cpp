#include <iostream>
#include <fstream>
#include "globalFile.h"
#include "identity.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"

// 进入教师子菜单界面
void teacherMenu(Identity *&teacher) {
  while (true) {
    // 调用教师子菜单
    teacher->operMenu();

    Teacher *tea = (Teacher *) teacher;

    int select = 0;
    std::cin >> select;

    if (select == 1) {   // 查看所有预约
      tea->showAllOrders();
    } else if (select == 2) {   // 审核预约
      tea->vailOrder();
    } else { // 注销登录
      delete tea;
      std::cout << "注销登录" << std::endl;
      system("pause");
      return;
    }
  }
}

// 进入学生子菜单界面
void studentMenu(Identity *&student) {
  while (true) {
    // 调用学生子菜单
    student->operMenu();

    Student *stu = (Student *) student;

    int select = 0;
    std::cin >> select;

    if (select == 1) { // 申请预约
      stu->applyOrder();
    } else if (select == 2) { // 查看自身预约
      stu->showSelfOrder();
    } else if (select == 3) { // 查看所有人预约
      stu->showAllOrders();
    } else if (select == 4) { // 取消预约
      stu->cancelOrder();
    } else {// 注销登录
      delete stu;
      std::cout << "注销登录" << std::endl;
      system("pause");
      return;
    }
  }
}

// 进入管理员子菜单界面
void managerMenu(Identity *manager) {
  while (true) {
    // 调用管理员子菜单
    manager->operMenu();

    // 将父类指针转为子类指针，调用子类里其他接口
    Manager *man = (Manager *) manager;

    int select = 0;
    std::cin >> select;

    if (select == 1) { // 添加账号
      std::cout << "添加账号" << std::endl;
      man->addPerson();
    } else if (select == 2) { // 查看账号
      std::cout << "查看账号" << std::endl;
      man->showPerson();
    } else if (select == 3) { // 查看机房
      std::cout << "添加机房" << std::endl;
      man->addComputerRoom();
    } else if (select == 4) { // 查看机房
      std::cout << "查看机房" << std::endl;
      man->showComputer();
    } else if (select == 5) { // 清空预约
      std::cout << "清空预约" << std::endl;
      man->clearFile();
    } else {
      // 注销堆区对象
      delete manager;
      std::cout << "注销成功" << std::endl;
      return;
    }
  }
}

/**
 * 登录功能
 * @param fileName 操作文件名
 * @param type 操作身份类型
 */
void loginIn(std::string fileName, int type) {
  // 父类指针，用于指向子类对象
  Identity *person = nullptr;

  // 读文件
  std::ifstream ifs(fileName, std::ios::in);

  if (!ifs.is_open()) {
    std::cout << "文件不存在" << std::endl;
    ifs.close();
    return;
  }

  // 接受用户信息
  int id = 0;
  std::string name;
  std::string pwd;

  // 判断身份
  if (type == 1) { // 学生身份
    std::cout << "请输入您的学号：" << std::endl;
    std::cin >> id;

  } else if (type == 2) { // 教师身份
    std::cout << "请输入您的职工号：" << std::endl;
    std::cin >> id;
  }

  std::cout << "请输入用户名：" << std::endl;
  std::cin >> name;
  std::cout << "请输入密码：" << std::endl;
  std::cin >> pwd;

  if (type == 1) { // 学生身份验证
    // 从文件读取的信息
    int fId;
    std::string fName;
    std::string fPwd;
    while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
      if (fId == id && fName == name && fPwd == pwd) {
        std::cout << "学生验证登录成功!" << std::endl;
        system("pause");
        person = new Student(id, name, pwd);
        // 进入学生身份的子菜单
        studentMenu(person);
        return;
      }
    }
  } else if (type == 2) { // 教师身份验证
    // 从文件读取的信息
    int fId;
    std::string fName;
    std::string fPwd;
    while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
      if (fId == id && fName == name && fPwd == pwd) {
        std::cout << "教师验证登录成功!" << std::endl;
        system("pause");
        person = new Teacher(id, name, pwd);
        // 进入教师身份的子菜单
        teacherMenu(person);
        return;
      }
    }
  } else if (type == 3) { // 管理员身份验证
    // 从文件读取的信息
    std::string fName;
    std::string fPwd;
    while (ifs >> fName && ifs >> fPwd) {
      if (fName == name && fPwd == pwd) {
        std::cout << "管理员验证登录成功!" << std::endl;
        system("pause");
        person = new Manager(name, pwd);
        // 进入管理员身份的子菜单
        managerMenu(person);
        return;
      }
    }
  }

  std::cout << "登录失败" << std::endl;
  std::system("pause");
}

int main() {
  int select = 0; // 用户选择
  while (true) {
    std::cout << "================ 欢迎来到机房预约系统 =============" << std::endl;
    std::cout << "\t|-----------------------------|" << std::endl;
    std::cout << "\t|          1. 学生代表          |" << std::endl;
    std::cout << "\t|          2. 老   师          |" << std::endl;
    std::cout << "\t|          3. 管 理 员         |" << std::endl;
    std::cout << "\t|          0. 退   出          |" << std::endl;
    std::cout << "\t|-----------------------------|" << std::endl;
    std::cout << "请输入您的身份：" << std::endl;
    std::cin >> select;

    switch (select) {
      case 1: // 学生身份
        loginIn(SRUDENT_FILE, 1);
        break;
      case 2: // 老师身份
        loginIn(TEACHER_FILE, 2);
        break;
      case 3: // 管理员身份
        loginIn(ADMIN_FILE, 3);
        break;
      case 0: // 退出系统
        std::cout << "欢迎下次使用" << std::endl;
        return 0;
      default:std::cout << "输入错误，请重新选择!" << std::endl;
        std::system("pause");
        break;
    }
  }
}
