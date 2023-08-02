#pragma once
#include <iostream>
#include "identity.h"

// ��ʦ��
class Teacher : public Identity {
 public:
  int empId; // ְ����

  Teacher();
  // �вι���
  Teacher(int empId, std::string name, std::string pwd);
  // �˵�����
  virtual void operMenu();
  // �鿴����ԤԼ
  void showAllOrders();
  // ���ԤԼ
  void vailOrder();
};

Teacher::Teacher() {}

// �вι���
Teacher::Teacher(int empId, std::string name, std::string pwd) {
  this->empId = empId;
  this->name = name;
  this->pwd = pwd;
}

// �˵�����
void Teacher::operMenu() {
  std::cout << "��ӭ��ʦ: " << this->name << "��¼!" << std::endl;
  std::cout << "\t|-----------------------------|" << std::endl;
  std::cout << "\t|          1. �鿴����ԤԼ      |" << std::endl;
  std::cout << "\t|          2. ���ԤԼ          |" << std::endl;
  std::cout << "\t|          0. ע����¼          |" << std::endl;
  std::cout << "\t|-----------------------------|" << std::endl;
  std::cout << "���������Ĳ�����" << std::endl;
}

// �鿴����ԤԼ
void Teacher::showAllOrders() {
  OrderFile order_file;
  if (order_file.o_size == 0) {
    std::cout << "����ԤԼ!" << std::endl;
    system("pause");
    return;
  }

  for (int i = 0; i < order_file.o_size; ++i) {
    std::cout << i + 1 << "�� ";
    std::cout << "ԤԼ���ڣ���" << order_file.orderData[i]["date"];
    std::cout << "  ʱ��Σ�" << (order_file.orderData[i]["interval"] == "1" ? "����" : "����");
    std::cout << "  ѧ�ţ�" << order_file.orderData[i]["stuId"];
    std::cout << "  ������" << order_file.orderData[i]["stuName"];
    std::cout << "  ������ţ�" << order_file.orderData[i]["roomId"];
    std::string status = "  ״̬��"; // 1. �����  2. ��ԤԼ  -1. ԤԼʧ��  0. ȡ��ԤԼ
    if (order_file.orderData[i]["status"] == "1") {
      status += "�����";
    } else if (order_file.orderData[i]["status"] == "2") {
      status += "��ԤԼ";
    } else if (order_file.orderData[i]["status"] == "-1") {
      status += "ԤԼʧ�ܣ����δͨ��";
    } else if (order_file.orderData[i]["status"] == "0") {
      status += "ԤԼ��ȡ��";
    }
    std::cout << status << std::endl;
  }

  system("pause");
}

// ���ԤԼ
void Teacher::vailOrder() {
  OrderFile order_file;
  if (order_file.o_size == 0) {
    std::cout << "����ԤԼ!" << std::endl;
    system("pause");
    return;
  }

  std::cout << "�����ԤԼ�ļ�¼���£�" << std::endl;

  std::vector<int> v;
  int index = 1;
  for (int i = 0; i < order_file.o_size; ++i) {
    // ���ж��Ƿ�����ѧ��
    if (order_file.orderData[i]["status"] == "1") {
      v.push_back(i);
      std::cout << index++ << "��";
      std::cout << "ԤԼ���ڣ���" << order_file.orderData[i]["date"];
      std::cout << "  ʱ��Σ�" << (order_file.orderData[i]["interval"] == "1" ? "����" : "����");
      std::cout << "  ѧ�ţ�" << order_file.orderData[i]["stuId"];
      std::cout << "  ������" << order_file.orderData[i]["stuName"];
      std::cout << "  ������ţ�" << order_file.orderData[i]["roomId"];
      std::string status = "  ״̬�������";
      std::cout << status << std::endl;
    }
  }

  int select = 0; // �����û�ѡ���ԤԼ��¼
  int result = 0; // ����ԤԼ�����¼
  while (true) {
    std::cout << "��������˵ļ�¼��0 - ����" << std::endl;
    std::cin >> select;

    if (select >= 0 && select <= v.size()) {
      if (select != 0) {
        std::cout << "��������˽����" << std::endl;
        std::cout << "1. ͨ��" << std::endl;
        std::cout << "2. ��ͨ��" << std::endl;
        std::cin >> result;

        if (result == 1) {
          order_file.orderData[v[select - 1]]["status"] = "2";
        } else {
          order_file.orderData[v[select - 1]]["status"] = "-1";
        }
        order_file.updateOrder(); // ����ԤԼ��¼
        std::cout << "������" << std::endl;
      }
      break;
    }
    std::cout << "��������!" << std::endl;
  }

  system("pause");
}
