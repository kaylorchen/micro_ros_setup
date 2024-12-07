#include <iostream>
#include "yaml-cpp/yaml.h"
#include "fstream"

const std::string ros2_prefix = "ssh://git@shenzhen.kaylordut.com:10022/ros2/";
const std::string microros_prefix = "ssh://git@shenzhen.kaylordut.com:10022/microros/";

std::string getLastItem(const std::string& input) {
  // 找到最后一个 '/' 的位置
  std::size_t pos = input.find_last_of('/');
  if (pos == std::string::npos) {
    return input;  // 如果没有找到分隔符，返回整个字符串
  }
  // 提取最后一段
  return input.substr(pos + 1);
}
std::string getLastNonEmptySegment(const std::string& input) {
  if(input.empty()){
    return ""; // 处理输入为空的情况
  }

  std::size_t pos = input.find_last_of('/');

  // 如果字符串末尾有一个反斜杠并且不是第一个字符，以此为终止
  while (pos == input.length() - 1 && pos != 0) {
    pos = input.find_last_of('/', pos - 1);
  }

  if (pos == std::string::npos) {
    return input;  // 如果没有找到分隔符，返回整个字符串
  }

  std::string lastSegment = input.substr(pos + 1);

  // 如果最后一个段是空的，再找倒数第二个段
  if (lastSegment.empty() && pos != 0) {
    pos = input.find_last_of('/', pos - 1);
    if (pos == std::string::npos) {
      return input;  // 如果在这一段没有找到其他分隔符，返回整个字符串
    }
    return input.substr(pos + 1);
  }

  return lastSegment;
}

int main(int argc, char **argv) {
  std::string filename = argv[1];
  YAML::Node yaml_node = YAML::LoadFile(filename);
  std::string main_key = "repositories";
  auto size = yaml_node[main_key].size();
  if (size == 0) {
    std::cerr << "size = 0" << std::endl;
    return 0;
  }
  std::ofstream file(filename);
  for (auto it: yaml_node[main_key]) {
    auto url = it.second["url"].as<std::string>();
    auto repo = it.first.as<std::string>();
    if (repo.rfind("ros2/", 0) == 0){
      it.second["url"] = ros2_prefix + getLastNonEmptySegment(url);
    }else{
      it.second["url"] = microros_prefix + getLastNonEmptySegment(url);
    }
    std::cout << "repo: " <<  repo<< std::endl;
    std::cout << url << std::endl;
    std::cout << it.second["url"].as<std::string>() << std::endl;
  }
  file<< yaml_node;
//  std::cout << yaml_node;
  file.close();
  return 0;
}
