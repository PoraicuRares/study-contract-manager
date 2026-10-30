#pragma once
#include "repository.h"
#include "validatori.h"
#include <functional>
#include "contract.h"
#include "undo.h"
#include <memory>
#include "observer.h"
class ServiceDiscipline : public Observable {
private:
	RepoDiscipline& repo;
	ValidatorDisciplina& val;
	Contract& contractStudii;
	vector<std::unique_ptr<ActiveUndo>> undoActions;
	vector <Disciplina> filtreaza(std::function<bool(const Disciplina &)> fct) const ;
	vector <Disciplina> sorteaza(std::function<bool(const Disciplina&, const Disciplina&)> fct) const;
public:
	//~ServiceDiscipline();
	ServiceDiscipline(RepoDiscipline& repo , ValidatorDisciplina &val , Contract & con) noexcept: repo(repo)  , val(val) , contractStudii(con) {}
	void add(const std::string& denumire, int orePeSapt, const std::string& tip, const std::string& cadruDidactic);
	void remove(const std::string& denumire);
	void modify(const std::string& denumireVeche, const std::string& denumireNoua, int orePeSapt, const std::string & tip, const std::string &cadruDidactic);
	const vector<Disciplina> &  getAllService() const noexcept;
	double statisticaDupaTip(const std::string& tip) const noexcept;
	const Disciplina& search(const std::string& denumire) const;
	vector<Disciplina> filtreazaDupaOre(int nrOre) const;
	vector <Disciplina> filtreazaDupaCadru(const std::string& cadruDidactic)const;
	vector <Disciplina> sorteazaDupaDenumire() const;
	vector <Disciplina> sorteazaDupaOre() const;
	vector <Disciplina> sorteazaDupaCadruTip() const;
	void golesteContractStudii() noexcept;
	void adaugaDisciplinaContract(const std::string& denumire);
	void genereazaContract(int nrDisc) ;
	const std::vector<Disciplina>& getContractService() const noexcept;
	void exportaContractFisier(const std::string& numeFis) const;
	void undo() ;
	void stergeDuplicate();
};