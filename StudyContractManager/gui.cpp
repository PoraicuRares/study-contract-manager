#include "gui.h"
#include "searchwindow.h"
#include "contractwindow.h"
#include "CosCRUDGui.h"
#include "cosreadonlygui.h"

Gui::Gui(ServiceDiscipline& srv) : srv(srv) {
	initGUI();
	loadData(srv.getAllService());
	initConnect();
}

void Gui::initGUI() {

	QHBoxLayout* mainLy = new QHBoxLayout;
	this->setLayout(mainLy);

	auto leftLy = new QVBoxLayout;
	leftLy->addWidget(disc);
	QHBoxLayout* btnLy = new QHBoxLayout;
	btnLy->addWidget(btnSortDen);
	btnLy->addWidget(btnSortOre);
	btnLy->addWidget(btnSortCadruTip);
	leftLy->addLayout(btnLy);
	mainLy->addLayout(leftLy);

	auto* btnLy3 = new QHBoxLayout;
	btnLy3->addWidget(btnFiltreazaCadru);
	btnLy3->addWidget(btnFiltreazaOre);
	leftLy->addLayout(btnLy3);


	QVBoxLayout* rightLy = new QVBoxLayout;
	QFormLayout* formLy = new QFormLayout;
	formLy->addRow("Denumire:", denumire);
	formLy->addRow("Nr ore pe saptamana :", nrOre);
	formLy->addRow("Tipul:", tip);
	formLy->addRow("Cadru didactic:", cadruDidactic);

	rightLy->addLayout(formLy);

	QHBoxLayout* btnLy1 = new QHBoxLayout;
	btnLy1->addWidget(btnAdd);
	btnLy1->addWidget(btnDelete);
	btnLy1->addWidget(btnModify);
	btnLy1->addWidget(btnUndo);
	rightLy->addLayout(btnLy1);

	QHBoxLayout* btnLy2 = new QHBoxLayout;
	btnLy2->addWidget(btnFind);
	btnLy2->addWidget(btnStatistica);
	btnLy2->addWidget(btnDeleteDuplicates);
	btnLy2->addWidget(btnExit);

	QHBoxLayout* btnLy4 = new QHBoxLayout;
	btnLy4->addWidget(btnAdaugaContract);
	btnLy4->addWidget(btnDeschideContract);
	
	auto btnLy5 = new QHBoxLayout;
	btnLy5->addWidget(btnDeschideCosCRUD);
	btnLy5->addWidget(btnDeschideCosReadOnly);

	rightLy->addLayout(btnLy2);
	rightLy->addLayout(btnLy4);
	rightLy->addLayout(btnLy5);
	mainLy->addLayout(rightLy);

}

void Gui::loadData(const vector<Disciplina>& discipline) {
	disc->clear();
	for (const auto& d : discipline) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(d.getDenumire()));
		if (d.getOrePeSapt() > 2)
			item->setForeground(QBrush(Qt::red));
		else
			item->setForeground(QBrush(Qt::green));
		disc->addItem(item);
	}
}

void Gui::initConnect() {
	QObject::connect(btnExit, &QPushButton::clicked, this, &QWidget::close);
	QObject::connect(btnAdd, &QPushButton::clicked, this, &Gui::adaugaGui);
	QObject::connect(btnDelete, &QPushButton::clicked, this, &Gui::stergeGui);
	QObject::connect(btnModify, &QPushButton::clicked, this, &Gui::modificaGui);
	QObject::connect(btnFind, &QPushButton::clicked, this, &Gui::gasesteGui);
	QObject::connect(disc, &QListWidget::itemSelectionChanged,this ,&Gui::umpleCamuri);
	QObject::connect(btnSortDen, &QPushButton::clicked, this, &Gui::sorteazaDupaDenumireGui);
	QObject::connect(btnSortOre, &QPushButton::clicked, this, &Gui::sorteazaDupaOreGui);
	QObject::connect(btnSortCadruTip, &QPushButton::clicked, this, &Gui::sorteazaDupaCadruTipGui);
	QObject::connect(btnDeleteDuplicates, &QPushButton::clicked, this, &Gui::stergeDuplicateGui);
	QObject::connect(btnUndo, &QPushButton::clicked, this, &Gui::undoGui);
	QObject::connect(btnFiltreazaOre, &QPushButton::clicked, this, &Gui::filtreazaDupaOreGui);
	QObject::connect(btnFiltreazaCadru, &QPushButton::clicked, this, &Gui::filtreazaDupaCadruGui);
	QObject::connect(btnStatistica, &QPushButton::clicked, this, &Gui::statisticaDupaTipGui);
	QObject::connect(btnDeschideContract, &QPushButton::clicked, this, &Gui::deschideContractGui);
	QObject::connect(btnAdaugaContract, &QPushButton::clicked, this, &Gui::adaugaContractGui);
	QObject::connect(btnDeschideCosCRUD, &QPushButton::clicked, this, &Gui::deschideCosCRUD);
	QObject::connect(btnDeschideCosReadOnly, &QPushButton::clicked, this, &Gui::deschideCosReadOnly);
}

//conexiuni

void Gui::adaugaGui() {
	try {
		std::string denumireStr = denumire->text().toStdString();
		const int nrOreInt = nrOre->text().toInt();
		std::string tipStr = tip->text().toStdString();
		std::string cadruDidacticStr = cadruDidactic->text().toStdString();
		srv.add(denumireStr, nrOreInt, tipStr, cadruDidacticStr);
		loadData(srv.getAllService());
		denumire->clear();
		nrOre->clear();
		tip->clear();
		cadruDidactic->clear();
	}
	catch (const ValidatorException& ve) {
		QMessageBox::information(this, "Eroare de validare!", QString::fromStdString(ve.getMesaje()));
	}
	catch (const RepoException& re) {
		QMessageBox::information(this, "Eroare de stocare!", QString::fromStdString(re.getMesaj()));
	}
}

