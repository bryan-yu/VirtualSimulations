#pragma once

#include "ActionTrigger.h"

namespace AABSEngine
{
  namespace AI
  {
    class TargetNeedTrigger: public ActionTrigger
    {
    private:
    protected:
    public:
      TargetNeedTrigger();
      virtual void Evaluate(Agent* agent, AABSEngine::Core::InteractiveObject* object);
    };
  }
}