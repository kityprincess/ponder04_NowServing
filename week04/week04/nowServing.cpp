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
#include "line.h"       // for LINE
using namespace std;

/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   // display instructions
   cout << "Every prompt is one minute.  The following input is accepted:\n";
   cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   cout << "\tnone                         : no new request this minute\n";
   cout << "\tfinished                     : end simulation\n";

   // create students
   Student currentStudent;    // the student currently being helped
   Student incomingStudent;   // the student entering the line
   
   // declare variables
   string className;
   string name;
   int time;
   int minutesPassed = 0; 

   Line line;      // create a line of students, held in a deque

   // loop through prompts until finished
   do {
      cout << "<" << minutesPassed++ << "> ";      // keep track of minutes passed since simulation began
   
      // get user input
      cin >> className;
      if (className == "!!")     // handle emergency case and skip over exclamation points
      {
         cin >> className >> name >> time;      // store input in variables

         // pass the data to incomingStudent
         incomingStudent.setClass(className);  
         incomingStudent.setName(name);
         incomingStudent.setTime(time);
         incomingStudent.setEmergency(true);
         line.addEmerg(incomingStudent);      // add emergency incomingStudent to front of line
      }
      else if (className != "none" && className != "finished")    // handle regular help request
      {
         cin >> name >> time;    // store input in variables

         // pass the data to incomingStudent
         incomingStudent.setClass(className);  
         incomingStudent.setName(name);
         incomingStudent.setTime(time);
         incomingStudent.setEmergency(false);
         line.addStudent(incomingStudent);     // add regular incomingStudent to back of line
      }
      else if (className == "finished")      // break if finished
      {
         break;
      }

      int timeCount = currentStudent.getTime();          // keep track of the currently helped student's remaining time

      if (timeCount > 0)      // if time left, decrement and set current student's remaining time
      {
         timeCount--;
         currentStudent.setTime(timeCount);
      }

      if (timeCount == 0)     // if no time left, let's serve someone else!
      {
         if (!line.empty())
            currentStudent = line.serveNext();
      }

      if (currentStudent.getTime() > 0)      // we have a new current student so we need to get time again
      {
         if (currentStudent.isEmergency())      // display status of emergency request
         {
         cout << "\tEmergency for " << currentStudent.getName() << " for class "
            << currentStudent.getClass() << ". Time left: " << currentStudent.getTime() << endl;
         }
         else     // display status of regular request 
         {
         cout << "\tCurrently serving " << currentStudent.getName() << " for class "
            << currentStudent.getClass() << ". Time left: " << currentStudent.getTime() << endl;
         }
      }
   }
   while (className != "finished");

   cout << "End of simulation\n";      // end simulation
}



