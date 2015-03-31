#pragma once
/*
#include "NeedContainer.h"
#include "Need.h"
class Hunger : public AABSEngine::AI::Need
{
public:
	Hunger(){}

	void Evaluate(Decimal t){}
};

class Thirst : public AABSEngine::AI::Need
{
public:
	Thirst(){}

	void Evaluate(Decimal t){}
};


void NeedsTest()
{
	AABSEngine::AI::NeedContainer myNeeds;
	myNeeds.Create<Hunger>("Hunger");
	myNeeds.Create<Thirst>("Thirst");

	Thirst* thirst = myNeeds.Access<Thirst>("Thirst");
	Hunger* hunger = myNeeds.Access<Hunger>("Hunger");

	hunger->SetBase(150.0);
	hunger->ClampBase();

	thirst->SetBase(25.0);
	thirst->ClampBase();

	hunger->ApplyDecay(5.0);
	thirst->ApplyGrowth(10.0);

	AABSEngine::AI::PrioritizedNeeds needpq;

	myNeeds.Access(needpq,1);

	while(!needpq.empty())
	{
		std::cout<<needpq.top()->GetName()<<","<<needpq.top()->GetBase()<<std::endl;
		needpq.pop();
	}

	std::cout<<std::endl;
	std::cout<<hunger->GetBase()<<","<<thirst->GetBase()<<std::endl;
	getchar();
}
*/