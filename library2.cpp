#include "library2.h"   
#include "City.h"
void *Init(int k)
{
    City* new_city;
    try{
        new_city=new City(k);
    }catch(std::bad_alloc& e){return nullptr;}

    return (void*)new_city;
}


StatusType AddEmployee(void *DS, int EmployeeID, int CompanyID, int Salary, int Grade)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    return ((City*)DS)->AddEmployee(EmployeeID,CompanyID,Salary,Grade);
}


StatusType RemoveEmployee(void *DS, int EmployeeID)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    return ((City*)DS)->RemoveEmployee(EmployeeID);
}


StatusType PromoteEmployee(void *DS, int EmployeeID, int SalaryIncrease, int BumpGrade)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    return ((City*)DS)->PromoteEmployee(EmployeeID,SalaryIncrease,BumpGrade);
}


StatusType AcquireCompany(void *DS, int AcquirerID, int TargetID, double Factor)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    return ((City*)DS)->AcquireCompany(AcquirerID,TargetID,Factor);
}


StatusType EmployeeSalaryIncrease(void *DS, int employeeID, int salaryIncrease)
{
 if(!DS)
    {
        return INVALID_INPUT;
    }
    return ((City*)DS)->EmployeeSalaryIncrease( employeeID,  salaryIncrease);
}

StatusType SumOfBumpGradeBetweenTopWorkersByGroup(void *DS, int companyID, int m, void ** sumBumpGrade)
{
 if(!DS)
    {
        return INVALID_INPUT;
    }

      return ((City*)DS)->SumOfBumpGradeBetweenTopWorkersByGroup( companyID,  m,  sumBumpGrade);
}

StatusType AverageBumpGradeBetweenSalaryByGroup(void *DS, int companyID, int lowerSalary, int higherSalary, void ** averageBumpGrade)
{
 if(!DS)
    {
     return INVALID_INPUT;
    }
    return ((City*)DS)->AverageBumpGradeBetweenSalaryByGroup(companyID,  lowerSalary,  higherSalary, averageBumpGrade);
}

StatusType CompanyValue(void *DS, int companyID, void ** standing)
{
 if(!DS || !standing)
    {
        return INVALID_INPUT;
    }
    return ((City*)DS)->CompanyValue( companyID, standing);
}

StatusType BumpGradeToEmployees(void *DS, int lowerSalary, int higherSalary, int bumpGrade)
{
     if(!DS)
    {
        return INVALID_INPUT;
    }
    return ((City*)DS)->BumpGradeToEmployees(  lowerSalary,  higherSalary,  bumpGrade);

}
void Quit(void** DS)
{
    if(!DS)
    {
        return;
    }
    ((City*)(*DS))->destroyCity();
    delete ((City*)*DS);
    *DS=nullptr;
}