//
// Created by Maxime Boucher on 21/06/2024.
//
#include "XorMethod.hpp"

XorMethod::XorMethod() {
	method = Method::XOR;
}

std::string XorMethod::encrypt(std::string data, std::string key) {
	std::string encryptedData;
	for (int i = 0; i < data.size(); i++) {
		encryptedData += data[i] ^ key[i % key.size()];
	}
	return encryptedData;
}

std::string XorMethod::decrypt(std::string data, std::string key) {
	return encrypt(data, key); // XOR is its own inverse
}
