#include <vector>
#include "disciplina.h"
using std::vector;
class Contract {
private:
	vector<Disciplina> discipline;
public:
	//Constructor
	Contract() = default;

	//Goleste un contract de studii
	void golesteContract() noexcept{	
		discipline.clear();
	}
	//Adauga o disciplina in contractul de studii
	void adaugaDisciplina(const Disciplina& d) {
		discipline.push_back(d);
	}

	//Returneaza contractul de studii
	const vector<Disciplina>& getContract() const noexcept{
		return discipline;
	}

};