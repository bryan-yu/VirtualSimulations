#pragma once

#include "Need.h"
#include <cmath>

namespace AABSEngine
{
	namespace AI
	{
		struct LinearDecay
		{
		private:
			int m_rate;
		public:
			LinearDecay() { m_rate = 0; }
			LinearDecay(int rate) { if (rate > 0) rate *= -1; m_rate = std::max(std::min(0, rate), -100); }
			Decimal operator() (const Need* n) const
			{
			Decimal change = (m_rate / n->GetRange())*100;
			return n->GetBase() + change;
			}
		};

		struct LinearGrowth
		{
		private:
			int m_rate;
		public:
			LinearGrowth() { m_rate = 0; }
			LinearGrowth(int rate) { m_rate = abs(m_rate = std::max(std::min(100, rate), 0)); }
			Decimal operator() (const Need* n) const
			{
			Decimal change = (m_rate / n->GetRange())*100;
			return n->GetBase() + change;
			}
		};
	}
}