#pragma once
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qmessagebox.h>
#include <QtGui/qbrush.h>
#include <QtGui/qcolor.h>
#include <qinputdialog.h>
#include <service.h>

class Gui : public QWidget{
private:
	ServiceDiscipline& srv;

	//lista de discipline
	QListWidget* disc = new QListWidget;

	//campurile de completat
	QLineEdit* denumire = new QLineEdit;
	QLineEdit* nrOre = new QLineEdit;
	QLineEdit* tip = new QLineEdit;
	QLineEdit* cadruDidactic = new QLineEdit;

	//butoanele
	QPushButton* btnAdd = new QPushButton("Adauga");
	QPushButton* btnDelete = new QPushButton("Sterge");
	QPushButton* btnModify = new QPushButton("Modifica");
	QPushButton* btnFind = new QPushButton("Cauta");
	QPushButton* btnExit = new QPushButton("Exit");
	QPushButton* btnDeleteDuplicates = new QPushButton("Sterge duplicate");
	QPushButton* btnUndo = new QPushButton("Undo");
	
	QPushButton* btnSortDen = new QPushButton("Sorteaza dupa denumire");
	QPushButton* btnSortOre = new QPushButton("Sorteaza dupa nr ore");
	QPushButton* btnSortCadruTip = new QPushButton("Sorteaza dupa cadru si tip");

	QPushButton* btnFiltreazaOre = new QPushButton("Filtreaza dupa ore");
	QPushButton* btnFiltreazaCadru = new QPushButton("Filtreaza dupa cadru");
	QPushButton* btnStatistica = new QPushButton("Statistica dupa tip");

	QPushButton* btnAdaugaContract = new QPushButton("Adauga in contract");
	QPushButton* btnDeschideContract = new QPushButton("Deschide contractul");
	QPushButton* btnDeschideCosCRUD = new QPushButton("Deschide cos CRUD");
	QPushButton* btnDeschideCosReadOnly = new QPushButton("Deschide cos readonly");
	/*
	* Inititalizeaza componentele vizuale si seteaza layout-ul aplicatiei
	*/
	void initGUI();
	
	/*
	* Incarca datele din service si populeaza lista vizuala
	*/
	void loadData(const vector<Disciplina>& discipline);

	/*
	* Leaga semnalele emise de componentele ui la sloturile corespunzatoare
	*/
	void initConnect();

	//Metodele pentru butoane

	/*
	* Ia datele din campuri, apeleaza service-ul pentru adaugare si da refresh la lista
	* Afiseaza un mesaj de eroare in caz de o exceptie
	*/
	void adaugaGui();

	/*
	* Sterge disciplina selectata
	*/
	void stergeGui();

	/*
	* Modifica disciplina selectata 
	* Afiseaza un mesaj de eroare in caz de o exceptie
	*/
	void modificaGui();

	/*
	* Umple campurile cu text cu date corespunzatoare disciplinei selectate
	*/
	void umpleCamuri();

	/*
	* Face o alta fereastra pentru cautarea unei discipline 
	* Selecteaza in lista disciplina gasita
	* Afiseaza un mesaj de eroare in caz ca nu s-a gasit
	*/
	void gasesteGui();

	/*
	* Ordoneaza disciplinele vizual dupa denumire
	*/
	void sorteazaDupaDenumireGui();

	/*
	* Ordoneaza disciplinele vizual dupa nr de ore pe saptamana
	*/
	void sorteazaDupaOreGui();


	/*
	* Ordoneaza disciplinele vizual dupa cadru didactic iar pentru acelasi cadru dupa tip
	*/
	void sorteazaDupaCadruTipGui();

	/*
	* Sterge disciplinele cu tipuri duplicate vizual
	*/
	void stergeDuplicateGui();

	/*
	* Reface operatia de adauga/sterge/modifica
	*/
	void undoGui();


	/*
	* Face o alta fereastra pentru introducerea orei dupa care se filtreaza
	* Arata un mesaj de eroare daca ora introdusa nu a fost corecta
	*/
	void filtreazaDupaOreGui();

	/*
	* Face o alta fereastra pt introducerea cadrului didactic dupa care se filtreaza
	* Arata un mesaj de eroare daca ora introdusa nu a fost corecta
	*/
	void filtreazaDupaCadruGui();

	/*
	* Face o alta fereastra pt introducerea tipului dupa care se face statistica
	* Arata un mesaj de eroare daca tipul introdus nu a fost  corect	
	*/
	void statisticaDupaTipGui();

	/*
	* Adauga o disciplina selectata in contractul cu discipline
	*/
	void adaugaContractGui();

	/*
	* Deschide fereastra cu contractul
	*/
	void deschideContractGui();

	/*
	* Deschide fereastra cu cos CRUD
	*/
	void deschideCosCRUD();

	/*
	* Deschide fereastra cu cos readonly
	*/
	void deschideCosReadOnly();

public:
	Gui(ServiceDiscipline& srv);
};