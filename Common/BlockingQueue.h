#ifndef _BLOCKING_QUEUE_H_
#define _BLOCKING_QUEUE_H_

#include <boost/noncopyable.hpp>
#include <deque>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>

template<class T>
class BlockingQueue : boost::noncopyable
{
public:
   typedef std::deque<T> container_type;
   typedef T value_type;
   
private:
   boost::mutex m_mutex;
   boost::condition_variable m_signal;
   container_type m_container;

public:
   int size()
   {
      boost::mutex::scoped_lock lock(m_mutex);
      return m_container.size();
   }

   bool push(const value_type& v)
   {
      boost::mutex::scoped_lock lock(m_mutex);
      m_container.push_front(v);
      m_signal.notify_one();
      return true;
   }

   T& head()
   {
      boost::mutex::scoped_lock lock(m_mutex);
      while (m_container.empty())
      {
         m_signal.wait(lock);  // yield the mutex and wait
      }
      return m_container.back();
   }

   T pop()
   {
      boost::mutex::scoped_lock lock(m_mutex);

      while ( m_container.empty() )
      {
         m_signal.wait( lock );  // yield the mutex and wait
      }

      // now we are here so there must be something on the queue.

      // Remove the item from the queue
      T res = m_container.back();  
      m_container.pop_back();

      return res;
   }
};

#endif