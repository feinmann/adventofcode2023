#include <iomanip>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>


std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream iss(str);
    std::string token;

    while (std::getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}


int extractNumberBeforeKeyword(const std::string& text, const std::string& keyword) {
    size_t found = text.find(keyword);
    if (found != std::string::npos) {
        std::string sub = text.substr(found - 3, found); 
        int number {0};
        number = std::stoi(sub);
        return number;
    }
    return -1;
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
  
  int game {1};
  int result {0};

  for (const std::string& line : lines) {
    
    std::vector<std::string> draws { splitString(line, ';') };
    int draw_nr {1};
    int max_red {0};
    int max_blue {0};
    int max_green {0};
    for (const std::string& draw : draws) {
      
      int red { extractNumberBeforeKeyword(draw, "red") };
      int blue { extractNumberBeforeKeyword(draw, "blue") };
      int green { extractNumberBeforeKeyword(draw, "green") };

      max_red = red > max_red ? red : max_red;
      max_blue = blue > max_blue ? blue : max_blue;
      max_green = green > max_green ? green : max_green;

      // std::cout << "Game: " << game 
      //           << ";draw: " << draw_nr
      //           << "; red: " << red 
      //           << "; max_red: " << max_red
      //           << "; blue: " << blue 
      //           << "; green: " << green << '\n';
      ++draw_nr;
    }
    // is any max-value greater than 12 red cubes, 13 green cubes, or 14 blue cubes?
    if (max_red <= 12 && max_green <= 13 && max_blue <= 14) {
      result += game;
      std::cout << "Possible game: " << game << "; Result: " << result
                << "; max_red: " << max_red
                << "; max_green: " << max_green
                << "; max_blue: " << max_blue << '\n';
    } else {
      std::cout << "NOT possible game: " << game << "; Result: " << result
                << "; max_red: " << max_red
                << "; max_green: " << max_green
                << "; max_blue: " << max_blue << '\n';
    }
    ++game;
  }

  input_file.close();

  std::cout << "The result for Puzzle 1 is " << result << '\n';

  return 0;
}
