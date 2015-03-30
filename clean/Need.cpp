#include "StdAfx.h"
#include "Need.h"
#include "AffordanceManager.h"
#include "NeedsEvaluators.h"

AABSEngine::AI::Need::Need(Decimal _min, Decimal _max, Decimal _base)
{
	//set parameters of the need
	
	SetMinimum(_min);

	SetMaximum(_max);

	SetBase(_base);

	ClampBase();
}

AABSEngine::AI::Need::Need(NeedDefinition need)
{
  SetMaximum(need.max);
  SetMinimum(need.min);
  SetBase(need.base);
  SetName(need.name);
  m_affordance = need.affordance;
  SetLowWaterMark(need.lowWaterMark);
  SetHighWaterMark(need.highWaterMark);
  /* TODO evaluator manager */
  if (need.evaluatorFunction == "LinearDecay" && need.evaluatorFunctionParam != 0)
    SetEvaluator(LinearDecay(need.evaluatorFunctionParam));//need.evaluatorFunctionParam)); // default of 5% LinearDecay
  else if (need.evaluatorFunction == "LinearGrowth" && need.evaluatorFunctionParam != 0)
    SetEvaluator(LinearGrowth(need.evaluatorFunctionParam));//need.evaluatorFunctionParam));
  else
    SetEvaluator(LinearDecay(5));//5)); // default of 5% LinearDecay
}

AABSEngine::AI::Need::Need(const Need& other)
{
	SetMinimum(other.m_minimum);

	SetMaximum(other.m_maximum);

	SetBase(other.m_base);

	SetEvaluator(other.m_evaluation);
}

void AABSEngine::AI::Need::ApplyDecay(Decimal x, Decimal duration)
{
	Decimal final = m_base - abs(x) * duration;

	#undef max
	m_base = std::max(m_minimum,final); 
}

void AABSEngine::AI::Need::ApplyGrowth(Decimal x, Decimal duration)
{
	Decimal final = m_base + abs(x) * duration;

	#undef min
	m_base = std::min(m_maximum,final); 
}

AABSEngine::AI::Need& AABSEngine::AI::Need::operator=(const Need& other)
{
	if(this != &other)
	{
		SetMinimum(other.m_minimum);

		SetMaximum(other.m_maximum);

		SetBase(other.m_base);

		SetEvaluator(other.m_evaluation);
	}
	return *this;
}

Decimal AABSEngine::AI::Need::GetBase()const
{
	return m_base;
}

Decimal AABSEngine::AI::Need::GetMaximum()const
{
	return m_maximum;
}

Decimal AABSEngine::AI::Need::GetMinimum()const
{
	return m_minimum;
}

Decimal AABSEngine::AI::Need::GetRange() const
{
  return (m_maximum - m_minimum);
}

std::string AABSEngine::AI::Need::GetName()const
{
	return m_name;
}

void AABSEngine::AI::Need::ClampBase()
{
	m_base = m_base > m_maximum ? m_maximum : m_base < m_minimum ? m_minimum : m_base;
}

void AABSEngine::AI::Need::SetName(std::string name)
{
	m_name = name;
}

void AABSEngine::AI::Need::SetMinimum(Decimal _min)
{
	if(_min > m_maximum)
	{
		m_minimum = m_maximum;
		m_maximum = _min;
	}
	else
	{
		m_minimum = _min;
	}
}

void AABSEngine::AI::Need::SetMaximum(Decimal _max)
{
	if(_max < m_minimum)
	{
		m_maximum = m_minimum;
		m_minimum = _max;
	}
	else
	{
		m_maximum = _max;
	}
}

void AABSEngine::AI::Need::SetBase(Decimal _base)
{
  m_base = _base;
  ClampBase();
  //std::cout << "SetNeed: " << m_name << ": " << m_base << std::endl;
}

std::string AABSEngine::AI::Need::GetSatisfyingAffordance() const
{
  return m_affordance;
}

void AABSEngine::AI::Need::SetLowWaterMark(Decimal mark)
{
  if (mark > 100) mark = 100;
  if (mark < 0) mark = 0;
  m_lowWaterMark = mark;
}

Decimal AABSEngine::AI::Need::GetLowWaterMark() const
{
  return m_lowWaterMark;
}

void AABSEngine::AI::Need::SetHighWaterMark(Decimal mark)
{
  if (mark > 100) mark = 100;
  if (mark < 0) mark = 0;
  m_highWaterMark = mark;
}

Decimal AABSEngine::AI::Need::GetHighWaterMark() const
{
  return m_highWaterMark;
}