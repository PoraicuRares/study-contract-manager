#include <QtWidgets/QApplication>
#include "repository.h"
#include "service.h"
#include "teste.h"
#include "gui.h"

int main(int argc , char** argv)
{	
	QApplication a(argc, argv);
	RepoDiscipline repo;
	ValidatorDisciplina val;
	Contract con;
	ServiceDiscipline srv(repo, val , con);
	testAll();
	Gui gui(srv);
	gui.show();
	return a.exec();
}
	