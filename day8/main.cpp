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
    instructionPairs.emplace_back(instruction, val);
  }
}

using InstructionPair = std::vector<std::pair<std::string, int>>;
using Passed = std::unordered_set<int>;

bool teriminates(InstructionPair &instructionPairs, Passed passed, int &acc, int counter){
  while(counter < instructionPairs.size() && passed.find(counter) == passed.end()){
    auto &pair = instructionPairs.at(counter);
    std::string instruction = pair.first;
    int val = pair.second;

    passed.insert(counter);

    if(instruction == "acc"){
      acc += val;
      counter++;
    }else if(instruction == "jmp"){
      counter += val;
    }else{
      // nop
      counter++;
    }
  }

  if(counter == instructionPairs.size()){
    return true;
  }else{
    return false;
  }
}

void part2(std::vector<std::pair<std::string, int>> &instructionPairs){
  std::unordered_set<int> passed;
  int acc = 0;
  int counter = 0;

  while(counter < instructionPairs.size() && passed.find(counter) == passed.end()) {
    passed.insert(counter);
    auto &pair = instructionPairs.at(counter);
    std::string instruction = pair.first;
    int val = pair.second;
    int tmp = acc;

    if (instruction == "acc") {
      acc += val;
      counter++;
    } else if (instruction == "jmp") {
      // what if this were nop
      if(teriminates(instructionPairs, passed, tmp, counter + 1)){
        std::cout << "ended\n";
        acc = tmp;
        break;
      }
      // keep as jmp
      counter += val;
    } else {
      // nop
      if(teriminates(instructionPairs, passed, tmp, counter + val)){
        std::cout << "ended\n";
        acc = tmp;
        break;
      }
      counter++;
    }
  }

  std::cout << "Part 2: " << acc << "\n";
}

int main(){
  std::ifstream input("/Users/williamcao/CLionProjects/adventofcode2020/day8/input.txt");
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