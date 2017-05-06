#pragma once
/********************************************************************
* DEQUE
*
* Implements a deque, a double-ended-queue
* @author Matthew Burr
* @version 1.0
* @since 2017-05-06
*********************************************************************/

template <class T>
class Deque
{
public:
   // default and non-default constructor
   Deque<T>(int in_capacity = 0);
   
   // copy constructor
   Deque<T>(const Deque<T> & source);

   // destructor
   ~Deque();

   // assignment operator
   Deque<T> & operator = (const Deque<T> & rhs);

   // indicates if the deque is empty or not
   bool empty() const;

   // gets the size (# of items) in the deque
   int size() const;

   // gets the capacity (# of items it can hold) of the deque
   int capacity() const;

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

   // front and back nodes
   Node * m_front;
   Node * m_back;
};

