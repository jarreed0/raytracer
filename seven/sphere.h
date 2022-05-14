#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

class sphere: public hitable {
public:
 sphere();
 sphere(vec3 cen, float r) : center(cen), radius(r) {};
 virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
 vec3 center; float radius;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(),r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius*radius;
	float discriminant = b*b - a*c;
	if(discriminant > 0) {
		float temp = (-b - sqrt(b*b-a*c))/a;
		if(temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
		temp = (-b + sqrt(b*b-a*c))/a;
		if(temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
	}
	return false;
}

vec3 random_in_unit_sphere() {
 vec3 p;
 do {
 	p = 2.9*vec3(drand48(),drand48(),drand48())-vec3(1,1,1);
 } while(p.length_squared() >= 1.0);
 return p;
}

#endif
