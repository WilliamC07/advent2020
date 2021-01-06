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

int main(){
  std::ifstream input("input.txt");

  std::vector<long> nums;
  long tmp;
  while(input >> tmp) nums.push_back(tmp);

  long invalidNum;
  for(int i = 25; i < nums.size(); i++){
    long current = nums.at(i);
    bool found = false;
    for(int j = i - 25; j < i; j++){
      for(int k = j + 1; k < i; k++){
        if(nums.at(j) + nums.at(k) == current){
          found = true;
        }
      }
    }
    if(!found) {
      invalidNum = current;
      std::cout << "Part 1: " << current << "\n";
    }
  }

  // sliding window
  long current = nums.at(0);
  int start = 0;
  int end = 0;
  while(current != invalidNum){
    if(start == end){
      end++;
      current += nums.at(end);
    }
    if(current < invalidNum){
      end++;
      current += nums.at(end);
    }
    while(current > invalidNum){
      current -= nums.at(start);
      start++;
    }
  }

  long min = nums.at(start), max = 0;
  long sum = 0;
  for(; start <= end; start++){
    long n = nums.at(start);
    if(n > max){
      max = n;
    }
    if(n < min){
      min = n;
    }
    sum += n;
  }

  std::cout << "Part 2: " << min + max << "\n";
}