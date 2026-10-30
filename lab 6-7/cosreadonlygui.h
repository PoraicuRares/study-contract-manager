#pragma once
#include <qwidget.h>
#include <observer.h>
#include "service.h"
class CosReadOnlyGUI : public QWidget, public Observer {
private:
	ServiceDiscipline& srv;
public:
	/*
	* Constructorul clasei CosReadOnlyGUI
	*/
	CosReadOnlyGUI(ServiceDiscipline& srv);
	/*
	* Destructorul clasei CosReadOnlyGUI
	*/
	~CosReadOnlyGUI();

	/*
	* Redeseneaza tot
	*/
	void update() override;
protected:
	/*
	* Deseneaza figurile geometrice random
	*/
	void paintEvent(QPaintEvent* ev) override;
};