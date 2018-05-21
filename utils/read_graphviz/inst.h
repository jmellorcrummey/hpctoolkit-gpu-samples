#ifndef _INST_H_
#define _INST_H_

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <regex>

struct Inst {
  int offset;
  std::string opcode;
  std::string port;
  std::vector<std::string> operands;

  Inst(std::string &inst_str) {
    if (inst_str[0] == '/') {  // Dual issue
      inst_str = inst_str.substr(2);
      auto pos = inst_str.find("*/");
      inst_str.replace(pos, 2, "");
    }
    std::istringstream iss(inst_str);
    std::string s;
    if (std::getline(iss, s, ':')) {
      if (s.find("<") != std::string::npos) {
        auto pos = s.find(">");
        this->port = s.substr(1, pos - 1);
        s = s.substr(pos + 1); 
      }
      std::stringstream ss;
      ss << std::hex << s;
      ss >> offset;
      if (std::getline(iss, s, ':')) {
        std::regex e("\\\\ ");
        iss = std::istringstream(std::regex_replace(s, e, "\n"));
        while (std::getline(iss, s)) {
          if (s != "") {
            if (opcode == "") {
              opcode = s;
            } else {
              operands.push_back(s);
            }
          }
        }
      }
    }
  }
};

#endif
