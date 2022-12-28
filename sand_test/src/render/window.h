#pragma once

#include <GLFW/glfw3.h>

typedef struct window_data {
	GLFWwindow* glfw_window;
	unsigned int initial_width, initial_height;
	const char* title;
} WindowData;

void render_window_data_init(WindowData*, unsigned int, unsigned int, const char*);
void render_window_init(WindowData*);

void render_window_framebuffer_size_callback(GLFWwindow*, int, int);