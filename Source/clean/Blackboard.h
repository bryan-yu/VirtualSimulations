#pragma once

#include <vector>

namespace AABSEngine
{
  namespace AI
  {
    template <typename T>
		/**
		* @class Blackboard
		*
		* @brief Virtual blackboard (or bulletin board) for handling globally available interactions
		*
		* @author AABS
		* @version X
		* @date October 2013
		*
		*/
    class Blackboard
    {
    private:
      typename std::vector<T*>::iterator pos;
      typename std::vector<T*> m_items;
    protected:
      void IndexFirstEntry();
      bool GetNextEntry(T** entry);
	  std::vector<T*> GetItemList() const { return m_items; }
    public:
      virtual ~Blackboard() = 0 { pos = m_items.begin(); } /* to make pure virtual without providing a specific function to overload */
      void AddEntry(T* entry) { m_items.push_back(entry); }
      void RemoveEntry(T* entry);
      /* implement GetEntry getters in derived classes */
    };

	template <typename T>
	void Blackboard<T>::RemoveEntry(T* entry) 
	{ 
		for (std::vector<T*>::iterator it = m_items.begin(); it != m_items.end(); ) 
		{
			if (*it == entry) 
			{ 
				delete *it; 
				it = m_items.erase(it); 
			} 
			else 
			{
				it++;
			}
		}
    }

		template <typename T>
		void Blackboard<T>::IndexFirstEntry()
		{
			pos = m_items.begin();
		}

		template <typename T>
		bool Blackboard<T>::GetNextEntry(T** entry)
		{
			*entry = NULL;
			if (pos != m_items.end())
			{
				*entry = *pos;
				pos++;
			}
			return (*entry != NULL);
		}
	}
}