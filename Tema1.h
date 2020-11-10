#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Tema1 : public SimpleScene
{
	public:
		Tema1();
		~Tema1();

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

	protected:
		glm::mat3 modelMatrix;
		float translate1X, translate2X, translate3X, translateY, translateeY,tx,ty;
		float scaleX, scaleY;
		float angularStep;
		int widthh;
		int width2;
		int width3;
		int width4;
		int width5;
		int width6;
		int width8;
		bool gameStop;
		float radius;
		float radius2;
		bool falling = true;
		glm::vec3 corner = glm::vec3(0, 0, 0);
		float squareSide = 100;

		int width_aripa = 15;
		int length_aripa = 25;
		int length = 55;
		int width = 26;
		int length_cioc = 15;
		int scor = 0;

		// compute coordinates of square center
		float cx = corner.x + squareSide / 2;
		float cy = corner.y + squareSide / 2;
};
