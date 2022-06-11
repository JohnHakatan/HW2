#ifndef  COMPANY_H_
#define  COMPANY_H_

//using namespace MEVNY;
//#include "Employee.h"
#include "AVLTree.h"
#include "library2.h"
#include "LinkedList.h"
#include <memory>
#include <iostream>
using namespace std;
using  std::shared_ptr;

class Employee;
class EmployeeComparebySalary;
class EmployeeComparebyID;
class CompanyCompareByID;
class Company
{
private:
int id;
double value;
int num_of_employees;


public:

Company(const Company&)=default;
AVLTree<shared_ptr<Employee>,EmployeeComparebySalary> employees_by_salary;
//AVLTree<shared_ptr<Employee>,EmployeeComparebyID> employees_by_id;

LinkedList<Company*>* family;//to update comapny values that in the same group 

void setValue(int value);
Company(int CompanyId,int Value=0):id(CompanyId),value(Value),num_of_employees(0),
employees_by_salary(AVLTree<shared_ptr<Employee>,EmployeeComparebySalary>()),family(LinkedList())
{
  //adding Company To her Family
this->family->InsertInStart(this,CompanyId);
}

~Company()=default;
int getId()const;
int getNumOfEmployees() const;
double getValue()const;
void RemoveEmployee(int EmployeeID);
void addEmployeeToCompany(shared_ptr<Employee> employee);
int increaseValue(int value_to_add);
void updateEmployee(shared_ptr<Employee> employee);
bool moveEmployees(AVLTree<shared_ptr<Employee>,EmployeeComparebySalary>& employees_by_salary1,Company* company);


//AVLNode<shared_ptr<Employee>,EmployeeComparebyID>* GetEmployeeById(int id);
AVLNode<shared_ptr<Employee>,EmployeeComparebySalary>* GetEmployeeBySalry(int id,int salary);
//get for the trees


};


class CompanyCompareByID{
        public:
    // Comparator function
    int operator()(const Company* a,
                    const Company* b)const 
    {

return b->getId()-a->getId();
    }
       int operator()(const Company a,
                    const Company b)const 
    {

return b.getId()-a.getId();
    }
      int operator()(const shared_ptr<Company> a,
                    const shared_ptr<Company> b)const 
    {

return b->getId()-a->getId();
    }
};
class Employee
{
    int id;
    int grade;
    int salary;
    int company_id;
    Company* company;

    public : 
    //
   void setCompany(Company*  company1);
    int getId() const;
    int getSalary() const;
    int getGrade() const;
    int getCompanyId() const;
    void setSalary(int salary);
    void setGrade(int grade);
    Employee(int id,int grade=0,int salary=0,int company_id =0,Company* company=nullptr ): 
              id(id),grade(grade),salary(salary),company_id(company_id),company(company){}
    Employee(const Employee& Employee)=default;
    Employee& operator=(const Employee& Employee)=default;
    ~Employee()=default;
    void setCompanyId(int id);
    bool operator==(const Employee& to_compare)const;
    bool operator!=(const Employee& to_compare)const;
    bool operator<(const Employee& to_compare)const;
    bool operator<=(const Employee& to_compare)const;
    bool operator>(const Employee& to_compare)const;
    bool operator>=(const Employee& to_compare)const;
    const Company* getCompany()const;

 

};
    
 class EmployeeComparebyID{
        public:
    // Comparator function
    int operator()(const Employee* a,
                    const Employee* b)const 
    {

       return (a->getId()-b->getId());
    }

      int operator()(const Employee a,
                    const Employee b)const 
    {

       return (a.getId())-(b.getId());
    }

     int operator()(const std::shared_ptr<Employee>& a,const std::shared_ptr<Employee>& b)const
     {
       return a->getId()-b->getId();
     }
    
};

 class EmployeeComparebySalary{
        public:
    // Comparator function
    int operator()(const Employee* a,
                    const Employee* b)const 
    {

      if(a->getSalary()==b->getSalary())
      {
        return (b->getId())-(a->getId());// maybe we must swap
      }
      return (a->getSalary())-(b->getSalary());
    }
     
    
      int operator()(const std::shared_ptr<Employee>& a,const std::shared_ptr<Employee>& b)const 
    {
      if(a->getSalary()==b->getSalary())
      {
        return (b->getId())-(a->getId());// maybe we must swap
      }
      return (a->getSalary())-(b->getSalary());

    }


   int operator()(const Employee a,
                    const Employee b)const 
    {

      if(a.getSalary()==b.getSalary())
      {
        return (b.getId())-(a.getId());
      }
      return (a.getSalary())-(b.getSalary());
    }
    
};

#endif



