#pragma once

namespace AABSEngine
{
  namespace Core
  {
    template <typename T>
    class Singleton
    {
    private:
      static T* m_instance;
      Singleton();
      ~Singleton();
    protected:
    public:
      static T* Instance();
    };

    template <typename T>
    T* Singleton<T>::m_instance = NULL;

    template <typename T>
    T* Singleton<T>::Instance() 
    { 
      if (m_instance == NULL) 
        m_instance = new T(); 
      return m_instance;
    }
  }
}
