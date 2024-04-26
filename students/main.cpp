#include "student.hpp"

int main()
{
    std::shared_ptr<Student> s1 = std::make_shared<Student>(Student(1, 21, "Alex"));

    Campus camp;
    camp.addStudent(s1);
    camp.getStudentData(1);
    return 0;
}