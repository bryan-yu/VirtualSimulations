#pragma once

#include <string>
#include <lua.hpp>
#include "types.h"

namespace AABSEngine
{
	namespace Utility
	{
		/**
		** @class LuaManager
		** @brief Wrapper for lua functions and processes
		** @author Bryan
		**/

		//-1 index is top and lower traverses downwards, 1 is bottom higher traverses upwards

		class LuaManager
		{
		public:
			enum DataType
			{
				NUMBER,
				STRING,
				BOOLEAN,
				USERDATA,
				TABLE,
				CFUNCTION,
				FUNCTION,
				NIL
			};

			LuaManager();
			~LuaManager();

			/**
			** @brief Run a lua script once through
			** @param .lua file name
			**/
			void RunScriptFile(const char *filename);

			/**
			** @brief Run string command via lua
			** @param command/input
			**/
			void RunStringCommand(std::string command);

			/**
			** @brief Check if the data at a specific index is of a certain type
			** @param expected type
			** @param index on stack
			** @return true if types are confirmed, else false
			**/
			int IsType(DataType type, int index)const;

			/**
			**@brief Templated function provide support for numbers of any time without requiring the user to manually convert
			** after calling lua_ToNumber which is by default a double
			**@param Name represents name of the global variable on stack
			**/
			template<typename T> T PopNumeric(const char *variable);

			/**
			** @brief Pop number from table
			** @param key
			**/
			template<typename T> T PopNumericFromTable(const char* table, const char* key);

			/**
			** @Brief Function to provide support for popping strings off the lua file without having to go through the long processes
			** @param name of global variable on stack
			**/
			std::string PopString(const char *variable);

			/**
			** @Brief FUnction to pop strings off a table based on a key value
			** @param key
			**/
			std::string PopStringFromTable(const char* table, const char* key);

			/**
			** @brief Function to provide support for popping boolean values off the stack whilst automating the long processes involved
			** @param name of global variable on stack
			**/
			bool PopBoolean(const char* variable);

			/**
			** @brief Register C function within lua
			** @param function name
			** @param actual function
			**/
			void RegisterCFunction(const char* name, int (*function)(lua_State*));

			/**
			** @brief Print type of a element at chosen position on the stack 
			** @param index
			** @return type integer
			**/
			int TypeIdentifierAt(int index);

			/**
			** @brief Return type of variable at position "index" in the stack
			** @param index in the stack
			** @return type string
			**/
			const char* TypeNameAt(int index);

			/**
			** @brief Show/print all elements on the stack
			**/
			void DisplayStackedElementTypes();

			/**
			** @brief Set top index of lua
			** @param index
			**/
			void SetTop(int index);

			/**
			** @brief Get top of stack which is also the stack size
			** @return top positive index
			**/
			int GetTop()const;

			/**
			** @brief Clears lua stack by calling lua_settop(m_lua,0)
			**/
			void ClearStack();

			/**
			** @brief get a variable from the loaded lua chunk
			** @param variable name
			**/
			void GlobalToStack(const char* variable);

			/**
			** @brief Push a c function on stack to use for future operations
			** @param pointer to a c function
			**/
			void Push(int (*function)(lua_State*));

			/**
			** @brief Push decimal number onto stack
			** @param decimal
			**/
			void Push(double _number);
			/**
			** @brief Push integer number onto stack
			** @param integer
			**/
			void Push(int _number);

			/**
			** @brief Push boolean onto stack
			** @param boolean
			**/
			void Push(bool _bool);

			/**
			** @brief Push string onto stack
			** @param string
			**/
			void Push(std::string _string);

			/**
			** @brief Push userdata onto stack
			** @param user-defined objects
			**/
			void Push(void* _userData);

			/**
			** @brief Pop number off stack from a specified index
			** @parma index
			**/
			void Pop(int index = 1);

			/**
			** @brief Peek into stack for an integer from a specified index
			** @parma index
			**/
			int PeekInteger(int index);

			/**
			** @brief Peek into stack for a number from a specified index
			** @parma index
			**/
			double PeekDecimal(int index);

			/**
			** @brief Peek into stack for a string from a specified index
			** @parma index
			**/	
			std::string PeekString(int index);

			/**
			** @brief Peek into stack for a boolean from a specified index
			** @parma index
			** @return true or false depending on variable at index
			**/	
			int PeekBoolean(int index);

			/**
			** @brief Peek into stack for a user data type from a specified index
			** @parma index
			**/
			template<typename T> T* PeekUserData(int index);


			void BindModule();

		private:
			LuaManager(const LuaManager&) {}
			LuaManager& operator=(const LuaManager&) {return *this;}

			lua_State *m_lua;
		};
	}
}

/*
template<class T>
T* LuaManager::PopUserData(const char* object)
{
	lua_settop(m_lua,0);
	lua_getglobal(m_lua, variable);

	if(!lua_isuserdata(m_lua,1))
	{
		std::cout<<"Is not a number error"<<std::endl;
		return 0;
	}

	T* object = static_cast<T*>(lua_touserdata(m_lua,1));
	lua_pop(m_lua,1);

	return object;
}
*/
template<class T>
T* AABSEngine::Utility::LuaManager::PeekUserData(int index)
{
	if(!IsType(DataType::BOOLEAN,index))
	{
		std::cout<<"Not a user data type error has occured in lua manager peek"<<std::endl;
		return 0;
	}
	return static_cast<T*>(lua_touserdata(m_lua,index));
}

template<class T>
T AABSEngine::Utility::LuaManager::PopNumericFromTable(const char* table, const char *key)
{	
	T number;
	lua_settop(m_lua,0);
	lua_getglobal(m_lua,table);

	if(!lua_istable(m_lua,-1))
	{
		std::cout<<"Not a table"<<std::endl;
		return number;
	}

	lua_pushstring(m_lua,key); //push key on stack
	lua_gettable(m_lua,-2);
	
	if(!lua_isnumber(m_lua,-1))
	{
		std::cout<<"Not a numeric value from table"<<std::endl;
		return number;
	}

	number = lua_tonumber(m_lua,-1);
	lua_pop(m_lua,-1);

	return number;
}


template<class T>
T AABSEngine::Utility::LuaManager::PopNumeric(const char *variable)
{
	lua_settop(m_lua,0);
	lua_getglobal(m_lua, variable);

	if(!lua_isnumber(m_lua,1))
	{
		std::cout<<"Is not a number error"<<std::endl;
		return 0;
	}

	T number = (T)lua_tonumber(m_lua,1);
	lua_pop(m_lua,1);

	return number;
}

