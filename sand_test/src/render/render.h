#pragma once
#include <GLFW/glfw3.h>



typedef struct window_data {
	GLFWwindow* window;
	int initial_width;
	int initial_height;
	const char* title;
} WindowData;

void render_init(WindowData*, int, int, const char*);
void render_begin(WindowData*);
void render_end(WindowData*);

typedef struct shader_program {
	unsigned int program;
	unsigned int vertex_shader;
	unsigned int fragment_shader;
} ShaderProgram;

void render_shader_init(ShaderProgram*, const char*, const char*);