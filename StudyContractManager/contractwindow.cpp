#include "contractwindow.h"
#include <QtWidgets/qvboxlayout>
#include <QtWidgets/qhboxlayout>
#include <qinputdialog.h>
#include <qmessagebox.h>
ContractWindow::ContractWindow(ServiceDiscipline& srv) : srv{ srv } {
	srv.addObserver(this);
	initGui();
	loadData();
	initConnect();
}

ContractWindow::~ContractWindow() {
	srv.removeObserver(this);
}

void ContractWindow::initGui() {
	setWindowTitle("Contracte de studii");
	auto mainLy = new QVBoxLayout;
	setLayout(mainLy);
	mainLy->addWidget(contract);
	auto btnLy = new QHBoxLayout;
	btnLy->addWidget(btnGoleste);
	btnLy->addWidget(btnGenereaza);
	btnLy->addWidget(btnExport);
	mainLy->addLayout(btnLy);
}

void ContractWindow::loadData() {
	contract->clear();
	for (const auto& d : srv.getContractService()) {
		contract->addItem(QString::fromStdString(d.getDenumire()));
	}
}

void ContractWindow::update() {
	loadData();
}

void ContractWindow::initConnect() {
	QObject::connect(btnGoleste, &QPushButton::clicked, this, [&]() {
		srv.golesteContractStudii();
		loadData();
		});

	QObject::connect(btnGenereaza, &QPushButton::clicked, this, [&]() {
		bool ok;
		QString txt = QInputDialog::getText(this, "Generare", "Dati numarul de discipline care sa le contina contractul dupa generare:",QLineEdit::Normal,"",&ok);
		if (ok && !txt.isEmpty()) {
			int nr = txt.toInt();
			try {
				srv.genereazaContract(nr);
				loadData();
			}
			catch (const RepoException& re) {
				QMessageBox::information(this, "Eroare", QString::fromStdString(re.getMesaj()));
			}
			
		}
		});

	QObject::connect(btnExport, &QPushButton::clicked, this, [&]() {
		bool ok;
		QString txt = QInputDialog::getText(this, "Export", "Dati numele fisierului unde se exporta contractul", QLineEdit::Normal, "", &ok);
		if (ok && !txt.isEmpty()) {
			srv.exportaContractFisier(txt.toStdString());
		}
		});

}