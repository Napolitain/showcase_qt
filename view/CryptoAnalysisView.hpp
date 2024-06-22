/**
 * This is a view for showing basics crypto behaviors.
 * We can
 * - Set a key (from a text field, or a text file)
 * - Set a data (from a text field, or a text file, or an image file)
 * - Set a crypto method (from a list of available methods)
 * - Data is encrypted every time a key, data or crypto method is set, using async processing
 *
 * Because of that we have in our view :
 * - A text field for the key
 * - A text field for the data
 * - A list of open actions for the data, and the key in the menu bar
 */

#ifndef SHOWCASE_QT_CRYPTOANALYSISVIEW_HPP
#define SHOWCASE_QT_CRYPTOANALYSISVIEW_HPP


#include <QMainWindow>
#include "../controller/DataCrypto.hpp"
#include "Constants.hpp"

class CryptoAnalysisView {
	// Controller
	DataCrypto dataCrypto;

	// View elements

public:
	/**
	 * Because of that we have in our view :
	 * - A text field for the key
	 * - A text field for the data
	 * - A list of open actions for the data, and the key in the menu bar
	 * Those fields are included in the current MainWindow
	 */
	explicit CryptoAnalysisView(QMainWindow &mainWindow);

};


#endif //SHOWCASE_QT_CRYPTOANALYSISVIEW_HPP
