#include <iostream>
#include <fstream>
#include "globalFile.h"
#include "identity.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"

// �����ʦ�Ӳ˵�����
void teacherMenu(Identity *&teacher) {
  while (true) {
    // ���ý�ʦ�Ӳ˵�
    teacher->operMenu();

    Teacher *tea = (Teacher *) teacher;

    int select = 0;
    std::cin >> select;

    if (select == 1) {   // �鿴����ԤԼ
      tea->showAllOrders();
    } else if (select == 2) {   // ���ԤԼ
      tea->vailOrder();
    } else { // ע����¼
      delete tea;
      std::cout << "ע����¼" << std::endl;
      system("pause");
      return;
    }
  }
}

// ����ѧ���Ӳ˵�����
void studentMenu(Identity *&student) {
  while (true) {
    // ����ѧ���Ӳ˵�
    student->operMenu();

    Student *stu = (Student *) student;

    int select = 0;
    std::cin >> select;

    if (select == 1) { // ����ԤԼ
      stu->applyOrder();
    } else if (select == 2) { // �鿴����ԤԼ
      stu->showSelfOrder();
    } else if (select == 3) { // �鿴������ԤԼ
      stu->showAllOrders();
    } else if (select == 4) { // ȡ��ԤԼ
      stu->cancelOrder();
    } else {// ע����¼
      delete stu;
      std::cout << "ע����¼" << std::endl;
      system("pause");
      return;
    }
  }
}

// �������Ա�Ӳ˵�����
void managerMenu(Identity *manager) {
  while (true) {
    // ���ù���Ա�Ӳ˵�
    manager->operMenu();

    // ������ָ��תΪ����ָ�룬���������������ӿ�
    Manager *man = (Manager *) manager;

    int select = 0;
    std::cin >> select;

    if (select == 1) { // ����˺�
      std::cout << "����˺�" << std::endl;
      man->addPerson();
    } else if (select == 2) { // �鿴�˺�
      std::cout << "�鿴�˺�" << std::endl;
      man->showPerson();
    } else if (select == 3) { // �鿴����
      std::cout << "��ӻ���" << std::endl;
      man->addComputerRoom();
    } else if (select == 4) { // �鿴����
      std::cout << "�鿴����" << std::endl;
      man->showComputer();
    } else if (select == 5) { // ���ԤԼ
      std::cout << "���ԤԼ" << std::endl;
      man->clearFile();
    } else {
      // ע����������
      delete manager;
      std::cout << "ע���ɹ�" << std::endl;
      return;
    }
  }
}

/**
 * ��¼����
 * @param fileName �����ļ���
 * @param type �����������
 */
void loginIn(std::string fileName, int type) {
  // ����ָ�룬����ָ���������
  Identity *person = nullptr;

  // ���ļ�
  std::ifstream ifs(fileName, std::ios::in);

  if (!ifs.is_open()) {
    std::cout << "�ļ�������" << std::endl;
    ifs.close();
    return;
  }

  // �����û���Ϣ
  int id = 0;
  std::string name;
  std::string pwd;

  // �ж����
  if (type == 1) { // ѧ�����
    std::cout << "����������ѧ�ţ�" << std::endl;
    std::cin >> id;

  } else if (type == 2) { // ��ʦ���
    std::cout << "����������ְ���ţ�" << std::endl;
    std::cin >> id;
  }

  std::cout << "�������û�����" << std::endl;
  std::cin >> name;
  std::cout << "���������룺" << std::endl;
  std::cin >> pwd;

  if (type == 1) { // ѧ�������֤
    // ���ļ���ȡ����Ϣ
    int fId;
    std::string fName;
    std::string fPwd;
    while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
      if (fId == id && fName == name && fPwd == pwd) {
        std::cout << "ѧ����֤��¼�ɹ�!" << std::endl;
        system("pause");
        person = new Student(id, name, pwd);
        // ����ѧ����ݵ��Ӳ˵�
        studentMenu(person);
        return;
      }
    }
  } else if (type == 2) { // ��ʦ�����֤
    // ���ļ���ȡ����Ϣ
    int fId;
    std::string fName;
    std::string fPwd;
    while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
      if (fId == id && fName == name && fPwd == pwd) {
        std::cout << "��ʦ��֤��¼�ɹ�!" << std::endl;
        system("pause");
        person = new Teacher(id, name, pwd);
        // �����ʦ��ݵ��Ӳ˵�
        teacherMenu(person);
        return;
      }
    }
  } else if (type == 3) { // ����Ա�����֤
    // ���ļ���ȡ����Ϣ
    std::string fName;
    std::string fPwd;
    while (ifs >> fName && ifs >> fPwd) {
      if (fName == name && fPwd == pwd) {
        std::cout << "����Ա��֤��¼�ɹ�!" << std::endl;
        system("pause");
        person = new Manager(name, pwd);
        // �������Ա��ݵ��Ӳ˵�
        managerMenu(person);
        return;
      }
    }
  }

  std::cout << "��¼ʧ��" << std::endl;
  std::system("pause");
}

int main() {
  int select = 0; // �û�ѡ��
  while (true) {
    std::cout << "================ ��ӭ��������ԤԼϵͳ =============" << std::endl;
    std::cout << "\t|-----------------------------|" << std::endl;
    std::cout << "\t|          1. ѧ������          |" << std::endl;
    std::cout << "\t|          2. ��   ʦ          |" << std::endl;
    std::cout << "\t|          3. �� �� Ա         |" << std::endl;
    std::cout << "\t|          0. ��   ��          |" << std::endl;
    std::cout << "\t|-----------------------------|" << std::endl;
    std::cout << "������������ݣ�" << std::endl;
    std::cin >> select;

    switch (select) {
      case 1: // ѧ�����
        loginIn(SRUDENT_FILE, 1);
        break;
      case 2: // ��ʦ���
        loginIn(TEACHER_FILE, 2);
        break;
      case 3: // ����Ա���
        loginIn(ADMIN_FILE, 3);
        break;
      case 0: // �˳�ϵͳ
        std::cout << "��ӭ�´�ʹ��" << std::endl;
        return 0;
      default:std::cout << "�������������ѡ��!" << std::endl;
        std::system("pause");
        break;
    }
  }
}
