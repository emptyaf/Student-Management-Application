#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

using namespace std;



class Student{
private:
    //array "name" to hold the name of students;   
    
public:
	double* assignment;
	double* test;
	double* exam;

	string name;

    string school_name;

    string course_name;

    int day_of_birth;

    Student()
    {
        this->name         = "\0";
        this->school_name  = "\0";
        this->course_name  = "\0";
        this->day_of_birth = 0;
        this->assignment   = NULL;
        this->test         = NULL;
        this->exam         = NULL;
    }
    Student(string new_name, int day_of_birth, string course_name, string school_name)
    {
        this->name = new_name;
        this->day_of_birth = day_of_birth;
        this->course_name = course_name;
        this->school_name = school_name;
    }
    virtual ~Student(){}
    virtual string get_name() = 0;
    virtual string get_day_of_birth() = 0;
    virtual string get_course_name() = 0;
    virtual string get_school_name() = 0;
    virtual void DoAssignment(void) = 0;
    virtual void TakeTest(void)     = 0;
    virtual void TakeExam(void)     = 0;

    virtual double get_assignment_score(int semester, int assignment_number) = 0;
    virtual double get_test_score(int semester, int test_number) = 0;
    virtual double get_exam_score(int semester, int exam_number) = 0;

    virtual int get_type_of_student(void) = 0;
};

class UniStudent : public Student {
private:
	static int num_of_uni_sem;
	static int num_of_assignment_per_uni_sem;
	static int num_of_test_per_uni_sem;
	static int num_of_exam_per_uni_sem;
public:
	UniStudent()
	{
		this->assignment = new double [num_of_uni_sem * num_of_assignment_per_uni_sem];
		this->test       = new double [num_of_uni_sem * num_of_test_per_uni_sem];
		this->exam       = new double [num_of_uni_sem * num_of_exam_per_uni_sem];
	}
	UniStudent(string new_name, string course_name, string school_name, double* assignment_score, double* test_score, double* exam_score, int day_of_birth) : Student (new_name, day_of_birth, course_name, school_name)
	{
		this->assignment = new double [num_of_uni_sem * num_of_assignment_per_uni_sem];
		this->test       = new double [num_of_uni_sem * num_of_test_per_uni_sem];
		this->exam       = new double [num_of_uni_sem * num_of_exam_per_uni_sem];

		for(int i = 0; i < num_of_uni_sem * num_of_assignment_per_uni_sem; i++)
		{
			this->assignment[i] = assignment_score[i];
		}
		for(int i = 0; i < num_of_uni_sem * num_of_test_per_uni_sem; i++)
		{
			this->test[i] = test_score[i];
		}
		for(int i = 0; i < num_of_uni_sem * num_of_exam_per_uni_sem; i++)
		{
			this->exam[i] = exam_score[i];
		}
	}
	UniStudent(string new_name, string course_name, string school_name, int day_of_birth): Student (new_name, day_of_birth, course_name, school_name)
	{
		this->assignment = new double [num_of_uni_sem * num_of_assignment_per_uni_sem];
		this->test       = new double [num_of_uni_sem * num_of_test_per_uni_sem];
		this->exam       = new double [num_of_uni_sem * num_of_exam_per_uni_sem];
	}
	~UniStudent()
	{
		delete[] this->assignment;
		delete[] this->test;
		delete[] this->exam;
	}
	double get_assignment_score(int semester, int assignment_number)
	{
		return this->assignment[semester * num_of_assignment_per_uni_sem - num_of_assignment_per_uni_sem + assignment_number];
	}

	double get_test_score(int semester, int test_number)
	{
		return this->test[semester * num_of_test_per_uni_sem - num_of_test_per_uni_sem + test_number];
	}

	double get_exam_score(int semester, int exam_number)
	{
		return this->exam[semester * num_of_exam_per_uni_sem - num_of_exam_per_uni_sem + exam_number];
	}

	string get_name()
    {
        return this->name;
    }
    string get_day_of_birth()
    {
    	string month_of_birth = to_string(this->day_of_birth % 100);
    	string date_of_birth = to_string(this->day_of_birth / 100);
        return date_of_birth + "/" + month_of_birth;
    }
    string get_course_name()
    {
    	return this->course_name;
    }
    string get_school_name()
    {
    	return this->school_name;
    }

