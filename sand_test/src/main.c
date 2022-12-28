#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include "render/window.h"
#include "io/file.h"

int main(void) {
	WindowData window_data;
	render_window_data_init(&window_data, 2000, 1500, "sand simulation");
	render_window_init(&window_data);

	char* test = io_file_read_file("res/hello_world.txt");
	printf("%s\n", test);
	free(test);

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