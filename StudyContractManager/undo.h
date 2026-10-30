#include "disciplina.h"
#include "repository.h"
class ActiveUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiveUndo() = default;
};

class UndoAdauga : public ActiveUndo {
private:
	Disciplina discAdaugata;
	RepoDiscipline& rep;
public:
	UndoAdauga(const Disciplina& disc, RepoDiscipline& r) : discAdaugata{ disc }, rep(r) {}
	void doUndo() override {
		rep.remove(discAdaugata.getDenumire());
	}
};

class UndoSterge : public ActiveUndo {
private:
	Disciplina discStearsa;
	RepoDiscipline& rep;
public:
	UndoSterge(const Disciplina& disc, RepoDiscipline& r)  : discStearsa(disc), rep(r) {}
	void doUndo() override {
		rep.store(discStearsa);
	}
};

class UndoModifica : public ActiveUndo {
private:
	Disciplina discVeche , discNoua;
	RepoDiscipline& repo;
public: 
	UndoModifica(const Disciplina& d1, const Disciplina& d2, RepoDiscipline& r)  : discVeche(d1), discNoua(d2), repo(r) {}
	void doUndo() override {
		repo.update(discNoua.getDenumire(), discVeche);
	}
};