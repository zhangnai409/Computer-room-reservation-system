#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include "globalFile.h"

class OrderFile {
 public:
  // ��¼ԤԼ����
  int o_size;
  // ��¼����ԤԼ��Ϣ������ key��¼���� value��¼������Ϣ
  std::map<int, std::map<std::string, std::string>> orderData;

  OrderFile();
  // ��ʼ��
  void initOrderFile();
  // ����ԤԼ��¼
  void updateOrder();
};

OrderFile::OrderFile() {
  this->o_size = 0;
  this->initOrderFile();
}

// ��ȡ�ֶγ� key value
void substrKeyValue(std::map<std::string, std::string> &m, std::string val) {
  // date:1
  std::string key;
  std::string value;
  int pos = val.find(":");
  if (pos != -1) {
    key = val.substr(0, pos);
    value = val.substr(pos + 1, val.size() - pos - 1);
    m.insert(std::make_pair(key, value));
  }
}
// ��ʼ��
void OrderFile::initOrderFile() {
  std::ifstream ifs(ORDER_FILE, std::ios::in);

  if (!ifs.is_open()) {
    std::cout << "�ļ���ʧ��!" << std::endl;
    ifs.close();
    return;
  }

  std::string date;     // ����
  std::string interval; // ʱ���
  std::string stuId;    // ѧ�����
  std::string stuName;  // ѧ������
  std::string roomId;   // �������
  std::string status;   // ԤԼ���

  while (ifs >> date && ifs >> interval && ifs >> stuId
      && ifs >> stuName && ifs >> roomId && ifs >> status) {

    std::map<std::string, std::string> m;
    // ��ȡ����
    substrKeyValue(m, date);
    // ��ȡʱ���
    substrKeyValue(m, interval);
    // ��ȡѧ�����
    substrKeyValue(m, stuId);
    // ��ȡѧ������
    substrKeyValue(m, stuName);
    // ��ȡ�������
    substrKeyValue(m, roomId);
    // ��ȡԤԼ���
    substrKeyValue(m, status);

    // ��Сmap�������뵽���map������
    this->orderData.insert(std::make_pair(this->o_size, m));
    this->o_size++;
  }

  ifs.close();

//  for (auto it : this->orderData) {
//    std::cout << "����Ϊ��" << it.first << " value = " << std::endl;
//    for (auto i : it.second) {
//      std::cout << " key = " << i.first << " value = " << i.second << " ";
//    }
//    std::cout << std::endl;
//  }
}

// ��¼����ԤԼ��Ϣ������ key��¼���� value��¼������Ϣ
void OrderFile::updateOrder() {
  if (this->o_size == 0) {
    // ԤԼ��¼0����ֱ�ӷ���
    return;
  }

  std::ofstream ofs(ORDER_FILE, std::ios::out | std::ios::trunc);
  for (int i = 0; i < this->o_size; ++i) {
    ofs << "date:" << this->orderData[i]["date"] << " ";
    ofs << "interval:" << this->orderData[i]["interval"] << " ";
    ofs << "stuId:" << this->orderData[i]["stuId"] << " ";
    ofs << "stuName:" << this->orderData[i]["stuName"] << " ";
    ofs << "roomId:" << this->orderData[i]["roomId"] << " ";
    ofs << "status:" << this->orderData[i]["status"] << std::endl;
  }

  ofs.close();
}