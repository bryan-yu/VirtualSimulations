#pragma once
#ifndef PriorityQ_h
#define PriorityQ_h

#include <vector>
#include <string>



namespace AABSEngine
{
	namespace Utility
	{
		#define PQ_INVALID_INDEX -1
		#define PQ_RESIZE 20

		/**
		 * @class ArrayException
		 *
		 * @brief 
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class ArrayException
		{
		public:
			ArrayException(std::string message) : m_message(message){}

			std::string Error()const { return m_message; }
		private:
			std::string m_message;
		};

		template<class T>
		class IndexedPQ
		{
		public:
			IndexedPQ(std::vector<T>& info) : m_maxSize(PQ_RESIZE), m_size(0), m_info(info)
			{
				p_greaterComparator = 0;

				m_links.resize(m_maxSize);
				m_revLinks.resize(m_maxSize);
			}

			IndexedPQ(size_t maxsize, std::vector<T>& info)  : m_info(info)
			{
				p_greaterComparator = 0;

				m_maxSize = maxsize;
				m_size = 0;

				m_links.resize(m_maxSize);
				m_revLinks.resize(m_maxSize);
			}

			void SetData(std::vector<T>& info)
			{
				m_info = info;

				m_links.clear();
				m_links.resize(m_info.size());

				m_revLinks.clear();
				m_revLinks.resize(m_info.size());
			}

			size_t Size()const { return m_size; }

			void UpdateAt(int elem_k)
			{
				if(!Empty() && elem_k >= 0 && elem_k < m_size)
				{
					BottomTopHeapify(m_revLinks[elem_k] + 1);
					TopBottomHeapify(m_revLinks[elem_k] + 1);
				}
			}

			void Add(int elem_k)
			{
				Expand();
	
				m_links[m_size] = elem_k; 	//store integer that can be used to access the m_info array in O(n) time
		
				m_revLinks[elem_k] = m_size; 
			
				BottomTopHeapify(++m_size);
			}


			T PopElem()
			{
				if(Empty())
				{
					throw ArrayException("Out of bounds array access attempt in priority queue");
				}

				return m_info[PopIndex()];
			}

			int PopIndex()
			{
				if(Empty())
				{
					return PQ_INVALID_INDEX; //represent invalid position
				}

				--m_size;

				Swap(0,m_size);

				int index = m_links[m_size]; //minimum element

				TopBottomHeapify(1); //reorder the queue, excluding last element which will be popped off
		
				return index; //return index pointing to an element removed from the referenced vector
			}

			int PeekIndex()
			{
				if(m_size != 0)
				{
					return m_links[0];
				}
				return PQ_INVALID_INDEX;
			}

			T PeekElem()
			{
				return m_info[m_links[m_size]];
			}

			bool Empty()const { return m_size == 0; }

			bool (*p_greaterComparator)(T o1, T o2);


		private:
			IndexedPQ(const IndexedPQ&){}
			IndexedPQ &operator=(const IndexedPQ&){return *this;}

			void Expand()
			{
				if(m_size + 1 >= m_maxSize)
				{
					m_maxSize += PQ_RESIZE;

					m_links.resize(m_maxSize);

					m_revLinks.resize(m_maxSize);
				}
			}

			//retrieve left child of parent if any
			//parent should be its 'size' index(i.e. arrayIdx + 1)
			//returns array index
			int LeftChild(const int parentSizeIndex)const
			{
				int arrayIndex = (parentSizeIndex * 2) - 1;

				return arrayIndex > (m_size - 1) ? -1 : arrayIndex;
			}
	
			//retrieve right child of parent if any
			//parent should be its 'size' index(i.e. arrayIdx + 1)
			//returns array index
			int RightChild(const int parentSizeIndex)const
			{
				int arrayIndex = (parentSizeIndex * 2);

				return arrayIndex > (m_size - 1) ? -1 : arrayIndex;
			}


			//retrieve parent of child
			//child index should be its 'size' index
			//returns array index
			int Parent(const int childSizeIndex)const
			{
				int arrayIndex = (childSizeIndex / 2) - 1;

				return arrayIndex < 0 ? -1 : arrayIndex;
			}

			void BottomTopHeapify(int size_idx)
			{
				int parent = Parent(size_idx);

	
				while(parent >= 0 && p_greaterComparator(m_info[m_links[parent]], m_info[m_links[size_idx - 1]]))
				{
					Swap(parent,size_idx - 1); //reshuffle elements
					size_idx = parent + 1; //back to 'size index'
					parent = Parent(size_idx); //move up the tree
				}
			}

			void TopBottomHeapify(int topSizeIdx)
			{
				while(topSizeIdx <= m_size)
				{
					int lchild = LeftChild(topSizeIdx);
					int rchild = RightChild(topSizeIdx);
					int swapChild = lchild;

					if(rchild < m_size && rchild >= 0 && p_greaterComparator(m_info[m_links[lchild]], m_info[m_links[rchild]]))
					{
						swapChild = rchild;
					}
								
					if(lchild < m_size && lchild >= 0 && p_greaterComparator(m_info[m_links[topSizeIdx - 1]], m_info[m_links[swapChild]]))
					{
						Swap(topSizeIdx - 1, swapChild);
						topSizeIdx = swapChild + 1;
					}
					else
					{
						return;
					}

				}
			}

			void Swap(int a, int b)
			{
				int temp = m_links[a];
				m_links[a] = m_links[b];
				m_links[b] = temp;

				m_revLinks[m_links[a]] = a;
				m_revLinks[m_links[b]] = b;
			}
	
			std::vector<T>& m_info;

			std::vector<int> m_links;

			std::vector<int> m_revLinks;

			int m_size;

			int m_maxSize;
		};
	}
}

#endif