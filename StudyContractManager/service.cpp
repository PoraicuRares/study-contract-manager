#include "service.h"
#include <algorithm>
#include <random>
#include <fstream>

//adauga o disciplina in service
void ServiceDiscipline::add(const std::string& denumire, int orePeSapt, const std::string& tip, const std::string& cadruDidactic) {
	Disciplina d(denumire, orePeSapt, tip, cadruDidactic);

	val.valideaza(d);
	repo.store(d);
	undoActions.push_back(std::make_unique<UndoAdauga>(d , repo));
}

//sterge o disciplina din service dupa denumire
void ServiceDiscipline::remove(const std::string& denumire) {
	Disciplina d = repo.find(denumire);
	undoActions.push_back(std::make_unique<UndoSterge>(d , repo));
	repo.remove(denumire);
}

//modifica o disciplina din service dupa denumire
void ServiceDiscipline::modify(const std::string& denumireVeche, const std::string& denumireNoua, int orePeSapt, const std::string& tip, const std::string& cadruDidactic) {
	if (denumireNoua != denumireVeche) {
		bool exista = false;
		try {
			repo.find(denumireNoua);
			exista = true;
		}
		catch(const RepoException&) { 
		}
		if (exista)
			throw RepoException("Exista deja o disciplina cu aceasta denumire!\n");
	}
	Disciplina d(denumireNoua, orePeSapt, tip, cadruDidactic);
	val.valideaza(d);
	Disciplina d2 = repo.find(denumireVeche); 
	undoActions.push_back(std::make_unique<UndoModifica>(d2 , d,repo));
	repo.update(denumireVeche, d);
}

//returneaza un vector cu toate disciplinele din service
const vector<Disciplina>&  ServiceDiscipline::getAllService() const noexcept{
	return repo.getAll();
}

//Returneaza procentul de discipline care au un tip
double ServiceDiscipline::statisticaDupaTip(const std::string& tip) const noexcept{
	double cnt = 0;
	for (const auto& disciplina : repo.getAll()) {
		if (disciplina.getTip() == tip)
			cnt++;
	}
	if (repo.getAll().size() == 0)
		return 0;
	const double aux = static_cast<double>(100 / static_cast<double>(repo.getAll().size()));
	return cnt * aux;
}

//cauta o disciplina dupa denumire
const Disciplina& ServiceDiscipline::search(const std::string& denumire) const {
	return repo.find(denumire);
}

//filtreaza dupa un anumit criteriu
vector <Disciplina> ServiceDiscipline::filtreaza(std::function<bool(const Disciplina&)> fct) const {
	vector<Disciplina> rezultat;
	const auto& toate = repo.getAll();
	std::copy_if(toate.begin(), toate.end(), std::back_inserter(rezultat), fct);
	return rezultat;
}

//filtreaza dupa nr de ore pe saptamana
vector <Disciplina> ServiceDiscipline::filtreazaDupaOre(int nrOre) const {
	return filtreaza([nrOre](const Disciplina& d) noexcept{
		return d.getOrePeSapt() == nrOre;
		});
}

//filtreaza dupa cadru didactic
vector <Disciplina> ServiceDiscipline::filtreazaDupaCadru(const std::string& cadruDidactic)const {
	return filtreaza([&cadruDidactic](const Disciplina& d) noexcept{
		return d.getCadruDidactic() == cadruDidactic;
		});
}

//sorteaza dupa un criteriu custom
vector <Disciplina> ServiceDiscipline::sorteaza(std::function<bool(const Disciplina&, const Disciplina&)> fct) const {
	vector<Disciplina> rez = repo.getAll();
	std::sort(rez.begin(), rez.end(), fct);
	return rez;
}

//sorteaza dupa denumire
vector <Disciplina> ServiceDiscipline::sorteazaDupaDenumire() const {
	return sorteaza([](const Disciplina& d1 , const Disciplina &d2) noexcept{
		return d1.getDenumire() < d2.getDenumire();
		});
}

//sorteaza dupa nr de ore
vector <Disciplina> ServiceDiscipline::sorteazaDupaOre() const {
	return sorteaza([](const Disciplina& d1, const Disciplina& d2) noexcept{
		return d1.getOrePeSapt() < d2.getOrePeSapt();
		});
}

