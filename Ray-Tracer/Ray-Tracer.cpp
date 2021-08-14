#include "Utility.h"
#include "Color.h"
#include "Hittable_list.h"
#include "Sphere.h"
#include "Camera.h"
#include<fstream>
#include<iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <filesystem>
#include <thread>

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;


const auto aspect_ratio = 16.0 / 9.0;
const int image_width = 400;
const int image_height = static_cast<int>(image_width / aspect_ratio);
const int samples_per_pixel = 50;
const int max_depth = 50;

bool init();
bool loadMedia();
void close();
void displayImage();
void updateImage();
void writeToSurface(int offset);
int offset = 0;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;
SDL_Rect position;
std::vector<Uint32> colors{0,0,0};

//surface to write pixels and display real time
SDL_Surface* canvas = SDL_CreateRGBSurfaceWithFormat(
	0, image_width, image_height, 32, SDL_PIXELFORMAT_RGBA8888
);

//from writeToSurface
Uint32* buffer = (Uint32*)canvas->pixels;
Uint32 color;

bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//create window
		gWindow = SDL_CreateWindow("Raytraced Image", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 900, 600, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	//gHelloWorld = IMG_Load("image.ppm");
	/*if (gHelloWorld == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "image.ppm", SDL_GetError());
		success = false;
	}*/
	return success;
}

void close()
{
	//Deallocate surface
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

Color ray_color(const Ray& r, const Hittable& world, int depth) {
	hit_record rec;

	if (depth <= 0)
		return Color(0, 0, 0);


	if (world.hit(r, 0.001, infinity, rec)) {

		//Uniform scatter direction
		//Point3 target = rec.p + random_in_hemisphere(rec.normal);

		//Lambertian diffuse
		Point3 target = rec.p + rec.normal + random_unit_vector();
		return 0.5 * ray_color(Ray(rec.p, target - rec.p), world, depth - 1);
	}

	Vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);

}

void render()
{
	// World
	Hittable_list world;
	world.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
	world.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));

	//Camera
	Camera cam;

	// Render
	std::ofstream ofs;
	
	//ofs.open("./image.ppm", std::ofstream::out | std::ofstream::binary);
	//ofs << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	Color pixel_color(0, 0, 0);
	Ray r = cam.get_ray(0, 0); 
	for (int j = image_height - 1; j >= 0; --j) {

		for (int i = 0; i < image_width; ++i)
		{
			pixel_color = Vec3{ 0,0,0 };
			for (int s = 0; s < samples_per_pixel; ++s)
			{
				auto u = (i + random_double()) / (image_width - 1);
				auto v = (j + random_double()) / (image_height - 1);
				r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world, max_depth);
			}
			//write_color(ofs, pixel_color, samples_per_pixel);
			extractColors(colors, pixel_color, samples_per_pixel);
			writeToSurface(offset);
			offset += 1;
		}
		if (j % 2 == 0) updateImage();
	}
	//ofs.close();	
	std::cerr << "\nDone.\n";
}

void displayImage()
{
	
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			position.x = 200;
			position.y = 200;
			position.w = canvas->w;
			position.h = canvas->h;

			//While application is running
			int counter = 0;
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					if(counter == 0)
					{
						render();
						counter++;
					}
				}
			}
		}
		//Free resources and close SDL
		close();
	}
}

void createBlackPPM()
{
	std::ofstream ofs;
	ofs.open("./image.ppm", std::ofstream::out | std::ofstream::binary);
	ofs << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j) {
		std::cerr << "\rScanlines remaining: " << j << std::flush;
		for (int i = 0; i < image_width; ++i)
		{
			Color pixel_color(1.0, 0, 0);
			write_color(ofs, pixel_color, samples_per_pixel);
		}
	}
	ofs.close();
}

void updateImage()
{
	SDL_BlitSurface(canvas, NULL, gScreenSurface, &position);
	//Update the surface
	SDL_UpdateWindowSurface(gWindow);
}


void writeToSurface(int offset)
{
	SDL_LockSurface(canvas);
	color = SDL_MapRGBA(canvas->format, colors[0], colors[1], colors[2], 255);
	buffer[offset] = color;
	SDL_UnlockSurface(canvas);
}

int main(int argc, char* argv[])
{
	displayImage();
	return 0;
}


