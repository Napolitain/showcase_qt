//
// Created by Maxime Boucher on 21/06/2024.
//
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QComboBox>
#include "CryptoAnalysisView.hpp"
#include "../model/Data/TextData.hpp"
#include "../model/CryptoMethods/XorMethod.hpp"
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <iostream>

CryptoAnalysisView::CryptoAnalysisView(QMainWindow &mainWindow) {
	// Requirements :
	auto layout = new QGridLayout();

	// - A text field for the key input (full length with some margin, which we can type in).
	auto keyInput = new QTextEdit();
	keyInput->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
	keyInput->setContentsMargins(100, 100, 100, 100);
	keyInput->show();

	// - A text field for the data input (full length with some margin, which we can type in).
	auto dataInput = new QTextEdit(&mainWindow);
	dataInput->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	dataInput->setContentsMargins(100, 100, 100, 100);
	dataInput->setMinimumHeight(Constants::WINDOW_HEIGHT / 2 - 200);
	dataInput->show();

	// - A text field for the encrypted data output (full length with some margin, which we can't type in).
	auto encryptedDataOutput = new QTextEdit(&mainWindow);
	encryptedDataOutput->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	encryptedDataOutput->setContentsMargins(100, 100, 100, 100);
	encryptedDataOutput->setMinimumHeight(Constants::WINDOW_HEIGHT / 2 - 200);
	encryptedDataOutput->setReadOnly(true);
	encryptedDataOutput->show();

	// - A selector of encryption methods (a dropdown list with the available methods).
	auto methodSelector = new QComboBox();
	methodSelector->addItem("None");
	methodSelector->addItem("XOR");
	methodSelector->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	methodSelector->setContentsMargins(100, 100, 100, 100);
	methodSelector->show();

	// Graphs :
	// - Entropy of the data, with the entropy of the data.
	QLabel *entropyData = new QLabel("Entropy of the data: ");
	entropyData->show();

	// - Entropy of the encrypted data, with the entropy of the data.
	QLabel *entropyEncryptedData = new QLabel("Entropy of the encrypted data: ");
	entropyEncryptedData->show();

	std::unordered_map<char, int> dataHistogram;
	std::unordered_map<char, int> encryptedDataHistogram;
	for (int i = 0; i < 256; ++i) {
		dataHistogram[i] = 0;
		encryptedDataHistogram[i] = 0;
	}
	// - Histogram of the data, with the frequency of each character.


	// - Histogram of the encrypted data, with the frequency of each character.

	layout->addWidget(keyInput, 0, 0);
	layout->addWidget(methodSelector, 1, 0);
	layout->addWidget(dataInput, 2, 0);
	layout->addWidget(encryptedDataOutput, 3, 0);
	layout->addWidget(entropyData, 0, 1);
	layout->addWidget(entropyEncryptedData, 1, 1);

	auto centralWidget = new QWidget();
	centralWidget->setLayout(layout);
	mainWindow.setCentralWidget(centralWidget);

	// Events :
	// - When the key input is modified, the key is updated in the model and the encrypted data is updated, using async processing.
	keyInput->connect(keyInput, &QTextEdit::textChanged, [this, keyInput, entropyEncryptedData, encryptedDataOutput]() {
		try {
			dataCrypto.keyUpdated(keyInput->toPlainText().toStdString());
		} catch (const std::runtime_error &e) {
			return;
		}
		encryptedDataOutput->setText(QString::fromStdString(dataCrypto.getEncryptedData()));
		entropyEncryptedData->setText(QString::fromStdString("Entropy of the encrypted data: " + std::to_string(dataCrypto.getEncryptedDataEntropy())));
	});
	// - Opening a text file as a key file.
	auto menuBar = mainWindow.menuBar();
	QMenu *fileMenu = menuBar->addMenu("File");
	fileMenu->addAction("Open key file", [this, &mainWindow, keyInput]() {
		QString fileName = QFileDialog::getOpenFileName(&mainWindow, "Open key file", "", "Text Files (*.txt)");
		if (!fileName.isEmpty()) {
			QFile file(fileName);
			if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
				QTextStream in(&file);
				keyInput->setText(in.readAll());
				file.close();
			}
		}
	});

	// - When the data input is modified, the data is updated in the model and the encrypted data is updated, using async processing.
	dataInput->connect(dataInput, &QTextEdit::textChanged, [this, entropyData, entropyEncryptedData, dataInput, encryptedDataOutput]() {
		try {
			auto textData = std::make_unique<TextData>(dataInput->toPlainText().toStdString());
			dataCrypto.dataUpdated(std::move(textData));
		} catch (const std::runtime_error &e) {
			return;
		}
		encryptedDataOutput->setText(QString::fromStdString(dataCrypto.getEncryptedData()));
		entropyData->setText(QString::fromStdString("Entropy of the data: " + std::to_string(dataCrypto.getEntropy())));
		entropyEncryptedData->setText(QString::fromStdString("Entropy of the encrypted data: " + std::to_string(dataCrypto.getEncryptedDataEntropy())));
	});
	// - Opening a text file as a data file.
	fileMenu->addAction("Open data file", [this, &mainWindow, dataInput]() {
		QString fileName = QFileDialog::getOpenFileName(&mainWindow, "Open data file", "", "Text Files (*.txt)");
		if (!fileName.isEmpty()) {
			QFile file(fileName);
			if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
				QTextStream in(&file);
				dataInput->setText(in.readAll());
				file.close();
			}
		}
	});

	// - When the method selector is modified, the method is updated in the model and the encrypted data is updated, using async processing.
	methodSelector->connect(methodSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), [this, entropyData, entropyEncryptedData, encryptedDataOutput, methodSelector]() {
		try {
			auto method = methodSelector->currentText().toStdString();
			if (method == "XOR") {
				auto xorMethod = std::make_unique<XorMethod>();
				dataCrypto.cryptoMethodUpdated(std::move(xorMethod));
			} else {
				dataCrypto.cryptoMethodUpdated(nullptr);
			}
		} catch (const std::runtime_error &e) {
			return;
		}
		encryptedDataOutput->setText(QString::fromStdString(dataCrypto.getEncryptedData()));
		entropyData->setText(QString::fromStdString("Entropy of the data: " + std::to_string(dataCrypto.getEntropy())));
		entropyEncryptedData->setText(QString::fromStdString("Entropy of the encrypted data: " + std::to_string(dataCrypto.getEncryptedDataEntropy())));
	});

}
