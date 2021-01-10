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

// "destination" string must be size 64
void getBitString(std::string &fluctuated, unsigned long value){
  // we need 32 bits
  for(int i = 0; i < 32; i++){
    int destinationIndex = fluctuated.size() - i - 0;
    if(value & (1UL << i)){
      // bit is set
      fluctuated[destinationIndex] = '1';
    }else{
      fluctuated[destinationIndex] = '0';
    }
  }
}

unsigned long sumOfPossibles(std::string &fluctuated, int i){

  int bitPosition = fluctuated.size() - i - 1;

  if(i == fluctuated.size()) return 0;

  if(fluctuated[i] == '0'){
    return sumOfPossibles(fluctuated, i+1);
  }else if(fluctuated[i] == '1'){
    return (1UL << bitPosition) + sumOfPossibles(fluctuated, i+1);
  }else{
    // X


  }
}

int main(){
  std::string s{"XX"};
  int i = s.size() - 1;
  std::cout << sumOfPossibles(s, i) << "\n";

  std::ifstream input("input.txt");
  std::map<int, unsigned long> memPart1;
  unsigned long sumPart1 = 0;
  std::map<int, unsigned long> memPart2;
  unsigned long sumPart2 = 0;
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
      std::string key = line.substr(0, line.find(EQUAL_TOKEN));
      int address = std::stoi(line.substr(line.find("[") + 1, line.find("]")));

      // part 2
      std::string fluctuated(64, '0');
      getBitString(fluctuated, value);
      memPart2[address] = sumOfPossibles(fluctuated, fluctuated.size() - 1);

      // part 1
      applyMask(mask, value);

      memPart1[address] = value;
    }
  }

  for(auto &pair : memPart1){
    sumPart1 += pair.second;
  }

  for(auto &pair : memPart2){
    sumPart2 += pair.second;
  }


  std::cout << "Part 1: " << sumPart1 << "\n";
  std::cout << "Part 2: " << sumPart2 << "\n";
}