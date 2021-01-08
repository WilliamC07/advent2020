#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

void part1(const std::vector<std::string> &instructions){
  int x = 0, y = 0;
  int direction = 90;

  for(const auto &instruction : instructions){
    int amount = std::stoi(instruction.substr(1));
    switch(instruction[0]){
      case 'N':
        y+=amount;
        break;
      case 'S':
        y-=amount;
        break;
      case 'E':
        x+=amount;
        break;
      case 'W':
        x-=amount;
        break;
      case 'L':
        direction -= amount;
        if(direction < 0) direction = 360 + direction;
        break;
      case 'R':
        direction = (direction + amount) % 360;
        break;
      case 'F':
        switch (direction) {
          case 0:
            // north
            y+=amount;
            break;
          case 90:
            // east
            x+=amount;
            break;
          case 180:
            // south
            y-=amount;
            break;
          case 270:
            // west
            x-=amount;
            break;
          default:
            std::cout << "Unknown direction " << direction << "\n";
            exit(1);
        }
        break;
      default:
        std::cout << "Unknown character " << instruction << "\n";
        exit(1);
    }
  }

  std::cout << "Part 1: " << std::abs(x) + std::abs(y) << "\n";
}

void rotate(int direction, int &wayPointX, int &wayPointY){
  switch(direction){
    case 0:
      // nothing
      break;
    case 90:
      // 90 right
      wayPointX *= -1;
      std::swap(wayPointX, wayPointY);
      break;
    case 180:
      wayPointY *= -1;
      wayPointX *= -1;
      break;
    case 270:
      wayPointY *= -1;
      std::swap(wayPointX, wayPointY);
      break;
    default:
      std::cout << "Don't understand the direction: " << direction << "\n";
      exit(1);
  }
}

void part2(const std::vector<std::string> &instructions){
  // way point is 10 units east and 1 unit north
  // relative to ship
  int wayPointX = 10, wayPointY = 1;

  // ship cords
  int x, y;
  x = y = 0;

  for(const auto &instruction : instructions){
    int amount = std::stoi(instruction.substr(1));
    char c = instruction[0];

    switch(c) {
      case 'F':
        x += amount * wayPointX;
        y += amount * wayPointY;
        break;
      case 'N':
        wayPointY+=amount;
        break;
      case 'S':
        wayPointY-=amount;
        break;
      case 'E':
        wayPointX+=amount;
        break;
      case 'W':
        wayPointX-=amount;
        break;
      case 'R':
      case 'L':
        int direction;
        if(c == 'R'){
          direction = amount % 360;
        }else{
          direction = (360 - amount) % 360;
        }
        rotate(direction, wayPointX, wayPointY);
        break;
    }
  }

  std::cout << "Part 2: " << std::abs(x) + std::abs(y) << "\n";
}

int main(){
  std::ifstream input("input.txt");
  std::vector<std::string> instructions;
  std::string line;
  while(input >> line) {
    instructions.push_back(line);
  }

  part1(instructions);
  part2(instructions);
}