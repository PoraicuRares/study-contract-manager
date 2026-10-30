#pragma once
#include <string>
#include <iostream>

class Disciplina {
private:
	std::string denumire, tip, cadruDidactic;
	int orePeSapt;
public:
	Disciplina() = default;
	Disciplina(const std::string& denumire, int orePeSapt, const std::string& tip, const std::string& cadruDidactic);
	const std::string& getDenumire() const noexcept;
	const std::string& getTip() const noexcept;
	const std::string& getCadruDidactic() const noexcept;
	int getOrePeSapt() const noexcept;
	friend std::ostream& operator<<(std::ostream& os, const Disciplina& d);
};