#include <iostream>
#include "sdltemplate.h"
#include "vec3.h"

int main() {
	int width = 800;
	int height = 400;
	std::cout << "P3\n" << width << " " << height << "\n255\n";
	sdltemplate::sdl("Ray Tracer", width, height);
	sdltemplate::loop();
	for(int y=height-1; y>=00; y--) {
		for(int x=0; x<width; x++) {
			vec3 col(float(x) / float(width),float(y) / float(height),0.2);
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			std::cout << ir << " " << ig << " " << ib << "\n";
			sdltemplate::setDrawColor(sdltemplate::createColor(ir,ig,ib,255));
			sdltemplate::drawPoint(x,height-y);
		}
	}
	while(sdltemplate::running) {
		sdltemplate::loop();
	}
}