void Gui::stergeGui() {
	try {
		if (disc->selectedItems().isEmpty()) {
			QMessageBox::information(this, "Eroare", "Selecteaza o disciplina din lista inainte sa stergi!");
			return;
		}
		std::string denumireStr = disc->selectedItems().at(0)->text().toStdString();
		srv.remove(denumireStr);
		loadData(srv.getAllService());
	}
	catch (const RepoException& re) {
		QMessageBox::information(this, "Eroare", QString::fromStdString(re.getMesaj()));
	}
}

void Gui::modificaGui() {
	try {
		if (disc->selectedItems().isEmpty()) {
			QMessageBox::information(this, "Info", "Selecteaza o disciplina din lista inainte sa modifici!");
			return;
		}
		std::string denumireVeche = disc->selectedItems().at(0)->text().toStdString();
		std::string denumireNoua = denumire->text().toStdString();
		int nrOreInt = nrOre->text().toInt();
		std::string tipStr = tip->text().toStdString();
		std::string cadruStr = cadruDidactic->text().toStdString();
		srv.modify(denumireVeche, denumireNoua, nrOreInt, tipStr, cadruStr);
		loadData(srv.getAllService());
	}
	catch (const ValidatorException& ve) {
		QMessageBox::information(this, "Eroare de validare!", QString::fromStdString(ve.getMesaje()));
	}
	catch (const RepoException& re) {
		QMessageBox::information(this, "Eroare", QString::fromStdString(re.getMesaj()));
	}
}

void Gui::umpleCamuri() {
	if (disc->selectedItems().isEmpty()) {
		denumire->clear();
		nrOre->clear();
		tip->clear();
		cadruDidactic->clear();
		return;
	}
	auto disciplinaSelectata = srv.search(disc->selectedItems().at(0)->text().toStdString());
	denumire->setText(QString::fromStdString(disciplinaSelectata.getDenumire()));
	nrOre->setText(QString::number(disciplinaSelectata.getOrePeSapt()));
	tip->setText(QString::fromStdString(disciplinaSelectata.getTip()));
	cadruDidactic->setText(QString::fromStdString(disciplinaSelectata.getCadruDidactic()));
}

void Gui::gasesteGui() {
	auto w = new SearchWindow(srv, disc);
	w->show();
}

void Gui::sorteazaDupaDenumireGui() {
	loadData(srv.sorteazaDupaDenumire());
}

void Gui::sorteazaDupaOreGui() {
	loadData(srv.sorteazaDupaOre());
}

void Gui::sorteazaDupaCadruTipGui() {
	loadData(srv.sorteazaDupaCadruTip());
}

void Gui::stergeDuplicateGui() {
	srv.stergeDuplicate();
	loadData(srv.getAllService());
}

void Gui::undoGui() {
	try {
		srv.undo();
		loadData(srv.getAllService());
	}
	catch (const RepoException& re) {
		QMessageBox::information(this, "Eroare", QString::fromStdString(re.getMesaj()));
	}
	
}

void Gui::filtreazaDupaOreGui() {
	bool ok;
	QString txt = QInputDialog::getText(this, "Filtrare", "Dati numarul de ore dupa care se filtreaza:", QLineEdit::Normal, "", &ok);
	if (ok && !txt.isEmpty()) {
		auto filtrare = srv.filtreazaDupaOre(txt.toInt());
		loadData(filtrare);
	}
}

void Gui::filtreazaDupaCadruGui() {
	bool ok;
	QString txt = QInputDialog::getText(this, "Filtrare", "Dati cadrul didactic dupa care se filtreaza:", QLineEdit::Normal, "", &ok);
	if (ok && !txt.isEmpty()) {
		auto filtrare = srv.filtreazaDupaCadru(txt.toStdString());
		loadData(filtrare);
	}
}

void Gui::statisticaDupaTipGui() {
	bool ok;
	QString txt = QInputDialog::getText(this, "Statistica", "Dati tipul dupa care se face statistica", QLineEdit::Normal, "", &ok);
	if (ok && !txt.isEmpty()) {
		auto rez = srv.statisticaDupaTip(txt.toStdString());
		auto rezStr = std::to_string(rez);
		auto mesaj = "Tipul " + txt.toStdString() + " apare de " + rezStr +"%";
		QMessageBox::information(this, "Rezultat", QString::fromStdString(mesaj));
	}
}

void Gui::adaugaContractGui() {
	if (disc->selectedItems().isEmpty()) {
		QMessageBox::information(this, "Eroare", "Selecteaza o disicplina din lista pentru a fi adaugata in contract!");
		return;
	}
	try {
		std::string denumireStr = disc->selectedItems().at(0)->text().toStdString();
		srv.adaugaDisciplinaContract(denumireStr);
		QMessageBox::information(this, "Succes", "Disciplina a fost adaugata cu succes in contract");
		disc->clearSelection();
	}
	catch (const RepoException& re) {
		QMessageBox::information(this, "Eroare", QString::fromStdString(re.getMesaj()));
	}

}

void Gui::deschideContractGui() {
	auto w = new ContractWindow(srv);
	w->show();
	
}

void Gui::deschideCosCRUD(){
	auto* fereastraCRUD = new CosCRUDGUI(srv);
	fereastraCRUD->show();
}

void Gui::deschideCosReadOnly(){
	auto* fereastraReadOnly = new CosReadOnlyGUI(srv);
	fereastraReadOnly->show();
}
