#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "identity.h"
#include "globalFile.h"
#include "computerRoom.h"

// ����Ա��
class Manager : public Identity {
 public:
  // ѧ������
  std::vector<Student> vStu;
  // ��ʦ����
  std::vector<Teacher> vTea;
  // ������Ϣ
  std::vector<ComputerRoom> vCom;

  Manager();
  // �вι���
  Manager(std::string name, std::string pwd);
  // ��ʼ������
  void initVector();
  // �˵�����
  virtual void operMenu();
  // ����˺�
  void addPerson();
  // �鿴�˺�
  void showPerson();
  // ��ӻ���
  void addComputerRoom();
  // �鿴������Ϣ
  void showComputer();
  // ���ԤԼ
  void clearFile();
  // ����ظ����� id
  bool checkRepeat(int id, int type);
};

Manager::Manager() {}

// �вι���
Manager::Manager(std::string name, std::string pwd) {
  this->name = name;
  this->pwd = pwd;
  // ��ʼ���ļ� ��ȡ�ļ�ѧ������ʦ��������Ϣ
  this->initVector();
}

// ��ʼ������
void Manager::initVector() {
  // �������
  vStu.clear();
  vTea.clear();
  vCom.clear();

  // ��ȡ��Ϣ - ѧ��
  std::ifstream ifs(SRUDENT_FILE, std::ios::in);

  if (!ifs.is_open()) {
    std::cout << "�ļ���ȡʧ��!" << std::endl;
    return;
  }

  Student s;
  while (ifs >> s.id && ifs >> s.name && ifs >> s.pwd) {
    vStu.push_back(s);
  }

//  std::cout << "��ǰѧ������Ϊ: " << vStu.size() << std::endl;
  ifs.close();

  // ��ȡ��Ϣ - ��ʦ
  std::ifstream ifs2(TEACHER_FILE, std::ios::in);

  if (!ifs2.is_open()) {
    std::cout << "�ļ���ȡʧ��!" << std::endl;
    return;
  }

  Teacher t;
  while (ifs2 >> t.empId && ifs2 >> t.name && ifs2 >> t.pwd) {
    vTea.push_back(t);
  }

//  std::cout << "��ǰ��ʦ����Ϊ: " << vTea.size() << std::endl;
  ifs2.close();

  // ��ȡ������
  std::ifstream ifs3(COMPUTER_FILE, std::ios::in);

  if (!ifs3.is_open()) {
    std::cout << "�ļ���ȡʧ��!" << std::endl;
    return;
  }

  ComputerRoom com;
  while (ifs3 >> com.comId && ifs3 >> com.maxNum) {
    vCom.push_back(com);
  }

  ifs3.close();
}

// �˵�����
void Manager::operMenu() {
  std::cout << "��ӭ����Ա: " << this->name << "��¼!" << std::endl;
  std::cout << "\t|-----------------------------|" << std::endl;
  std::cout << "\t|          1. ����˺�          |" << std::endl;
  std::cout << "\t|          2. �鿴�˺�          |" << std::endl;
  std::cout << "\t|          3. ��ӻ���          |" << std::endl;
  std::cout << "\t|          4. �鿴����          |" << std::endl;
  std::cout << "\t|          5. ���ԤԼ          |" << std::endl;
  std::cout << "\t|          0. ע��ԤԼ          |" << std::endl;
  std::cout << "\t|-----------------------------|" << std::endl;
  std::cout << "���������Ĳ�����" << std::endl;
}

