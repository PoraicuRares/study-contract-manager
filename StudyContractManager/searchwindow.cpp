#include "searchwindow.h"
#include <QtWidgets/qmessagebox.h>
SearchWindow::SearchWindow(ServiceDiscipline& srv, QListWidget* l) : srv{ srv }, listaDiscipline{l} {
	initGui();
	initConnect();
}

void SearchWindow::initGui() {
	this->setWindowTitle("Cauta disciplina");
	auto ly = new QHBoxLayout;
	this->setLayout(ly);

	ly->addWidget(new QLabel("Introdu denumirea:"));
	ly->addWidget(txtCauta);
	ly->addWidget(btn);
}

void SearchWindow::initConnect() {
	QObject::connect(btn, &QPushButton::clicked, this, [this]() {
		std::string denumire = txtCauta->text().toStdString();
		try {
			Disciplina d = srv.search(denumire);
			auto element = listaDiscipline->findItems(QString::fromStdString(denumire), Qt::MatchExactly);
			if (!element.isEmpty()) {
				listaDiscipline->clearSelection();
				element.at(0)->setSelected(true);
				this->close();
			}
		}
		catch (const RepoException& re) {
			QMessageBox::information(this, "Eroare", "Disciplina nu este in lista!");
			(void)re;
		}
		});
}