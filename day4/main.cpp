#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <vector>

bool hasValidFields(const std::string &passport);
void readPassports(std::ifstream &input, std::vector<std::string> &passports);
bool hasValidFieldData(const std::string &passport);

// ok if we missed "cid", so we didn't include it in this list
const char *fields[7] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

int main(){
  std::ifstream input("input.txt");
  std::vector<std::string> passports;
  readPassports(input, passports);

  int numWithValidFields{};
  int numWithValidFieldsValues{};
  for(auto &passport : passports){
    if(hasValidFields(passport)){
      // part 1
      numWithValidFields++;

      // part 2
      if(hasValidFieldData(passport)){
        numWithValidFieldsValues++;
      }
    }
  }

  std::cout << "Part 1: " << numWithValidFields << "\n";
  std::cout << "Part 2: " << numWithValidFieldsValues << "\n";
}

void readPassports(std::ifstream &input, std::vector<std::string> &passports){
  std::string line;
  std::string passportInfo;

  while(std::getline(input, line)){
    if(line.empty()){
      // remove trailing space
      passportInfo.erase(passportInfo.length() - 1);
      passports.push_back(passportInfo);
      passportInfo = "";
    }else{
      passportInfo += line + " ";
    }
  }

  // last passport
  passportInfo += line + " ";
  passports.push_back(passportInfo);
}

bool hasValidFields(const std::string &passport){
  for(const char *field : fields){
    if(passport.find(field) == std::string::npos){
      //did not find field
      return false;
    }
  }
  return true;
}

void splitKeyValuePair(const std::string &keyValuePair, std::string &key, std::string &value){
  int indexColon = keyValuePair.find(':');
  key = keyValuePair.substr(0, indexColon);
  value = keyValuePair.substr(indexColon + 1);
}

bool isNumberAndBetween(const std::string &s, int min, int max){
  if(std::all_of(s.cbegin(), s.cend(), isdigit)){
    int val = std::stoi(s);
    return val >= min && val <= max;
  }
  return false;
}

bool isHex(const std::string &s){
  const std::string &codes = "0123456789abcdef";
  auto check = [codes](char c){return codes.find(c) != std::string::npos;};
  auto start = s.cbegin();
  start++;
  std::cout << *start << "--\n";
  return *s.begin() == '#' && std::all_of(start, s.cend(), check);
}

bool validEyeColor(const std::string &s){
  const std::string valids = "amb blu brn gry grn hzl oth";
  return s.length() == 3 && s.find(' ') == std::string::npos && valids.find(s) != std::string::npos;
}

bool hasValidFieldData(const std::string &passport){
  std::istringstream source{passport};

  std::string keyValuePair;
  while(source >> keyValuePair){
    std::string key, value;
    splitKeyValuePair(keyValuePair, key, value);
    int valueLength = value.length();
    if(key == "byr"){
      if(!isNumberAndBetween(value, 1920, 2002)){
        return false;
      }
    }else if(key == "iyr"){
      if(!isNumberAndBetween(value, 2010, 2020)){
        return false;
      }
    }else if(key == "eyr"){
      if(!isNumberAndBetween(value, 2020, 2030)){
        return false;
      }
    }else if(key == "hgt"){
      if(valueLength < 3) return false;
      std::string unit{value.substr(valueLength - 2)};
      std::string unitRemoved{value.substr(0, valueLength - 2)};
      if(unit == "cm"){
        // at least 150 and at most 193.
        if(!isNumberAndBetween(unitRemoved, 150, 193)){
          return false;
        }
      }else if(unit == "in"){
        // at least 59 and at most 76.
        if(!isNumberAndBetween(unitRemoved, 59, 76)){
          return false;
        }
      }else{
        return false;
      }
    }else if(key == "hcl"){
      if(!(valueLength == 7 && isHex(value))){
        return false;
      }
    }else if(key == "ecl"){
      if(!validEyeColor(value)){
        return false;
      }
    }else if(key == "pid"){
      if(!(valueLength == 9 && std::all_of(value.begin(), value.end(), isdigit))){
        return false;
      }
    }
  }

  return true;
}