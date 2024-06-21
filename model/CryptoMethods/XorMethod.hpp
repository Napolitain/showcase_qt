//
// Created by Maxime Boucher on 21/06/2024.
//
#ifndef SHOWCASE_QT_XORMETHOD_HPP
#define SHOWCASE_QT_XORMETHOD_HPP


#include <string>
#include "ICryptoMethod.hpp"

class XorMethod : public ICryptoMethod {

public:
	XorMethod();

	/**
	 * Encrypts the data
	 * @param data
	 * @param key
	 * @return
	 */
	std::string encrypt(std::string data, std::string key) override;

	/**
	 * Decrypts the data
	 * @param data
	 * @param key
	 * @return
	 */
	std::string decrypt(std::string data, std::string key) override;

};


#endif //SHOWCASE_QT_XORMETHOD_HPP