	static int get_num_of_uni_sem()
	{
		return num_of_uni_sem;
	}

	static int get_num_of_assignment_per_uni_sem()
	{
		return num_of_assignment_per_uni_sem;
	}

	static int get_num_of_test_per_uni_sem()
	{
		return num_of_test_per_uni_sem;
	} 

	static int get_num_of_exam_per_uni_sem()
	{
		return num_of_exam_per_uni_sem;
	}

	void DoAssignment(void)
	{
		for(int i = 0; i < this->num_of_uni_sem * this->num_of_assignment_per_uni_sem; i++)
		{
			this->assignment[i] = double(rand() % 10 + 1);			
		}
	}

	void TakeTest(void)
	{
		for(int i = 0; i < this->num_of_uni_sem * this->num_of_test_per_uni_sem; i++)
		{
			this->test[i] = double(rand() % 10 + 1);			
		}
	}

	void TakeExam(void)
	{
		for(int i = 0; i < this->num_of_uni_sem * this->num_of_exam_per_uni_sem; i++)
		{
			int a = rand() % 10 + 1;
			this->exam[i] = double(a);			
		}
	}

	int get_type_of_student(void)
	{
		return 1;
	}
};

const int input_num_of_uni_sem                 = 8;
const int input_num_of_assignment_per_uni_sem  = 3;
const int input_num_of_test_per_uni_sem        = 1; 
const int input_num_of_exam_per_uni_sem        = 1;

int UniStudent::num_of_uni_sem                = input_num_of_uni_sem;
int UniStudent::num_of_assignment_per_uni_sem = input_num_of_assignment_per_uni_sem;
int UniStudent::num_of_test_per_uni_sem       = input_num_of_test_per_uni_sem;
int UniStudent::num_of_exam_per_uni_sem       = input_num_of_exam_per_uni_sem;

class CollegeStudent : public Student {
private:
	
	static int num_of_college_sem;
	static int num_of_assignment_per_college_sem;
	static int num_of_test_per_college_sem;
	static int num_of_exam_per_college_sem;
public:
	CollegeStudent()
	{
		this->assignment = new double [num_of_college_sem * num_of_assignment_per_college_sem];
		this->test       = new double [num_of_college_sem * num_of_test_per_college_sem];
		this->exam       = new double [num_of_college_sem * num_of_exam_per_college_sem];
	}
	CollegeStudent(string new_name, string course_name, string school_name, double* assignment_score, double* test_score, double* exam_score, int day_of_birth) : Student (new_name, day_of_birth, course_name, school_name)
	{
		this->assignment = new double [num_of_college_sem * num_of_assignment_per_college_sem];
		this->test       = new double [num_of_college_sem * num_of_test_per_college_sem];
		this->exam       = new double [num_of_college_sem * num_of_exam_per_college_sem];

		for(int i = 0; i < num_of_college_sem * num_of_assignment_per_college_sem; i++)
		{
			this->assignment[i] = assignment_score[i];
		}
		for(int i = 0; i < num_of_college_sem * num_of_test_per_college_sem; i++)
		{
			this->test[i] = test_score[i];
		}
		for(int i = 0; i < num_of_college_sem * num_of_exam_per_college_sem; i++)
		{
			this->exam[i] = exam_score[i];
		}
	}
	CollegeStudent(string new_name, string course_name, string school_name, int day_of_birth) : Student (new_name, day_of_birth, course_name, school_name)
	{
		this->assignment = new double [num_of_college_sem * num_of_assignment_per_college_sem];
		this->test       = new double [num_of_college_sem * num_of_test_per_college_sem];
		this->exam       = new double [num_of_college_sem * num_of_exam_per_college_sem];
	}
	~CollegeStudent()
	{
		delete[] this->assignment;
		delete[] this->test;
		delete[] this->exam;
	}
	double get_assignment_score(int semester, int assignment_number)
	{
		return this->assignment[semester * num_of_assignment_per_college_sem - num_of_assignment_per_college_sem + assignment_number];
	}

	double get_test_score(int semester, int test_number)
	{
		return this->test[semester * num_of_test_per_college_sem - num_of_test_per_college_sem + test_number];
	}

	double get_exam_score(int semester, int exam_number)
	{
		return this->exam[semester * num_of_exam_per_college_sem - num_of_exam_per_college_sem + exam_number];
	}

