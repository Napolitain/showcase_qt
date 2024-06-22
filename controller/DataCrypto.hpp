//
// Created by Maxime Boucher on 21/06/2024.
//
#ifndef SHOWCASE_QT_DATACRYPTO_HPP
#define SHOWCASE_QT_DATACRYPTO_HPP


#include <string>
#include "../model/Data/IData.hpp"
#include "../model/CryptoMethods/ICryptoMethod.hpp"
#include <memory>

class DataCrypto {
	std::string key;
	// That data could be text, image, etc. Its interface will streamline data processing.
	std::unique_ptr<IData> data;
	std::string encryptedData;
	// This is a pointer to an interface, so we need to use a smart pointer.
	// It will be used to change easily the encryption method.
	std::unique_ptr<ICryptoMethod> cryptoMethod;

	// Internal methods to update the encrypted data, used by the controller methods
	void setKey(std::string key);
	void setData(std::unique_ptr<IData> data);
	void setCryptoMethod(std::unique_ptr<ICryptoMethod> cryptoMethod);
	void setEncryptedData();
	void guardUpdate();
	void update();

public:
	// Controller methods accessible from the view
	void keyUpdated(std::string key);
	void dataUpdated(std::unique_ptr<IData> data);
	void cryptoMethodUpdated(std::unique_ptr<ICryptoMethod> cryptoMethod);
	std::string getEncryptedData();
};


#endif //SHOWCASE_QT_DATACRYPTO_HPP
