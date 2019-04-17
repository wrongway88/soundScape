#ifndef ID_MANAGER
#define ID_MANAGER

#include "core/Defines.h"

class IdManager
{
public:
	IdManager();
	~IdManager();

	id getNextId();

private:
	id m_nextFreeId;
};

#endif // ID_MANAGER