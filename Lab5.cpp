//I have compiled and run this code successfully using the g++ compiler on Terminal in MacOS High Sierra

#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
//The header file containing the class Student and class University
#include "Lab5.h"  

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
	fflush(stdin);
	int limit = 0;
	while(status!=1)
	{
		if(limit < 10)
		{
			printf("Invalid input... please enter a number: ");
			cin.ignore(100,'\n');
		    status = scanf("%d", &input);
		    fflush(stdin);
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

	int first_time = 1;

	int change_attributes = 1;

    //the condition of the "while" loop to pop up the menu
    // if working is true, then continue to show the menu to the user, otherwise exit the program
    bool working = true;

    //This variable represents the action that the users want to carry out
    int actions = -1;

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
        cout<<"Enter 2 to view all current students from a particular university and their respective scores."<<endl;
        cout<<"Enter 3 to delete the first student with this name in a particular university."<<endl;
        cout<<"Enter 4 to view all current students from all universities."<<endl;
        cout<<"Enter 5 to view all current Uni students from a particular university and their respective scores."<<endl;
        cout<<"Enter 6 to view all current College students from a particular university and their respective scores."<<endl;
        cout<<"Enter any other number to exit."<<endl;
        if(first_time == 1)
        {
        	int status;
			status = scanf("%d", &actions);
			fflush(stdin);
			int limit = 0;
			while(status!=1)
			{
				if(limit < 10)
				{
					printf("Invalid input... please enter a number: ");
					cin.ignore(100,'\n');
				    status = scanf("%d", &actions);
				    fflush(stdin);
				    limit++;
				}
				else
				{
					status = 1;
					actions = 4;
					cout<<"You've entered the wrong input too many times, now you will be defaulted to action number 4(show all students)."<<endl;
				}
			}
        	first_time = 0;
        }
        else
        {
        	cin.ignore(100, '\n');
        	cin>>actions;
        	change_attributes = 0;
        }

        switch(actions){
          case 1:{ //add a student to a university
          	cout<<"Please enter the university name: ";
          	string university_name;          	
            cin.ignore(100, '\n');
            getline(cin, university_name);
            
            cout<<"Enter 1 if you want to add a university student."<<endl;
            cout<<"Enter 2 if you want to add a college student."<<endl;
            cout<<"Enter the number here: ";
            int input, status, temp;
			status = scanf("%d", &input);
			int limit = 0;
			while(status!=1)
			{
				if(limit < 3)
				{
					printf("Invalid input... please enter a number: ");
					cin.ignore(100,'\n');
				    status = scanf("%d", &input);
				    limit++;
				}
				else
				{
					status = 1;
				}
			}
            int university_index = find_university(university_name, list_of_university, number_of_university);
            if(input == 1)
            {
            	if(university_index == -1)
	            {	
	            	number_of_university++;
	            	list_of_university = (University**)realloc(list_of_university, sizeof(University*) * number_of_university);
	            	list_of_university[number_of_university - 1] = new University(university_name);
	            	list_of_university[number_of_university - 1]->add_uni_student();
	            }
	            else
	            {
	            	list_of_university[university_index]->add_uni_student();
	            }
	        }
	        else if(input == 2)
	        {
	        	if(university_index == -1)
	            {	
	            	number_of_university++;
	            	list_of_university = (University**)realloc(list_of_university, sizeof(University*) * number_of_university);
	            	list_of_university[number_of_university - 1] = new University(university_name);
	            	list_of_university[number_of_university - 1]->add_college_student();
	            }
	            else
	            {
	            	list_of_university[university_index]->add_college_student();
	            }
	        }
	        else
	        {
	        	cout<<"There is no such options."<<endl;
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
        			if(list_of_university[status-1]->get_total_number_of_student() > 0)
        			{
        				list_of_university[status-1]->display_uni_students(0);
        				list_of_university[status-1]->display_college_students(list_of_university[status-1]->get_number_of_uni_student());
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
          case 3:{ //delete a student from a university
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
                    if(list_of_university[status - 1]->get_total_number_of_student() >= 1)
                    {
	                  cout<<"Please enter the name you want to delete: ";
	                  string name_to_delete;
	                  cin.ignore(100, '\n');
	                  getline(cin, name_to_delete);

	                  cout<<"Enter 1 if you want to delete a university student."<<endl;
		              cout<<"Enter 2 if you want to delete a college student."<<endl;
		              cout<<"Enter the number here: ";
		              int input, check;
					  check = scanf("%d", &input);
					  int limit = 0;
					  while(check!=1)
					  {
						  if(limit < 3)
						  {
							  printf("Invalid input... please enter a number: ");
							  cin.ignore(100,'\n');
						      check = scanf("%d", &input);
						      limit++;
						  }
						  else
						  {
						  	  input = 3;
							  check = 1;
						  }
					  }
	                  if(input == 1)
	                  {
	                  	if(!list_of_university[status-1]->delete_uni_student(name_to_delete))
	                    {
	                        cout<<endl;
	                        cout<<endl;
	                        cout<<"There is no Uni students with that name.";
	                        cout<<endl;
	                        cout<<endl;
	                        cout<<endl;
	                    }
	                  }
	                  else if (input == 2)
	                  {
	                  	if(!list_of_university[status-1]->delete_college_student(name_to_delete))
	                    {
	                        cout<<endl;
	                        cout<<endl;
	                        cout<<"There is no College students with that name.";
	                        cout<<endl;
	                        cout<<endl;
	                        cout<<endl;
	                    }
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
          case 4:{ //display all students from all universities
          	if(number_of_university >= 1)
          	{
          	    int total_num_of_student = 0;
	          	for(int i = 0; i < number_of_university; i++)
	          	{
	          		if(list_of_university[i]->get_number_of_uni_student() > 0)
	          		{
	          			list_of_university[i]->display_uni_students(total_num_of_student);
	          		    total_num_of_student += list_of_university[i]->get_number_of_uni_student();
	          		}
	          		if(list_of_university[i]->get_number_of_college_student() > 0)
	          		{
	          			list_of_university[i]->display_college_students(total_num_of_student);
	          		    total_num_of_student +=list_of_university[i]->get_number_of_college_student();
	          		}
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
          case 5:{ //Display all Uni students from a university
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
        			if(list_of_university[status-1]->get_number_of_uni_student() > 0)
        			{
        				list_of_university[status-1]->display_uni_students(0);
        			}
        			else
        			{
    					cout<<endl;
    					cout<<endl;
    					cout<<"There is no uni student in that university.";
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
          case 6:{ //Display all College students from a university
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
        			if(list_of_university[status-1]->get_number_of_college_student() > 0)
        			{
        				list_of_university[status-1]->display_college_students(0);
        			}
        			else
        			{
    					cout<<endl;
    					cout<<endl;
    					cout<<"There is no college student in that university.";
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