	string get_name()
    {
        return this->name;
    }
    string get_day_of_birth()
    {
    	string month_of_birth = to_string(this->day_of_birth % 100);
    	string date_of_birth = to_string(this->day_of_birth / 100);
        return date_of_birth + "/" + month_of_birth;
    }
    string get_course_name()
    {
    	return this->course_name;
    }
    string get_school_name()
    {
    	return this->school_name;
    }

	static int get_num_of_college_sem()
	{
		return num_of_college_sem;
	}

	static int get_num_of_assignment_per_college_sem()
	{
		return num_of_assignment_per_college_sem;
	}

	static int get_num_of_test_per_college_sem()
	{
		return num_of_test_per_college_sem;
	} 

	static int get_num_of_exam_per_college_sem()
	{
		return num_of_exam_per_college_sem;
	}
	
	void DoAssignment(void)
	{
		for(int i = 0; i < this->num_of_college_sem * this->num_of_assignment_per_college_sem; i++)
		{
			this->assignment[i] = rand() % 10 + 1;			
		}
	}

	void TakeTest(void)
	{
		for(int i = 0; i < this->num_of_college_sem * this->num_of_test_per_college_sem; i++)
		{
			this->test[i] = rand() % 10 + 1;			
		}
	}

	void TakeExam(void)
	{
		for(int i = 0; i < this->num_of_college_sem * this->num_of_exam_per_college_sem; i++)
		{
			this->exam[i] = rand() % 10 + 1;			
		}
	}

	int get_type_of_student()
	{
		return 2;
	}
};

const int input_num_of_college_sem                 = 4;
const int input_num_of_assignment_per_college_sem  = 1;
const int input_num_of_test_per_college_sem        = 1;
const int input_num_of_exam_per_college_sem        = 1; 

int CollegeStudent::num_of_college_sem                = input_num_of_college_sem;
int CollegeStudent::num_of_assignment_per_college_sem = input_num_of_assignment_per_college_sem;
int CollegeStudent::num_of_test_per_college_sem       = input_num_of_test_per_college_sem;
int CollegeStudent::num_of_exam_per_college_sem       = input_num_of_exam_per_college_sem;


class University{
private:
	string name;

    int num_of_student;

    int num_of_uni_student;

    int num_of_college_student;

    Student** list_of_students;
public:
	University()
	{
		this->name = "\0";
		this->list_of_students = new Student*[1];
		this->num_of_student = 0;
		this->num_of_college_student = 0;
		this->num_of_uni_student = 0;
	}
	University(string name)
	{
		this->name = name;
		this->list_of_students = new Student*[1];
		this->num_of_student = 0;
		this->num_of_college_student = 0;
		this->num_of_uni_student = 0;
	}
	~University()
	{
		delete[] this->list_of_students;
	}
	string get_name()
	{
		return this->name;
	}
	int get_total_number_of_student()
	{
		return this->num_of_student;
	}

	int get_number_of_uni_student()
	{
		return this->num_of_uni_student;
	}

	int get_number_of_college_student()
	{
		return this->num_of_college_student;
	}

