#include "cosreadonlygui.h"
#include <qpainter.h>
#include <cstdlib>
CosReadOnlyGUI::CosReadOnlyGUI(ServiceDiscipline& srv) : srv(srv){
	srv.addObserver(this);
	this->setAttribute(Qt::WA_DeleteOnClose);
}

CosReadOnlyGUI::~CosReadOnlyGUI(){
	srv.removeObserver(this);

}

void CosReadOnlyGUI::update(){
	repaint();
}

void CosReadOnlyGUI::paintEvent(QPaintEvent * ev){
	(void)ev;
	QPainter p(this);
	int nrDisc = (int)srv.getContractService().size();
	for (int i = 0; i < nrDisc; ++i) {
		int x = rand() % width();
		int y = rand() % height();
		int diametru = 20 + rand() % 40;
		if (i % 2 == 0) {
			p.drawEllipse(x, y, diametru, diametru);
		}
		else {
			p.drawRect(x, y, diametru, diametru);
		}
	}
}
