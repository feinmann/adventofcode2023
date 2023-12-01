#include <iomanip>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

int get_number(std::string numberword) {
  if (numberword == "one" || numberword == "1") {
    return 1;
  } else if (numberword == "two" || numberword == "2") {
    return 2;
  } else if (numberword == "three" || numberword == "3") {
    return 3;
  } else if (numberword == "four" || numberword == "4") {
    return 4;
  } else if (numberword == "five" || numberword == "5") {
    return 5;
  } else if (numberword == "six" || numberword == "6") {
    return 6;
  } else if (numberword == "seven" || numberword == "7") {
    return 7;
  } else if (numberword == "eight" || numberword == "8") {
    return 8;
  } else if (numberword == "nine" || numberword == "9") {
    return 9;
  } else {
    return 0;
  }
}


int main() {
  std::string filename{"data.txt"};
  std::vector<std::string> lines;
  std::string line;

  std::ifstream input_file(filename);
  
  if (!input_file.is_open()) {
    std::cerr << "Could not open the file - '" << filename 
              << "'" << std::endl;
    return 1;
  }

  while (std::getline(input_file, line)) {
    lines.push_back(line);
  }
  
  std::vector<std::string> all_numbers_vec = {
    "1", "2", "3", "4", "5", "6", "7", "8", "9",
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
  int result {0};

  for (const std::string& str : lines) {
    
    int actual_idx_left {static_cast<int>(str.size())};
    int actual_idx_right {0};
    int first_digit {0};
    int last_digit {0};

    for (const std::string& numberstr : all_numbers_vec) {

      size_t first_found = str.find(numberstr);
      if (first_found != std::string::npos)
        if (first_found <= actual_idx_left) {
          actual_idx_left = first_found;
          first_digit = get_number(numberstr);
        }

      size_t last_found = str.rfind(numberstr);
      if (last_found != std::string::npos)
        if (last_found >= actual_idx_right) {
          actual_idx_right = last_found;
          last_digit = get_number(numberstr);
        }
    }
    std::cout << "For " << str << ": " 
              << "first_digit is " << first_digit
              << " last digit is " << last_digit << '\n';
    std::cout << '\n';
    result = result + first_digit * 10 + last_digit;
  }

  input_file.close();

  std::cout << "The result for Puzzle 2 is " << result << '\n';

  return 0;
}
