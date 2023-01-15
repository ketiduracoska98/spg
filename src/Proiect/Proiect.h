#pragma once
#include "components/simple_scene.h"
#include "hittable_list.h"


using namespace std;


class Proiect : public gfxc::SimpleScene
{
public:
	Proiect();
	~Proiect();
	void Init() override;
private:
    void FrameStart() override;
    void Update(float deltaTimeSeconds) override;
    void FrameEnd() override;

    void OnInputUpdate(float deltaTime, int mods) override;
    void OnKeyPress(int key, int mods) override;
    void OnKeyRelease(int key, int mods) override;
    void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
    void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
    void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
    void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
    void OnWindowResize(int width, int height) override;
	void DrawOnGPU();
	
	
    void Ray();
    hittable_list w_scene();
private:  
	Texture2D* originalImage;
	Texture2D* processedImage;

	bool flip;
	int outputMode;

	int scene = 1;
	float timeToOneSec = 0;
	int frames = 0;
	int framesPerSec = 0;
	bool continuousPrint = false;
	bool onGPU = true;
	float rotationValue = 0;
	float rotationDirection = 1;
	float translationValue = 0;
	float translationDirection = 1;
	float scalingValue = 1;
	float scalingDirection = 1;
	float animationSpeed = 5;
	float currTime = 0;


	const float aspect_ratio = 16.0 / 9.0;
	const int image_width = 1200;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 10;
	const int max_depth = 50;

	unsigned char buffer[3];


	
	
};