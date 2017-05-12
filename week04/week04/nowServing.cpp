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
   int timeCount = student.getTime();

   cin >> student.setClass() >> student.setName() >> student.setTime();

   if (student.emerg())
   {
      line.addEmerg(student);
      cout << "Emergency for " << line.front().student.getName() << " for class "
         << line.front().student.getClass() << ". Time left: " << timeCount--;
   }
   else if (student.getClass == "none")
   {
      cout << "Currently serving " << line.front().student.getName() << " for class "
         << line.front().student.getClass() << ". Time left: " << timeCount--;
   }
   else if (student.getClass == "finished")
   {
      return;
   }
   else
   {
      line.addStudent(student);
      cout << "Currently serving " << line.front().student.getName() << " for class "
         << line.front().student.getClass() << ". Time left: " << timeCount--;
   }

   // end
   cout << "End of simulation\n";
}


