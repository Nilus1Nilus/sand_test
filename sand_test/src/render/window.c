#include <glad/glad.h>
#include "render/window.h"
#include "util/util.h"


void render_window_data_init(
	WindowData* window_data,
	unsigned int initial_width,
	unsigned int initial_height,
	const char* title
) {
	window_data->initial_width = initial_width;
	window_data->initial_height = initial_height;
	window_data->title = title;
	window_data->glfw_window = NULL;
}


void render_window_init(WindowData* window_data) {
	if (!glfwInit()) {
		ERROR_EXIT("Failed to initialize glfw.\n");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window_data->glfw_window = glfwCreateWindow(
		window_data->initial_width,
		window_data->initial_height,
		window_data->title,
		NULL,
		NULL
	);
	if (window_data->glfw_window == NULL) {
		ERROR_EXIT("Failed to create glfw window.\n");
	}

	unsigned int x_pos, y_pos;
	const GLFWvidmode* video_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	x_pos = (int)(video_mode->width / 2 - window_data->initial_width / 2);
	y_pos = (int)(video_mode->height / 2 - window_data->initial_height / 2);
	glfwSetWindowPos(window_data->glfw_window, x_pos, y_pos);

	glfwMakeContextCurrent(window_data->glfw_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		ERROR_EXIT("Failed to initialize glad.\n");
	}

	glViewport(0, 0, window_data->initial_width, window_data->initial_height);
	glfwSetFramebufferSizeCallback(window_data->glfw_window, render_window_framebuffer_size_callback);
}


void render_window_framebuffer_size_callback(GLFWwindow* glfw_window, int width, int height) {
	glViewport(0, 0, width, height);
}