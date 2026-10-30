#include "CosCRUDGui.h"
#include <qvboxlayout>
#include <qinputdialog.h>
#include <qhboxlayout>
#include <qmessagebox.h>

void CosCRUDGUI::initGUI(){
	auto mainLy = new QVBoxLayout;
	setLayout(mainLy);

	tableView->setModel(model);
	mainLy->addWidget(tableView);
	QHBoxLayout* btnLy = new QHBoxLayout;
	btnLy->addWidget(btnGolire);
	btnLy->addWidget(btnGenerare);
	mainLy->addLayout(btnLy);
}

void CosCRUDGUI::connectSignals(){
	QObject::connect(btnGolire, &QPushButton::clicked, this, [&]() {
		srv.golesteContractStudii();
		});

	QObject::connect(btnGenerare, &QPushButton::clicked, this, [&]() {
		bool ok;
		QString txt = QInputDialog::getText(this, "Generare", "Dati numarul de discipline care sa le contina contractul dupa generare:", QLineEdit::Normal, "", &ok);
		if (ok && !txt.isEmpty()) {
			int nr = txt.toInt();
			try {
				srv.genereazaContract(nr);
			}
			catch (const RepoException& re) {
				QMessageBox::information(this, "Eroare", QString::fromStdString(re.getMesaj()));
			}

		}
		});
}

CosCRUDGUI::CosCRUDGUI(ServiceDiscipline& srv) : srv(srv) {
	model = new TableModel(srv.getContractService());
	this->setAttribute(Qt::WA_DeleteOnClose);
	initGUI();
	srv.addObserver(this);
	connectSignals();
}

CosCRUDGUI::~CosCRUDGUI(){
	srv.removeObserver(this);
}

void CosCRUDGUI::update(){

	auto disciplineNoi = srv.getContractService();
	model->setDiscipline(disciplineNoi);
}
