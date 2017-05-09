/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE
#include "student.h"    // for Student data
#include "line.h"
using namespace std;

/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   // instructions
   cout << "Every prompt is one minute.  The following input is accepted:\n";
   cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   cout << "\tnone                         : no new request this minute\n";
   cout << "\tfinished                     : end simulation\n";

   // your code here
   Student student;
   int timeCount = student.getTime();
   
   // declaring variables
   string m_className;
   string m_name;
   int m_time;
   
   // saving data into variables here
   cin >> m_className >> m_name >> m_time;
   
   // passing these variable into student class
   student.setClass(m_className);  
   student.setName(m_name);
   student.setTime(m_time);

   Deque <Student> line;
   if (student.emerg())
   {
      line.push_front(student);
      cout << "Emergency for " << line.front().getName() << " for class "
         << line.front().getClass() << ". Time left: " << timeCount--;
   }
   else if (m_className == "none")
   {
      cout << "Currently serving " << line.front().getName() << " for class "
         << line.front().getClass() << ". Time left: " << timeCount--;
   }
   else if (m_className == "finished")
   {
      return;
   }
   else
   {
      line.push_back(student);
      cout << "Currently serving " << line.front().getName() << " for class "
         << line.front().getClass() << ". Time left: " << timeCount--;
   }

   // end
   cout << "End of simulation\n";
}



