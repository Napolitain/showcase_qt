//
// Created by Maxime Boucher on 21/06/2024.
//
#ifndef SHOWCASE_QT_IDATA_HPP
#define SHOWCASE_QT_IDATA_HPP


#include <string>

class IData {
public:
	enum class Type {
		UNDEFINED,
		TEXT,
		IMAGE,
	};

protected:
	std::string data;
	Type type = Type::UNDEFINED;

public:
	virtual ~IData() = default;

	/**
	 * Returns the type
	 * @return
	 */
	Type getType();

	/**
	 * Sets the data
	 * @param data
	 */
	virtual void setData(std::string data) = 0;

	/**
	 * Returns the string representation of the data
	 * @return
	 */
	virtual std::string getData() = 0;

};


#endif //SHOWCASE_QT_IDATA_HPP
