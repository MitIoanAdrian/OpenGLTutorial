#pragma once

struct StbHelper{

	static unsigned char* stbi_helper_load(const char* file, int* width, int* height, int* channels,
        int desired_channels);

	static void stbi_helper_free(void* data);

};
