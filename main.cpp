/**
 * This file is the main entry point for the application.
 * It creates a Qt 6 application.
 */

#include <QApplication>
#include <QWindow>
#include <QMainWindow>
#include <QLabel>
#include "view/CryptoAnalysisView.hpp"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	// Create the window
	QMainWindow window;
	window.resize(1920, 1080);  // Set window size

	// Set the window title
	window.setWindowTitle("Showcase Qt");

	// Show the window
	window.show();

	// Crypto analysis view
	CryptoAnalysisView cryptoAnalysisView(window);

	return QApplication::exec();
}
