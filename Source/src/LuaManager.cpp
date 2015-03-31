#include "StdAfx.h"

#include "LuaManager.h"
#include <iostream>
#include <luabind\luabind.hpp>

int add(int a, int b) { return a * b; }

AABSEngine::Utility::LuaManager::LuaManager()
{
	m_lua = luaL_newstate();

	if(!m_lua) 
	{
		std::cout<<"Error opening a lua instance"<<std::endl;
		return;
	}

	std::cout<<"Success opening lua instance"<<std::endl;

	luaL_openlibs(m_lua); //open lua libs(i.e. math)
	//luabind::open(m_lua);
}

void AABSEngine::Utility::LuaManager::RunScriptFile(const char *fileName)
{
	int state = luaL_dofile(m_lua,fileName);
	
	switch(state)
	{
		case 0: std::cout<<"Successfully opened lua file: "<<fileName<<std::endl; break;
		case 1: std::cout<<"Error trying to open lua file: "<<fileName<<std::endl; break;
	}
}

void AABSEngine::Utility::LuaManager::RunStringCommand(std::string command)
{
	luaL_dostring(m_lua,command.c_str());
}

int AABSEngine::Utility::LuaManager::GetTop()const
{
	return lua_gettop(m_lua);
}

void AABSEngine::Utility::LuaManager::Push(int (*function)(lua_State*))
{
	lua_pushcfunction(m_lua,function);
}

void AABSEngine::Utility::LuaManager::RegisterCFunction(const char* name, int (*function)(lua_State*))
{
	lua_register(m_lua,name,function);
}

int AABSEngine::Utility::LuaManager::IsType(DataType type, int index)const
{
	switch(type)
	{
	case NUMBER: return lua_isnumber(m_lua,index);
	case STRING: return lua_isstring(m_lua,index);
	case BOOLEAN: return lua_isboolean(m_lua,index);
	case TABLE: return lua_istable(m_lua,index);
	case USERDATA: return lua_isuserdata(m_lua,index);
	case CFUNCTION: return lua_iscfunction(m_lua,index);
	case FUNCTION: return lua_isfunction(m_lua,index);
	case NIL: return lua_isnil(m_lua,index);
	}
	return 0;	
}

void AABSEngine::Utility::LuaManager::ClearStack()
{
	lua_settop(m_lua,0);
}

void AABSEngine::Utility::LuaManager::Push(double _number)
{
	lua_pushnumber(m_lua,_number);
}

void AABSEngine::Utility::LuaManager::Push(int _number)
{
	lua_pushinteger(m_lua,_number);
}

void AABSEngine::Utility::LuaManager::Push(bool _bool)
{
	lua_pushboolean(m_lua,_bool);
}

void AABSEngine::Utility::LuaManager::Push(std::string _string)
{
	lua_pushstring(m_lua,_string.c_str());
}

void AABSEngine::Utility::LuaManager::Push(void* _userData)
{
	lua_pushlightuserdata(m_lua,_userData);
}

void AABSEngine::Utility::LuaManager::Pop(int index)
{
	lua_pop(m_lua,index);
}

bool AABSEngine::Utility::LuaManager::PopBoolean(const char* variable)
{
	bool truth=0;

	lua_settop(m_lua,0);
	lua_getglobal(m_lua,variable);

	if(!lua_isboolean(m_lua,1))
	{
		std::cout<<"Not a boolean"<<std::endl;
		return truth; 
	}

	truth = lua_toboolean(m_lua,1);
	lua_pop(m_lua,1);
	
	return truth;
}

void AABSEngine::Utility::LuaManager::SetTop(int index)
{
	lua_settop(m_lua,0);
}

void AABSEngine::Utility::LuaManager::GlobalToStack(const char* variable)
{
	lua_getglobal(m_lua,variable);
}

std::string AABSEngine::Utility::LuaManager::PopStringFromTable(const char* table, const char* key)
{
	std::string str;	

	lua_settop(m_lua,0);
	lua_getglobal(m_lua,table);

	if(!lua_istable(m_lua,-1))
	{
		std::cout<<"Not a table"<<std::endl;
		return str;
	}
	
	lua_pushstring(m_lua,key); //push key on stack
	lua_gettable(m_lua,-2);

	if(!lua_isstring(m_lua,-1))
	{
		std::cout<<"Not a string from table"<<std::endl;
		return str;
	}

	str = lua_tostring(m_lua,-1);
	lua_pop(m_lua,-1);

	return str;
}

std::string AABSEngine::Utility::LuaManager::PopString(const char *variable)
{
	std::string str;
	str.clear();

	lua_settop(m_lua,0);
	lua_getglobal(m_lua,variable);

	if(!lua_isstring(m_lua,1))
	{
		std::cout<<"Not a string"<<std::endl;
		return str;
	}

	str = lua_tostring(m_lua,1);
	lua_pop(m_lua,1);

	return str;
}

int AABSEngine::Utility::LuaManager::TypeIdentifierAt(int index)
{
	return lua_type(m_lua,index);
}

const char* AABSEngine::Utility::LuaManager::TypeNameAt(int index)
{
	return lua_typename(m_lua,index);
}

void AABSEngine::Utility::LuaManager::DisplayStackedElementTypes()
{
	int top = lua_gettop(m_lua);

	for(int i=0; i < top; i++)
	{
		switch(TypeIdentifierAt(i))
		{
			case LUA_TSTRING:
				std::cout<<lua_tostring(m_lua,i)<<std::endl;
			break;

			case LUA_TNUMBER:
				std::cout<<lua_tonumber(m_lua,i)<<std::endl;
			break;
			
			case LUA_TBOOLEAN:
				std::cout<<lua_toboolean(m_lua,i)<<std::endl;
			break;

			default:
				std::cout<<TypeNameAt(i)<<std::endl;
			break; 
		}
	}
}


AABSEngine::Utility::LuaManager::~LuaManager()
{
	lua_close(m_lua);
}

int AABSEngine::Utility::LuaManager::PeekInteger(int index)
{
	if(!IsType(DataType::NUMBER,index)) 
	{
		std::cout<<"Not an integer error has occured in lua manager peek"<<std::endl;
		return 0;
	}
	return lua_tointeger(m_lua,index);
}

double AABSEngine::Utility::LuaManager::PeekDecimal(int index)
{
	if(!IsType(DataType::NUMBER,index)) 
	{
		std::cout<<"Not a number error has occured in lua manager peek"<<std::endl;
		return 0;
	}
	return lua_tonumber(m_lua,index);
}

std::string AABSEngine::Utility::LuaManager::PeekString(int index)
{
	if(!IsType(DataType::STRING,index))
	{
		std::cout<<"Not a string error has occured in lua manager peek"<<std::endl;
		return "";
	}
	return lua_tostring(m_lua,index);
}

int AABSEngine::Utility::LuaManager::PeekBoolean(int index)
{
	if(!IsType(DataType::BOOLEAN,index))
	{
		std::cout<<"Not a boolean error has occured in lua manager peek"<<std::endl;
		return false;
	}
	return lua_toboolean(m_lua,index);
}

void AABSEngine::Utility::LuaManager::BindModule()
{
}