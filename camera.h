#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

vec3 random_in_unit_disk() {
	vec3 p;
	do {
		p = 2.0*vec3(drand48(),drand48(),0.0) - vec3(1,1,0);
	} while(dot(p,p)>=1.0);
	return p;
}

class camera {
public:
 camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist) {
 	lens_radius = aperture / 2;
 	float theta = vfov*M_PI/180;
 	float half_height = tan(theta/2);
 	float half_width = aspect * half_height;
 	origin = lookfrom;
 	w = unit_vector(lookfrom - lookat);
 	u = unit_vector(cross(vup,w));
 	v = cross(w,u);
 	lower_left_corner = origin - half_width*focus_dist*u - half_height*focus_dist*v - focus_dist*w;
	horizontal=2*half_width*u*focus_dist;
	vertical=2*half_height*v*focus_dist;
 }

 ray get_ray(float s, float t) {
 	vec3 rd = lens_radius*random_in_unit_disk();
 	vec3 offset = u * rd.x() + v * rd.y();
 	return ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset);
 }


 vec3 lower_left_corner, horizontal, vertical, origin;
 float lens_radius;
 vec3 u,v,w;
};

#endif







