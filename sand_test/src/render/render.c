#include <glad/glad.h>
#include "render/render.h"
#include "render/render_internal.h"
#include "io/file/file.h"
#include "util/util.h"

void render_init(WindowData* window_data, int initial_width, int initial_height, const char* title) {
	window_data->initial_width = initial_width;
	window_data->initial_height = initial_height;
	window_data->title = title;
	window_data->window = render_window_init(window_data);
}

void render_begin(WindowData* window_data) {
	glClearColor(0.1f, 0.3f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void render_end(WindowData* window_data) {
	glfwSwapBuffers(window_data->window);
}

void render_shader_init(ShaderProgram* shader_program, const char* vertex_path, const char* fragment_path) {
	shader_program->program = glCreateProgram();
	shader_program->vertex_shader = render_load_shader(vertex_path, GL_VERTEX_SHADER);
	shader_program->fragment_shader = render_load_shader(fragment_path, GL_FRAGMENT_SHADER);
	glAttachShader(shader_program->program, shader_program->vertex_shader);
	glAttachShader(shader_program->program, shader_program->fragment_shader);
	glLinkProgram(shader_program->program);
	
	int success;
	char info_log[512];
	glGetProgramiv(shader_program->program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program->program, 512, NULL, info_log);
		ERROR_EXIT("Failed to link shader program: %s\n", info_log);
	}
	glDeleteShader(shader_program->vertex_shader);
	glDeleteShader(shader_program->fragment_shader);
}