#pragma once

#include <memory>
#include <iostream>
#include <string>
#include <map>

class Student
{
public:
    Student(const size_t id, const size_t age ,const std::string& name)
        : m_id(id)
        , m_name(name)
        , m_age(age)
        {}

    ~Student() = default;
private:
    size_t m_id;
    size_t m_age;
    std::string m_name;

    friend class Campus;
};

class Campus
{
public:
    Campus() = default;
    ~Campus() = default;

    void addStudent(std::shared_ptr<Student>& student)
    {
        if (student == nullptr || student->m_name.empty())
        {
            std::cout << "Error" << std::endl;
            return;
        }

        m_students[student->m_id] = student;
    }

    void removeStudent(const size_t id)
    {
        if (m_students.find(id) == m_students.end())
        {            
            std::cout << "Error" << std::endl;
        }
        m_students.erase(id);
    }
    
    void getStudentData(const size_t id)
    {
        if (m_students.find(id) == m_students.end())
        {
            std::cout << "Error" << std::endl;
        }
        std::cout << "Name " << m_students[id]->m_name << '\n'
                  << "age " << m_students[id]->m_age  << '\n'
                  << "id " << id;
    }

private:
    std::map<size_t, std::shared_ptr<Student>> m_students;
};
