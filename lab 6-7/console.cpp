#include "console.h"
#include <iostream>
using std::cin;
using std::cout;

//Afiseaza meniul cu optiuni
static void printMenu() {
	cout << "\nMeniu de optiuni\n";
	cout << "1.Adaugare disciplina\n";
	cout << "2.Sterge disciplina\n";
	cout << "3.Modifica disciplina\n";
	cout << "4.Afiseaza disciplina\n";
	cout << "5.Statistica dupa tip\n";
	cout << "6.Cauta dupa denumire\n";
	cout << "7.Filtrare\n";
	cout << "8.Sortare\n";
	cout << "9.Goleste contract studii\n";
	cout << "10.Adauga in contract studii \n";
	cout << "11.Genereaza contract \n";
	cout << "12.Export contract in fisier \n";
	cout << "13.Undo\n";
	cout << "14.Sterge duplicate\n";
	cout << "0.Exit\n";
	cout << "Alegeti optiunea: ";
}

//Afiseaza o lista de discipline
static void afiseazaLista(const vector<Disciplina>& l) {
	if (l.size() == 0) {
		cout << "Lista este goala!\n";
		return;
	}
	for (const auto& d : l)
		cout << d;
}

//Citeste o disciplina pentru a fi adaugata in service
static void adaugaUi(ServiceDiscipline & srv) {

	std::string denumire, tip, cadruDidactic;
	int orePeSapt;
	cout << "Dati denumirea disciplinei:";
	getline(cin >> std::ws, denumire);
	cout << "Dati ore pe saptamana:";
	cin >> orePeSapt;
	cout << "Dati tipul disciplinei:";
	getline(cin >> std::ws, tip);
	cout << "Dati cadrul didactic disciplinei:";
	getline(cin >> std::ws, cadruDidactic);
	try {
		srv.add(denumire, orePeSapt, tip, cadruDidactic);
		cout << "S-a adaugat disciplina cu succes!\n";
	}
	catch (const ValidatorException& ve) {
		cout << ve.getMesaje();
	}
	catch (const RepoException& ve) {
		cout << ve.getMesaj();
	}
	
}

//Citeste denumirea disciplinei de sters
static void removeUi(ServiceDiscipline& srv) {
	std::string denumire;
	cout << "Dati denumirea disciplinei de sters:";
	getline(cin >> std::ws, denumire);
	try {
		srv.remove(denumire);
		cout << "Disciplina s-a sters cu succes\n";
	}
	catch (const RepoException& re) {
		cout << re.getMesaj();
	}
}

//Citeste denumirea disciplinei de modificat si disciplina noua
static void modifyUi(ServiceDiscipline& srv) {

	std::string denumireVeche , denumire, tip, cadruDidactic;
	int orePeSapt;
	cout << "Dati denumirea disciplinei de modificat:";
	getline(cin >> std::ws, denumireVeche);
	cout << "Dati denumirea disciplinei noi:";
	getline(cin >> std::ws, denumire);
	cout << "Dati orele noi pe saptamana:";
	cin >> orePeSapt;
	cout << "Dati tipul nou al disciplinei:";
	getline(cin >> std::ws, tip);
	cout << "Dati cadrul didactic nou al disciplinei:";
	getline(cin >> std::ws, cadruDidactic);
	try {
		srv.modify(denumireVeche, denumire, orePeSapt, tip, cadruDidactic);
		cout << "S-a modificat disciplina cu succes!\n";
	}
	catch (const ValidatorException& ve) {
		cout << ve.getMesaje();
	}
	catch (const RepoException& ve) {
		cout << ve.getMesaj();
	}
}

//Afiseaza toate disciplinele
static void afiseazaDiscipline(const ServiceDiscipline& srv) {
	const auto& discipline = srv.getAllService();
	if (discipline.size() == 0)
		cout << "Nu exista discipline adaugate!\n";
	for (const auto& d : discipline) {
		cout << d;
	}
}

//Citeste un tip pentru a face statistica dupa tip
static void statisticaTipUi(const ServiceDiscipline& srv) {
	std::string tip;
	cout << "Dati tipul pentru statistica: ";
	getline(cin >> std::ws, tip);
	const double rezultat = srv.statisticaDupaTip(tip);
	cout << "Disciplinele cu tipul : " << tip << " sunt " << rezultat << "%\n";
}

//Citeste o denumire pentru a cauta o disciplina
static void cautaUi(const ServiceDiscipline& srv) {
	std::string denumire;
	cout << "Dati denumirea disciplinei de cautat:";
	getline(cin >> std::ws, denumire);
	try {
		const auto& d = srv.search(denumire);
		cout << d;
	}
	catch (const RepoException& re) {
		cout << re.getMesaj();
	}
}

