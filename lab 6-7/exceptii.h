#pragma once
#include <string>
#include <vector>

class RepoException {
private:
	std::string mesaje;
public:
	//constructor	
	RepoException(const std::string& msj) : mesaje(msj) {}

	//returneaza mesajul unei exceptii din repo
	const std::string& getMesaj()const noexcept{
		return mesaje;
	}
};

class ValidatorException {
private:
	std::string mesaje;
public:
	//constructor
	ValidatorException(const std::string& msj) :mesaje(msj) {}

	//returneaza mesajul unei exceptii de validare
	const std::string& getMesaje() const noexcept{
		return mesaje;
	}
};