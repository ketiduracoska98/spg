#include "Proiect.h"
#include <iostream>



using namespace std;


Proiect::Proiect()
{

}
Proiect::~Proiect()
{
}
void Proiect::Init()
{
   
    auto camera = GetSceneCamera();
    camera->SetPositionAndRotation(glm::vec3(0, 5, 4), glm::quat(glm::vec3(-30 * TO_RADIANS, 0, 0)));
    camera->Update();

    
    }
}
void Proiect::FrameStart()
{

}
void Proiect::Update(float deltaTimeSeconds)
{


    ClearScreen();
	 

}
void Proiect::FrameEnd()
{	
	DrawCoordinateSystem();
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

