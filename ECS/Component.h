#ifndef COMPONENT_H
#define COMPONENT_H

//purely abstract class that all Components will inherit from. Processed by Systems, held by Entities.

struct Component
{
	virtual ~Component() =0 {};
};

#endif