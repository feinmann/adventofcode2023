#include <iomanip>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

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
  
  int result {0};

  for (const std::string& str : lines) {
    
    int actual_idx_left {static_cast<int>(str.size())};
    int actual_idx_right {0};
    int first_digit {0};
    int last_digit {0};

    for (int num = 1; num < 10; ++num) {
      size_t first_found = str.find(std::to_string(num));
      if (first_found != std::string::npos)
        //std::cout << "For " << str << ": " 
        //                    << num << " found at " << found << ",\n";
        if (first_found <= actual_idx_left) {
          actual_idx_left = first_found;
          first_digit = num;
        }
      size_t last_found = str.rfind(std::to_string(num));
      if (last_found != std::string::npos)
        //std::cout << "For " << str << ": " 
        //                    << num << " found at " << found << ",\n";
        if (last_found >= actual_idx_right) {
          actual_idx_right = last_found;
          last_digit = num;
        }
    }
    std::cout << "For " << str << ": " 
              << "first_digit is " << first_digit
              << " last digit is " << last_digit << '\n';
    std::cout << '\n';
    result = result + first_digit * 10 + last_digit;
    //std::cout << i << std::endl;
  }

  input_file.close();

  std::cout << "The result for Puzzle 1 is " << result << '\n';

  return 0;
}
