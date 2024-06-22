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
	auto layout = new QVBoxLayout();

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

	layout->addWidget(keyInput);
	layout->addWidget(dataInput);
	layout->addWidget(encryptedDataOutput);
	layout->addWidget(methodSelector);

	auto centralWidget = new QWidget();
	centralWidget->setLayout(layout);
	mainWindow.setCentralWidget(centralWidget);

	// Events :
	// - When the key input is modified, the key is updated in the model and the encrypted data is updated, using async processing.
	keyInput->connect(keyInput, &QTextEdit::textChanged, [this, keyInput, dataInput, encryptedDataOutput]() {
		try {
			dataCrypto.keyUpdated(keyInput->toPlainText().toStdString());
		} catch (const std::runtime_error &e) {
			return;
		}
		encryptedDataOutput->setText(QString::fromStdString(dataCrypto.getEncryptedData()));
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
	dataInput->connect(dataInput, &QTextEdit::textChanged, [this, keyInput, dataInput, encryptedDataOutput]() {
		try {
			auto textData = std::make_unique<TextData>(dataInput->toPlainText().toStdString());
			dataCrypto.dataUpdated(std::move(textData));
		} catch (const std::runtime_error &e) {
			return;
		}
		encryptedDataOutput->setText(QString::fromStdString(dataCrypto.getEncryptedData()));
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
	methodSelector->connect(methodSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), [this, keyInput, dataInput, encryptedDataOutput, methodSelector]() {
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
	});

}
