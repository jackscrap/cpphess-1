#include <iostream>
#include <vector>

#include <SDL2/SDL.h>

#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 600;

int main() {
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");

	Vertex cubeVertices[] = {
		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 0), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(0, 0, -1)),

		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 1), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 1), glm::vec3(0, 0, 1)),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 1), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 1), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(0, 0), glm::vec3(0, -1, 0)),

		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(1, 1), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 0), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 1, 0)),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 1), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(-1, 0, 0)),

		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 0), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(1, 0, 0)),
	};

	unsigned int cubeIndices[] = {
		0, 1, 2,
		0, 2, 3,

		6, 5, 4,
		7, 6, 4,

		10, 9, 8,
		11, 10, 8,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		22, 21, 20,
		23, 22, 20
	};

	Mesh cube(
		cubeVertices,
		sizeof cubeVertices / sizeof *cubeVertices,
		cubeIndices,
		sizeof cubeIndices / sizeof *cubeIndices
	);

	Vertex boardVertices[] = {
		Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 1), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 1), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(0, 0), glm::vec3(0, -1, 0)),
	};

	unsigned int boardIndices[] = {
		0, 1, 2,
		0, 2, 3
	};

	Mesh board(
		boardVertices,
		sizeof boardVertices / sizeof *boardVertices,
		boardIndices,
		sizeof boardIndices / sizeof *boardIndices
	);

	Mesh piece[8];

	/* Mesh king("res/king.obj"); */
	/* Mesh cyoob("res/cube.obj"); */

	Shader shader("res/checker");
	Texture texture("res/bricks.jpg");
	Transform transform;
	Camera camera(
		glm::vec3(
			0.0f,
			1.0f,
			-5.0f
		),
		70.0f,
		(float) DISPLAY_WIDTH / (float) DISPLAY_HEIGHT,
		0.1f,
		100.0f
	);
	camera.Pitch(0.4);

	SDL_Event e;
	bool isRunning = true;
	float counter = 0.0f;
	while(isRunning) {
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT) {
				isRunning = false;
			}
		}

		display.Clear(0.6f, 0.6f, 0.6f, 0.3f);

		float
			sinCounter = sinf(counter),
			absSinCounter = abs(sinCounter);

		/* transform.GetScale()->x = 0.1; */
		/* transform.GetScale()->y = 0.1; */
		/* transform.GetScale()->z = 0.1; */

		shader.Bind();
		texture.Bind();
		shader.Update(transform, camera);

		board.Draw();

		for (
			int i = 0;
			i < sizeof piece / sizeof *piece;
			i++
		) {
			piece[i].Draw();

			transform.GetPos()->x = 0;
		}

		/* king.Draw(); */
		/* cyoob.Draw(); */
		/* cube.Draw(); */

		display.SwapBuffers();
		SDL_Delay(1);
	}

	return 0;
}
