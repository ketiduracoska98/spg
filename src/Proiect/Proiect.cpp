#include "Proiect.h"
#include<chrono>
#include <vector>
#include <iostream>

#include <Core/Engine.h>

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
	camera->SetPositionAndRotation(glm::vec3(0, 4, 0), glm::quat(glm::vec3(-30 * TO_RADIANS, 0, 0)));
	camera->Update();
	std::string shaderPath = "src/Proiect/Shaders/";

	{
		Shader* shader = new Shader("Ray");
		shader->AddShader(shaderPath + "RayVert.glsl", GL_VERTEX_SHADER);
		shader->AddShader(shaderPath + "RayFrag.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Mesh* mesh = new Mesh("quad");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "/primitives", "/quad.obj");
	//	mesh->UseMaterials(false);
		meshes[mesh->GetMeshID()] = mesh;

	}
}
void Proiect::FrameStart()
{
}
void Proiect::Update(float deltaTimeSeconds)

{
	ClearScreen();
	RenderOnGPU();
}


void Proiect::FrameEnd()
{	
}

void Proiect::OnKeyPress(int key, int mods)
{
	switch (key)
	{
		case GLFW_KEY_1:
		{
			scene = 1;
			break;
		}
		case GLFW_KEY_2:
		{
			scene = 2;
			break;
		}
		case GLFW_KEY_3:
		{
			scene = 3;
			break;
		}
		default: break;
	}
	
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

void Proiect::RenderOnGPU()
{
	Shader* shader = shaders["Ray"];

	shaders["Ray"]->Use();
	glm::mat4 modelMatrix = glm::mat4(1);
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(GetSceneCamera()->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(GetSceneCamera()->GetProjectionMatrix()));
	glUniform1f(glGetUniformLocation(shader->program, "z_near"), GetSceneCamera()->GetProjectionInfo().zNear);
	glUniform1f(glGetUniformLocation(shader->program, "z_far"), GetSceneCamera()->GetProjectionInfo().zFar);


	vector<int> indexes;
	switch (scene) {
	case 1:
		indexes = { 0, 2, 0, 2, 0, 1, 0, 1, 0, 1 };
		break;
	case 2:
		indexes = { 2, 5, 2, 14, 1, 4, 1, 3, 1, 4 };
		break;
	case 3:
		indexes = { 5, 8, 14, 24, 4, 8, 3, 5, 4, 5 };
		break;

	default: 
		break;
	}

	glUniform1i(glGetUniformLocation(shader->program, "cube_start"), indexes[0]);
	glUniform1i(glGetUniformLocation(shader->program, "cube_stop"), indexes[1]);
	glUniform1i(glGetUniformLocation(shader->program, "sphere_start"), indexes[2]);
	glUniform1i(glGetUniformLocation(shader->program, "sphere_stop"), indexes[3]);
	glUniform1i(glGetUniformLocation(shader->program, "cylinder_start"), indexes[4]);
	glUniform1i(glGetUniformLocation(shader->program, "cylinder_stop"), indexes[5]);
	glUniform1i(glGetUniformLocation(shader->program, "cone_start"), indexes[6]);
	glUniform1i(glGetUniformLocation(shader->program, "cone_stop"), indexes[7]);
	glUniform1i(glGetUniformLocation(shader->program, "light_start"), indexes[8]);
	glUniform1i(glGetUniformLocation(shader->program, "light_stop"), indexes[9]);

	meshes["quad"]->Render();
}

