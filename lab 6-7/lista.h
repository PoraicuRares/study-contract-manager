#pragma once

template<typename T>
struct Nod {
	T valoare;
	Nod* urmator;
};


template<typename T>
class IteratorLista {
private:
	Nod<T>* curent;
public:
	//constructor	
	IteratorLista(Nod<T>* c) :curent(c) {}

	//returenaza nodul curent al iteratorului - folosita in clasa lista
	Nod<T>* getNodCurent() const {
		return curent;
	}

	//operatori
	//supraincarcare *
	T& operator*() {
		return curent->valoare;
	}
	
	//supraincarcare ->
	T* operator->() {
		return &(curent->valoare);
	}

	//supraincarcare !=
	friend bool operator!=(const IteratorLista& it1, const IteratorLista& it2) {
		return (it1.curent != it2.curent);
	}

	//supraincarcare ==
	friend bool operator==(const IteratorLista& it1, const IteratorLista& it2) {
		return (it1.curent == it2.curent);
	}

	//supraincarcare ++
	IteratorLista<T> operator++(int) {
		IteratorLista<T> copie = *this;
		curent = curent->urmator;
		return copie;
	}

	IteratorLista<T>& operator++() {
		curent = curent->urmator;
		return *this;
	}
};


template<typename T>
class Lista {
private:
	Nod<T>* prim , *ultim;
	int dim;
public:
	//Constructor
	Lista() {
		dim = 0;
		prim = nullptr;
		ultim = nullptr;
	}

	//Constructor de copiere
	Lista(const Lista& ot) {
		dim = 0;
		prim = nullptr;
		ultim = nullptr;
		for (auto it = ot.begin(); it != ot.end(); ++it)
			this->push_back(*it);
	}

	//Operator atribuire
	Lista& operator=(const Lista& ot) {
		if (this == &ot)
			return *this;
		Nod<T>* curent = prim;
		while (curent != nullptr) {
			Nod<T>* urm = curent->urmator;
			delete curent;
			curent = urm;
		}
		dim = 0;
		prim = nullptr;
		ultim = nullptr;
		for (auto it = ot.begin(); it != ot.end(); ++it)
			this->push_back(*it);
		return *this;
	}

	//Destructor
	~Lista() {
		Nod<T>* curent = prim;
		while (curent != nullptr) {
			Nod<T>* urm = curent->urmator;
			delete curent;
			curent = urm;
		}
	}

	//adauga un element la finalul listei
	void push_back(const T& elem) {
		Nod<T>* nod_nou = new Nod<T>;
		nod_nou->valoare = elem;
		nod_nou->urmator = nullptr;

		if (prim == nullptr) {
			prim = nod_nou;
			ultim = nod_nou;
		}
		else {
			ultim->urmator = nod_nou;
			ultim = nod_nou;
		}
		this->dim++;
	}

	//returneaza un iterator pentru inceputul listei
	IteratorLista<T> begin() const {
		return IteratorLista<T>(prim);
	}

	//returneaza un iterator pentru finalul listei
	IteratorLista<T> end() const {
		return IteratorLista<T>(nullptr);
	}

	//sterge un nod dupa un anumit iterator
	void erase(IteratorLista<T> it) {
		Nod<T>* deSters = it.getNodCurent();
		if (deSters == nullptr)return;
		Nod<T>* curent = prim;

		if (deSters == prim) {
			prim = prim->urmator;
			if (prim == nullptr)
				ultim = nullptr;
			
		}
		else {
			while (curent->urmator != deSters) {
				curent = curent->urmator;
			}
			curent->urmator = deSters->urmator;
			if (deSters == ultim) {
				ultim = curent;
			}
		}
		
		delete deSters;
		this->dim--;
	}

	//returneaza cate elemente sunt in lista
	int size() const {
		return this->dim;
	}

	//operatori

	//supraincarcarea operatorului [] de accesare
	T& operator[](int index) {
		Nod<T>* curent = prim;
		for (int i = 0; i < index; i++)
			curent = curent->urmator;
		return curent->valoare;
	}
	
	const T& operator[](int index) const{
		Nod<T>* curent = prim;
		for (int i = 0; i < index; i++)
			curent = curent->urmator;
		return curent->valoare;
	}

};