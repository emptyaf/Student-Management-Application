//I have compiled and run this code successfully using the g++ compiler on Terminal in MacOS High Sierra

#include <iostream>
#include<iomanip>
#include <string>

//#define number_of_student 50;

using namespace std;

//This is the function to add a new student and their score to the list
//and then return the score
int add_student(char** name, int*score, int number_of_student)
{
    cout<<"Please enter the student's name: ";
    string new_name;

    //Get the student' name from user
    cin.ignore(100, '\n');
    getline(cin, new_name);

    //Put the name in the 2-D array "name"
    name[number_of_student-1] = (char *) malloc(sizeof(char) * (new_name.length()));
    new_name.copy(name[number_of_student-1], new_name.length(), 0);

    //Get the student' score from user and put it in the array "score" 
    cout<<"Please enter the student's score: ";
    cin>>score[number_of_student-1];

    //Return the student' score to compare to max_score
    return score[number_of_student-1];
}

//This is the function to display all the current students in the list
void display_all_students(char** name, int* score, int number_of_student)
{
    if(number_of_student == 0)
    {
        cout<<"There are no student in the list"<<endl<<endl;
    }
    else
    {
    	cout<<setw(7)<<"Name"<<setw(30)<<"Score"<<endl;
        for(unsigned int i = 0; i < number_of_student; i++)
        {
           cout<<i+1<<") "<<name[i]<<setw(32-strlen(name[i]))<<score[i]<<endl;
        }
    }
}

//This is the function to display all the student(s) with the highest score
void display_max(char** name, int* score, int number_of_student, int max_score)
{
	int order = 1;
	cout<<setw(7)<<"Name"<<setw(30)<<"Score"<<endl;
    for(int i = 0; i < number_of_student; i++)
    {
    	if(score[i] == max_score)
    	{
    		cout<<order<<") "<<name[i]<<setw(32-strlen(name[i]))<<score[i]<<endl;
    		order++;
    	}
    }   
}

int main()
{
    // the counter to count the number of student
    int number_of_student = 0;

    // max_score is used to hold the maximum score among all students
    int max_score = 0;

    //dynamic array "score" to hold the score of all students;
    int* score;
    score = new int [1];

    //dynamic array "name" to hold the name of all students;
    char** name;
    name = (char**)malloc(sizeof(char*) * 1);

    //the condition of the "while" loop to pop up the menu
    // if working is true, then continue to show the menu to the user, otherwise exit the program
    bool working = true;

    //This variable represents the action that the users want to carry out
    //if action = 1, then the add_student function will be called;
    //if action = 2, then the display_all_students function will be called;
    //if action = 3, then the delete_student function will be called;
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
        cout<<"Press any other number to exit."<<endl;
        cin>>actions;

        //Using switch case to identify which function to call
        switch(actions){
          case 1:{
          	//Increase number_of_student
            number_of_student++;

            if(number_of_student > 1)
            {	
            	//If number_of_student > 1, then reallocate the 2 array "name" and "score"
            	//to the size of the new number_of_student
            	name = (char **) realloc(name, sizeof(char*) * number_of_student);
            	score = (int*) realloc(score, sizeof(int) * number_of_student);

            	//new_score is the score of the new student
            	//new_score is compared to max_score to find the maximum score among all students 
            	int new_score = add_student(name, score, number_of_student);
            	if(new_score > max_score)
            	{
            		max_score = new_score;
            	}
            }
            else
            {
            	//If number_of_student == 1, then max_score will be assigned to the newly entered student' score
            	max_score = add_student(name, score, number_of_student);
            }

            cout<<endl;
            break;
        }
          case 2:{
            display_all_students(name, score, number_of_student);
            cout<<endl;
            break;
        }
          case 3:{
            display_max(name, score, number_of_student, max_score);
            cout<<endl;
            break;
          }

          //When user input any number other than 1,2 or 3, change the variable "working" to false to exit the "while" loop
          default:
            working = false;

            //Delete the 2 arrays "name" and "score"
            delete [] score;
            for(int i = 0; i < number_of_student; i++)
            {
            	delete[] name[i];
            }
            break;
         }

    }
    return 0;
}
