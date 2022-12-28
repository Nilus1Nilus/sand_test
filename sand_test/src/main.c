#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include "render/window.h"
#include "io/file.h"
#include "util/util.h"

float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};

int main(void) {
	WindowData window_data;
	render_window_data_init(&window_data, 1280, 720, "sand simulation");
	render_window_init(&window_data);

	int success;
	char info_log[512];

	unsigned int vertex_shader;
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	char* vertex_src = io_file_read_file("res/vertex.glsl");
	glShaderSource(vertex_shader, 1, &vertex_src, NULL);
	free(vertex_src);
	glCompileShader(vertex_shader);

	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
		ERROR_EXIT("Failed to compile shader: %s", info_log);
	}

	unsigned int fragment_shader;
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	char* fragment_src = io_file_read_file("res/fragment.glsl");
	glShaderSource(fragment_shader, 1, &fragment_src, NULL);
	free(fragment_src);
	glCompileShader(fragment_shader);

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
		ERROR_EXIT("Failed to compile shader: %s", info_log);
	}

	unsigned int shader_program;
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program, 512, NULL, info_log);
		ERROR_EXIT("Failed to create shader program: %s", info_log);
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window_data.glfw_window)) {
		glfwPollEvents();

		glClearColor(0.2, 0.3, 0.4, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader_program);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glUseProgram(0);
		glBindVertexArray(0);

		glfwSwapBuffers(window_data.glfw_window);
	}

	glfwDestroyWindow(window_data.glfw_window);
	glfwTerminate();
	return 0;
}