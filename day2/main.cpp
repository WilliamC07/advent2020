#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

int main(){
  std::ifstream input("input.txt");

  int valid_count_partA = 0;
  int valid_count_partB = 0;

  std::string line;
  while(getline(input, line)){
    char string[100] = {'\0'};
    strcpy(string, line.c_str());

    // split up the tokens
    char *token = strtok(string, "-");
    int min_occur = atoi(token);
    token = strtok(NULL, " ");
    int max_occur = atoi(token);
    char character = string[line.find(':') - 1];
    std::string password = line.substr(line.rfind(' ') + 1);

    // part a
    int passwordOccurrences = std::count(password.begin(), password.end(), character);
    if(passwordOccurrences >= min_occur && passwordOccurrences <= max_occur){
      valid_count_partA++;
    }

    // part b
    if(password.at(min_occur-1) == character ^ password.at(max_occur-1) == character){
      valid_count_partB++;
    }
  }

  std::cout << "Valid passwords for part a: " << valid_count_partA << "\n";
  std::cout << "Valid passwords for part b: " << valid_count_partB << "\n";

}