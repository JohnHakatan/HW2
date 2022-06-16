#include "Company.h"
   

Company* Employee::getCompany()const
{
      
  return this->company;
}

int Company::increaseValue(int value_to_add)
{
  return this->value+=value_to_add;
}

int Company::getNumOfEmployees() const
{
    return this->num_of_employees;
}

double Company::getValue() const
{
    return this->value;
}

void Company::RemoveEmployee(int EmployeeID)
{// shared_ptr<Employee> to_remove=this->Employees.Find(EmployeeID)->data;
  shared_ptr<Employee> to_remove1=GetEmployee(EmployeeID);
  if(to_remove1->getSalary()==0)
  {
    this->employees_with_zero_salary--;
    this->sum_of_zero_employees_grade-=to_remove1->getGrade();
  }

  employees_by_salary.AVLRemoveVal(to_remove1);
  this->Employees->remove(EmployeeID);
  this->num_of_employees--;


}

int Company::getId()const
{
return this->id;
}

void Company::addEmployeeToCompany( shared_ptr<Employee> employee)
{
    shared_ptr<Employee>employee2=employee;
    Employees->insert(employee->getId(),employee2);
    this->num_of_employees++;
    this->employees_with_zero_salary++;
    this->sum_of_zero_employees_grade+=employee->getGrade();


} 
  



void Company::setValue(double value)
{
  this->value=value;
}

shared_ptr<Employee> Company::GetEmployee(int id)
{
    //shared_ptr<Employee> to_find=make_shared<Employee>(id);
    return Employees->find(id)->data;
}

void Employee::setCompanyId(int id)
{
  this->company_id=id;
}



bool Company::moveEmployees(AVLTree<shared_ptr<Employee>,EmployeeComparebySalary>* employees_by_salary1,Company* company,double Factor)
{
   //updating hashTables
    this->Employees->merge(company->Employees);
    
    HashTable<shared_ptr<Employee>>* ptr1=this->Employees;
    this->sum_of_zero_employees_grade=0;
    this->employees_with_zero_salary=0;
     for(int i=0;i<ptr1->size_of_array;i++)
    {
        if(!ptr1->dynamic_array[i])continue;
        ListNode<shared_ptr<Employee>>* to_move=(ptr1->dynamic_array[i]->head->next);
        
        while(to_move)
        {
          to_move->data->setCompanyId(this->id);
        to_move->data->setCompany(this);
          if(to_move->data->getSalary()==0){this->employees_with_zero_salary++;
            this->sum_of_zero_employees_grade+=to_move->data->getGrade();
          
            
          }
    
            to_move=to_move->next;
        }
    }
    

//movingEmployees
    int num=(company->num_of_employees);
    //if returned false - error happened - udpating tree
    if(!this->employees_by_salary.moveTree(*employees_by_salary1,this->employees_by_salary))return false;//maybe moveTree in avl must delete the old
  

    this->num_of_employees+=num;
    
    

    //what about employee with no salary ?
    //adding employees with no salary
    //adding size of them

//calculating values of family members
ListNode<Company*>* current=this->family->head->next;

do
{

  current->data->setValue(current->data->getValue()+Factor*(company->getValue()));
  current=current->next;

}while(current);

//adding company to family
//current=company->family->head;//must update something in acuqired company ?
ListNode<Company*>* current1=company->family->head->next;
while(current1)
{
 this->family->InsertInStart(current1->data,current1->id);
  current1=current1->next;
}

return true;
}

void Employee::setCompany(Company* company1)
{
    this->company=company1;
}

void Employee::setSalary(int salary)
{
  this->salary=salary;
}

void Employee::setGrade(int grade)
{
  this->grade=grade;
}

int Employee::getId()const
{
        return this->id;
}

int Employee::getCompanyId()const
{
        return this->company_id;
}

int Employee::getSalary()const
{
        return this->salary;
}

int Employee::getGrade() const
{
       return this->grade;
}

bool Employee::operator==(const Employee& to_compare)const
{
  if((this->id==to_compare.id) && (this->salary==to_compare.salary))
  {
    return true;
  }
  else{
    return false;
  }
}

bool Employee::operator!=(const Employee& to_compare)const
{
  return (!((*this)==to_compare));
}

bool Employee::operator<(const Employee& to_compare)const
{
  if(this->salary<to_compare.salary)
  {
    return true;
  }
  else if(this->salary==to_compare.salary)
  {
    return this->id>to_compare.id;
  }
  else{
    return false;
  }
}

bool Employee::operator<=(const Employee& to_compare)const
{
  return (*this<to_compare)||(*this==to_compare);
}

bool Employee::operator>(const Employee& to_compare)const
{
  return !(*this<=to_compare);
}

bool Employee::operator>=(const Employee& to_compare)const
{
  return !(*this<to_compare);
}

