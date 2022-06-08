#pragma once

#include <cmath>
#include <vector>
#include <optional>
#include <Eigen/Geometry>

using Eigen::Vector3d;
using Line3d = Eigen::ParametrizedLine<double, 3>;

struct HitsAt {
  double t;
  Vector3d p;
  Vector3d normal;
};

class AnObject {
public:
	virtual ~AnObject() = default;
	virtual std::optional<HitsAt>
		ray_hits_at(const Line3d& ray, double t_min, double t_max) = 0;
};

class Sphere final : public AnObject {
public:
	Sphere() = default;
	Sphere(Vector3d center, double radius) : center(center), radius(radius) {}

	virtual std::optional<HitsAt>
	  ray_hits_at(const Line3d& ray, double t_min, double t_max);

private:
	inline HitsAt _record_hit(const Line3d& ray, double t);

	Vector3d center;
	double radius;
};

inline HitsAt Sphere::_record_hit(const Line3d& ray, double t) {
  HitsAt hit;
  hit.t = t;
  hit.p = ray.pointAt(t);
  hit.normal = (hit.p - center) / radius;
  return hit;
}

std::optional<HitsAt> Sphere::ray_hits_at(const Line3d& ray, double t_min, double t_max) {
	Vector3d oc = ray.origin() - center;

	double a = ray.direction().dot(ray.direction());
  double b = 2 * ray.direction().dot(oc);
  double c = oc.dot(oc) - radius * radius;

  double discriminant = (b * b - 4 * a * c);
  if (discriminant > 0) {
  	double root = (-b - sqrt(discriminant)) / (2.0 * a);
  	if (t_min < root && root < t_max) {
  		return _record_hit(ray, root);
  	}
  	root = (-b + sqrt(discriminant)) / (2.0 * a);
  	if (t_min < root && root < t_max) {
  		return _record_hit(ray, root);
  	}
  }

  return std::nullopt;
}

class ManyObjects final : public AnObject {
public:
	ManyObjects() = default;

	void add_object(AnObject* obj) {
		objects_list.push_back(obj);
	}

	inline std::optional<HitsAt>
		ray_first_hits_an_object_at(const Line3d& ray, double t_min, double t_max) {
		return ray_hits_at(ray, t_min, t_max);
	}

private:
	virtual std::optional<HitsAt>
	  ray_hits_at(const Line3d& ray, double t_min, double t_max);

	std::vector<AnObject*> objects_list;
};

std::optional<HitsAt> ManyObjects::ray_hits_at(const Line3d& ray, double t_min, double t_max) {
	std::optional<HitsAt> maybe_hit = std::nullopt;
	double t_closest = t_max;
	for (auto obj : objects_list) {
		auto hit = obj->ray_hits_at(ray, t_min, t_closest);
		if (hit.has_value()) {
			maybe_hit = hit;
			t_closest = hit.value().t;
		}
	}
	return maybe_hit;
}