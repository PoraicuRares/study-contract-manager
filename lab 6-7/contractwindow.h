#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qpushbutton.h>
#include "service.h"
class ContractWindow :public QWidget ,public Observer {
private:
	ServiceDiscipline& srv;
	
	QListWidget* contract = new QListWidget;
	QPushButton* btnGoleste = new QPushButton("Goleste contract");
	QPushButton* btnGenereaza = new QPushButton("Genereaza contract");
	QPushButton* btnExport = new QPushButton("Exporta contractul");

	void initGui();
	void loadData();
	void initConnect();
public:
	ContractWindow(ServiceDiscipline& srv);
	~ContractWindow();
	void update() override;
};
