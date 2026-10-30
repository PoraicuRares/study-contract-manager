#pragma once
#include <qwidget.h>
#include <qtableview.h>
#include <qpushbutton.h>
#include "tablemodel.h"
#include "service.h"
#include "observer.h"
class CosCRUDGUI : public QWidget , public Observer{
private:
	ServiceDiscipline& srv;
	QTableView* tableView = new QTableView;
	QPushButton* btnGolire = new QPushButton("Golire cos");
	QPushButton* btnGenerare = new QPushButton("Generare cos");
	
	TableModel* model;
	/*
	* Initializeaza interfata grafica a ferestrei coscrudgui
	*/
	void initGUI();

	/*
	* Initializeaza semnalele 
	*/
	void connectSignals();
public:
	/*
	* Constructorul clasei CosCRUDGUI
	*/
	CosCRUDGUI(ServiceDiscipline& srv);
	/*
	* Destructorul clasei CosCRUDGUI
	*/
	~CosCRUDGUI();
	
	/*
	* Functia este apelata de observable
	*/
	void update() override;
};