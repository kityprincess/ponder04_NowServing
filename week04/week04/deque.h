#pragma once
/********************************************************************
* DEQUE
*
* Implements a deque, a double-ended-queue
* @author Matthew Burr
* @version 1.0
* @since 2017-05-06
* Citation: Props to Nyhoff's text book (chapter 8.3) for giving me
* a more efficient approach to popping items
*********************************************************************/
#include <new>
#include <cassert>

template <class T>
class Deque
{
public:
   // default and non-default constructor
   Deque<T>(int in_capacity = 0) :
      m_capacity(in_capacity), m_size(0), m_front(0), m_back(0)
   { }
   
   // copy constructor
   Deque<T>(const Deque<T> & source);

   // destructor
   ~Deque() { clear(); }

   // assignment operator
   Deque<T> & operator = (const Deque<T> & rhs);

   // indicates if the deque is empty or not
   bool empty() const { return m_size == 0; }

   // gets the size (# of items) in the deque
   int size() const { return m_size; }

   // gets the capacity (# of items it can hold) of the deque
   // now, we don't really need capacity since we're using a linked list,
   // so if we never really keep this up-to-date until somebody asks for it
   int capacity() 
   { 
      // if we haven't set the capacity yet, but we have some data
      // then we initialize our capacity to 1
      if (m_capacity == 0 && m_size > 0)
         m_capacity = 1;

      // if our capacity is ever less than our size, we just double it
      // until it exceeds our size
      while (m_capacity < m_size)
         m_capacity *= 2;

      return m_capacity; 
   }

   // empties the deque
   void clear();

   // adds an item to the back of the deque
   void push_back(T in_value);

   // adds an item to the front of the deque
   void push_front(T in_value);

   // removes an item from the back of the deque
   // also returns the item
   T pop_back();

   // removes an item from the front of the deque
   // also returns the item
   T pop_front();

   // returns the item at the front of the deque
   T front() const;

   // returns the item at the back of the deque
   T back() const;

private:
   // This internal class is used to store linked list items
   class Node
   {
   public:
      // Because it's internal to the deque class, we go ahead
      // and make fields public
      
      // the contained data
      T data;
      
      // the previous node in the list
      Node * prev;

      // the next node in the list
      Node * next;

      // there is no default constructor; only a non-default
      Node(T in_data, Node * in_prev = 0, Node * in_next = 0)
         : data(in_data), prev(in_prev), next(in_next)
      { }
   };

   // we can check this at any time to ensure our structure appears
   // valid -- useful for asserts
   bool isValid() const;

   // front and back nodes
   Node * m_front;
   Node * m_back;

   // keeping track of the size and capacity
   int m_capacity;
   int m_size;
};

/*****************************************************************************
* DEQUE :: COPY CONSTRUCTOR
* Creates a new deque by copying another
*****************************************************************************/
template<class T>
inline Deque<T>::Deque(const Deque<T>& source)
   : m_capacity(0), m_size(0), m_front(NULL), m_back(NULL)
{
   Node * ptr = source.m_front;

   // And now we just push the data onto our list one at a time
   while (ptr)
   {
      push_back(ptr->data);
      ptr = ptr->next;
   }

   // We expect our size to be the same as the source's at this point
   assert(m_size == source.m_size);

   // Make sure we're valid
   assert(isValid());
}

/*****************************************************************************
* DEQUE :: ASSIGNMENT
* Copies one deck onto another
*****************************************************************************/
template<class T>
inline Deque<T>& Deque<T>::operator=(const Deque<T>& rhs)
{
   // for starters, if we're copying onto ourselves, this is a noop
   if (this == &rhs)
      return *this;

   // okay, so now we clear our existing deque
   clear();

   // Now we copy the old onto the new

   // The easiest way to do this is simply to walk the rhs list
   // and push them onto our own -- this may not be the most
   // efficient, but we're not dealing with a lot of data right now
   m_size = 0; // we start at zero since we're currently empty
   Node * ptr = rhs.m_front;

   while (ptr)
   {
      push_back(ptr->data);
      ptr = ptr->next;
   }

   // we expect our size to be the same as the rhs size at this point
   assert(m_size == rhs.m_size);

   // lastly, we make sure we're valid
   assert(isValid());

   return *this;
}

/*****************************************************************************
* DEQUE :: CLEAR
* Empty the deque of all its contents
*****************************************************************************/
template<class T>
inline void Deque<T>::clear()
{
   // if we're already empty, then we don't need to do anything
   if (empty())
      return;

   // otherwise, we just walk through the list deleting nodes
   // we expect that we have a non-null front at this point
   while (NULL != m_front)
   {
      Node * oldFront = m_front;
      m_front = m_front->next;
      delete oldFront;
   }

   // we set m_back to NULL and set our size to 0
   m_back = NULL;
   m_size = 0;

   // and make sure we're valid after all this
   assert(isValid());
}

/*****************************************************************************
 * DEQUE :: PUSH BACK
 * Pushes an item onto the back of the deque.
 *****************************************************************************/
