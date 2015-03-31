#pragma once

#include "ActionTrigger.h"

namespace AABSEngine
{
  namespace AI
  {
    class LocalNeedTrigger: public ActionTrigger
    {
    private:
      std::string m_need;
      Decimal threshold;
    protected:
    public:
      LocalNeedTrigger(std::string need, Decimal threshold);
      virtual void Evaluate(Agent* agent, AABSEngine::Core::InteractiveObject* object);
    };
  }
}