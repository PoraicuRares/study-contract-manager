#include "disciplina.h"
#include <assert.h>
#include "repository.h"
#include "service.h"
#include <sstream>

static void testDisciplina() {
	Disciplina d("mate", 2, "obligatorie", "berinde");
	assert(d.getCadruDidactic() == "berinde");
	assert(d.getDenumire() == "mate");
	assert(d.getTip() == "obligatorie");
	assert(d.getOrePeSapt() == 2);
	std::stringstream ss;
	ss << d;
	assert(ss.str() != "");
}

static void testContract() {
	Disciplina d("mate", 2, "obligatorie", "berinde");
	Contract c;
	c.adaugaDisciplina(d);
	assert(c.getContract().size() == 1);
	c.golesteContract();
	assert(c.getContract().size() == 0);
}

static void testValidator() {
	ValidatorDisciplina val;
	Disciplina d("mate", 2, "obligatorie", "berinde");
	try {
		val.valideaza(d);
		assert(true);
	}
	catch (const ValidatorException& ve) {
		(void)ve;
		assert(false);
	}

	Disciplina d1("", 2, "obligatorie", "berinde");
	try {
		val.valideaza(d1);
		assert(false);
	}
	catch (const ValidatorException& ve) {
		assert(ve.getMesaje() != "");
	}

	Disciplina d2("mate", -23, "obligatorie", "berinde");
	try {
		val.valideaza(d2);
		assert(false);
	}
	catch (const ValidatorException& ve) {
		assert(ve.getMesaje() == "Nr de ore pe sapt invalid\n");
	}
}

static void testRepo() {
	RepoDiscipline repo;
	const auto& discipline = repo.getAll();
	assert(discipline.size() == 0);


	Disciplina d("mate", 2, "obligatorie", "berinde");
	repo.store(d);
	try {
		repo.store(d);
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMesaj() != "");
	}

	const auto& discipline2 = repo.getAll();
	assert(discipline.size() == 1);
	d = discipline2.at(0);
	assert(d.getCadruDidactic() == "berinde");
	assert(d.getDenumire() == "mate");
	assert(d.getTip() == "obligatorie");
	assert(d.getOrePeSapt() == 2);

	repo.remove("mate");
	assert(repo.getAll().size() == 0);
	try {
		repo.remove("mate");
		assert(false);
	}
	catch (const RepoException& re) {
		(void)re;
		assert(true);
	}

	repo.store(d);
	Disciplina d2("info", 3, "laborator", "istvan");
	repo.update("mate", d2);
	assert(repo.getAll().size() == 1);

	const auto& discipline3 = repo.getAll();
	d = discipline3.at(0);

	assert(d.getCadruDidactic() == "istvan");
	assert(d.getDenumire() == "info");
	assert(d.getTip() == "laborator");
	assert(d.getOrePeSapt() == 3);
	try {
		repo.update("rawka", d2);
		assert(false);
	}
	catch (const RepoException& re) {
		(void)re;
		assert(true);
	}

	const auto& rez = repo.find("info");
	assert(rez.getDenumire() == "info");
	try {
		repo.find("sfasfa");
		assert(false);
	}
	catch (const RepoException& re) {
		(void)re;
		assert(true);
	}
}

