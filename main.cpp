/**
 * This file is the main entry point for the application.
 * It creates a Qt 6 application.
 */

#include <QApplication>
#include <QWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMainWindow>
#include <QLabel>
#include <QFileDialog>
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

	// Create a menu bar
	auto menuBar = window.menuBar();
	QMenu *fileMenu = menuBar->addMenu("File");
	
	// Add actions to the menu
	// Open text file action
	fileMenu->addAction("Open Text File", [&]() {
		QString fileName = QFileDialog::getOpenFileName(&window, "Open Text File", "", "Text Files (*.txt)");
		if (!fileName.isEmpty()) {
			QFile file(fileName);
			if (file.open(QIODevice::ReadOnly)) {
				QByteArray data = file.readAll();
				auto label = new QLabel(QString::fromUtf8(data));
				window.setCentralWidget(label);
			}
		}
	});

	// Crypto analysis view
	CryptoAnalysisView cryptoAnalysisView(window);


	return QApplication::exec();
}
