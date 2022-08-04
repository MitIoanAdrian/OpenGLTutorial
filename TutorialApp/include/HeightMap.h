#pragma once

#include <iostream>
#include <array>

class HeightMap{
private:
	static const std::size_t m_TxtWidth = 2048;
	static const std::size_t m_TxtHeight = 2048;

    std::array <float, m_TxtWidth * m_TxtHeight> m_Height = {0};

	void readHeights(unsigned char* data, const short bytes_per_pixel);

public:
	HeightMap();

	bool load(const char* file);

	const std::size_t getWidth();
	const std::size_t getHeight();

	float getHeight(std::size_t x, std::size_t z); 

};