static void testService() {
	RepoDiscipline repo;
	ValidatorDisciplina val;
	Contract con;
	ServiceDiscipline srv(repo,val , con);
	assert(srv.statisticaDupaTip("asf") == 0);
	srv.add("mate", 2, "seminar", "modoi");
	const auto& discipline = srv.getAllService();
	assert(discipline.size() == 1);
	Disciplina d = discipline.at(0);
	assert(d.getCadruDidactic() == "modoi");
	assert(d.getDenumire() == "mate");
	assert(d.getOrePeSapt() == 2);
	assert(d.getTip() == "seminar");

	srv.remove("mate");
	assert(srv.getAllService().size() == 0);

	srv.add("mate", 2, "seminar", "modoi");
	srv.modify("mate", "info", 3, "lab", "gabi");
	const auto& discipline2 = srv.getAllService();
	d = discipline2.at(0);
	assert(d.getCadruDidactic() == "gabi");
	assert(d.getDenumire() == "info");
	assert(d.getOrePeSapt() == 3);
	assert(d.getTip() == "lab");

	srv.add("mate", 3, "curs", "modoi");
	const double rez = srv.statisticaDupaTip("curs");
	assert(rez == 50);

	const auto & dis  = srv.search("mate");
	assert(dis.getDenumire() == "mate");
	
	auto filtru = srv.filtreazaDupaCadru("gabi");
	assert(filtru.size() == 1);

	filtru = srv.filtreazaDupaOre(3);
	assert(filtru.size() == 2);

	srv.add("algebra", 1, "seminar", "gabi");

	filtru = srv.sorteazaDupaOre();
	assert(filtru.size() == 3);

	filtru = srv.sorteazaDupaDenumire();
	assert(filtru.size() == 3);

	filtru = srv.sorteazaDupaCadruTip();
	assert(filtru.size() == 3);

	try {
		srv.modify("algebra", "mate", 2, "ab", "modoi");
		assert(false);
	}
	catch (const RepoException& re) {
		(void)re;
		assert(true);
	}
	srv.adaugaDisciplinaContract("algebra");
	assert(srv.getContractService().size() == 1);
	try {
		srv.adaugaDisciplinaContract("algebra");
		assert(false);
	}
	catch (const RepoException& re) {
		(void)re;
		assert(true);
	}
	srv.golesteContractStudii();
	assert(srv.getContractService().size() == 0);
	srv.genereazaContract(3);
	assert(srv.getContractService().size() == 3);
	try {
		srv.genereazaContract(124);
		assert(false);
	}
	catch (const RepoException& re) {
		(void)re;
		assert(true);
	}
	srv.golesteContractStudii();
	srv.adaugaDisciplinaContract("mate");
	srv.exportaContractFisier("test.csv");

}

static void testUndo() {
	RepoDiscipline r;
	ValidatorDisciplina v;
	Contract c;
	ServiceDiscipline srv(r, v, c);
	srv.add("1", 1, "1", "1");
	srv.undo();
	assert(srv.getAllService().size() == 0);
	try {
		srv.undo();
		assert(false);
	}
	catch (const RepoException& re) {
		(void)re;
		assert(true);
	}
	srv.add("1", 1, "1", "1");
	srv.remove("1");
	srv.undo();
	assert(srv.getAllService().size() == 1);
	srv.modify("1", "2", 2, "2", "2");
	srv.undo();
	try {
		srv.search("1");
		assert(true);
	}
	catch (const RepoException& re) {
		(void)re;
		assert(false);
	}
}

static void testStergeDuplicate() {
	RepoDiscipline r;
	ValidatorDisciplina v;
	Contract c;
	ServiceDiscipline srv(r, v, c);
	srv.add("1", 1, "1", "1");
	srv.add("2", 3, "2", "2");
	srv.add("3", 4, "3", "3");
	srv.add("4", 4, "2", "2");
	srv.add("5", 4, "3", "3");
	srv.stergeDuplicate();
	assert(srv.getAllService().size() == 3);
}

/*
static void testLista() {
	Lista<int> l;
	l.push_back(2);
	assert(l.size() == 1);
	assert(*l.begin() == 2);
	assert(l.end() == nullptr);
	l.push_back(3);
	l.erase(l.begin());
	assert(*l.begin() == 3);
	l.erase(l.begin());
	l.erase(l.begin());
	l.push_back(7);
	int el = l[0];
	const int el2 = l[0];
	assert(el == 7);
	assert(el2 == 7);
	IteratorLista<int> it{ l.begin() };
	auto nod = it.getNodCurent();
	assert(nod->valoare == 7);
	assert(it != l.end());
	assert(it == l.begin());
	it++;
	assert(it == l.end());
	it = l.begin();
	++it;
	assert(it == l.end());
	l = l;
	l.push_back(3);
	l.erase(++l.begin());
	assert(l.size() == 1);
	l.push_back(3);
	l.push_back(5);
	l.push_back(7);
	l.push_back(2);
	IteratorLista<int>it2{ l.begin() };
	++it2; ++it2;
	l.erase(it2);
	assert(l.size() == 4);
	Lista<int> l2;
	l2 = l;
	assert(l2.size() == 4);
}
*/
void testAll() {
	testDisciplina();
	testRepo();
	testService();
	//testLista();
	testValidator();
	testContract();
	testUndo();
	testStergeDuplicate();
}