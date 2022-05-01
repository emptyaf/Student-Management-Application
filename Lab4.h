using namespace std;

class Student{
private:
    //array "name" to hold the name of students;   
    string name;
    double score;
public:
    Student()
    {
        this->name = "\0";
        this->score = 0.0;
    }
    Student(string new_name, double new_score)
    {
        this->name = new_name;
        this->score = new_score;
    }
    ~Student(){}
    string get_name()
    {
        return this->name;
    }
    double get_score()
    {
        return this->score;
    }

};

class University{
private:
	string name;

	//The dynamically allocate array to hold the Student's object 
    Student ** list_of_students;

    int number_of_student;

    double max_score;
public:
	University()
	{
		this->name = "\0";
		this->list_of_students = NULL;
		this->number_of_student = 0;
		this->max_score = 0.0;
	}
	University(string name)
	{
		this->name = name;
		this->list_of_students = new Student*[1];
		this->number_of_student = 0;
		this->max_score = 0.0;
	}
	~University()
	{
		for(int i = 0; i < this->number_of_student; i++)
        {
            delete this->list_of_students[i];
        } 
	}
	string get_name()
	{
		return this->name;
	}
	int get_number_of_student()
	{
		return this->number_of_student;
	}
	//This is the function to add a new student and their score to the list
    //and then comepare the score with the current maximum score to update the max score
    void add_student()    
    {
    	//If number_of_student > 1, then reallocate the list_of_students
    	//to the size of the new number_of_student
        if(this->number_of_student > 1)
        {
        	this->list_of_students = (Student**)realloc(this->list_of_students, sizeof(Student*) * this->number_of_student + 1);
        }

        cout<<"Please enter the student's name: ";
        string new_name;
        getline(cin, new_name);

        double new_score; 
        cout<<"Please enter the student's score: ";
        int status;
		status = scanf("%le", &new_score);
		int limit = 0;
		while(status!=1)
		{
			if(limit < 10)
			{
				printf("Invalid input... please enter a number: ");
				cin.ignore(100,'\n');
			    status = scanf("%le", &new_score);
			    limit++;
			}
			else
			{
				status = 1;
			}
		}
        
    	this->number_of_student++;
        this->list_of_students[this->number_of_student - 1] = new Student(new_name, new_score);   

        if(new_score > this->max_score)
        {
        	this->max_score = new_score;
        }
    }

    //This is the function to display all the current students in the list
	void display_all_students(int signal)    
	{
	    for(unsigned int i = 0; i < number_of_student; i++)
	    {
		    if(!signal)
		    {
		    	cout<<i+1<<") ";
		    }
		    else
		    {
		    	cout<<signal + i + 1<<") ";
		    }
		    cout<<this->list_of_students[i]->get_name();
		    cout<<setw(32-this->list_of_students[i]->get_name().length());
	        cout<<this->list_of_students[i]->get_score();
	        cout<<setw(15)<<this->get_name()<<endl;
	    }
	}

	//This is the function to display all the student(s) with the highest score
	void display_max()
	{
		int order = 1;
		cout<<setw(7)<<"Name"<<setw(30)<<"Score"<<setw(15)<<"University"<<endl;
	    for(int i = 0; i < number_of_student; i++)
	    {
	    	if(this->list_of_students[i]->get_score() == this->max_score)
	    	{
	    		cout<<order<<") ";
	            cout<<this->list_of_students[i]->get_name();
	            cout<<setw(32-this->list_of_students[i]->get_name().length());
	            cout<<this->list_of_students[i]->get_score();
	            cout<<setw(15)<<this->get_name()<<endl;
	    		order++;
	    	}
	    }   
	}

	//This is the function to delete the first student whose name match what the user enter
	//this function will also update the max_score of all the students in case the student
	//with the highest score is to be deleted
	bool delete_student(string name_to_delete)
	{
	    //This function will return true if it has found at least 1 student to be deleted, 
	    //otherwise it will return false

		//This variable indicate whether we have found at least 1 student to be deleted yet
		int found = 0;

		//This variable holds the new maximum score after the deletion of one student
		double new_max_score = 0.0;

		for(int i = 0; i < this->number_of_student; i++)
		{
			if(!found) //when we haven't found the student whose name match with "name_to_delete"
			{
				if(this->list_of_students[i]->get_name() == name_to_delete)
			    {
			    	//If we have found the student to be deleted
			    	//First, we will delete that student
			    	//and then, we will start pushing all the elements from this index backward
				    delete this->list_of_students[i];
				    this->list_of_students[i] = this->list_of_students[i+1];
				    found = 1;
			    }
			    //If this isn't the student we want to delete,
			    //use the student score to compare with new_max_score 
			    else if(this->list_of_students[i]->get_score() > new_max_score)
			    {
			    	new_max_score = this->list_of_students[i]->get_score();
			    }
			}
			else
			{
				//use the student score to compare with new_max_score 
				if(this->list_of_students[i]->get_score() > new_max_score)
				{
					new_max_score = this->list_of_students[i]->get_score();
				}

				//pushing the elements in the array backwward except the last element
				if(i < this->number_of_student - 1)
				{
				    this->list_of_students[i] = this->list_of_students[i+1];
				}
			}
		}
		if(found)
		{
			//if after the deletion of 1 student, there is still at least 1 student in list_of_students
			//we will update "max_score" with "new_max_score" and reallocate list_of_students 
			//to the new size of (number_of_student - 1)
			if(this->number_of_student > 1)
			{
				this->max_score = new_max_score;
			    this->list_of_students = (Student**)realloc(this->list_of_students,sizeof(Student*) * (this->number_of_student - 1));
			}
			this->number_of_student--;
			return true;
		}	
		return false;
	}

};





