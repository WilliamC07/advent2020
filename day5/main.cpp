#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <vector>
#include <numeric>
#include <unordered_set>

int bsp(int low, int high, char first, char last, const std::string &instructions){
  float midpoint = (low + high) / 2.0;
  char instruction = instructions[0];

  if(instructions.length() == 1){
    if(instruction == first)
      return low;
    else
      return high;
  }

  if(instruction == first){
    return bsp(low, std::floor(midpoint), first, last, instructions.substr(1));
  }else{
    return bsp(std::ceil(midpoint), high, first, last, instructions.substr(1));
  }
}

int calculateID(int row, int column){
  return row * 8 + column;
}

int main(){
  std::ifstream input("input.txt");

//  std::cout << bsp(0, 127, 'F', 'B', "FBFBBFF") << "\n";
//  std::cout << bsp(0, 7, 'L', 'R', "RLR")<< "\n";

  int highestId = 0;
  // running program previously, we know highest id is 890
  const int HIGHEST_ID = 890;
  bool seatID[HIGHEST_ID + 1] = {false};
  std::unordered_set<std::string> seatsTaken;

  std::string line;
  while(input >> line){
    const std::string row_instructions = line.substr(0, 7);
    int row = bsp(0, 127, 'F', 'B', row_instructions);

    const std::string column_instructions = line.substr(7);
    int column = bsp(0, 7, 'L', 'R', column_instructions);

    int id = calculateID(row, column);
    seatID[id] = true;
    seatsTaken.insert(std::to_string(row) + " " + std::to_string(column));
    highestId = std::max(highestId, id);
  }

  std::cout << "Part 1: " << highestId << "\n";

  for(int row = 0; row < 128; row++){
    for(int column = 0; column < 8; column++){
      int id = calculateID(row, column);
      std::string rowColumnPair = std::to_string(row) + " " + std::to_string(column);
      if(id < HIGHEST_ID && seatID[id-1] && seatID[id+1] && seatsTaken.find(rowColumnPair) == seatsTaken.end()){
        std::cout << "Part 2: " << id << "\n";
        break;
      }
    }
  }
}