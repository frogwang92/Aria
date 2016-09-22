#ifndef _SCOPEDGILRELEASE_H_
#define _SCOPEDGILRELEASE_H_

#include <Python.h>

struct ScopedGILAcquire
{
   ScopedGILAcquire()
   {
      state = PyGILState_Ensure();
   }
   ~ScopedGILAcquire()
   {
      PyGILState_Release(state);
   }
private:
   PyGILState_STATE state;
};

struct ScopedGILRelease
{
   ScopedGILRelease(void)
   {
      m_thread_state = PyEval_SaveThread();
   }

   ~ScopedGILRelease(void)
   {
      PyEval_RestoreThread(m_thread_state);
      m_thread_state = NULL;
   }

private:
   PyThreadState* m_thread_state;
};

#endif