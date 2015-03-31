#pragma once 

#include "..\clean\LuaManager.h"
class LuaTest
{
public:

	void TestLua()
	{
		AABSEngine::Utility::LuaManager mgr;
		mgr.RunScriptFile("TestFile.lua");
	
		if(mgr.PopBoolean("Boolz")) std::cout<<"Success popping boolean from .lua file"<<std::endl;
		if(mgr.PopNumeric<float>("Numeric")==55.5) std::cout<<"Success popping number from .lua file"<<std::endl;
		if(mgr.PopString("Text")=="Hello World")std::cout<<"Success popping string from .lua file"<<std::endl;	
		if(mgr.PopNumericFromTable<long>("data","A") == 45) std::cout<<"Success popping number at index 'A' from table"<<std::endl;
		if(mgr.PopNumericFromTable<int>("data","B") == 120) std::cout<<"Success popping number at index 'B' from table"<<std::endl;
		
		mgr.ClearStack();

		if(mgr.GetTop() == 0) std::cout<<"Clear stack function success"<<std::endl;

		std::cout<<"Testing push functions of lua manager which should add 4 more elements to the stack"<<std::endl;
		mgr.Push("Test String");
		mgr.Push(900);
		mgr.Push(45.5);
		mgr.Push(true);

		if(mgr.GetTop() == 4) std::cout<<"Success adding all 4 items on stack"<<std::endl;

		std::cout<<"Testing pop function to pop off the top element from the stack"<<std::endl;
		mgr.Pop(1); 

		if(mgr.GetTop() == 3)std::cout<<"Success popping off one of the elements off the stack. Stack size now equals 3"<<std::endl;
		
		std::cout<<"Printing remaining elements"<<std::endl;

		if(mgr.PeekDecimal(-1) == 45.5) std::cout<<"Success peeking into stack with decimal entry"<<std::endl;
		if(mgr.PeekInteger(-2) == 900) std::cout<<"Success peeking into stack with integer entry"<<std::endl;
		if(mgr.PeekBoolean(-3) == true) std::cout<<"Success peeking into stack with boolean entry"<<std::endl;

		std::cout<<"Testing string command function of lua manager by executing command 'print(120)'"<<std::endl;
		mgr.RunStringCommand("print(120)");
	}
};