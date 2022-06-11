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
{ shared_ptr<Employee> to_remove=this->Employees.Find(EmployeeID)->data;
  AVLNode<shared_ptr<Employee>,EmployeeComparebySalary>* to_remove1=GetEmployeeBySalry(EmployeeID,to_remove->getSalary());
  employees_by_salary.AVLRemoveVal(to_remove1->getData());
  this->Employees.Remove(EmployeeID);
  this->num_of_employees--;
}

int Company::getId()const
{
return this->id;
}

void Company::addEmployeeToCompany( shared_ptr<Employee> employee)
{
    
    shared_ptr<Employee>employee2=employee;
    
    Employees.Insert(employee2,employee2->getGrade());
    this->num_of_employees++;
}



void Company::setValue(double value)
{
  this->value=value;
}

AVLNode<shared_ptr<Employee>,EmployeeComparebySalary>* Company::GetEmployeeBySalry(int id,int salary)
{
    shared_ptr<Employee>to_find=make_shared<Employee>(id,0,salary);
    return employees_by_salary.find(employees_by_salary.getRoot(),to_find);
}

void Employee::setCompanyId(int id)
{
  this->company_id=id;
}

bool Company::moveEmployees(AVLTree<shared_ptr<Employee>,EmployeeComparebySalary>& employees_by_salary1,Company* company,double Factor)
{
//movingEmployees
    int num=employees_by_salary1.getNum_of_nodes();
    AVLNode<shared_ptr<Employee>,EmployeeComparebySalary>*  ptr=employees_by_salary1.getMaxNode();
    while (ptr!=NULL)
    {
        
        ptr->getData()->setCompanyId(this->id);
        ptr->getData()->setCompany(company);
     
        ptr=employees_by_salary1.the_next_node_iterating(ptr);
     
    }
    //if returned false - error happened
    if(!this->employees_by_salary.moveTree(employees_by_salary1,this->employees_by_salary))return false;//maybe moveTree in avl must delete the old
    this->num_of_employees+=num;
//udpating family
if(this->family==nullptr)
{
  this->family=make_shared<LinkedList<Company*>>();
  this->family->InsertInStart(this,this->getId());
}
 if(company->family==nullptr)
{
 company->family=make_shared<LinkedList<Company*>>();
company->family->InsertInStart(company,company->getId());
}
//calculating values of family members

    ListNode<Company*>* current=this->family->head;
do
{
  current->data->setValue(current->data->getValue()+Factor*(company->getValue()));
  current=current->next;
} while (current);

//adding company to family
current=company->family->head;//must update something in acuqired company ?
company->family=this->family;


    return true;
}

void Employee::setCompany(Company*  company1)
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

