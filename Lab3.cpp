//I have compiled and run this code successfully using the g++ compiler on Terminal in MacOS High Sierra

#include <iostream>
#include <iomanip>
#include <string>

//The header file containing the class Student
#include "Lab3.h"  

using namespace std;

//This is the function to add a new student and their score to the list
//and then return the score to compare with the current maximum score
double add_student(Student** list_of_students, const int number_of_student)    
{
    cout<<"Please enter the student's name: ";
    string new_name;

    //Get the student' name from user
    cin.ignore(100, '\n');
    getline(cin, new_name);

    //Get the student' score from user
    double new_score; 
    cout<<"Please enter the student's score: ";
    cin>>new_score;

    //Create new object in list_of_students and initialize it with "new_name" and "new_score"
    list_of_students[number_of_student - 1] = new Student(new_name, new_score);   

    return new_score;
}

//This is the function to display all the current students in the list
void display_all_students(Student** list_of_students, const int number_of_student)    
{
    cout<<setw(7)<<"Name"<<setw(30)<<"Score"<<endl;
    for(unsigned int i = 0; i < number_of_student; i++)
    {
        cout<<i+1<<") ";
        cout<<list_of_students[i]->get_name();
        cout<<setw(32-list_of_students[i]->get_name().length());
        cout<<list_of_students[i]->get_score()<<endl;
    }
}


//This is the function to display all the student(s) with the highest score
void display_max( Student** list_of_students, const int number_of_student, double max_score)
{
	int order = 1;
	cout<<setw(7)<<"Name"<<setw(30)<<"Score"<<endl;
    for(int i = 0; i < number_of_student; i++)
    {
    	if(list_of_students[i]->get_score() == max_score)
    	{
    		cout<<order<<") ";
            cout<<list_of_students[i]->get_name();
            cout<<setw(32-list_of_students[i]->get_name().length());
            cout<<list_of_students[i]->get_score()<<endl;
    		order++;
    	}
    }   
}

//This is the function to delete the first student whose name match what the user enter
//this function will also update the max_score of all the students in case the student
//with the highest score is to be deleted
bool delete_student(Student** list_of_students, const int number_of_student, string name_to_delete, double* max_score)
{
    //This function will return true if it has found at least 1 student to be deleted, 
    //otherwise it will return false

	//This variable indicate whether we have found at least 1 student to be deleted yet
	int found = 0;

	//This variable holds the new maximum score after the deletion of one student
	double new_max_score = 0.0;

	for(int i = 0; i < number_of_student; i++)
	{
		if(!found) //when we haven't found the student whose name match with "name_to_delete"
		{
			if(list_of_students[i]->get_name() == name_to_delete)
		    {
		    	//If we have found the student to be deleted
		    	//First, we will delete that student
		    	//and then, we will start pushing all the elements from this index backward
			    delete list_of_students[i];
			    list_of_students[i] = list_of_students[i+1];
			    found = 1;
		    }
		    //If this isn't the student we want to delete,
		    //use the student score to compare with new_max_score 
		    else if(list_of_students[i]->get_score() > new_max_score)
		    {
		    	new_max_score = list_of_students[i]->get_score();
		    }
		}
		else //if we have already found and delete 1 student
		{
			//use the student score to compare with new_max_score 
			if(list_of_students[i]->get_score() > new_max_score)
			{
				new_max_score = list_of_students[i]->get_score();
			}

			//pushing the elements in the array backwward except the last element
			if(i < number_of_student - 1)
			{
			    list_of_students[i] = list_of_students[i+1];
			}
		}
	}
	if(found)
	{
		//if after the deletion of 1 student, there is still at least 1 student in list_of_students
		//we will update "max_score" with "new_max_score" and reallocate list_of_students 
		//to the new size of (number_of_student - 1)
		if(number_of_student > 1)
		{
			*max_score = new_max_score;
		    list_of_students = (Student**)realloc(list_of_students,sizeof(Student*) * (number_of_student - 1));
		}
		return true;
	}	
	return false;
}

int main()
{
	//The dynamically allocate array to hold the Student's object 
    Student ** list_of_students = new Student*[1];

    //The number of student in the list
    int number_of_student = 0;

    //This variable holds the maximum score among all students 
    double max_score = 0.0;

    //the condition of the "while" loop to pop up the menu
    // if working is true, then continue to show the menu to the user, otherwise exit the program
    bool working = true;

    //This variable represents the action that the users want to carry out
    //if action = 1, then the add_student function will be called;
    //if action = 2, then the display_all_students function will be called;
    //if action = 3, then the display_max function will be called;
    //if action = 4, then the delete_student function will be called;
    //otherwise, exit the program
    int actions = 0;

    //This is the while loop to pop up the menu to the user
    while(working)
    {
        //Print out the menu
        cout<<"Please enter the number according to your desired actions"<<endl;
        cout<<"Press 1 to add a new student and their score."<<endl;
        cout<<"Press 2 to view all current students and their respective score."<<endl;
        cout<<"Press 3 to view the student(s) with the highest score."<<endl;
        cout<<"Press 4 to delete the first student with this name ."<<endl;
        cout<<"Press any other number to exit."<<endl;
        cin>>actions;

        //Using switch case to identify which function to call
        switch(actions){
          case 1:{
          	//Increase number_of_student
            number_of_student++;

            if(number_of_student > 1)
            {	
            	//If number_of_student > 1, then reallocate the list_of_students
            	//to the size of the new number_of_student
                list_of_students = (Student**)realloc(list_of_students, sizeof(Student*) * number_of_student);

            	//new_score is the score of the new student
            	//new_score is compared to max_score to find the maximum score among all students 
            	double new_score = add_student(list_of_students, number_of_student);
            	if(new_score > max_score)
            	{
            		max_score = new_score;
            	}
            }
            else
            {
            	//If number_of_student == 1, then max_score will be assigned to the newly entered student' score
            	max_score = add_student(list_of_students, number_of_student);
            }

            cout<<endl;
            break;
        }
          case 2:{
          	//If the list is not wempty
            if(number_of_student > 0)
            {
            	display_all_students(list_of_students, number_of_student);
                cout<<endl;
            }
            else  //if the list is empty
            {
            	cout<<"There is no students in the list \n";
            }
            break;
        }
          case 3:{
          	//If the list is not wempty
            if(number_of_student > 0)
            {
            	display_max(list_of_students, number_of_student, max_score);
            }
            else //if the list is empty
            {
            	cout<<"There is no students in the list \n";
            }
            cout<<endl;
            break;
        }
          case 4:{
            //If the list_of_students is not empty
          	if(number_of_student > 0)
            {
            	//Ask user to enter the name to delete
            	cout<<"Please enter the name of the student you want to delete: ";
                string name_to_delete;
                cin.ignore(100, '\n');
                getline(cin, name_to_delete);

                //if there is a student to be deleted, decrease the number of student by 1
                if(delete_student(list_of_students, number_of_student, name_to_delete, &max_score))
                {
                	number_of_student--;
                }
                else //if there is no student with that name, inform the user about it
	            {
		            cout<<"There is no student with that name on the list \n";
	            }
                cout<<endl;
            }
            else //if the list is empty
            {
            	cout<<"There is no students in the list \n";
            }
            break;
        }


          //When user input any number other than 1,2 or 3, change the variable "working" to false to exit the "while" loop
          default:{
            working = false;

            //Delete the list_of_students
            for(int i = 0; i < number_of_student; i++)
            {
            	delete list_of_students[i];
            } 
            break;
        }
    }
    }
    return 0;
}
