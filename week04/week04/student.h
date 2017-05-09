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
   Student student(bool emerg() = 0);
   int getTime() const                 { return m_time;       }
   string getName() const              { return m_name;       }
   string getClass() const             { return m_className;  }
   void setTime(int m_time)            { assert(m_time > 0);  this->m_time = m_time; }
   void setName(string m_name)         { this->m_name = m_name;  }
   void setClass(string m_className)   { this->m_className = m_className;  }
   bool emerg()                        { if (m_className == "!!") return 1; }

  private:
   string m_name;
   string m_className;
   int m_time;
};
#endif // STUDENT_H
