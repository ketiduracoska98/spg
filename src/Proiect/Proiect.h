#pragma once
#include "components/simple_scene.h"


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
	
	
private:  
	int scene = 1;	
	float rotationValue = 0;
	float rotationDirection = 1;
	float translationValue = 0;
	float translationDirection = 1;
	float scalingValue = 1;
	float scalingDirection = 1;
	float animationSpeed = 5;
	float currTime = 0;
};