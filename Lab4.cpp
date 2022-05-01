//I have compiled and run this code successfully using the g++ compiler on Terminal in MacOS High Sierra

#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
//The header file containing the class Student and class University
#include "Lab4.h"  

using namespace std;

//This function find the university whose name match with "university_name"
//and return their index
int find_university(string university_name, University** list_of_university, const int number_of_university)
{
	for(int i = 0; i < number_of_university; i++)
	{
		if(list_of_university[i]->get_name() == university_name)
		{
			return i;
		}
	}
	return -1;
}

//this function prompt the user to choose which university user want to interact with
//and return the corresponding value
int display_universities_as_options(University** list_of_university, int number_of_university, string action)
{
	if(number_of_university < 1)
	{
		return -1;
	}
	for(int i = 0; i < number_of_university; i++)
    {
  	    cout<<"Press "<<i+1<<" if you want to "<< action <<" students from "<<list_of_university[i]->get_name()<<endl;
    }
	cout<<"Please enter the number here: ";
	int input, status, temp;
	status = scanf("%d", &input);
	int limit = 0;
	while(status!=1)
	{
		if(limit < 10)
		{
			printf("Invalid input... please enter a number: ");
			cin.ignore(100,'\n');
		    status = scanf("%d", &input);
		    limit++;
		}
		else
		{
			return -1;
		}
	}
	return input;
}

int main()
{
	University ** list_of_university = new University* [1];

	int number_of_university = 0;

    //the condition of the "while" loop to pop up the menu
    // if working is true, then continue to show the menu to the user, otherwise exit the program
    bool working = true;

    //This variable represents the action that the users want to carry out
    int actions = 0;

    cout<<endl<<endl<<endl<<"/***************************";
    cout<<endl<<endl<<endl;
    cout<<"Please keep in mind that this program allows user to create multiple Universities.";
    cout<<endl<<"Please follow the on-screen instructions.";
    cout<<endl;
    cout<<endl<<endl<<"/***************************"<<endl<<endl;
    while(working)
    {
        //Print out the menu
        cout<<"Please enter the number according to your desired actions"<<endl;
        cout<<"Enter 1 to add a new student and their score."<<endl;
        cout<<"Enter 2 to view all current students from a particular university and their respective score."<<endl;
        cout<<"Enter 3 to view the student(s) with the highest score from a particular university."<<endl;
        cout<<"Enter 4 to delete the first student with this name in a particular university."<<endl;
        cout<<"Enter 5 to view all current students from all universities."<<endl;
        cout<<"Enter any other number to exit."<<endl;
        cin>>actions;

        switch(actions){
          case 1:{ //add a student to a university
          	cout<<"Please enter the university name: ";
          	string university_name;          	
            cin.ignore(100, '\n');
            getline(cin, university_name);
            
            int university_index = find_university(university_name, list_of_university, number_of_university);
            if(university_index == -1)
            {	
            	number_of_university++;
            	list_of_university = (University**)realloc(list_of_university, sizeof(University*) * number_of_university);
            	list_of_university[number_of_university - 1] = new University(university_name);
            	list_of_university[number_of_university - 1]->add_student();
            }
            else
            {
            	list_of_university[university_index]->add_student();
            }

            cout<<endl;
            break;
        }
          case 2:{ //display all students from a university

          	//Prompt user to choose univerisity
          	int status = display_universities_as_options(list_of_university, number_of_university, "view");

      			if(number_of_university >= 1)
            {
              if(status < 1 || status > number_of_university)
        			{
        				cout<<endl;
        				cout<<endl;
        				cout<<"There is no such university"<<endl;
        				cout<<endl;
        				cout<<endl;
        			}
        			else	
        			{
        				if(list_of_university[status-1]->get_number_of_student() > 0)
        				{
                    cout<<setw(7)<<"Name"<<setw(30)<<"Score"<<setw(15)<<"University"<<endl;
        					  list_of_university[status-1]->display_all_students(0);
        				}
        				else
        				{
        					cout<<endl;
        					cout<<endl;
        					cout<<"There is no student in that university.";
        					cout<<endl;
        					cout<<endl;
        				}
        			}
            }
            else
            {
              cout<<"You have not created any University yet."<<endl;
              cout<<"Please use feature number 1 (add a student and their score) before using this feature"<<endl<<endl;
            }
      			cout<<endl;
            break;
        }
          case 3:{ //display the highest score student(s) from a university
            if(number_of_university >= 1)
            {
              //Prompt user to choose univerisity
              int status = display_universities_as_options(list_of_university, number_of_university, "view");

              if(status < 1 || status > number_of_university)
              {
                cout<<endl;
                cout<<endl;
                cout<<"There is no such university"<<endl;
                cout<<endl;
                cout<<endl;
              }
              else  
              {
                if(list_of_university[status-1]->get_number_of_student() > 0)
                {
                  list_of_university[status-1]->display_max();
                }
                else
                {
                  cout<<endl;
                  cout<<endl;
                  cout<<"There is no student in that university.";
                  cout<<endl;
                  cout<<endl;
                }
              }
              cout<<endl;
            }
            else
            {
              cout<<"You have not created any University yet."<<endl;
              cout<<"Please use feature number 1 (add a student and their score) before using this feature"<<endl<<endl;
            }       	
            break;
        }
          case 4:{ //delete a student from a university
            if(number_of_university >= 1)
            {
              //Prompt user to choose univerisity
              int status = display_universities_as_options(list_of_university, number_of_university, "delete");

              if(status < 1 || status > number_of_university)
              {
                cout<<endl;
                cout<<endl;
                cout<<"There is no such university"<<endl;
                cout<<endl;
                cout<<endl;
              }
              else  
              {
                if(list_of_university[status - 1]->get_number_of_student() >= 1)
                {
                  cout<<"Please enter the name you want to delete: ";
                  string name_to_delete;
                  cin.ignore(100, '\n');
                  getline(cin, name_to_delete);
                  if(!list_of_university[status-1]->delete_student(name_to_delete))
                  {
                    cout<<endl;
                    cout<<endl;
                    cout<<"There is no students with that name.";
                    cout<<endl;
                    cout<<endl;
                    cout<<endl;
                  }
                }
                else
                {
                  cout<<endl<<endl<<"There is no student in that University."<<endl<<endl<<endl;
                }
              }
              cout<<endl;
            }
            else
            {
              cout<<"You have not created any University yet."<<endl;
              cout<<"Please use feature number 1 (add a student and their score) before using this feature"<<endl<<endl;
            }
          	
            break;
        }
          case 5:{ //display all students from all universities
          	if(number_of_university >= 1)
          	{
          		cout<<setw(7)<<"Name"<<setw(30)<<"Score"<<setw(15)<<"University"<<endl;
          	    int total_num_of_student = 0;
	          	for(int i = 0; i < number_of_university; i++)
	          	{
	          		list_of_university[i]->display_all_students(total_num_of_student);
	          		total_num_of_student +=list_of_university[i]->get_number_of_student();
	          	}
	          	if(total_num_of_student == 0)
	          	{
	          		cout<<"There is no student in all of the Universities."<<endl<<endl;
	          	}
	          	cout<<endl;
	        }
	        else
	        {
	        	cout<<"You have not created any University yet."<<endl;
	        	cout<<"Please use feature number 1 (add a student and their score) before using this feature"<<endl<<endl;
	        }
          	break;
          }

          default:{
            working = false;

            //Delete the list_of_university
            for(int i = 0; i < number_of_university; i++)
            {
            	delete list_of_university[i];
            } 
            break;
        }
    }
    }
    return 0;
}
