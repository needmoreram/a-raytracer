#include <iostream>

#include "objects.h"

Vector3d make_color(const Line3d& ray, ManyObjects& objs) {
  auto maybe_hit = objs.ray_first_hits_an_object_at(ray, 0.0, std::numeric_limits<double>::max());
  if (maybe_hit.has_value()) {
    Vector3d& normal = maybe_hit.value().normal;
    return 0.5 * Vector3d(normal.x() + 1, normal.y() + 1, normal.z() + 1);
  }

  Vector3d dir = ray.direction().normalized();
  double t = 0.5 * (dir.y() + 1.0);
  Vector3d a = (1.0 - t) * Vector3d(1, 1, 1);
  Vector3d b = t * Vector3d(0.5, 0.7, 1.0);

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

  ManyObjects objs;
  objs.add_object(new Sphere(Vector3d(0, 0, -1), 0.5));
  objs.add_object(new Sphere(Vector3d(0, -100.5, -1), 100));

  for (int j = rows - 1; j >= 0; j --) {
    for (int i = 0; i < cols; i ++) {
      double u = double(i) / double(cols);
      double v = double(j) / double(rows);
      Vector3d direction(lower_left_corner + u * horizontal + v * vertical);
      Line3d ray(origin, direction);
      Vector3d color = make_color(ray, objs);
      std::cout << int(color.x() * 255.99) << " "
                << int(color.y() * 255.99) << " "
                << int(color.z() * 255.99) << "\n";
    }
  }

  return 0;
}
