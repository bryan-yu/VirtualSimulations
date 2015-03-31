#pragma once
#ifndef Hash_h
#define Hash_h
#include <string>
#include <cassert>
#include "types.h"
#include "MD5.h"

namespace AABSEngine
{
	namespace Utility
	{
		const size_t HASHTABLE_DEFAULT_SIZE = 100;
			
		const HashKey HASHTABLE_UNOCCUPIED_BUCKET = -1;

		const Decimal HASHTABLE_RESIZE_RATIO = 0.85;

		/**
		 * @struct HashNode 
		 *
		 * @brief Hash node definition
		 *
		 */
		template<class Data>
		struct HashNode
		{
		public:
			HashNode(HashKey key, Data data)
			{
				m_key = key;
				m_data = data;
			}

			HashNode& operator=(const HashNode& other)
			{
				if(this != &other)
				{
					m_key = other.m_key;
					m_data = other.m_data;
				}
				return *this;
			}

			HashNode()
			{
				m_key = HASHTABLE_UNOCCUPIED_BUCKET;
			}

			HashKey GetHash()const { return m_key; }

			Data GetData()const { return m_data; }

			void SetData(Data data) { m_data = data; }

		private:
			HashKey m_key;
			Data m_data;
		};



		template<class Data>
		class HashTable
		{
		public:
			~HashTable()
			{
				Clean();
			}

			HashTable()
			{
				m_hashTable = 0;
				m_freeBuckets = 0;
				m_totalSize = 0;
			}

			HashKey Insert(Data data, std::string key)
			{
				CheckResize();
		
				HashKey hash = MD5(key).decdigest() % m_totalSize; //generate hash key(array index)
				
	
				if(Hashed(hash)) //check if it exists within the hash table
				{
					hash = LinearProbe(hash); //probe for a free bucket
				}

				m_hashTable[hash] = HashNode<Data>(hash,data);
				--m_freeBuckets;

				return hash;
			}

			bool Remove(HashKey hash)
			{
				if(Exists(hash))
				{
					m_hashTable[hash].m_key = HASHTABLE_UNOCCUPIED_BUCKET;
					++m_freeBuckets;

					return true;
				}
				return false;
			}
	
			HashNode<Data>* Retrieve(HashKey hash)
			{
				if(Hashed(hash))
				{
					return &m_hashTable[hash];
				}
		
				return 0;
			}

			size_t FreeBuckets()const
			{ 
				return m_freeBuckets;
			}

			size_t TableSize()const
			{ 
				return m_totalSize;
			}

			bool Hashed(HashKey hash)const
			{
				if(hash < m_totalSize && m_hashTable[hash].GetHash() != HASHTABLE_UNOCCUPIED_BUCKET)
				{
					return true;
				}
				return false;
			}

			void Clear()
			{
				for(size_t i=0; i < TableSize(); i++)
				{
					Remove(i);
				}
			}

		private:
			HashTable(const HashTable&){}
			HashTable& operator=(const HashTable& ){ return *this; }

			HashKey LinearProbe(HashKey hash)
			{
				for(HashKey probe = (hash + 1) % m_totalSize; 
					probe != hash; 
					probe = (probe + 1) % m_totalSize)
				{
					if(m_hashTable[probe].GetHash() == HASHTABLE_UNOCCUPIED_BUCKET)
					{
						return probe;
					}
				}
				return 0 ;
			}

			void Clean()
			{
				delete []m_hashTable;
				m_hashTable = 0;

				m_freeBuckets = 0;
				m_totalSize = 0;
			}

			void CheckResize()
			{
				//ensure that the hash table always has buckets allocated
				if(m_hashTable == 0)
				{
					m_hashTable = new HashNode<Data>[HASHTABLE_DEFAULT_SIZE];

					if(m_hashTable)
					{
						m_freeBuckets = HASHTABLE_DEFAULT_SIZE;
						m_totalSize = HASHTABLE_DEFAULT_SIZE;
					}
					return;
				}

				const Decimal currRatio = (Decimal)(m_freeBuckets / m_totalSize);

				if(currRatio >= HASHTABLE_RESIZE_RATIO)
				{
					HashNode<Data> *temp = new HashNode<Data>[m_totalSize];
					memcpy(temp,m_hashTable,sizeof(HashNode<Data>) * m_totalSize);

					//increase the table memory alloc size to accomodate more elements in the future
					m_totalSize = (size_t)((m_totalSize * 3.0) * 0.5 + 1.0);

					//free memory and reallocate for bigger hash table
					delete []m_hashTable; 
					m_hashTable = temp;
				}
			}
	
			HashNode<Data> *m_hashTable;
			size_t m_freeBuckets;
			size_t m_totalSize;
		};
	}
}

#endif