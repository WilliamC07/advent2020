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

const std::string BAG = " bag";
struct Hash;

struct BagNode {
  std::string color;
  std::unordered_map<std::string, int> branch;

  BagNode(const std::string &color): color(color) {}
};

const std::string SHINY_GOLD = "shiny gold";
bool containGold(BagNode *bag, std::unordered_map<std::string, BagNode*> &bags){
  for(const auto &pair : bag->branch){
    if(pair.first == SHINY_GOLD){
      return true;
    }else if(containGold(bags[pair.first], bags)){
      return true;
    }
  }

  return false;
}

void divideToParts(std::string &containBags, std::vector<std::string> &parts){
  std::replace(containBags.begin(), containBags.end(), ',', '\n');
  std::istringstream source{containBags};
  std::string part;

  while(std::getline(source, part)){
    if(part[0] == ' ') {
      part = part.substr(1);
    }
    parts.push_back(part);
  }
}

int countBagInside(BagNode *gold, std::unordered_map<std::string, BagNode*> &bags){
  int amt = 0;
  for(const auto &pair : gold->branch){
    auto *bagNode = bags[pair.first];
    amt += pair.second;
    amt += pair.second * countBagInside(bagNode, bags);
  }
  return amt;
}

int main() {
  std::ifstream input("input.txt");

  // keep track of nodes in the tree
  std::unordered_map<std::string, BagNode*> bags;
  std::string bagInfo;
  const std::string CONTAIN = " contain ";

  while(std::getline(input, bagInfo)) {
    int containIndex = bagInfo.find(CONTAIN);
    auto bagColor = bagInfo.substr(0, bagInfo.find(BAG));
    auto containBags = bagInfo.substr(containIndex + CONTAIN.length());

    auto *bagNode = new BagNode(bagColor);
    std::vector<std::string> parts;
    divideToParts(containBags, parts);

    for(std::string &part : parts){
      if(part.find("no other bags") != std::string::npos){
        continue;
      }

      int amount = part[0] - '0';
      std::string color{part.substr(2, part.find(BAG) - 2)};
      bagNode->branch[color] = amount;
    }

    bags[bagColor] = bagNode;
  }

  // part 1
  int amtWithGold = 0;
  for(auto &pair : bags){
    if(containGold(pair.second, bags)){
      amtWithGold++;
    }
  }
  std::cout << "Part 1: " << amtWithGold << "\n";

  // part 2
  std::cout << "Part 2: " << countBagInside(bags[SHINY_GOLD], bags) << "\n";
}