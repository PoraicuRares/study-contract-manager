#include "repository.h"
#include "exceptii.h"
#include <algorithm>

//adauga o disciplina in repo
void RepoDiscipline::store(const Disciplina& d) {
	const bool exista = std::any_of(discipline.begin(), discipline.end(),
		[&d](const Disciplina &disc) noexcept{
			return disc.getDenumire() == d.getDenumire();
		});
	if (exista)
		throw RepoException("Disciplina a fost adaugata deja!\n");
	discipline.push_back(d);
}

//sterge o disciplina din repo dupa denumire
void RepoDiscipline::remove(const std::string&  denumire) {
	auto it = std::find_if(discipline.begin(), discipline.end(),
		[&denumire](const Disciplina & d) noexcept{
			return d.getDenumire() == denumire;
		});
	if (it != discipline.end()) {
		discipline.erase(it);
	}
	else{
		throw RepoException("Disciplina cu acest nume nu exista!\n");
	}
}

//modifica o disciplina din repo dupa o denumire
void RepoDiscipline::update(const std::string& denumireVeche, const Disciplina& d) {
	auto it = std::find_if(discipline.begin(), discipline.end(),
		[&denumireVeche](const Disciplina &disc) noexcept{
			return disc.getDenumire() == denumireVeche;
		});
	if (it != discipline.end()) {
		*it = d;
	}
	else{
		throw RepoException("Disciplina cu acest nume nu exista!\n");
	}
}

//returneaza un vector cu toate disciplinele din repo
const vector<Disciplina>& RepoDiscipline::getAll() const noexcept{
	return discipline;
}

//cauta o disciplina in repository dupa denumire
const Disciplina& RepoDiscipline::find(const std::string& denumire) const{
	auto it = std::find_if(discipline.begin(), discipline.end(),
		[&denumire](const Disciplina &d) noexcept{
			return d.getDenumire() == denumire;
		});
	if ( it != discipline.end() ){
		return *it;
	}
	throw RepoException("Disciplina cu acest nume nu exista!\n");
}