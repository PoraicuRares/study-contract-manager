#pragma once
#include "disciplina.h"
#include "exceptii.h"
class ValidatorDisciplina {
public:	
	//valideaza o disciplina 
	void valideaza(const Disciplina& d) {
		std::string erori = "";
		if (d.getCadruDidactic() == "") erori += "Cadru didactic invalid\n";
		if (d.getDenumire() == "") erori += "Denumire invalida\n";
		if (d.getOrePeSapt() <= 0) erori += "Nr de ore pe sapt invalid\n";
		if (d.getTip() == "") erori += "Tip invalid\n";
		if (erori != "")
			throw ValidatorException(erori);
	}
};