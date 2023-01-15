#include "Proiect.h"

#include <vector>
#include <iostream>
#include <chrono>

#include <Core/Engine.h>
#include "rtweekend.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "box.h"
#include "cylinder.h"
#include "cone.h"
#include <core/gpu/frame_buffer.h>

using namespace std;


Proiect::Proiect()
{
	
}
Proiect::~Proiect()
{
}

FrameBuffer* processed;
/*point3 lookfrom(13, 2, 3);
point3 lookat(0, 0, 0);
vec3 vup(0, 1, 0);
double dist_to_focus = 10.0;
double aperture = 0.1;
const double aspect_ratio = 16.0 / 9.0;
camera_cpu cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

const int image_width = 1200;
const int image_height = static_cast<int>(image_width / aspect_ratio);
const int samples_per_pixel = 10;
const int max_depth = 50;
//auto world = w_scene();
glm::ivec2 imageSize = glm::ivec2(image_width, image_height);

unsigned char* newData;
*/

void Proiect::Init()
{
   
	originalImage = TextureManager::LoadTexture(RESOURCE_PATH::TEXTURES + "cube/pos_x.png", nullptr, "image", true, true);
	processedImage = TextureManager::LoadTexture(RESOURCE_PATH::TEXTURES + "cube/pos_x.png", nullptr, "newImage", true, true);

	// World


	// Camera

}
void Proiect::FrameStart()
{
}
void Proiect::Update(float deltaTimeSeconds)

{

	/*for (int j = image_height - 1; j >= 0; --j) {
		for (int i = 0; i < image_width; ++i) {
			color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; ++s) {
				auto u = (i + random_double()) / (image_width - 1);
				auto v = (j + random_double()) / (image_height - 1);
				ray r = cam.get_ray(u, v);
			//	pixel_color += ray_color(r, world, max_depth);
			}
			int offset = (j * imageSize.x + i);
			write_color(&newData[offset], pixel_color, samples_per_pixel);
		}
	}*/
	Ray();
	 

}


void Proiect::FrameEnd()
{	
}

color ray_color(const ray& r, const hittable& world, int depth) {
	hit_record rec;

	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0)
		return color(0, 0, 0);

	if (world.hit(r, 0.001, infinity, rec)) {
		ray scattered;
		color attenuation;
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return attenuation * ray_color(scattered, world, depth - 1);
		return color(0, 0, 0);
	}

	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}







void Proiect::Ray()
{
	using namespace std::chrono;
	auto start = high_resolution_clock::now();
	unsigned int channels = originalImage->GetNrChannels();
	unsigned char* data = originalImage->GetImageData();
	unsigned char* newData = processedImage->GetImageData();

	if (channels < 3)
		return;

	glm::ivec2 imageSize = glm::ivec2(originalImage->GetWidth(), originalImage->GetHeight());
	// Image

	const auto aspect_ratio = 16.0 / 9.0;
	const int samples_per_pixel = 20;
	const int max_depth = 20;

	// World
	auto world = w_scene();

	// Camera

	point3 lookfrom(-13, 4, 5);
	point3 lookat(0, 0, 0);
	vec3 vup(0, 1, 0);
	auto dist_to_focus = 10;
	auto aperture = 0.1;

	camera_cpu cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);


#pragma omp parallel for
	for (int j = imageSize.y - 1; j >= 0; j--)
	{
		for (int i = 0; i < imageSize.x; i++)
		{

			color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; ++s) {
				auto u = (i + random_double()) / ((double)imageSize.x - 1);
				auto v = (j + random_double()) / ((double)imageSize.y - 1);
				ray r = cam.get_ray(u, v);
				pixel_color = pixel_color + ray_color(r, world, max_depth);
			}
			int offset = channels * (j * imageSize.x + i);

			write_color(&newData[offset], pixel_color, samples_per_pixel);
		}
	}

	processedImage->UploadNewData(newData);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(stop - start);
	if (continuousPrint) {
		cout << 3600.f / static_cast<float>(duration.count()) << endl;
	}
}

hittable_list Proiect::w_scene()
{
	hittable_list world;

	auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
	world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto choose_mat = random_double();
			point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

			if ((center - point3(4, 0.2, 0)).length() > 0.9) {
				shared_ptr<material> sphere_material;

				if (choose_mat < 0.8) {
					// diffuse
					auto albedo = color::random() * color::random();
					sphere_material = make_shared<lambertian>(albedo);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95) {
					// metal
					auto albedo = color::random(0.5, 1);
					auto fuzz = random_double(0, 0.5);
					sphere_material = make_shared<metal>(albedo, fuzz);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
				else {
					// glass
					sphere_material = make_shared<dielectric>(1.5);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	auto material1 = make_shared<dielectric>(1.5);
	world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

	auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
	world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

	auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
	world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

	return world;
}





void Proiect::OnKeyPress(int key, int mods)
{
	
	
}

void Proiect::OnInputUpdate(float deltaTime, int mods)
{
	
}

void Proiect::OnKeyRelease(int key, int mods)
{
	// Add key release event
}


void Proiect::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// Add mouse move event
}


void Proiect::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button press event
}


void Proiect::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button release event
}


void Proiect::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// Treat mouse scroll event
}


void Proiect::OnWindowResize(int width, int height)
{
	// Treat window resize event
}

