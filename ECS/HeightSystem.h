#ifndef HEIGHTSYSTEM_H
#define HEIGHTSYSTEM_H

#include "System.h"

class Engine;

class HeightSystem :public System
{
public:
	HeightSystem(Engine* engine, unsigned int id);
	~HeightSystem();
	virtual void processEntities();
};
#endif