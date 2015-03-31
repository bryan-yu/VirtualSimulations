#pragma once

#include "ActionTrigger.h"

namespace AABSEngine
{
  namespace AI
  {
    class TargetMoodTrigger: public ActionTrigger
    {
    private:
    protected:
    public:
      TargetMoodTrigger();
      virtual void Evaluate(Agent* agent, AABSEngine::Core::InteractiveObject* object);
    };
  }
}