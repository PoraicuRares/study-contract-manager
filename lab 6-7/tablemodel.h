#pragma once
#include "disciplina.h"
#include <qabstracttablemodel>
#include <vector>
using std::vector;
class TableModel : public QAbstractTableModel {
private:
	vector<Disciplina> discipline;
public:
	TableModel(const vector<Disciplina>& disc) : discipline(disc) {}

	/*
	* Returneaza numarul de linii din tabel
	*/
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	/*
	* Returneaza numarul de coloane din tabel
	*/
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	/*
	* Returneaza datele din fiecare celula
	*/
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	/*
	* Returneaza ce se pune capul tabelului
	*/
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	/*
	* Pentru actualizarea datelor cand se apasa pe un buton sau vine semnal din observer
	*/
	void setDiscipline(const vector<Disciplina>& disc);

};