	//This is the function to add a new uni student and their score to the list
    //and then compare the score with the current maximum score to update the max score
    void add_student(int type_of_student)    
    {
        cout<<"Please enter the student's name: ";
        string new_name;
        cin.ignore(1, '\n');
        getline(cin, new_name);

        cout<<"Please enter the student's course name: ";
        string new_course_name;
        getline(cin, new_course_name);

        double day_of_birth; 
        cout<<"Please enter the student's day of birth in the form of an integer."<<endl;
        cout<<"For example: If the day of birth of the student is the fifth of July,then enter '0507'"<<endl;
        int status;
		status = scanf("%le", &day_of_birth);
		fflush(stdin);
		int limit = 0;
		while(status!=1)
		{
			if(limit < 5)
			{
				printf("Invalid input... please enter a number: ");
				cin.ignore(100,'\n');
			    status = scanf("%le", &day_of_birth);
			    fflush(stdin);
			    limit++;
			}
			else
			{
				status = 1;
			}
		}
		if(limit == 5)
		{
			cout<<"You've entered wrong too many times, the day of birth will be defaulted to 1/1."<<endl;
			day_of_birth = 101;
		}

        int num_of_sem           = 0;
        int num_of_assignment    = 0;
        int num_of_test          = 0;
        int num_of_exam          = 0;

        double* assignment_score = NULL;
        double* test_score       = NULL;
        double* exam_score       = NULL;
 
        if(type_of_student == 1) //if a UniStudent is added
        {
        	num_of_sem           = UniStudent::get_num_of_uni_sem();
	        num_of_assignment    = UniStudent::get_num_of_assignment_per_uni_sem();
	        num_of_test          = UniStudent::get_num_of_test_per_uni_sem();
	        num_of_exam          = UniStudent::get_num_of_exam_per_uni_sem();

	        assignment_score     = new double[num_of_sem * num_of_assignment];
	        test_score           = new double[num_of_sem * num_of_test];
	        exam_score           = new double[num_of_sem * num_of_exam];
	    }
	    else //if a College student is added
	    {
	    	num_of_sem           = CollegeStudent::get_num_of_college_sem();
	        num_of_assignment    = CollegeStudent::get_num_of_assignment_per_college_sem();
	        num_of_test          = CollegeStudent::get_num_of_test_per_college_sem();
	        num_of_exam          = CollegeStudent::get_num_of_exam_per_college_sem();

	        assignment_score     = new double[num_of_sem * num_of_assignment];
	        test_score           = new double[num_of_sem * num_of_test];
	        exam_score           = new double[num_of_sem * num_of_exam];
	    }

	    int choice; 
        cout<<"Please enter 1 if you want to enter the the student's score yourself."<<endl;
        cout<<"Please enter 2 if you want to have the student's score randomly generated."<<endl;
        cout<<"Enter here: ";
		status = scanf("%d", &choice);
		fflush(stdin);
		limit = 0;
		while(status!=1)
		{
			if(limit < 3)
			{
				printf("Invalid input... please enter a number: ");
				cin.ignore(100,'\n');
			    status = scanf("%d", &choice);
			    fflush(stdin);
			    limit++;
			}
			else
			{
				status = 1;
			}
		}
		if(limit == 3)
		{
			cout<<"You've entered wrong too many times, the choice will be defaulted to 2"<<endl;
			choice = 2;
		}

		if(choice == 1)
		{
			for(int i = 0; i < num_of_sem; i++)
	        {
	        	for(int j = 0; j < num_of_assignment; j++)
	        	{
	        		double new_score; 
			        cout<<"Please enter the student's semester "<<i+1<<" assignment "<<j+1<<" score: ";
					status = scanf("%le", &new_score);
					fflush(stdin);
					limit = 0;
					while(status!=1)
					{
						if(limit < 3)
						{
							printf("Invalid input... please enter a number: ");
							cin.ignore(100,'\n');
						    status = scanf("%le", &new_score);
						    fflush(stdin);
						    limit++;
						}
						else
						{
							status = 1;
						}
					}
					if(limit == 3)
					{
						cout<<"You've entered wrong too many times, the score will be defaulted to 0"<<endl;
						new_score = 0.0;
					}
					assignment_score[(i + 1)* num_of_assignment - num_of_assignment + j] = new_score;
	        	}
	        	for(int k = 0; k < num_of_test; k++)
	        	{
	        		double new_score; 
			        cout<<"Please enter the student's semester "<<i+1<<" test "<<k+1<<" score: ";
					status = scanf("%le", &new_score);
					fflush(stdin);
					limit = 0;
					while(status!=1)
					{
						if(limit < 3)
						{
							printf("Invalid input... please enter a number: ");
							cin.ignore(100,'\n');
						    status = scanf("%le", &new_score);
						    fflush(stdin);
						    limit++;
						}
						else
						{
							status = 1;
						}
					}
					if(limit == 3)
					{
						cout<<"You've entered wrong too many times, the score will be defaulted to 0"<<endl;
						new_score = 0.0;
					}
					test_score[(i + 1)* num_of_test - num_of_test + k] = new_score;
	        	}
	        	for(int m = 0; m < num_of_exam; m++)
	        	{
	        		double new_score; 
			        cout<<"Please enter the student's semester "<<i+1<<" exam "<<m+1<<" score: ";
					status = scanf("%le", &new_score);
					fflush(stdin);
					limit = 0;
					while(status!=1)
					{
						if(limit < 3)
						{
							printf("Invalid input... please enter a number: ");
							cin.ignore(100,'\n');
						    status = scanf("%le", &new_score);
						    fflush(stdin);
						    limit++;
						}
						else
						{
							status = 1;
						}
					}
					if(limit == 3)
					{
						cout<<"You've entered wrong too many times, the score will be defaulted to 1"<<endl;
						new_score = 1.0;
					}
					exam_score[(i + 1)* num_of_exam - num_of_exam + m] = new_score;
	        	}        	
			}  
			this->num_of_student++;
			if(this->num_of_student > 1)
			{
				this->list_of_students = (Student**)realloc(this->list_of_students, sizeof(Student*) * this->num_of_student);      
			}
	        if(type_of_student == 1)
	        {
	        	this->list_of_students[this->num_of_student - 1] = new UniStudent(new_name, new_course_name, this->get_name(),assignment_score, test_score, exam_score, day_of_birth);
	        	this->num_of_uni_student++;
	        }
	        else
	        {
	        	this->list_of_students[this->num_of_student - 1] = new CollegeStudent(new_name, new_course_name, this->get_name(), assignment_score, test_score, exam_score, day_of_birth);
	        	this->num_of_college_student++;
	        }
		}
		else if(choice == 2)
		{
			this->num_of_student++;
			if(this->num_of_student > 1)
			{
				this->list_of_students = (Student**)realloc(this->list_of_students, sizeof(Student*) * this->num_of_student);      
			}
	        if(type_of_student == 1)
	        {
	        	this->list_of_students[this->num_of_student - 1] = new UniStudent(new_name, new_course_name, this->get_name(), day_of_birth);
	        	this->list_of_students[this->num_of_student - 1]->DoAssignment();
	        	this->list_of_students[this->num_of_student - 1]->TakeTest();
	        	this->list_of_students[this->num_of_student - 1]->TakeExam();
	        	this->num_of_uni_student++;
	        }
	        else
	        {
	        	this->list_of_students[this->num_of_student - 1] = new CollegeStudent(new_name, new_course_name, this->get_name(), day_of_birth);
	        	this->list_of_students[this->num_of_student - 1]->DoAssignment();
	        	this->list_of_students[this->num_of_student - 1]->TakeTest();
	        	this->list_of_students[this->num_of_student - 1]->TakeExam();
	        	this->num_of_college_student++;
	        }
		}       
    }

