#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <bitset>

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

// "destination" string must be size 64
void getBitString(std::string &fluctuated, const std::string &mask, unsigned long value){
  fluctuated = std::bitset<64>(value).to_string();

  // we need 32 bits
  for(int i = 0; i < mask.size(); i++){
    int destinationIndex = fluctuated.size() - i - 1;
    int maskIndex = mask.size() - i - 1;
    if(mask.at(maskIndex) == '1'){
      // bit is set
      fluctuated.at(destinationIndex) = '1';
    }else if(mask.at(maskIndex) == 'X'){
      fluctuated.at(destinationIndex) = 'X';
    }
  }
}

void possibilities(std::string &fluctuated, int i, std::map<unsigned long, unsigned long> &mem, unsigned long val){
  if(i == fluctuated.size()){
    mem[std::bitset<64>(fluctuated).to_ulong()] = val;
    return;
  }

  if(fluctuated.at(i) == 'X'){
    fluctuated.at(i) = '0';
    possibilities(fluctuated, i, mem, val);
    fluctuated.at(i) = '1';
    possibilities(fluctuated, i, mem, val);
    fluctuated.at(i) = 'X';
  }else{
    // 0 or 1
    possibilities(fluctuated, i + 1, mem, val);
  }
}

int main(){
  std::ifstream input("/Users/williamcao/CLionProjects/adventofcode2020/day_14/input.txt");
  std::map<int, unsigned long> memPart1;
  std::map<unsigned long, unsigned long> memPart2;
  const std::string EQUAL_TOKEN{" = "};

  std::string line;
  std::string mask;
  while(std::getline(input, line)) {
    if (line[1] == 'a') {
      // mask line
      mask = line.substr(line.find(EQUAL_TOKEN) + EQUAL_TOKEN.size());
    } else {
      // setting mem
      unsigned long value = std::stoi(line.substr(line.find(EQUAL_TOKEN) + EQUAL_TOKEN.size()));
      std::string key = line.substr(0, line.find(EQUAL_TOKEN));
      int address = std::stoi(line.substr(line.find('[') + 1, line.find(']')));

      // part 2
      std::string fluctuated;
      getBitString(fluctuated, mask, address);
      possibilities(fluctuated, 0, memPart2, value);

      // part 1
      applyMask(mask, value);
      memPart1[address] = value;
    }
  }

  unsigned long sumPart1 = 0;
  for(auto &pair : memPart1){
    sumPart1 += pair.second;
  }

  unsigned long sumPart2 = 0;
  for(auto &pair : memPart2){
    sumPart2 += pair.second;
  }


  std::cout << "Part 1: " << sumPart1 << "\n";
  std::cout << "Part 2: " << sumPart2 << "\n";
}