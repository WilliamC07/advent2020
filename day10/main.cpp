#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <vector>
#include <numeric>
#include <map>
#include <array>

void part1(std::set<int> &adapterVolts, int deviceVolt){
  int currentVolt = 0;
  int voltDifferences[3] = {0};
  while(currentVolt != deviceVolt){
    std::cout << currentVolt << "\n";
    for(int voltDifference = 1; voltDifference <= 3; voltDifference++){
      int volt = voltDifference + currentVolt;
      if(adapterVolts.find(volt) != adapterVolts.end()){
        voltDifferences[voltDifference-1]++;
        currentVolt = volt;
        break;
      }
    }
  }

  for(int i = 0; i < 3; i++){
    std::cout << i << ": " << voltDifferences[i] << "\n";
  }
  std::cout << "Part 1: " << voltDifferences[0] * voltDifferences[2] << "\n";
}

// discrete math :((
void numberWays(const std::set<int> &adapterVolts, int toVolt, std::map<int, long> &cache){
  if(toVolt <= 1){
    cache[toVolt] = 1;
  }else if(adapterVolts.find(toVolt) != adapterVolts.end()){
    long ways = 0;
    for(int i = 1; i <= 3; i++){
      ways += cache[toVolt - i];
    }
    cache[toVolt] = ways;
  }
}

void part2(std::set<int> &adapterVolts, int deviceVolt){
  std::map<int, long> cache;
  for(int i = 0; i <= deviceVolt; i++){
    numberWays(adapterVolts, i, cache);
    std::cout << i << ": " << cache[i] << "\n";
  }
  std::cout << "Part 2: " << cache[deviceVolt] << "\n";
}

int main(){
  std::ifstream input("input.txt");
  std::set<int> adapterVolts{};

  int tmp;
  int deviceVolt = 0;
  while(input >> tmp) {
    adapterVolts.insert(tmp);
    deviceVolt = std::max(deviceVolt, tmp);
  }
  deviceVolt += 3;
  adapterVolts.insert(deviceVolt);

  part1(adapterVolts, deviceVolt);
  part2(adapterVolts, deviceVolt);
}