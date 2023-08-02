#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include "globalFile.h"

class OrderFile {
 public:
  // 记录预约条数
  int o_size;
  // 记录所有预约信息的容器 key记录条数 value记录具体信息
  std::map<int, std::map<std::string, std::string>> orderData;

  OrderFile();
  // 初始化
  void initOrderFile();
  // 更新预约记录
  void updateOrder();
};

OrderFile::OrderFile() {
  this->o_size = 0;
  this->initOrderFile();
}

// 截取字段成 key value
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
// 初始化
void OrderFile::initOrderFile() {
  std::ifstream ifs(ORDER_FILE, std::ios::in);

  if (!ifs.is_open()) {
    std::cout << "文件打开失败!" << std::endl;
    ifs.close();
    return;
  }

  std::string date;     // 日期
  std::string interval; // 时间段
  std::string stuId;    // 学生编号
  std::string stuName;  // 学生姓名
  std::string roomId;   // 机房编号
  std::string status;   // 预约编号

  while (ifs >> date && ifs >> interval && ifs >> stuId
      && ifs >> stuName && ifs >> roomId && ifs >> status) {

    std::map<std::string, std::string> m;
    // 截取日期
    substrKeyValue(m, date);
    // 截取时间段
    substrKeyValue(m, interval);
    // 截取学生编号
    substrKeyValue(m, stuId);
    // 截取学生姓名
    substrKeyValue(m, stuName);
    // 截取机房编号
    substrKeyValue(m, roomId);
    // 截取预约编号
    substrKeyValue(m, status);

    // 将小map容器放入到大的map容器中
    this->orderData.insert(std::make_pair(this->o_size, m));
    this->o_size++;
  }

  ifs.close();

//  for (auto it : this->orderData) {
//    std::cout << "条数为：" << it.first << " value = " << std::endl;
//    for (auto i : it.second) {
//      std::cout << " key = " << i.first << " value = " << i.second << " ";
//    }
//    std::cout << std::endl;
//  }
}

// 记录所有预约信息的容器 key记录条数 value记录具体信息
void OrderFile::updateOrder() {
  if (this->o_size == 0) {
    // 预约记录0条，直接返回
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