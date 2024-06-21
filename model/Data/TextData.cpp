//
// Created by Maxime Boucher on 21/06/2024.
//
#include "TextData.hpp"

#include <utility>

TextData::TextData() {
	text = "";
	type = Type::TEXT;
}

TextData::TextData(std::string text) {
	this->text = std::move(text);
	type = Type::TEXT;
}

void TextData::setData(std::string text) {
	this->text = std::move(text);
}

std::string TextData::getData() {
	return text;
}
