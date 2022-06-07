#include <iostream>
#include <Eigen/Core>

int main() {
  int rows = 100;
  int cols = 200;

  std::cout << "P3\n" << cols << " " << rows << "\n255\n";

  for (int j = rows - 1; j >= 0; j --) {
    for (int i = 0; i < cols; i ++) {
      Eigen::Vector3f v(double(i) / double(cols),
                        double(j) / double(rows),
                        0.2);
      std::cout << int(v(0) * 256) << " "
                << int(v(1) * 256) << " "
                << int(v(2) * 256) << "\n";
    }
  }

  return 0;
}
