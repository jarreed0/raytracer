#include <iostream>
#include "sdltemplate.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "material.h"

vec3 color(const ray& r, hitable *world, int depth) {
	hit_record rec;
	if(world->hit(r, 0.001, MAXFLOAT, rec)) {
		//vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		//return 0.5*color(ray(rec.p,target-rec.p),world);
		ray scattered;
		vec3 attenuation;
		if(depth < 50 && rec.mat_ptr->scatter(r,rec,attenuation,scattered)) {
			return attenuation*color(scattered,world,depth+1);
		} else {
			return vec3(0,0,0);
		}
	} else {
		vec3 unit_dir = unit_vector(r.direction());
		float t = 0.5*(unit_dir.y() + 1.0);
		return (1.0-t)*vec3(1.0,1.0,1.0)+t*vec3(0.5,0.7,1.0);
	}
}

int main() {
	//sphere = vec3(0,0,-1);
	//sphere_radius = 0.5;
	int width = 800;
	int height = 400;
	int ns = 100;
	std::cout << "P3\n" << width << " " << height << "\n255\n";
	sdltemplate::sdl("Ray Tracer", width, height);
	sdltemplate::loop();
	hitable *list[5];
	list[0] = new sphere(vec3(0,0,-1),0.5,new lambertian(vec3(0.1,0.2,0.5)));
	list[1] = new sphere(vec3(0,-100.5,-1),100,new lambertian(vec3(0.8,0.8,0.0)));
	list[2] = new sphere(vec3(1,0,-1),0.5,new metal(vec3(0.8,0.6,0.2),0.2));
	//list[3] = new sphere(vec3(-1,0,-1),0.5,new metal(vec3(0.8,0.8,0.8),0.7));
	list[3] = new sphere(vec3(-1,0,-1),0.5,new dielectric(1.5));
	list[4] = new sphere(vec3(-1,0,-1),-0.45,new dielectric(1.5));
	hitable *world = new hitable_list(list,5);
	camera cam;
	for(int y=height-1; y>=0; y--) {
		for(int x=0; x<width; x++) {
			vec3 col(0,0,0);
			for(int s=0;s<ns;s++) {
				float u = float(x+drand48()) / float(width);
				float v = float(y+drand48()) / float(height);
				ray r = cam.get_ray(u,v);
				vec3 p = r.point_at_parameter(2.0);
				col += color(r, world, 0);
			}
			col /= float(ns);
			col = vec3(sqrt(col.r()),sqrt(col.g()),sqrt(col.b()));
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			//std::cout << ir << " " << ig << " " << ib << "\n";
			if(x % width == 1) sdltemplate::loop();
			sdltemplate::setDrawColor(sdltemplate::createColor(ir,ig,ib,255));
			sdltemplate::drawPoint(x,height-y);
		}
	}
	while(sdltemplate::running) {
		sdltemplate::loop();
	}
}
