//
// Created by Maxime Boucher on 21/06/2024.
//
#ifndef SHOWCASE_QT_TEXTDATA_HPP
#define SHOWCASE_QT_TEXTDATA_HPP


#include <string>
#include "IData.hpp"

class TextData : public IData {
	std::string text;

public:
	TextData();
	explicit TextData(std::string text);
	~TextData() override = default;

	void setData(std::string data) override;

	std::string getData() override;

};


#endif //SHOWCASE_QT_TEXTDATA_HPP
