#include <iostream>

int main() {
  int rows = 100;
  int cols = 200;

  std::cout << "P3\n" << cols << " " << rows << "\n255\n";

  for (int j = rows - 1; j >= 0; j --) {
    for (int i = 0; i < cols; i ++) {
      int r = double(i) / double(cols) * double(256);
      int g = double(j) / double(rows) * double(256);
      int b = 0.2 * 256;
      std::cout << r << " " << g << " " << b << "\n";
    }
  }

  return 0;
}
