#include <typeindex>

#include "Entity.h"
#include "Engine.h"
#include "ComponentDerivative.h"
#include "LifeSystem.h"
#include "HeightSystem.h"


int main( int argc, char* args[] )
{
	Engine engine;

	LifeSystem lifeSystem(&engine, 0);
	HeightSystem heightSystem(&engine, 1);
	engine.addSystem(&lifeSystem);
	engine.addSystem(&heightSystem);

	Entity* entity1 = new Entity(0, "Adam");
	Entity* entity2 = new Entity(1, "Sam");
	Entity* entity3 = new Entity(2, "Dad");
	Entity* entity4 = new Entity(3, "Mum");
	Entity* entity5 = new Entity(4, "Leo");
	Entity* entity6 = new Entity(5, "Sawsan");
	
	engine.addEntity(entity1);
	engine.addEntity(entity2);
	engine.addEntity(entity3);
	engine.addEntity(entity4);
	engine.addEntity(entity5);
	engine.addEntity(entity6);

	Velocity* vel1 = new Velocity(-10);
	//Component* vel1 = new Velocity(-10);
	Life* life1 = new Life(10);
	//Component* life1 = new Life(10);
	engine.addComponent(0,vel1);
	engine.addComponent(0,life1);
	
	Velocity* vel2 = new Velocity(-5);
	Life* life2 = new Life(20);
	engine.addComponent(1,vel2);
	engine.addComponent(1,life2);

	Life* life3 = new Life(30);
	Height* height1 = new Height(5);
	engine.addComponent(2,life3);
	engine.addComponent(2,height1);

	Height* height2 = new Height(8);
	Width* width1 = new Width(1);
	engine.addComponent(3,height2);
	engine.addComponent(3,width1);

	Velocity* vel3 = new Velocity(3);
	Width* width2 = new Width(3);
	Height* height3 = new Height(3);
	engine.addComponent(4,vel3);
	engine.addComponent(4,width2);
	engine.addComponent(4,height3);

	Velocity* vel4 = new Velocity(3);
	Width* width3 = new Width(3);
	Height* height4 = new Height(3);
	Life* life4 = new Life(3);
	engine.addComponent(5,vel4);
	engine.addComponent(5,width3);
	engine.addComponent(5,height4);
	engine.addComponent(5,life4);

	engine.registerAll();

	lifeSystem.processEntities();


	engine.removeEntity(0);
	engine.removeEntity(0);
	engine.removeEntity(1);

	engine.removeSystem(&lifeSystem);
}