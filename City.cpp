#include "City.h"
Company* City::getOriginalCompany(int id)
{
     Company** ptr=this->Companies->pointers;
     
    if(id<0 || id>=this->Companies->n)return nullptr;
     return ptr[id];

}

Company* City::getCompanyById(int id)
{      
      return this->Companies->findd(id);
}


    StatusType City::CompanyValue( int companyID, void ** standing)
    {
   
        if(companyID<=0 )return FAILURE;
        Company* ptr=this->getCompanyById(companyID);
        if(!ptr)return FAILURE;
        (*standing)=&(ptr->value);// THERE WILL BE SOME PRECISION ISSUES
        return SUCCESS;
             
    }


   shared_ptr<Employee> City::GetEmployee(int id)
    {
        shared_ptr<Employee> to_return=allEmployees.find(id)->data;
        return to_return;
    //     Company** ptr=this->Companies->pointers;
    //     shared_ptr<Employee> employee_to_check=nullptr;
    //    while(ptr!=nullptr)
    //    {
           
    //     employee_to_check=(*ptr)->GetEmployee(id);
    //     ptr++;
    //    }
    //    // shared_ptr<Employee>employee_to_check=make_shared<Employee>(id,0,salary);
    //   //  return this->Companies.find(this->employees_by_salary.(),employee_to_check);
    //   return employee_to_check;
    }

   /* void City::updateEmployee(int EmployeeID,int SalaryIncrease,int BumpGrade)
    {

        AVLNode<shared_ptr<Employee>,EmployeeComparebyID>* old_data_id=getEmployeeById(EmployeeID);
        
        int new_salary=old_data_id->getData()->getSalary()+SalaryIncrease;
        int new_grade=old_data_id->getData()->getGrade();
        if(BumpGrade>0)
        {
            new_grade+=1;
        }
        shared_ptr<Employee> new_by_id;
        try{
            new_by_id =make_shared<Employee>(EmployeeID,new_grade,new_salary,old_data_id->getData()->getCompanyId(),old_data_id->getData()->getCompany());
        }catch(std::bad_alloc& e)
        {
            throw;
        }

        shared_ptr<Employee> ptr=old_data_id->getData();
        employees_by_salary.AVLRemoveVal(ptr);
        employees_by_id.AVLRemoveVal(ptr);
        shared_ptr<Employee> new_by_id1=new_by_id;
        employees_by_id.AVLInsert(new_by_id);
        employees_by_salary.AVLInsert(new_by_id1);
        

    }*/


    City::City(int k){

   this->Companies=new UnionFind<Company>(k);
   this->num_of_employees=0;

    }



   

    StatusType City::AddEmployee(int EmployeeID, int CompanyID, int Grade)
    {
        //check conditions are valid
        //need to add a check for companyID<k
        if(CompanyID<=0 ||  EmployeeID<=0  || Grade<0 ||CompanyID>num_of_companies)
        {
            return INVALID_INPUT;
        }
       if(!getCompanyById(CompanyID))return FAILURE;
        //check the company is exist in the system
        Company* company_to_update = getCompanyById(CompanyID);
        if(!company_to_update)
        {
            return FAILURE;
        }

        if(GetEmployee(EmployeeID))return FAILURE;
        // employee_to_check(nullptr);
  

   
        shared_ptr<Employee> employee_to_check=make_shared<Employee>(EmployeeID,Grade,CompanyID,company_to_update);
        allEmployees.insert(EmployeeID,employee_to_check);      
        company_to_update->addEmployeeToCompany(employee_to_check);
        employees_with_zero_salary++;
        sum_of_zero_employees_grade+=Grade;
        num_of_employees++;

        // int val = employees_by_id.AVLInsert(employee_to_check);
        // if(val==MEMORY_ERROR || val==DATA_EXIST)
        // {
        //     return FAILURE;
        // }

        // val= employees_by_salary.AVLInsert(employee_to_check);
        //  if(val==MEMORY_ERROR || val==DATA_EXIST)
        // {//maybe we must delete what we have inserted
        //     return FAILURE;
        // }
   
        // this->num_of_employees++;
        // try{
        // company_to_update->addEmployeeToCompany( employee_to_check);
        // }catch(std::bad_alloc& e){
        // throw;
        // }
        return SUCCESS;

     
        

    }

    StatusType City::RemoveEmployee(int EmployeeID)
    {
        if(EmployeeID<=0)
        {
            return INVALID_INPUT;
        }

        // check if is there an employee with the same id in the city
        shared_ptr<Employee> employee_to_remove= this->GetEmployee(EmployeeID);
        if(!employee_to_remove)
        {
            return FAILURE;
        }
        allEmployees.remove(EmployeeID);
        if(employee_to_remove->getSalary()==0)
        {
            employees_with_zero_salary--;
            sum_of_zero_employees_grade-=employee_to_remove->getGrade();
        }
        employee_to_remove->getCompany()->RemoveEmployee(EmployeeID);
        employees_by_salary.AVLRemoveVal(employee_to_remove);
        this->num_of_employees--;
        return SUCCESS;

    }
    
    

    StatusType City::PromoteEmployee( int EmployeeID, int SalaryIncrease, int BumpGrade)
    {
        if(EmployeeID<=0 || SalaryIncrease<=0)
        {
            return INVALID_INPUT;
        }

        shared_ptr<Employee> to_update=GetEmployee(EmployeeID);
        if(!to_update)
        {
            return FAILURE;
        }
       // cout<<"-----------------------------------------"<<to_update->getData()->getCompanyId()<<endl;
         Company* company_of_employee=to_update->getCompany();
      //  cout<<company_of_employee->getData()->getID();
          try{
            updateEmployee(EmployeeID,SalaryIncrease,BumpGrade);
         }catch(std::bad_alloc& e)
        {
            return FAILURE;
        }
      to_update=getEmployee(EmployeeID);
        try{
            company_of_employee->updateEmployee(to_update->getData());
         }catch(std::bad_alloc& e)
        {
            return FAILURE;
        }

      

        return SUCCESS;
    }

    /*StatusType City::HireEmployee(int EmployeeID, int NewCompanyID)
    {
        if(EmployeeID <=0 || NewCompanyID <=0)return INVALID_INPUT;
 AVLNode<shared_ptr<Employee>,EmployeeComparebyID>* ptr =getEmployeeById(EmployeeID);
  if(!ptr)return FAILURE;
        AVLNode <shared_ptr<Company>,CompanyCompareByID>* ccc= getCompanyById(NewCompanyID);
        if((ccc==NULL) || ((ptr->getData()->getCompanyId())==NewCompanyID) )return FAILURE;

         shared_ptr<Company> company_ptr=ccc->getData();


shared_ptr<Employee>  employee_ptr=make_shared<Employee>(EmployeeID,ptr->getData()->getGrade(),ptr->getData()->getSalary()
,NewCompanyID,company_ptr);

     RemoveEmployee(EmployeeID);
    //  return AddEmployee(EmployeeID,NewCompanyID,)
     
  try{
        int val = employees_by_id.AVLInsert(employee_ptr);
        if(val==MEMORY_ERROR || val==DATA_EXIST)
        {
            return FAILURE;
        }

        val= employees_by_salary.AVLInsert(employee_ptr);
         if(val==MEMORY_ERROR || val==DATA_EXIST)
        {
            return FAILURE;
        }
      }catch(std::bad_alloc& e)
        {
            return ALLOCATION_ERROR;
        }

        this->num_of_employees++;
        try{
        company_ptr->addEmployeeToCompany(employee_ptr);
        }catch(std::bad_alloc& e){
        throw;
        }
        return SUCCESS;


        
    }*/

    StatusType City::AcquireCompany(int AcquirerID, int TargetID, double Factor)
    {
          if(AcquirerID<=0 || TargetID<=0 || AcquirerID==TargetID || Factor< 1.0)return INVALID_INPUT;
        if(!getCompanyById(AcquirerID) || !getCompanyById(TargetID))return FAILURE;
          Company* Acquirer_ptr=getCompanyById(AcquirerID);
          if(!Acquirer_ptr)return FAILURE;
          Company* Target_ptr=getCompanyById(TargetID);
          if(!Target_ptr)return FAILURE;

       
    if(!Acquirer_ptr->moveEmployees(Target_ptr->employees_by_salary,Target_ptr,Factor))return FAILURE;//dont forget employee with no salary
   
    return SUCCESS;  
    }

    StatusType City::SumOfBumpGradeBetweenTopWorkersByGroup( int companyID, int m)
    {
        //need to check companyID< k meaning
        if( companyID<0 ||m<= 0)return FAILURE;
        if(companyID==0)
        {
            if(this->num_of_employees<m)
            {
                return FAILURE;
            }else{
                SumbumpGradeFromTree(employees_by_salary.getRoot(),m);
            }
        }else{
            SumbumpGradeFromTree(getCompanyById(companyID)->employees_by_salary.getRoot(),m);
        }
        return SUCCESS;
    }

    int City::SumbumpGradeFromTree(AVLNode<shared_ptr<Employee>,EmployeeComparebySalary>* root,int m)
    {
        // if(employees_by_salary.getNum_of_nodes()<m)
        // {
        //     //return failure
        // }
        // if(employees_by_salary.getNum_of_nodes()==m)
        // {
        //     return employees_by_salary.getRoot()->getRank();
        // }
        
    }


    
    
    
    void City::destroyCity()
    {
  
    }
    City::~City()
    {
       
    }