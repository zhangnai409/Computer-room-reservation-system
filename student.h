#pragma once
#include <iostream>
#include <vector>
#include "identity.h"
#include "computerRoom.h"
#include "orderFile.h"

// ѧ����
class Student : public Identity {
 public:
  int id; // ѧ��ѧ��
  std::vector<ComputerRoom> vCom; // ��Ż�����Ϣ

  Student();
  // �вι���
  Student(int id, std::string name, std::string pwd);
  // ��ʼ����Ϣ
  void initStudent();
  // �˵�ҳ��
  virtual void operMenu();
  // ����ԤԼ
  void applyOrder();
  // �鿴����ԤԼ
  void showSelfOrder();
  // �鿴����ԤԼ
  void showAllOrders();
  // ȡ��ԤԼ
  void cancelOrder();
};

Student::Student() {}

// �вι���
Student::Student(int id, std::string name, std::string pwd) {
  this->id = id;
  this->name = name;
  this->pwd = pwd;

  // ��ʼ��
  this->initStudent();
}

// ��ʼ����Ϣ
void Student::initStudent() {
  std::ifstream ifs(COMPUTER_FILE, std::ios::in);

  ComputerRoom com;
  while (ifs >> com.comId && ifs >> com.maxNum) {
    // ����ȡ��Ϣ���뵽������
    vCom.push_back(com);
  }

  ifs.close();
}

// �˵�ҳ��
void Student::operMenu() {
  std::cout << "��ӭѧ��: " << this->name << "��¼!" << std::endl;
  std::cout << "\t|-----------------------------|" << std::endl;
  std::cout << "\t|          1. ����ԤԼ          |" << std::endl;
  std::cout << "\t|          2. �鿴����ԤԼ       |" << std::endl;
  std::cout << "\t|          3. �鿴����ԤԼ       |" << std::endl;
  std::cout << "\t|          4. ȡ��ԤԼ          |" << std::endl;
  std::cout << "\t|          0. ע����¼          |" << std::endl;
  std::cout << "\t|-----------------------------|" << std::endl;
  std::cout << "���������Ĳ�����" << std::endl;
}

// ����ԤԼ
void Student::applyOrder() {
  std::cout << "��������ʱ��Ϊ��һ������!" << std::endl;
  std::cout << "��ѡ������ԤԼʱ�䣺" << std::endl;
  std::cout << "1. ��һ" << std::endl;
  std::cout << "2. �ܶ�" << std::endl;
  std::cout << "3. ����" << std::endl;
  std::cout << "4. ����" << std::endl;
  std::cout << "5. ����" << std::endl;

  int date = 0; // ����
  int interval = 0; // ʱ���
  int room = 0; // �������

  while (true) {
    std::cin >> date;
    if (date >= 1 && date <= 5) {
      break;
    }
    std::cout << "��������������ѡ��..." << std::endl;
  }

  std::cout << "��ѡ������ԤԼʱ��Σ�" << std::endl;
  std::cout << "1. ����" << std::endl;
  std::cout << "2. ����" << std::endl;
  while (true) {
    std::cin >> interval;
    if (interval == 1 || interval == 2) {
      break;
    }
    std::cout << "��������������ѡ��..." << std::endl;
  }

  std::cout << "��ѡ�������" << std::endl;
  for (auto it : vCom) {
    std::cout << it.comId << "�Ż�������Ϊ��" << it.maxNum << std::endl;
  }

  while (true) {
    std::cin >> room;
    // �Ľ�
    if (room >= 1 && room <= this->vCom.size()) {
      break;
    }
    std::cout << "��������������ѡ��..." << std::endl;
  }

  std::cout << "ԤԼ�ɹ�!�����..." << std::endl;

  // д������
  std::ofstream ofs(ORDER_FILE, std::ios::app);
  if (!ofs.is_open()) {
    std::cout << "�ļ���ʧ��!" << std::endl;
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

// �鿴����ԤԼ
void Student::showSelfOrder() {
  OrderFile order_file;
  if (order_file.o_size == 0) {
    std::cout << "��ԤԼ��¼!" << std::endl;
    system("pause");
    return;
  }

  for (int i = 0; i < order_file.o_size; ++i) {
    // ��� string -> int
    // string ���� .c_str() ת const char *
    // ���� atoi(const char *) ת int
    if (this->id == atoi(order_file.orderData[i]["stuId"].c_str())) {
      // �ҵ�����ԤԼ
      std::cout << "ԤԼ���ڣ���" << order_file.orderData[i]["date"];
      std::cout << "  ʱ��Σ�" << (order_file.orderData[i]["interval"] == "1" ? "����" : "����");
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
  }

  system("pause");
}

// �鿴����ԤԼ
void Student::showAllOrders() {
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

// ȡ��ԤԼ
void Student::cancelOrder() {
  OrderFile order_file;
  if (order_file.o_size == 0) {
    std::cout << "����ԤԼ!" << std::endl;
    system("pause");
    return;
  }

  std::cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ����������ȡ���ļ�¼��" << std::endl;

  std::vector<int> v; // �������������е��±���
  int index = 1;
  for (int i = 0; i < order_file.o_size; ++i) {
    // ���ж��Ƿ�����ѧ��
    if (this->id == (atoi(order_file.orderData[i]["stuId"].c_str()))) {
      // ��ɸѡ״̬�� ����л�ԤԼ�ɹ��ļ�¼
      if (order_file.orderData[i]["status"] == "1" || order_file.orderData[i]["status"] == "2") {
        v.push_back(i);
        std::cout << index++ << "��";
        std::cout << "ԤԼ���ڣ���" << order_file.orderData[i]["date"];
        std::cout << "  ʱ��Σ�" << (order_file.orderData[i]["interval"] == "1" ? "����" : "����");
        std::cout << "  ������ţ�" << order_file.orderData[i]["roomId"];
        std::string status = "  ״̬��"; // 1. �����  2. ��ԤԼ
        if (order_file.orderData[i]["status"] == "1") {
          status += "�����";
        } else if (order_file.orderData[i]["status"] == "2") {
          status += "ԤԼ�ɹ�";
        }
        std::cout << status << std::endl;
      }
    }
  }

  int select = 0;
  while (true) {
    std::cout << "������ȡ���ļ�¼��0 - ����" << std::endl;
    std::cin >> select;

    if (select >= 0 && select <= v.size()) {
      if (select != 0) {
        order_file.orderData[v[select - 1]]["status"] = "0";

        order_file.updateOrder();
        std::cout << "��ȡ��ԤԼ" << std::endl;
      }
      break;
    }
    std::cout << "��������!" << std::endl;
  }

  system("pause");
}
