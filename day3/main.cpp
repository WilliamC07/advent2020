#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

constexpr int INPUT_LINE_NUMBER = 323;
int collisionForSlope(const int right, const int left, const std::string *patterns);

int main(){
  // part 1

  // read in the file
  std::ifstream input("input.txt");
  std::string patterns[INPUT_LINE_NUMBER];
  int counter = 0;
  while(input >> patterns[counter++]);

  // part 1: slope = -1/3
  std::cout << "Part 1: " << collisionForSlope(3, 1, patterns) << "\n";

  // part 2;
  int slopes[5][2] = {{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};
  long productTreeCollisions = 1;
  for(const int *slopePair : slopes){
    productTreeCollisions *= collisionForSlope(slopePair[0], slopePair[1], patterns);
  }

  std::cout << "Part 2: " << productTreeCollisions << "\n";
}

int collisionForSlope(const int right, const int down, const std::string *patterns){
  int column = 0;
  int row = 0;
  int treeCollisions = 0;
  const int PATTERN_WIDTH = patterns[0].length();
  for(; row < INPUT_LINE_NUMBER; row += down){
    if(patterns[row].at(column % PATTERN_WIDTH) == '#'){
      treeCollisions++;
    }
    column += right;
  }

  std::cout << treeCollisions << "\n";

  return treeCollisions;
}