template<class T>
inline void Deque<T>::push_back(T in_value)
{
   Node * newNode = NULL;

   try
   {
      if (!empty())
      {
         // If we are not empty, then we assume that m_back is a valid
         // pointer
         assert(NULL != m_back);
         
         newNode = new Node(in_value, m_back, NULL);
         m_back->next = newNode;
         m_back = newNode;
      }
      else
      {
         // If we _are_ empty, then we assume that m_back and m_front 
         // are both null pointers
         assert(NULL == m_back && NULL == m_front);

         newNode = new Node(in_value);
         m_front = m_back = newNode;
      }
   }
   catch (std::bad_alloc ex)
   {
      throw "ERROR: Unable to allocate a new buffer for deque";
   }

   // At this point, but m_front and m_back should be non-null
   assert(NULL != m_back && NULL != m_front);

   m_size++;
   
   // Our size should be positive
   assert(m_size > 0);

   // as a final sanity check, we check our structure is valid
   assert(isValid());
}

/*****************************************************************************
* DEQUE :: PUSH FRONT
* Pushes an item onto the front of the deque.
*****************************************************************************/
template<class T>
inline void Deque<T>::push_front(T in_value)
{
   Node * newNode = NULL;

   try
   {
      if (!empty())
      {
         // we expect that m_front is not null
         assert(NULL != m_front);

         newNode = new Node(in_value, NULL, m_front);
         m_front->prev = newNode;
         m_front = newNode;
      }
      else
      {
         // we expect that both m_front and m_back are null
         assert(NULL == m_front && NULL == m_back);
         
         newNode = new Node(in_value);
         m_front = m_back = newNode;
      }
   }
   catch (std::bad_alloc ex)
   {
      throw "ERROR: Unable to allocate a new buffer for deque";
   }

   // at this point neither m_front nor m_back should be null
   assert(NULL != m_front && NULL != m_back);

   m_size++;

   // size should be greater than 0
   assert(m_size > 0);

   // and we do once last sanity check that we're valid
   assert(isValid());
}

/*****************************************************************************
* DEQUE :: POP BACK
* Pops an item off of the back; also returns it
*****************************************************************************/
template<class T>
inline T Deque<T>::pop_back()
{
   // if we are empty, then we return an error
   if (empty())
      throw "ERROR: unable to pop from the back of empty deque";

   // We are assuming at this point that our m_back is a
   // valid, non-null pointer
   assert(NULL != m_back);

   T data = m_back->data;
   
   Node * oldBack = m_back;
   m_back = m_back->prev;
   delete oldBack;

   if (NULL == m_back) // indicating we're empty
      m_front = NULL;
   else
      m_back->next = NULL; // the last node shouldn't point to a next node

   m_size--;

   // check to ensure our structure is valid
   assert(isValid());

   return data;
}

/*****************************************************************************
* DEQUE :: POP FRONT
* Pops an item off of the front; also returns it
*****************************************************************************/
template<class T>
inline T Deque<T>::pop_front()
{
   // if we're empty, we return an error
   if (empty())
      throw "ERROR: unable to pop from the front of empty deque";

   // we expect m_front to be non-null
   assert(NULL != m_front);

   T data = m_front->data;

   Node * oldFront = m_front;
   m_front = m_front->next;
   delete oldFront;

   if (NULL == m_front) // indicating we're empty
      m_back = NULL;
   else
      m_front->prev = NULL; // the front node shouldn't point to a previous

   m_size--;

   // ensure we're valid
   assert(isValid());

   return data;
}

/*****************************************************************************
* DEQUE :: FRONT
* Returns the item at the front of the deque
*****************************************************************************/
template<class T>
inline T Deque<T>::front() const
{
   if (!empty())
   {
      // we expect that m_front is not null
      assert(NULL != m_front);
      return m_front->data;
   }
   else
   {
      throw "ERROR: unable to access data from an empty deque";
   }
}

/*****************************************************************************
* DEQUE :: BACK
* Returns an item from the back of the deque
*****************************************************************************/
template<class T>
inline T Deque<T>::back() const
{
   if (!empty())
   {
      // we expect that m_back is not null
      assert(NULL != m_back);
      return m_back->data;
   }
   else
   {
      throw "ERROR: unable to access data from an empty deque";
   }
}

/*****************************************************************************
* DEQUE :: IS VALID
* Checks to see that the deque is in a valid state
*****************************************************************************/
template<class T>
inline bool Deque<T>::isValid() const
{
   bool valid = true;

   // size should alway be positive or 0
   valid = valid && (m_size >= 0);
   
   // if size is 0, then our pointers should be null
   valid = valid && (m_size != 0 || (m_front == NULL && m_back == NULL));

   // if size is not zero, then our pointers should be non-null
   valid = valid && (m_size == 0 || (m_front != NULL && m_back != NULL));

   // lastly, if our size is 1, then m_front should == m_back
   valid = valid && (m_size != 1 || (m_front == m_back));

   return valid;
}


