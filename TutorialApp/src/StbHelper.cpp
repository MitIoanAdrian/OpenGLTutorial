#include "StbHelper.h"
#include "stb_image.h"

unsigned char* StbHelper::stbi_helper_load(const char* file, int* width, int* height, int* channels, int desired_channels){

	return stbi_load(file, width, height, channels, desired_channels);
}


void StbHelper::stbi_helper_free(void* data){
	stbi_image_free(data);
}
