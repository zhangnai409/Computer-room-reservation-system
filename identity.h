#pragma once
#include <iostream>
#include <string>

// ��ݳ�����
class Identity {
 public:
  std::string name; // �û���
  std::string pwd; // ����

  // �����˵� ���麯��
  virtual void operMenu() = 0;
};