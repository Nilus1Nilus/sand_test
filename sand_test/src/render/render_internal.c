#include <glad/glad.h>
#include "util/util.h"
#include "render/render_internal.h"
#include "render/render.h"
#include "io/file/file.h"


GLFWwindow* render_window_init(WindowData* window_data) {
	if (!glfwInit()) { ERROR_RETURN(NULL, RENDER_GENERAL_INIT_ERROR, "glfw"); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(
		window_data->initial_width,
		window_data->initial_height,
		window_data->title,
		NULL,
		NULL
	);
	if (window == NULL) { ERROR_RETURN(NULL, RENDER_GENERAL_INIT_ERROR, "glfw window"); }
	
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { ERROR_RETURN(NULL, RENDER_GENERAL_INIT_ERROR, "glad"); }

	int x, y;
	const GLFWvidmode* video_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	x = video_mode->width / 2 - window_data->initial_width / 2;
	y = video_mode->height / 2 - window_data->initial_height / 2;
	glfwSetWindowPos(window, x, y);

	glViewport(0, 0, window_data->initial_width, window_data->initial_height);
	glfwSetFramebufferSizeCallback(window, render_frame_buffer_size_callback);

	return window;
}


void render_frame_buffer_size_callback(GLFWwindow* window, int width, int height) {
	printf("WINDOW_WIDTH: %d | WINDOW_HEIGHT: %d\n", width, height);
	glViewport(0, 0, width, height);
};


unsigned int render_load_shader(const char* path, GLenum type) {
	char* src = io_file_read_file(path);
	int success;
	char info_log[512];

	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, &info_log);
		ERROR_RETURN(NULL, "Failed to compile shader: %s\n", info_log);
	}

	free(src);
	return shader;
}