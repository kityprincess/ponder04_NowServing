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
   Student currentStudent;
   Student incomingStudent;
   
   // declaring variables
   string className;
   string name;
   int time;
   int minutesPassed = 0;

   // create deque to hold students
   Deque <Student> line;

   do {
      // keep track of minutes passed since simulation began
      cout << "<" << minutesPassed++ << "> ";
   
      // saving data into variables here
      cin >> className;
      if (className == "!!")
      {
         cin >> className >> name >> time;
         // passing these variable into student class
         incomingStudent.setClass(className);  
         incomingStudent.setName(name);
         incomingStudent.setTime(time);
         incomingStudent.setEmergency(true);
         line.push_front(incomingStudent);
      }
      else if (className != "none" && className != "finished")
      {
         cin >> name >> time;
         incomingStudent.setClass(className);  
         incomingStudent.setName(name);
         incomingStudent.setTime(time);
         incomingStudent.setEmergency(false);
         line.push_back(incomingStudent);
      }
      else if (className == "finished")
      {
         break;
      }
      else if (className != "none")
      {
         cout << "Invalid command";
      }
      int timeCount = currentStudent.getTime();
      if (timeCount > 0)
      {
         timeCount--;
         currentStudent.setTime(timeCount);
      }
      if (currentStudent.getTime() == 0)
      {
         if (!line.empty())
            currentStudent = line.pop_front();
      }
      if (currentStudent.getTime() > 0)
      {
         if (currentStudent.isEmergency())
         {
         cout << "\tEmergency for " << currentStudent.getName() << " for class "
            << currentStudent.getClass() << ". Time left: " << currentStudent.getTime() << endl;
         }
         else
         {
         cout << "\tCurrently serving " << currentStudent.getName() << " for class "
            << currentStudent.getClass() << ". Time left: " << currentStudent.getTime() << endl;
         }
      }
   }
   while (className != "finished");

   // end
   cout << "End of simulation\n";
}



