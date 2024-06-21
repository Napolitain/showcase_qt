//
// Created by Maxime Boucher on 16/06/2024.
//

#ifndef SHOWCASE_QT_IMAGE_HPP
#define SHOWCASE_QT_IMAGE_HPP


#include "IData.hpp"

class Image : public IData {
	int width;
	int height;
	int channels;
	std::string data;

public:
	Image();
	~Image();

	void setData(std::string data) override;

	std::string getData() override;

};


#endif //SHOWCASE_QT_IMAGE_HPP
