#pragma once

#include <iostream>
#include "..\clean\PriorityQ.h"

inline bool Sort(int a, int b) { return a > b; }

void TestPriorityQ()
{
	std::vector<int> alfs;

	alfs.push_back( int(22));
	alfs.push_back( int(10));
	alfs.push_back( int(-40));
	alfs.push_back( int(120));
	alfs.push_back( int(5));
	alfs.push_back( int(-500));
	alfs.push_back( int(-90));
	alfs.push_back( int(1));
	alfs.push_back( int(57));
	alfs.push_back( int(666));
	alfs.push_back( int(90));
	alfs.push_back( int(2));
	alfs.push_back( int(45));
	alfs.push_back( int(20));
	alfs.push_back( int(55));

	AABSEngine::Utility::IndexedPQ<int> q(alfs);
	q.p_greaterComparator = Sort;

	for(int i=0; i<15; i++)
		q.Add(i);

	alfs[4]= 125;
	q.UpdateAt(2);

	while(!q.Empty())
		std::cout<<q.PopElem()<<std::endl;

	std::vector<int>::iterator itr=alfs.begin();

	while(itr != alfs.end())
	{
	///	delete *itr;
		itr = alfs.erase(itr);
	}

}