//Filtreaza dupa un anumit criteriu citit
static void filtreazaUi(const ServiceDiscipline& srv) {
	int criteriu;
	cout << "1.Dupa nr ore\n2.Dupa cadru didactic\nDati criteriul: ";
	cin >> criteriu;
	if (criteriu == 1) { // dupa nr ore
		int nrOre;
		cout << "Dati numarul de ore pe saptamana:";
		cin >> nrOre;
		auto rez = srv.filtreazaDupaOre(nrOre);
		afiseazaLista(rez);
	}
	else if (criteriu == 2) { // dupa cadru didactic
		std::string cadruDidactic;
		cout << "Dati cadrul didactic:";
		getline(cin >> std::ws, cadruDidactic);
		auto rez = srv.filtreazaDupaCadru(cadruDidactic);
		afiseazaLista(rez);
	}
	else {
		cout << "Criteriu incorect !\n";
		return;
	}
}

//Sorteaza dupa un anumit criteriu citit
static void sorteazaUi(const ServiceDiscipline& srv) {
	int criteriu;
	cout << "1.Dupa denumire \n2.Dupa nr ore\n3.Dupa cadru didactic + tip\nDati criteriu:";
	cin >> criteriu;
	if (criteriu == 1) { // denumire
		auto rez = srv.sorteazaDupaDenumire();
		afiseazaLista(rez);
	}
	else if (criteriu == 2) { // nrore
		auto rez = srv.sorteazaDupaOre();
		afiseazaLista(rez);
	}
	else if (criteriu == 3) { //cadrudidactic + tip
		auto rez = srv.sorteazaDupaCadruTip();
		afiseazaLista(rez);
	}
	else {
		cout << "Criteriu incorect!\n";
		return;
	}
}

//citeste  denumirea unei discipline pentru a fi adaugata in contract
static void adaugaContractUi(ServiceDiscipline& srv) {
	std::string denumire;
	cout << "Dati denumriea disciplinei de adaugat in contract:";
	getline(cin >> std::ws, denumire);
	try {
		srv.adaugaDisciplinaContract(denumire);
		cout << "Disciplina a fost adaugata cu succes!\n";
		cout << "Numarul de discipline din contract este "<<srv.getContractService().size() << '\n';
	}
	catch (const RepoException&  re) {
		cout << re.getMesaj();
	}
}

//genereaza un  contract cu un nr citit de discipline
static void genereazaContractUi(ServiceDiscipline& srv) {
	int nrDisc;
	cout << "Dati numarul de discipline din contract:";
	cin >> nrDisc;
	try {
		srv.genereazaContract(nrDisc);
		cout << "Numarul de discipline din contract este " << srv.getContractService().size() << '\n';
	}
	catch (const RepoException& re) {
		cout << re.getMesaj();
	}
}

//Salveaza contractul de studii in numele fisierului citit
static void salveazaFisier(const ServiceDiscipline& srv) {
	std::string numeFis;
	cout << "Dati numele fisierului:";
	getline(cin >> std::ws, numeFis);
	srv.exportaContractFisier(numeFis);
	cout << "Numarul de discipline din contract este " << srv.getContractService().size() << '\n';
}

//Reface ultima operatie
static void undoUi(ServiceDiscipline& srv) {
	srv.undo();
}

//sterge duplicatele 
static void stergeDuplicateUI(ServiceDiscipline& srv) {
	srv.stergeDuplicate();
	cout << "Duplicatele au fost sterse cu succes!\n";
}

void Console::runUi() {
	while (1) {
		printMenu();
		int cmd;
		cin >> cmd;
		if (cmd == 1) {
			adaugaUi(srv);
		}
		else if (cmd == 2) {
			removeUi(srv);
		}
		else if (cmd == 3) {
			modifyUi(srv);
		}
		else if (cmd == 4) {
			afiseazaDiscipline(srv);
		}
		else if (cmd == 5) {
			statisticaTipUi(srv);
		}
		else if (cmd == 6) {
			cautaUi(srv);
		}
		else if (cmd == 7) {
			filtreazaUi(srv);
		}
		else if (cmd == 8) {
			sorteazaUi(srv);
		}
		else if (cmd == 9) {
			srv.golesteContractStudii();
			cout << "Contractul a fost golit cu succes!\n";
			cout << "Numarul de  discipline din contract este 0\n";
		}
		else if (cmd == 10) {
			adaugaContractUi(srv);
		}
		else if (cmd == 11) {
			genereazaContractUi(srv);
		}
		else if (cmd == 12) {
			salveazaFisier(srv);
		}
		else if (cmd == 13) {
			undoUi(srv);
		}
		else if (cmd == 14) {
			stergeDuplicateUI(srv);
		}
		else if (cmd == 0) {
			return;
		}
		else {
			cout << "Optiune invalida!";
		}
	}
}