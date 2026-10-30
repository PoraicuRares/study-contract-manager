#include "service.h"

class Console {
private:
	ServiceDiscipline& srv;

public:
	Console(ServiceDiscipline& srv) noexcept: srv(srv) {}
	void runUi();
};