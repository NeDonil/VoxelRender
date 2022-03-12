#include <iostream>
#include <GLAD/glad.h>

#include "Graphics/Window.h"
#include "Graphics/Renderer.h"
#include "Graphics/Shader.h"
#include "Graphics/Camera.h"
#include "Graphics/Scene.h"

#include "Input/Input.h"

using namespace GraphicsSystem;
using namespace InputSystem;

int main()
{
	Window window(1280, 720, "Editor");
	window.SetVSync(0);

	float cameraSpeed = 0.05f;

	Camera mainCamera(90.0f, 1280.0f / 720.0f, 0.1f, 100.f);

	Renderer::Init();
	Renderer::SetClearColor(0.2f, 0.3f, 0.5f, 1.0f);

	Scene mainScene("assets/models/castles.vox");
	mainScene.AddLightSource({ 70.0f, 70.0f, 70.0f });


	while (window.IsActive())
	{
		//Clear
		Renderer::Clear();

		//Render
		Renderer::BeginVoxelScene(mainScene.GetCamera());
		mainScene.Draw();
		Renderer::EndVoxelScene();

		//Update
		mainScene.Update();
		window.Update();

		if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
			window.SetWindowActive(false);
	}

	return 0;
}