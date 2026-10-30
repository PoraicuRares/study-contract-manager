#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include "service.h"
class SearchWindow : public QWidget {
private:
	ServiceDiscipline& srv;
	QListWidget* listaDiscipline;

	QLineEdit* txtCauta = new QLineEdit;
	QPushButton* btn = new QPushButton("Cauta");
	void initGui();
	void initConnect();
public:
	SearchWindow(ServiceDiscipline&srv , QListWidget* l );
};