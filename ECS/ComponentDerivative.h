#ifndef COMPDER_H
#define COMPDER_H

#include "Component.h"
struct Velocity: public Component
{
	int m_velocity;
	Velocity(int velIn);
	~Velocity();
};

struct Height: public Component
{
	int m_height;
	Height(int heightIn);
	~Height();
};

struct Width: public Component
{
	int m_width;
	Width(int widthIn);
	~Width();
};

struct Life: public Component
{
	int m_life;
	Life(int lifeIn);
	~Life();
};
#endif