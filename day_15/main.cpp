#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <math.h>

int result(int endTurn){
  std::string puzzle{"1,0,16,5,17,4"};
  std::replace(puzzle.begin(), puzzle.end(), ',', ' ');
  std::istringstream input{puzzle};

  std::unordered_map<int, int> history;
  int turn = 1;
  int justSpoken;
  int lastSpoken;
  while (input >> justSpoken) {
    if(turn != 1){
      history[lastSpoken] = turn;
    }
    lastSpoken = justSpoken;
    turn++;
  }


  for (; turn <= endTurn; turn++) {
    if (history.find(lastSpoken) != history.end()) {
      // last spoken was not said for the first time
      int age = turn - history.find(lastSpoken)->second;
      justSpoken = age;
    }else{
      // last spoken was said for the first time
      justSpoken = 0;
    }
    history[lastSpoken] = turn;
    lastSpoken = justSpoken;
  }

  return lastSpoken;
}

int main() {
  std::cout << "Part 1: " << result(2020) << "\n";
  std::cout << "Part 2: " << result(30000000) << "\n";
}