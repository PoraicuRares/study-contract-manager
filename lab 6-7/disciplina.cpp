#include "disciplina.h"

//constructor pentru o disciplina
Disciplina::Disciplina(const std::string& denumire, int orePeSapt, const std::string& tip, const std::string& cadruDidactic)
	: denumire{ denumire }, orePeSapt{ orePeSapt }, tip{ tip }, cadruDidactic{ cadruDidactic } {
}

//returneaza cadrul didactic al disciplinei
const std::string& Disciplina::getCadruDidactic() const noexcept{
	return cadruDidactic;
}

//returneaza denumirea disciplinei
const std::string& Disciplina::getDenumire()  const noexcept{
	return denumire;
}

//returneaza tipul disciplinei
const std::string& Disciplina::getTip() const noexcept{
	return tip;
}

//returneaza numarul de ore pe saptamana al disciplinei
int Disciplina::getOrePeSapt() const noexcept{
	return orePeSapt;
}	

//supraincarcarea operatorului <<
std::ostream& operator<<(std::ostream& os, const Disciplina& d) {
	os << "Denumirea : " << d.getDenumire() << " |Ore pe sapt : " << d.getOrePeSapt() << " |Tipul disciplinei : " << d.getTip() << " |Cadrul didactic : " << d.getCadruDidactic() << '\n';
	return os;
}