//
// Created by Maxime Boucher on 21/06/2024.
//
#include <memory>
#include <stdexcept>
#include <iostream>
#include "DataCrypto.hpp"

void DataCrypto::setKey(std::string key) {
	this->key = std::move(key);
}

void DataCrypto::setData(std::unique_ptr<IData> data) {
	this->data = std::move(data);
}

void DataCrypto::setCryptoMethod(std::unique_ptr<ICryptoMethod> cryptoMethod) {
	this->cryptoMethod = std::move(cryptoMethod);
}

std::string DataCrypto::getEncryptedData() {
	return cryptoMethod->encrypt(this->data->getData(), key);
}

void DataCrypto::setEncryptedData() {
	this->encryptedData = getEncryptedData();
}

void DataCrypto::guardUpdate() {
	if (key.empty() || data == nullptr || data->getType() == IData::Type::UNDEFINED || data->getData().empty() || cryptoMethod == nullptr || cryptoMethod->getMethod() == ICryptoMethod::Method::UNDEFINED) {
		throw std::runtime_error("Key, data and crypto method must be set before calling this method.");
	}
}

void DataCrypto::keyUpdated(std::string key) {
	setKey(std::move(key));

	update();
}

void DataCrypto::dataUpdated(std::unique_ptr<IData> data) {
	setData(std::move(data));

	update();
}

void DataCrypto::cryptoMethodUpdated(std::unique_ptr<ICryptoMethod> cryptoMethod) {
	setCryptoMethod(std::move(cryptoMethod));

	update();
}

void DataCrypto::update() {
	// Guard clause, throw an exception if the data is not ready to trigger the update
	guardUpdate();

	setEncryptedData();
}
