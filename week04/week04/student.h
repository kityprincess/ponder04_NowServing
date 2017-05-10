/***********************************************************************
 * Header:
 *    Student
 * Summary:
 *    This class contains the student input.
 * Authors:
 *    Bryan Lopez, Kimberly Stowe, Matthew Burr & Shayla Nelson
 ************************************************************************/
#ifndef Student_h
#define Student_h

#include <string>      // for STRING
#include <cassert>
using namespace std;

class Student
{
  public:
   Student() : m_time(0) { };
   int getTime() const                  { return m_time;       }
   string getName() const               { return m_name;       }
   string getClass() const              { return m_className;  }
   bool isEmergency() const             { return m_emergency;  }
   void setTime(int in_time)            { assert(m_time > -1);  this->m_time = in_time; }
   void setName(string in_name)         { this->m_name = in_name;  }
   void setClass(string in_className)   { this->m_className = in_className; }
   void setEmergency(bool in_emergency) { this->m_emergency = in_emergency; }

  private:
   string m_name;
   string m_className;
   int m_time;
   bool m_emergency;
};
#endif // STUDENT_H