// ����˺�
void Manager::addPerson() {
  int select = 0;
  while (true) {
    std::cout << "��ѡ������˺�����" << std::endl;
    std::cout << "1.���ѧ��" << std::endl;
    std::cout << "2.��ӽ�ʦ" << std::endl;
    std::cin >> select;
    if (select == 1 || select == 2) {
      break;
    }
  }

  std::string fileName; // �����ļ���
  std::string tip; // ��ʾid��
  std::string errorTip; // �ظ�������ʾ
  std::ofstream ofs; // �����ļ�����

  if (select == 1) {
    fileName = SRUDENT_FILE;
    tip = "������ѧ�ţ�";
    errorTip = "ѧ���ظ�������������";
  } else {
    fileName = TEACHER_FILE;
    tip = "������ְ���ţ�";
    errorTip = "ְ�����ظ�������������";
  }

  // ����׷�ӵķ�ʽд�ļ�
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
    std::cout << "������������" << std::endl;
    std::cin >> name;
    std::cout << "���������룺" << std::endl;
    std::cin >> pwd;

    if (!name.empty() && !pwd.empty()) {
      break;
    }
  }

  // ���ļ��������
  ofs << id << " " << name << " " << pwd << " " << std::endl;
  std::cout << "��ӳɹ�!" << std::endl;
  system("pause");

  ofs.close();

  // ���ýӿڣ����³�ʼ��
  this->initVector();
}

void printStudent(Student &s) {
  std::cout << "ѧ�ţ�" << s.id << " ������" << s.name << " ���룺" << s.pwd << std::endl;
}
void printTeacher(Teacher &t) {
  std::cout << "ְ���ţ�" << t.empId << " ������" << t.name << " ���룺" << t.pwd << std::endl;
}
// �鿴�˺�
void Manager::showPerson() {
  std::cout << "��ѡ��鿴���ݣ�" << std::endl;
  std::cout << "1.�鿴����ѧ��" << std::endl;
  std::cout << "2.�鿴���н�ʦ" << std::endl;

  int select = 0;
  std::cin >> select;

  if (select == 1) {
    std::cout << "����ѧ����Ϣ���£�" << std::endl;
    std::for_each(vStu.begin(), vStu.end(), printStudent);
  } else {
    std::cout << "���н�ʦ��Ϣ���£�" << std::endl;
    std::for_each(vTea.begin(), vTea.end(), printTeacher);
  }
  std::cout << std::endl;
}

// ��ӻ���
void Manager::addComputerRoom() {
  std::ofstream ofs(COMPUTER_FILE, std::ios::out | std::ios::app);

  if (!ofs.is_open()) {
    std::cout << "�ļ���ʧ��!" << std::endl;
    ofs.close();
    return;
  }
  int id;
  int num;

  while (true) {
    std::cout << "����������ţ�" << std::endl;
    std::cin >> id;
    bool result = this->checkRepeat(id, 3);
    if (result) {
      std::cout << "�û������Ѵ���!" << std::endl;
    } else { break; }
  }

  std::cout << "������������������" << std::endl;
  std::cin >> num;
  num = num > 0 ? num : 0;

  // ���ļ��������
  ofs << id << " " << num << " " << std::endl;
  std::cout << "��ӳɹ�!" << std::endl;
  system("pause");

  ofs.close();

  // ���ýӿڣ����³�ʼ��
  this->initVector();
}

// �鿴������Ϣ
void Manager::showComputer() {
  std::cout << "������Ϣ���£�" << std::endl;
  for (auto it : vCom) {
    std::cout << "������ţ�" << it.comId << " �������������" << it.maxNum << std::endl;
  }
  std::cout << std::endl;
  system("pause");
}

// ���ԤԼ
void Manager::clearFile() {
  std::cout << "�Ƿ����ԤԼ��" << std::endl;
  std::cout << "1.��" << std::endl;
  std::cout << "2.��" << std::endl;

  int select = 0;
  std::cin >> select;
  if (select == 1) {
    std::ofstream ofs(ORDER_FILE, std::ios::trunc);
    ofs.close();
    std::cout << "��ճɹ�!" << std::endl;
  }
  system("pause");
}

// ����ظ����� id
bool Manager::checkRepeat(int id, int type) {
  if (type == 1) {
    // ���ѧ��
    for (auto it : vStu) {
      if (id == it.id) {
        return true;
      }
    }
  } else if (type == 2) {
    // ����ʦ
    for (auto it : vTea) {
      if (id == it.empId) {
        return true;
      }
    }
  } else if (type == 3) {
    // ������
    for (auto it : vCom) {
      if (id == it.comId) {
        return true;
      }
    }
  }

  return false;
}