#pragma once
#include <GLFW/glfw3.h>

#define RENDER_GENERAL_INIT_ERROR "Failed to initialize %s.\n"

typedef struct window_data WindowData;

GLFWwindow* render_window_init(WindowData*);
void render_frame_buffer_size_callback(GLFWwindow*, int, int);

unsigned int render_load_shader(const char*, GLenum type);