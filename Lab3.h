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