//sorteaza dupa cadru didactic iar pentru cadre didactice egale sorteaza dupa tip
vector <Disciplina> ServiceDiscipline::sorteazaDupaCadruTip() const {
	return sorteaza([](const Disciplina& d1, const Disciplina& d2) noexcept{
		if (d1.getCadruDidactic() != d2.getCadruDidactic())
			return d1.getCadruDidactic() < d2.getCadruDidactic();
		return d1.getTip() < d2.getTip();
		});
}

//Goleste contractul de studii
void ServiceDiscipline::golesteContractStudii() noexcept{
	contractStudii.golesteContract();
	notify();
}

//Adauga o disciplina in contractul de studii dupa denumire
void ServiceDiscipline::adaugaDisciplinaContract(const std::string & denumire) {
	const auto& disc = repo.find(denumire);

	const auto& con = contractStudii.getContract();
	auto it = std::find_if(con.begin(), con.end(),
		[&denumire](const Disciplina& d) noexcept{
			return d.getDenumire() == denumire;
		});
	if (it != con.end()) { //daca exista deja acea disc in contract
		throw RepoException("Exista deja aceasta disciplina in contract!\n");
	}
	else
		contractStudii.adaugaDisciplina(disc);

	notify();
}

//Populeaza contractul cu discipline aleatorii din repo 
void ServiceDiscipline::genereazaContract(int nrDisc)  {
	const auto& disc = repo.getAll();
	if (nrDisc > disc.size() || nrDisc < contractStudii.getContract().size()) {
		throw RepoException("Numarul de discipline din contract este invalid\n");
	}

	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> dist(0, static_cast<int>(disc.size() - 1));

	const auto& con = contractStudii.getContract();
	while (con.size() != nrDisc) {
		const int rndNr = dist(mt);
		const auto& disciplinaRnd = disc.at(rndNr);
		auto it = std::find_if(con.begin(), con.end(),
			[&disciplinaRnd](const Disciplina& d) noexcept{
				return disciplinaRnd.getDenumire() == d.getDenumire();
			});
		if (it == con.end()) { // daca nu am gasit 
			contractStudii.adaugaDisciplina(disciplinaRnd);
		}
	}
	notify();
}

//Returneaza contractul de discipline
const std::vector<Disciplina>& ServiceDiscipline::getContractService() const noexcept{
	return contractStudii.getContract();
}

//exporta intr-un fisier contractul de studii
void ServiceDiscipline::exportaContractFisier(const std::string& numeFis) const {
	std::ofstream out(numeFis , std::ios::trunc);
	for (const auto& d : contractStudii.getContract()) {
		out << d.getDenumire() << ","
			<< d.getOrePeSapt() << ","
			<< d.getTip() << ","
			<< d.getCadruDidactic() << '\n';
	}
	out.close();
}

//reface ultima operatie 
void ServiceDiscipline::undo() {
	if (undoActions.size() == 0)
		throw(RepoException("Nu mai exista operatii!"));
	undoActions.back()->doUndo();
	undoActions.pop_back();
}

//trebuie sa distrugem fiecare actiune ca sa nu avem mem leak
/*
ServiceDiscipline::~ServiceDiscipline() {
	for (const auto& act : undoActions) {
		delete act;	
	}
}
*/

//sterge duplicatele din repo
void ServiceDiscipline::stergeDuplicate() {
	auto aux = repo.getAll();
	std::sort(aux.begin(), aux.end(), [](const Disciplina& d1 , const Disciplina& d2) noexcept{
		return d1.getTip() < d2.getTip();
		});
	auto it = std::unique(aux.begin(), aux.end() , [](const Disciplina& d1, const Disciplina& d2) noexcept{
		return d1.getTip() == d2.getTip();
		});
	aux.erase(it, aux.end());
	auto toate = repo.getAll();
	for (int i = 0; i < toate.size() ; i++) {
		remove(toate.at(i).getDenumire());
	}
	for (int i = 0; i < aux.size(); i++) {
		repo.store(aux.at(i));
	}
}