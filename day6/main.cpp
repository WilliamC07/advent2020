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
#include <array>

void readGroups(std::ifstream &input, std::vector<std::string> &groups){
  std::string line;
  std::string group;

  while(std::getline(input, line)){
    if(line.empty()){
      groups.push_back(group);
      group = "";
    }else{
      group += line + " "; // space to separate question
    }
  }

  group += line;
  groups.push_back(group);
}

int uniqueYes(const std::string &group){
  std::array<bool, 26> uniquePeople{};

  for(const char c : group){
    if(c == ' ') continue;
    uniquePeople[c - 'a'] = true;
  }

  return std::count(uniquePeople.begin(), uniquePeople.end(), true);
}

int allYes(const std::string &group){
  std::array<int, 26> yes{};
  std::istringstream source(group);
  std::string question;
  int numQuestions = 0;

  while(source >> question){
    numQuestions++;
    for(const char c : question){
      yes[c - 'a']++;
    }
  }

  return std::count(yes.begin(), yes.end(), numQuestions);
}

int main() {
  std::ifstream input("input.txt");
  std::vector<std::string> groups;
  readGroups(input, groups);

  int sumYes = 0;
  int sumAllYes = 0;
  for(const auto &group : groups){
    sumYes += uniqueYes(group);
    sumAllYes += allYes(group);
  }

  std::cout << "Part 1: " << sumYes << "\n";
  std::cout << "Part 2: " << sumAllYes << "\n";
}