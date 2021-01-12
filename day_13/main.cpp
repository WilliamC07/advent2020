#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>

int WILD_ID = -1;

void getIds(std::vector<int> &ids, std::istream &input){
  std::string times;
  input >> times;
  const char *c_str = times.c_str();
  char copy[200];
  strcpy(copy, c_str);
  char *part = strtok(copy, ",");
  while(part != NULL){
    if(part[0] != 'x'){
      ids.push_back(std::stoi(part));
    }else{
      ids.push_back(WILD_ID);
    }
    part = strtok(NULL, ",");
  }
}

void part1(int earliest, const std::vector<int> &ids){
  int busEarliest = INT_MAX;
  int earliestID = 0;
  for(auto &id : ids){
    // get first multiple after earliest we can get on the bus
    int dividend = earliest / id;
    int nextTime = id * dividend + id;
    if(busEarliest > nextTime){
      busEarliest = nextTime;
      earliestID = id;
    }
  }
  std::cout << "Part 1: " << earliestID * (busEarliest - earliest) << "\n";
}

void part2(const std::vector<int> &ids){

  int firstId = ids.at(0);
  int t = firstId; // timestamp

  long result = 1;
  long product = 1;
  for(int i = 0; i < ids.size(); i++){
    int id = ids.at(i);
    if(id == -1) continue;
    result = (result + i) * id;
    product *= id;
  }

  while(result != 1068788){
    std::cout << result << "\n";
    result -= product;
  }


  std::cout << result << "\n";
}


int main(){
  std::ifstream input("input.txt");

  int earliest;
  input >> earliest;
  std::vector<int> ids;
  getIds(ids, input);

  part1(earliest, ids);
  part2(ids);
}