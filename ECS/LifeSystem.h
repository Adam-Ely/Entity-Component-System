#ifndef LIFESYSTEM_H
#define LIFESYSTEM_H

#include "System.h"

class LifeSystem: public System
{
public:
	LifeSystem(Engine* engine, unsigned int id);
	~LifeSystem();
	virtual void processEntities();
};
#endif