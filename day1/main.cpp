#include <fstream>
#include <set>
#include <iostream>

int main(){
  std::ifstream input("input.txt");
  std::set<int> numbers;

  int val;
  while(input >> val){
    // Part 1
    if(numbers.count(2020 - val)){
      std::cout << "Part 1: \n";
      std::cout << val << " and " << 2020 - val << "\n";
      std::cout << "product: " << val * (2020 - val) << "\n";
    }

    // Part 2:
    for(const int &n : numbers){
      int lookingFor = 2020 - val - n;
      if(numbers.count(lookingFor)){
        std::cout << "Part 2: \n";
        std::cout << val << " " << n << " " << lookingFor << "\n";
        std::cout << "product: " << val * n * lookingFor << "\n";
      }
    }

    numbers.insert(val);
  }
}