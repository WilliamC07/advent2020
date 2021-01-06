#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <vector>
#include <numeric>
#include <unordered_map>
#include <array>
#include <unordered_set>

void read(std::ifstream &input, std::vector<std::pair<std::string, int>> &instructionPairs){
  std::string instruction;
  int val;

  while(input >> instruction >> val){
    instructionPairs.push_back({instruction, val});
  }
}

bool terminates(std::unordered_set<int> &instructionPassed,
                std::vector<std::pair<std::string, int>> instructionPairs,
                int acc, int counter){
  if(instructionPassed.find(counter) != instructionPassed.end()){
    return false;
  }else{
    auto &pair = instructionPairs[counter];
    std::string instruction{pair.first};
    int val = pair.second;

    if(instruction == "acc"){
      acc += val;
      counter++;
    }else if(instruction == "jmp"){
      counter += val;
    }else{
      // nop
      counter++;
    }
    return terminates(instructionPassed, instructionPairs, acc, counter);
  }
}

void fixed(std::unordered_set<int> &instructionPassed,
          std::vector<std::pair<std::string, int>> instructionPairs,
          int &acc, int counter){
  if(instructionPassed.size() == instructionPairs.size()){
    return;
  }

  auto &pair = instructionPairs[counter];
  std::string instruction{pair.first};
  int val{pair.second};

  if(instruction == "nop"){
    int tmp = acc;
    // will it end if this were a jmp
    if(terminates(instructionPassed, instructionPairs, tmp, counter + val)){
      acc = tmp;
      return;
    }
    // stay as nop
    fixed(instructionPassed, instructionPairs, acc, counter + 1);
  }else if(instruction == "jmp"){
    int tmp = acc;
    // will it end if this were a nop
    if(terminates(instructionPassed, instructionPairs, tmp, counter + 1)){
      acc = tmp;
      return;
    }
    // stay as jmp
    fixed(instructionPassed, instructionPairs, acc, counter + val);
  }else{
    acc += val;
    fixed(instructionPassed, instructionPairs, acc, counter + 1);
  }
}

void part2(std::vector<std::pair<std::string, int>> &instructionPairs){
  std::unordered_set<int> instructionPassed;
  int acc = 0;
  fixed(instructionPassed, instructionPairs, acc, 0);
  std::cout << "Part 2: " << acc << "\n";
}

int main(){
  std::ifstream input("input.txt");
  std::vector<std::pair<std::string, int>> instructionPairs;
  read(input, instructionPairs);
  std::unordered_set<int> instructionPassed;

  int acc = 0;
  int prevAcc;
  int i = 0;
  while(instructionPassed.find(i) == instructionPassed.end()){
    prevAcc = acc;
    instructionPassed.insert(i);

    auto &pair = instructionPairs[i];
    std::string instruction{pair.first};
    int val = pair.second;

    if(instruction == "acc"){
      acc += val;
      i++;
    }else if(instruction == "jmp"){
      i += val;
    }else{
      // nop
      i++;
    }
  }

  std::cout << "Part 1: " << prevAcc << "\n";
  part2(instructionPairs);
}