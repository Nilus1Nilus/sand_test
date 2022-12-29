#include "render/render.h"

int main(void) {
	WindowData window_data;
	render_init(&window_data, 1280, 720, "title");

	ShaderProgram shader;
	render_shader_init(&shader, "res/vertex.glsl", "res/fragment.glsl");

	while (!glfwWindowShouldClose(window_data.window)) {
		glfwPollEvents();
		render_begin(&window_data);
		render_end(&window_data);
	}

	glfwTerminate();
	return 0;
}  