#include <glad/glad.h>
#include "render/window.h"

int main(void) {
	WindowData window_data;
	render_window_data_init(&window_data, 2000, 1500, "sand simulation");
	render_window_init(&window_data);

	while (!glfwWindowShouldClose(window_data.glfw_window)) {
		glfwPollEvents();

		glClearColor(0.5, 0.5, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window_data.glfw_window);
	}

	glfwDestroyWindow(window_data.glfw_window);
	glfwTerminate();
	return 0;
}