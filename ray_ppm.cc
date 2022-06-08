#include <iostream>
#include <Eigen/Geometry>

using Eigen::Vector3d;
using Eigen::ParametrizedLine;

using Color3d = Eigen::Vector3d;
using Line3d = ParametrizedLine<double, 3>;

Color3d make_color(const Line3d& ray) {
  Vector3d dir = ray.direction().normalized();
  double t = 0.5 * (dir.y() + 1.0);
  Color3d a = (1.0 - t) * Vector3d(1, 1, 1);
  Color3d b = t * Vector3d(0.5, 0.7, 1.0);
  return (a + b);
}

int main() {
  int rows = 100;
  int cols = 200;

  std::cout << "P3\n" << cols << " " << rows << "\n255\n";

  Vector3d origin(0, 0, 0);
  Vector3d lower_left_corner(-2, -1, -1);
  Vector3d horizontal(4, 0, 0);
  Vector3d vertical(0, 2, 0);

  for (int j = rows - 1; j >= 0; j --) {
    for (int i = 0; i < cols; i ++) {
      double u = double(i) / double(cols);
      double v = double(j) / double(rows);
      Vector3d direction(lower_left_corner + u * horizontal + v * vertical);
      Line3d ray(origin, direction);
      Color3d color = make_color(ray);
      std::cout << int(color.x() * 255.99) << " "
                << int(color.y() * 255.99) << " "
                << int(color.z() * 255.99) << "\n";
    }
  }

  return 0;
}