    //This is the function to display all the current students in the list
	void display_students(int signal, int type_of_student)    
	{
	    for(unsigned int i = 0; i < this->num_of_student; i++)
	    {
	    	if(type_of_student != 0)
	    	{
	    		if(this->list_of_students[i]->get_type_of_student() == type_of_student)
	    		{
	    			signal++;
	    			this->display(signal, i);	    			
	    		}
	    	}
	    	else
	    	{
	    		this->display(signal, i);
	    	}
	    }
	}

	void display(int signal, int i)
	{
		cout<<setw(7)<<"Name"<<setw(30)<<"Type"<<setw(20)<<"Day of birth"<<setw(30)<<"Course name"<<setw(30)<<"University"<<endl;
	    if(!signal)
	    {
	    	cout<<i+1<<") ";
	    }
	    else
	    {
	    	cout<<signal<<") ";
	    }

	    cout<<this->list_of_students[i]->get_name();
	    cout<<setw(38-this->list_of_students[i]->get_name().length());
	    if(this->list_of_students[i]->get_type_of_student() == 1)
	    {
	    	cout<<"University";
	    }
	    else
	    {
	    	cout<<"College";
	    }
        cout<<setw(10)<<this->list_of_students[i]->get_day_of_birth();
        
        int course_name_length = this->list_of_students[i]->get_course_name().length();
        int course_name_width = 0;
        int next_width = 0;
        if(course_name_length < 11)
        {
        	course_name_width = 30 + 6 - (11 - course_name_length)/2;
        	next_width = (11 - course_name_length)/2;
        }
        else
        {
        	course_name_width = 30 + 6 + (course_name_length - 11)/2;
        	next_width = (course_name_length - 11)/2;
        }
        cout<<setw(course_name_width);
        cout<<this->list_of_students[i]->get_course_name();
        
        int school_name_length = this->get_name().length();
        int school_name_width = 0;
        if(school_name_length < 10)
        {
        	if(course_name_length < 11)
        	{
        		school_name_width = 30 + next_width - (10 - school_name_length)/2;
        	}
        	else
        	{
        		school_name_width = 30 - next_width - (10 - school_name_length)/2;
        	}
        }
        else
        {
        	if(course_name_length < 11)
        	{
        		school_name_width = 30 + next_width - (school_name_length - 10)/2;
        	}
        	else
        	{
        		school_name_width = 30 - next_width - (school_name_length - 10)/2;
        	}
        }
        cout<<setw(school_name_width);
        cout<<this->get_name()<<endl<<endl;
        
        int num_of_sem           = 0;
        int num_of_assignment    = 0;
        int num_of_test          = 0;
        int num_of_exam          = 0;
 
        if(this->list_of_students[i]->get_type_of_student() == 1) //if a UniStudent is added
        {
        	num_of_sem           = UniStudent::get_num_of_uni_sem();
	        num_of_assignment    = UniStudent::get_num_of_assignment_per_uni_sem();
	        num_of_test          = UniStudent::get_num_of_test_per_uni_sem();
	        num_of_exam          = UniStudent::get_num_of_exam_per_uni_sem();
	    }
	    else //if a College student is added
	    {
	    	num_of_sem           = CollegeStudent::get_num_of_college_sem();
	        num_of_assignment    = CollegeStudent::get_num_of_assignment_per_college_sem();
	        num_of_test          = CollegeStudent::get_num_of_test_per_college_sem();
	        num_of_exam          = CollegeStudent::get_num_of_exam_per_college_sem();
	    }

        cout<<"          ";
	    for(int j = 0; j < num_of_assignment; j++)
	    {
	    	cout<<setw(17)<<"Assignment "<<j+1;
	    }
	    for(int j = 0; j < num_of_test; j++)
	    {
	    	cout<<setw(11)<<"Test "<<j+1;
	    }
	    for(int j = 0; j < num_of_exam; j++)
	    {
	    	cout<<setw(11)<<"Exam "<<j+1;
	    }

        for(int m = 0; m < num_of_sem; m++)
        {
        	cout<<endl<<"Semester "<<m+1;
		    for(int j = 0; j < num_of_assignment; j++)
		    {
		    	if(j == 0)
		    	{
		    		cout<<setw(12)<<this->list_of_students[i]->get_assignment_score(m+1, j);
		    	}
		    	else
		    	{
		    		cout<<setw(17)<<this->list_of_students[i]->get_assignment_score(m+1, j);
		    	}
		    }
     
		    for(int j = 0; j < num_of_test; j++)
		    {
		    	cout<<setw(18)<<this->list_of_students[i]->get_test_score(m+1, j);
		    }

		    for(int j = 0; j < num_of_exam; j++)
		    {
		    	cout<<setw(11)<<this->list_of_students[i]->get_exam_score(m+1, j);
		    }
        }
        cout<<endl<<endl<<endl;
        cout<<setw(60)<<"-----------------------------------";
        cout<<endl<<endl<<endl;
	}

	//This is the function to delete the first student whose name match what the user enter
	//this function will also update the max_score of all the students in case the student
	//with the highest score is to be deleted
	bool delete_student(string name_to_delete, int type_of_student)
	{
	    //This function will return true if it has found at least 1 student to be deleted, 
	    //otherwise it will return false

	    bool result = false;

		//This variable holds the new maximum score after the deletion of one student
		double new_max_score = 0.0;

		for(int i = 0; i < this->num_of_student; i++)
		{
			if(this->list_of_students[i]->get_name() == name_to_delete 
				&& this->list_of_students[i]->get_type_of_student() == type_of_student)
			{
				delete this->list_of_students[i];
				result = true;
				if(type_of_student == 1)
				{
					this->num_of_uni_student--;
				}
				else
				{
					this->num_of_college_student--;
				}
			}
			if(result && i < this->num_of_student - 1)
			{
				this->list_of_students[i] = this->list_of_students[i + 1];
			}			
		}
		if(result)
		{
			this->list_of_students = (Student**)realloc(this->list_of_students, sizeof(Student*) * this->num_of_student - 1);
			this->num_of_student--;
		}
		return result;
		
	}
};





