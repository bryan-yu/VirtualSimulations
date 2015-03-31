#pragma once

#include "Types.h"


namespace AABSEngine
{
	namespace AI
	{
		template<class Argument_T, class Return_T>
		/**
		* @class GeneralEvaluator
		*
		* @brief General evaluator
		*
		* @author AABS
		* @version X
		* @date October 2013
		*
		*/
		class GeneralEvaluator
		{
		public:
			virtual ~GeneralEvaluator(){}

			//Performing cloning i.e. deep copying of two functor objects
			virtual GeneralEvaluator* Clone()const = 0;

			//Perform evaluation 
			virtual Return_T Evaluate(Argument_T in)const = 0;
		};

		template<class Functor_T, class Argument_T, class Return_T>
		class StandardEvaluator : public GeneralEvaluator<Argument_T, Return_T>
		{
		public:
			explicit StandardEvaluator(Functor_T functor)
			{
				m_functor = functor;
			}

			virtual Return_T Evaluate(Argument_T in)const
			{
				return m_functor(in);
			}

			virtual GeneralEvaluator<Argument_T, Return_T>* Clone()const
			{
				return new StandardEvaluator(*this);
			}

		protected:
			Functor_T m_functor;
		};

		template<class Argument_T, class Return_T>
		class Evaluator
		{
		public:
			Evaluator()
			{
				m_function = 0;
			}

			~Evaluator()
			{
				Free();
			}

			Evaluator(const Evaluator& other)
			{
				Copy(other);
			}

			Evaluator& operator=(const Evaluator& other)
			{
				if(this != &other)
				{
					Free();
					Copy(other);
				}
				return *this;
			}

			template<class Functor_T> Evaluator(Functor_T functor)
			{
				m_function = new StandardEvaluator<Functor_T, Argument_T, Return_T>(functor);
			}

			Return_T operator()(Argument_T in)const
			{
				return m_function->Evaluate(in);
			}

			bool ContainsFunctor()const 
			{
				return m_function; 
			}

			void ClearFunctor()
			{
				Free();
			}

		private:
			void Free()
			{
				if(m_function) 
				{
					delete m_function;
					m_function = 0;
				}
			}

			void Copy(const Evaluator& other)
			{
				m_function = other.m_function ? other.m_function->Clone() : 0;
			}

			GeneralEvaluator<Argument_T, Return_T>* m_function;
		};
	}
}