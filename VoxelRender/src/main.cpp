#include <iostream>
#include <GLAD/glad.h>

#include "Graphics/Window.h"
#include "Graphics/Renderer.h"
#include "Graphics/Shader.h"
#include "Graphics/PerspectiveCamera.h"
#include "Graphics/Scene.h"

#include "Input/Input.h"

using namespace GraphicsSystem;
using namespace InputSystem;

int main()
{
	Window window(1280, 720, "Minecraft");
	window.SetVSync(0);

	float cameraSpeed = 0.05f;

	PerspectiveCamera mainCamera(90.0f, 1920.0f / 1280.0f, 0.1f, 100.f);
	mainCamera.SetSensitivity(0.035f);
	mainCamera.SetPosition(glm::vec3(20, 4, 15));

	glm::vec3 mainCameraPosition = mainCamera.GetPosition();

	Renderer::Init();
	Renderer::SetClearColor(0.2f, 0.3f, 0.5f, 1.0f);

	Scene mainScene("assets/models/castles.vox");

	mainScene.AddLightSource(glm::vec3(0.0f, 20.0f, 0.0f));
	mainScene.AddLightSource(glm::vec3(0.0f, 20.0f, 30.0f));
	mainScene.AddLightSource(glm::vec3(30.0f, 20.0f, 30.0f));
	mainScene.AddLightSource(glm::vec3(30.0f, 20.0f, 0.0f));

	while (window.IsActive())
	{
		Renderer::Clear();

		Renderer::BeginVoxelScene(mainCamera);

		mainScene.Draw();

		Renderer::EndVoxelScene();

		//KeyboardInput
		{
			mainCamera.SetYaw(Input::GetXOffset());
			mainCamera.SetPitch(Input::GetYOffset());

			if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
				window.SetWindowActive(false);

			if (Input::IsKeyPressed(GLFW_KEY_RIGHT))
				mainCamera.SetYaw(1);
			else if (Input::IsKeyPressed(GLFW_KEY_LEFT))
				mainCamera.SetYaw(-1);

			if (Input::IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
				cameraSpeed = 0.15f;
			else
				cameraSpeed = 0.05f;

			if (Input::IsKeyPressed(GLFW_KEY_W))
				mainCameraPosition += glm::vec3(mainCamera.GetFront().x, 0.0f, mainCamera.GetFront().z) * cameraSpeed;
			else if (Input::IsKeyPressed(GLFW_KEY_S))
				mainCameraPosition -= glm::vec3(mainCamera.GetFront().x, 0.0f, mainCamera.GetFront().z) * cameraSpeed;

			if (Input::IsKeyPressed(GLFW_KEY_D))
				mainCameraPosition += mainCamera.GetRight() * cameraSpeed;
			else if (Input::IsKeyPressed(GLFW_KEY_A))
				mainCameraPosition -= mainCamera.GetRight() * cameraSpeed;

		}

		//GamepadInput
		Input::UpdateGamepadStates();
		{
			float yaw = abs(Input::GetGamepadAxis(GLFW_GAMEPAD_AXIS_RIGHT_X)) > 0.06 ? Input::GetGamepadAxis(GLFW_GAMEPAD_AXIS_RIGHT_X) : 0;
			float pitch = abs(Input::GetGamepadAxis(GLFW_GAMEPAD_AXIS_RIGHT_Y)) > 0.06 ? Input::GetGamepadAxis(GLFW_GAMEPAD_AXIS_RIGHT_Y) : 0;
			float x_move = abs(Input::GetGamepadAxis(GLFW_GAMEPAD_AXIS_LEFT_X)) > 0.06 ? Input::GetGamepadAxis(GLFW_GAMEPAD_AXIS_LEFT_X) : 0;
			float y_move = abs(Input::GetGamepadAxis(GLFW_GAMEPAD_AXIS_LEFT_Y)) > 0.06 ? Input::GetGamepadAxis(GLFW_GAMEPAD_AXIS_LEFT_Y) : 0;

			mainCamera.SetYaw(yaw * 45.0f);
			mainCamera.SetPitch(-pitch * 45.0f);

			mainCameraPosition -= glm::vec3(mainCamera.GetFront().x, 0.0f, mainCamera.GetFront().z) * (y_move * 0.1f);
			mainCameraPosition += glm::vec3(mainCamera.GetRight().x, 0.0f, mainCamera.GetRight().z) * (x_move * 0.1f);
		}

		mainCamera.SetPosition(mainCameraPosition);

		window.Update();
	}

	return 0;
}