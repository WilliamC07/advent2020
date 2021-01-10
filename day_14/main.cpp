#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <math.h>

void applyMask(const std::string &mask, unsigned long &value) {
  int size = mask.size();
  for(int i = size - 1; i >= 0; i--){
    if(mask[i] == 'X') continue;

    int bitPosition = size - i - 1;
    // set bit to 1
    value |= (1UL << bitPosition);
    if(mask[i] == '0')
      value ^= (1UL << bitPosition);
  }
}

void getBitString(std::string &destination, unsigned long value){
  // we need 32 bits
  for(int i = 0; i < 32; i++){
    if(value & (1UL << i)){
      // bit is set
      destination = "1" + destination;
    }else{
      destination = "0" + destination;
    }
  }
}

void applyFloatingMask(const std::string &mask, unsigned long &value){
  int size = mask.size();
  for(int i = size - 1; i >= 0; i--){
    int bitPosition = size - i - 1;
    if(mask[i] == '0') continue;
    if(mask[i] == '1') {
      // set bit to 1
      value |= (1UL << bitPosition);
    }
  }
}

int main(){
  std::ifstream input("input.txt");
  std::map<int, unsigned long> mem;
  unsigned long sum = 0;

  const std::string EQUAL_TOKEN{" = "};

  std::string line;
  std::string mask;
  while(std::getline(input, line)){
    if(line[1] == 'a'){
      // mask line
      mask = line.substr(line.find(EQUAL_TOKEN) + EQUAL_TOKEN.size());
    }else{
      // setting mem
      unsigned long value = std::stoi(line.substr(line.find(EQUAL_TOKEN) + EQUAL_TOKEN.size()));
      applyMask(mask, value);
      std::string key = line.substr(0, line.find(EQUAL_TOKEN));
      std::string address = line.substr(line.find("[") + 1, line.find("]"));
      mem[std::stoi(address)] = value;
    }
  }

  for(auto &pair : mem){
    sum += pair.second;
  }

  std::cout << sum << "\n";
}