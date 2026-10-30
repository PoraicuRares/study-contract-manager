#pragma once
#include "disciplina.h"
#include <vector>

using std::vector;

class RepoDiscipline {
private:

	vector<Disciplina> discipline;
public:
	RepoDiscipline() = default;
	void store(const Disciplina& d);
	void remove(const std::string& denumire);
	void update(const std::string & denumireVeche , const Disciplina& d);
	const Disciplina& find(const std::string& denumire) const;
	
	const vector<Disciplina> &  getAll() const noexcept ;

};