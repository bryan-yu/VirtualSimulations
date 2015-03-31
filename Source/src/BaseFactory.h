#pragma once
#ifndef BASEFACTORY_H_INCLUDED
#define BASEFACTORY_H_INCLUDED

#include <map>
#include <iterator>
#include <new>
#include <iostream>
#include <string>


namespace AABSEngine
{
	namespace Utility
	{

		template<class Base>
		/**
		** @class Factory
		*
		* @brief Abstract factory in which every instance should have a base class as the template parameter. From there, register new 
		* objects derived from the base class and ensure that the constructor 
		*
		* MANUAL:
		* 1) Classes that are abstract will be required to be declared when creating a factory which creates more specific products i.e. Factory<Projectile>
		*
		* 2) When registering an object, i.e. Factory<BASE> test;   test.Register<Derived>("LaserBolt");
		*
		* 3) When dynamically creating an object i.e. Projectile *product= test.Create("LaserBolt") 
		*
		* Future Revisions: Factory<Base> --> test.Register<DERIVED> --> perhaps create a hash look-up based on derived std::type_Info ... thus --->  test.Create<DERIVED>()
		*
		* Pointers to these dynamically allocated objects are left to the user to ensure that they are safely destroyed/used.
		*
		* @author Bryan Yu
		* @version 01
		* @date 10/9/2012 Started
		*
		**/
		class Factory
		{
		private:
				Factory(const Factory &otherFactory) {}
				Factory &operator=(const Factory &otherFactory) {return *this;}

		protected:

				template<typename DerivedProduct>
				static Base *RegisFunc()
				{
					return new(std::nothrow) DerivedProduct();
				}

				typedef std::string Key;
				typedef Base* (*Creator)();

				/**@brief Map which stores a key and a 'callback creation' function.**/
				std::map<Key, Creator> m_Databank;

				/**@brief Iterator which allows traversals to be made in m_Database if necessary**/
				typename std::map<Key, Creator>::iterator m_Itr;

		public:
		
				Factory() {};
				~Factory() { Clear(); }

				/**@brief Searches the map and creates a new object via m_Itr->second() which actually calls CreateRegis<AssignedType>
				**@return  NULL if no such object is found
				**@param id is the map key used to search for the item.
				**/
				Base *Create(Key id);

				template<typename DerivedProduct> void Register(Key id)
				{
					Creator callback = RegisFunc<DerivedProduct>;
					m_Databank.insert( std::make_pair(id, callback) );
				}

				/**@brief Removes a object function pointer based on id passed in**/
				void DeRegister(Key id);

				/**@brief Performs a completely cleanup of the map**/
				void Clear();

				/**@brief Check if a product exists in the factory**/
				bool Exists(const Key key);
		};
	}
}

template<class Base>
bool AABSEngine::Utility::Factory<Base>::Exists(const Key key)
{
	m_Itr = m_Databank.find(key);

	if(m_Itr == m_Databank.end())
	{
		return false;
	}
	else
	{
		return true;
	}
}

template<class Base>
void AABSEngine::Utility::Factory<Base>::Clear()
{
    m_Databank.clear();
}

template<class Base>
void AABSEngine::Utility::Factory<Base>::DeRegister(Key id)
{
    m_Databank.erase(id);
}


template<class Base>//issues with string keys...
Base *AABSEngine::Utility::Factory<Base>::Create(Key id)
{
    m_Itr = m_Databank.find(id);

    if(m_Itr != m_Databank.end())
    {
        return m_Itr->second(); //will hold static create functions, every call calls the product's constructor and creates the object i.e. m_Database[id].Create()
    }
//std::cout<<"returning NULL..."<<std::endl;
    return NULL;
}

#endif // BASEFACTORY_H_INCLUDED
