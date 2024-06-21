//
// Created by Maxime Boucher on 21/06/2024.
//
#ifndef SHOWCASE_QT_ICRYPTOMETHOD_HPP
#define SHOWCASE_QT_ICRYPTOMETHOD_HPP


#include <string>

class ICryptoMethod {
public:
	enum class Method {
		UNDEFINED,
		XOR,
	};

protected:
	Method method = Method::UNDEFINED;

public:
	virtual ~ICryptoMethod() = default;

	/**
	 * Returns the method
	 * @return
	 */
	Method getMethod();

	/**
	 * Encrypts the data
	 * @param data
	 * @param key
	 * @return
	 */
	virtual std::string encrypt(std::string data, std::string key) = 0;

	/**
	 * Decrypts the data
	 * @param data
	 * @param key
	 * @return
	 */
	virtual std::string decrypt(std::string data, std::string key) = 0;

};


#endif //SHOWCASE_QT_ICRYPTOMETHOD_HPP
