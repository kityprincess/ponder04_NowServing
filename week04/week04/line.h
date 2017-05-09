/***********************************************************************
* Header:
*    Line
* Summary:
*    This class contains the line queue information.
* Authors:
*    Bryan Lopez, Kimberly Stowe, Matthew Burr & Shayla Nelson
************************************************************************/
#ifndef Line_h
#define Line_h

#include <string>      // for STRING
#include <cassert>
#include "student.h"
#include "deque.h"

class Line
{
public:
   Student serveNext() throw (std::string) 
   {
      if (line.empty()) 
         throw std::string("empty line"); 
      Student next = line.front(); // retrieve the next 
      line.pop_front(); // the patron is no longer at the front 
      return next; 
   }
   void addStudent(const Student & student)  { line.push_back(student); }
   void addEmerg(const Student & student)    { line.push_front(student); }
   bool emtpy() const                        { return line.empty(); }

private:
   Deque <Student> line;
};
#endif // LINE_H