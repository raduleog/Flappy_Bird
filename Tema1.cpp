#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"
#include <iostream>
#include <Windows.h>
#include <MMSystem.h>

using namespace std;
Tema1::Tema1()
{
}

Tema1::~Tema1()
{

}
void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	gameStop = true;
	
	// initialize tx and ty (the translation steps)
	translate1X = 1900;
	translate2X = 2300;
	translate3X = 2700;
	ty = 360;
	// initialize sx and sy (the scale factors)
	scaleX = 1;
	scaleY = 1;
	// initialize angularStep
	angularStep = 0;
	radius = 12;
	radius2 = 2;
	/*Imi creez cate o mesa pentru fiecare figura geometrica care va fi folosita  in joc
	Lungimea si latimea fiecarei tevi este data de widthX si squareSide
	Inaltimea tevii de sus este random, generata cu functia rand() inaltimea tevii de jos o aleg in functie de cea de sus*/
	//pipe 1
	widthh = rand() % 300;
	width2 = 500 - widthh;

	Mesh* square1 = Object2D::CreateRectangle("square1", corner, squareSide, widthh, glm::vec3(0, 0.7f, 0), true);
	AddMeshToList(square1);

	Mesh* square1_top = Object2D::CreateRectangle("square1_top", corner, squareSide + 6, 20, glm::vec3(0, 0.5f, 0), true);
	AddMeshToList(square1_top);
	
	Mesh* square2 = Object2D::CreateRectangle("square2", corner, squareSide, width2, glm::vec3(0, 0.7f, 0), true);
	AddMeshToList(square2);

	Mesh* square2_top = Object2D::CreateRectangle("square2_top", corner, squareSide + 6, 20, glm::vec3(0, 0.5f, 0), true);
	AddMeshToList(square2_top);

	//aripa
	Mesh* square3 = Object2D::CreateRectangle("square3", corner, length_aripa,width_aripa, glm::vec3(0.5f, 0.5f, 0.5f), true);
	AddMeshToList(square3);
	
	//pipe2
	width4 = rand() % 300;
	width3 = 500 - width4;

	Mesh* square4_top = Object2D::CreateRectangle("square4_top", corner, squareSide + 6, 20, glm::vec3(0, 0.5f, 0), true);
	AddMeshToList(square4_top);

	Mesh* square5_top = Object2D::CreateRectangle("square5_top", corner, squareSide + 6, 20, glm::vec3(0, 0.5f, 0), true);
	AddMeshToList(square5_top);

	Mesh* square4 = Object2D::CreateRectangle("square4", corner, squareSide, width3, glm::vec3(0, 0.7f, 0), true);
	AddMeshToList(square4);

	Mesh* square5 = Object2D::CreateRectangle("square5", corner, squareSide, width4, glm::vec3(0, 0.7f, 0), true);
	AddMeshToList(square5);
	
	//pipe3
	width5 = rand() % 300;
	width6 = 500 - width5;
	
	Mesh* square6_top = Object2D::CreateRectangle("square6_top", corner, squareSide + 6, 20, glm::vec3(0, 0.5f, 0), true);
	AddMeshToList(square6_top);

	Mesh* square7_top = Object2D::CreateRectangle("square7_top", corner, squareSide + 6, 20, glm::vec3(0, 0.5f, 0), true);
	AddMeshToList(square7_top);

	Mesh* square6 = Object2D::CreateRectangle("square6", corner, squareSide, width5, glm::vec3(0, 0.7f, 0), true);
	AddMeshToList(square6);

	Mesh* square7 = Object2D::CreateRectangle("square7", corner, squareSide, width6, glm::vec3(0, 0.7f, 0), true);
	AddMeshToList(square7);

	//corpu
	Mesh* square8 = Object2D::CreateRectangle("square8", corner, length, width, glm::vec3(0.2f, 0.2f, 0.2f), true);
	AddMeshToList(square8);

	//capu
	Mesh *capu = Object2D::CreateCircle("capu", glm::vec3(168, 367, 0), radius, glm::vec3(1, 0, 0), true);
	AddMeshToList(capu);

	//cioc
	Mesh *cioc = Object2D::CreateTriangle("cioc", glm::vec3(168, 367, 0), length_cioc, glm::vec3(1, 0.5f, 0), true);
	AddMeshToList(cioc);

	//ochi
	Mesh *ochi = Object2D::CreateCircle2("ochi", glm::vec3(168, 367, 0), radius2, glm::vec3(1, 0, 0), true);
	AddMeshToList(ochi);


}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0.8f,1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{

	if (gameStop == true) {

		//pasarea
		if (falling == true) {

			ty -= deltaTimeSeconds * 500; // "Gravitatia" cu care trage pasarea spre pamant
			//ochiul
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(length - 2 * radius, ty - 360);
			RenderMesh2D(meshes["ochi"], shaders["VertexColor"], modelMatrix);
			
			//capul
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(length - 2*radius , ty  - 360);
			RenderMesh2D(meshes["capu"], shaders["VertexColor"], modelMatrix);
			/*Atunci cand pasarea cade (falling == true" atunci trebuie sa rotesc corpul pasarii
			in functie de centrul de greutate al corpului pasarii folosind Rotate*/
			//corpul
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(150, ty);
			modelMatrix *= Transform2D::Rotate(1.75);
			modelMatrix *= Transform2D::Translate(width / 2, -length - 10);
			RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);

			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(150, ty);
			modelMatrix *= Transform2D::Rotate(1.75);
			modelMatrix *= Transform2D::Translate(width/2,-length - 10);
			RenderMesh2D(meshes["square8"], shaders["VertexColor"], modelMatrix);
			
			 // ciok
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(length - 2 * radius, ty - 360- 2*radius + 5);
			RenderMesh2D(meshes["cioc"], shaders["VertexColor"], modelMatrix);
		}
		else {
			//W apasat
			ty -= deltaTimeSeconds * 300;   // aici pasarea sare (bataia aripii anuleaza forta de gravitatie si aceasta urca)
			/*Am reprezentat aripile cu un patrat care se rotesc in jos atunci cand
			pasarea da din ele si urca*/	
			//aripile
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(150, ty);
			modelMatrix *= Transform2D::Rotate(-1.75f);
			modelMatrix *= Transform2D::Translate(0,width);
			RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);
			//ochi
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(length - radius, ty - width / 2 + 2 * radius - 360);
			RenderMesh2D(meshes["ochi"], shaders["VertexColor"], modelMatrix);
			//capu
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(length - radius, ty - width / 2 + 2 * radius - 360);
			RenderMesh2D(meshes["capu"], shaders["VertexColor"], modelMatrix);
			/*Cand pasarea urca, corpul se indreapta, deci nu trebuie rotit*/
			//ciok
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(length - 9, ty - width / 2 + 2 * radius - 360 - 15);
			RenderMesh2D(meshes["cioc"], shaders["VertexColor"], modelMatrix);
			//corpu
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(150, ty);
			RenderMesh2D(meshes["square8"], shaders["VertexColor"], modelMatrix);
		}
		/*Aici verific daca pasarea a cazut din ecran sau a urcat prea sus
		daca urca prea sus si se loveste de "tavan", este game over
		de asemenea, daca coboara pana jos, este game over
		La fiecare game over pe parcursul codului, afisez scorul.*/
		if (ty < 0 || ty > (720 - width)) {  
			gameStop = false;
			if (scor == 0 || scor == 1)
				cout << "Scorul dumneavoastra este:" << scor << "\n";
			else {
				scor--;
				cout << "Scorul dumneavoastra este:" << scor << "\n";
			}
			scor = 0;
		}
		/*Am ales sa creez 3 perechi de stalpi, cu aceeasi distanta intre ei.
		Generez primul stalp de inaltime aleatorie, iar apoi generez si pe cel de-al doilea stalp
		de jos in sus, in functie de primul stalp*/
		//1	pillar
		/*Verific coliziunile
		Daca pozitia pasarii pe axa OX (+ lungimea corpului si raza cercului) se intersecteaza
		cu pozitia vreunui stalp, atunci este game over.
		De asemenea, procedez la fel si cu axa OY, verificand daca pasarea este situata in intervalul
		format din cei doi stalpi. M-am asigurat ca pasarea are destul loc sa treaca printre stalpi
		si am modificat viteza de urcare si coborare a pasarii astfel incat jocul sa fie dificil.
		Dificultatea se poate creste sau scadea modificand viteza cu care aceasta coboara sau urca pe OY*/
		if (((translate1X < (150 + length + 2*radius)) && (tx < (translate1X + squareSide))) 
			&& ((ty + width) > (720 - widthh) || ty < width2)) {
			gameStop = false;
			if (scor > 1)
			scor--; 
			cout << "Scorul dumneavoastra este:" << scor << "\n";
			scor = 0;
		}
		if (translate1X > 150 - length) {
			translate1X -= deltaTimeSeconds * 200;
		}
		/*In situatia in care pasarea trece de o pereche de stalpi, atunci scorul creste, si stalpii sunt
		mutati la inceputul ecranului, cu ale lungimii diferite fata de cele initiale. Astfel, se vor genera la infinit 
		stalpi de lungime random, pastrand totusi distanta dintre stalpi constanta*/
		else {
			translate1X += 1280;
			scor++;
			widthh = rand() % 300;
			width2 = 500 - widthh;
			meshes["square1"] = Object2D::CreateRectangle("square1", corner, squareSide, widthh, glm::vec3(0, 0.7f, 0), true);
			meshes["square2"] = Object2D::CreateRectangle("square2", corner, squareSide, width2, glm::vec3(0, 0.7f, 0), true);
		}
		/*Aici imi creez stalpii, incercand o tentativa de a-i face asemanatori cu cei din jocul original.
		Peste cei doi stalpi pe care i-am gandit initial, mai fac o alta pereche de dreptunghiuri, pe care o translatez
		peste perechea initiala, o pereche de dreptunghiuri care are o lungime mult mai mica decat cele 2 dreptunghiuri initiale,
		lungime care este constanta, si o latime putin mai mare decat cele doua dreptunghiuri initiale. Astfel, creez efectul
		ca cele doua dreptunghiuri creeate sunt "intrarea" in tevile faimoase din jocul mario. Acestea au de asemenea o culoare diferita
		fata de baza tevii, pentru estetic*/
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(translate1X - 3, (720 - widthh - 20));
		RenderMesh2D(meshes["square1_top"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(translate1X - 3, (width2 - 20));
		RenderMesh2D(meshes["square2_top"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(translate1X, (720 - widthh));
		RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(translate1X, 0);
		RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

		/*Repet acelasi "algoritm" pentru fiecare pereche de tevi*/
		////2 pillar
		if (((translate2X < (150 + length + 2*radius)) && tx < (translate2X + squareSide))
			&& ((ty + width) > (720 - width3) || ty < width4)) {
			gameStop = false;
			if (scor > 1)
			scor--;
			cout << "Scorul dumneavoastra este:" << scor << "\n";
			scor = 0;
		}
		if (translate2X > 150 - length) {
			translate2X -= deltaTimeSeconds * 200;
		}
		else {
			translate2X += 1280;
			scor++;
			width4 = rand() % 300;
			width3 = 500 - width4;
			meshes["square4"] = Object2D::CreateRectangle("square1", corner, squareSide, width3, glm::vec3(0, 0.7f, 0), true);
			meshes["square5"] = Object2D::CreateRectangle("square2", corner, squareSide, width4, glm::vec3(0, 0.7f, 0), true);
		}
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(translate2X - 3, (720 - width3 - 20));
		RenderMesh2D(meshes["square4_top"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(translate2X - 3, (width4 - 20));
		RenderMesh2D(meshes["square5_top"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(translate2X, (720 - width3));
		RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(translate2X, 0);
		RenderMesh2D(meshes["square5"], shaders["VertexColor"], modelMatrix);

		//3 pillar
		if (((translate3X < (150 + length + 2*radius)) && tx < (translate3X + squareSide))
			&& ((ty + width) >(720 - width5) || ty < width6)) {
			gameStop = false;
			scor--;
			cout << "Scorul dumneavoastra este:" << scor<<"\n";
			scor = 0;
		}
		if (translate3X > 150 - length) {
			translate3X -= deltaTimeSeconds * 200;
		}
		else {
			translate3X += 1280;
			scor++;
			width5 = rand() % 300;
			width6 = 500 - width5;
			meshes["square6"] = Object2D::CreateRectangle("square1", corner, squareSide, width5, glm::vec3(0, 0.7f, 0), true);
			meshes["square7"] = Object2D::CreateRectangle("square2", corner, squareSide, width6, glm::vec3(0, 0.7f, 0), true);
		}
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(translate3X - 3, (720 - width5 - 20));
		RenderMesh2D(meshes["square6_top"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(translate3X - 3, (width6 - 20));
		RenderMesh2D(meshes["square7_top"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(translate3X, (720 - width5));
		RenderMesh2D(meshes["square6"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(translate3X, 0);
		RenderMesh2D(meshes["square7"], shaders["VertexColor"], modelMatrix);


	
	}
	
}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTimeSeconds, int mods)
{
	/*Daca am apasat tasta SPACE, pasarea incepe sa urce
	cand butonul SPACE nu mai este apasat, atunci pasarea cade.
	Salvez starea pasarii (cadere/urcar) in vareabila de tip bool "falling"*/
	if (window->KeyHold(GLFW_KEY_SPACE)) {
		ty += 1200 * deltaTimeSeconds;
		falling = false;

	}
	else
		falling = true;
}
void Tema1::OnKeyPress(int key, int mods)
{	
	/*Am ales de asemenea ca atunci cand este apasat butonul space, sa rulez sunetul din jocul Mario
	pentru "jump"*/
	if (window->KeyHold(GLFW_KEY_SPACE)) {
		PlaySound(TEXT("smb.wav.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
	//Daca este apasata tasta N atunci jocul o ia de la inceput.
	//In situatia de GAME OVER si START GAME de asemenea trebuie apasat butonul N
	if (key == GLFW_KEY_N) {
		Init();
	}

	
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
