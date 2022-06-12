#ifndef CITY_H_
#define CITY_H_

#include "library2.h"
#include "AVLRankTree.h"
#include "unionfind.h"
#include "Company.h"
//#include "Employee.h"
#include<memory>
#ifdef __cplusplus
extern "C" {
#endif

class City
{
    UnionFind<Company>* Companies;
       
    public:
    
    int num_of_employees;
    City(int k);
    ~City();
    City(const City& city)=default;
    AVLTree<shared_ptr<Employee>,EmployeeComparebySalary> employees_by_salary;

    Company* getCompanyById(int id);
//AVLNode<shared_ptr<Employee>,EmployeeComparebyID>* getEmployeeById(int id);
    shared_ptr<Employee> GetEmployee(int id);
    void updateEmployee(int EmployeeID,int SalaryIncrease,int BumpGrade);
    StatusType PromoteEmployee( int EmployeeID, int SalaryIncrease, int BumpGrade);
    Company* getOriginalCompany(int id);
    StatusType AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade);
    StatusType RemoveEmployee(int EmployeeID);
    StatusType EmployeeSalaryIncrease( int employeeID, int salaryIncrease);
    StatusType SumOfBumpGradeBetweenTopWorkersByGroup( int companyID, int m);
    StatusType AverageBumpGradeBetweenSalaryByGroup(int companyID, int lowerSalary, int higherSalary, void ** averageBumpGrade);
    StatusType CompanyValue( int companyID, void ** standing);
    StatusType AcquireCompany(int AcquirerID, int TargetID, double Factor);
    StatusType BumpGradeToEmployees(int lowerSalary, int higherSalary, int bumpGrade);
    int SumbumpGradeFromTree(AVLTree<shared_ptr<Employee>,EmployeeComparebySalary> employees_by_salary,int m);
    void destroyCity();
};


#ifdef __cplusplus
}
#endif

#endif