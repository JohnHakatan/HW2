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
 
    }

    void City::updateEmployee(shared_ptr<Employee> em,int EmployeeID,int SalaryIncrease,int BumpGrade)
    {
        //shared_ptr
        
        
        int new_grade=em->getGrade();
        if(BumpGrade>0)
        {
            new_grade+=BumpGrade;
        }
        em->setGrade(new_grade);

        
    
        
    }


    City::City(int k){

   this->Companies=new UnionFind<Company>(k);
   this->num_of_companies=k;
   this->num_of_employees=0;
   this->employees_with_zero_salary=0;
   this->sum_of_zero_employees_grade=0;
   this->employees_by_salary=AVLTree<shared_ptr<Employee>,EmployeeComparebySalary>();
    this->allEmployees=HashTable<shared_ptr<Employee>>();

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
    
    

    StatusType City::PromoteEmployee( int EmployeeID, int BumpGrade)
    {
        if(EmployeeID<=0)
        {
            return INVALID_INPUT;
        }

        shared_ptr<Employee> to_update=GetEmployee(EmployeeID);
        if(!to_update)
        {
            return FAILURE;
        }
    
     this->RemoveEmployee(EmployeeID);
     //to_update->setGrade(to_update->getGrade()+BumpGrade);
     this->AddEmployee(EmployeeID,to_update->getCompany()->getId(),to_update->getGrade()+BumpGrade);
     this->EmployeeSalaryIncrease(EmployeeID,to_update->getSalary());
     
      

        return SUCCESS;
    }




static double find_how_many_lower_than(AVLTree<shared_ptr<Employee>,EmployeeComparebySalary>* tree,AVLNode<shared_ptr<Employee>,EmployeeComparebySalary>* root,int Salary)
{
if(!root)return 0;// check this when using the function in avg function

//we arrived boundary - maybe there are more than one with Salary==Salary
if(root->getData()->getSalary()==Salary)
{
    
    if(root->getLeft()->getData()->getSalary()>Salary)
    {
        return root->getSub_tree_size()-1;
    }
    else//==
    {
     return find_sum_lower_than_aux(tree,root->getLeft(),Salary);
    }
}
//max boundary is in the left sub - we only want the sum of the nodes before it so we don't add something 
if(root->getData()->getSalary() < Salary)
{
    
    return find_sum_lower_than_aux(tree,root->getLeft(),Salary);

}

//max boundary is in the right - we want all of nodes that before max_boundary so we add 
return root->getSub_tree_size()-root->getRight()->getSub_tree_size()+find_sum_lower_than_aux(tree,root->getRight(),Salary);


}


static double find_sum_lower_than_aux(AVLTree<shared_ptr<Employee>,EmployeeComparebySalary>* tree,AVLNode<shared_ptr<Employee>,EmployeeComparebySalary>* root,int Salary)
{
 if(!root)return 0;// check this when using the function in avg function

//we arrived boundary - maybe there are more than one with Salary==Salary
 if(root->getData()->getSalary()==Salary)
 {
    
    if(root->getLeft()->getData()->getSalary()>Salary)
    {
        return root->getRank()-root->getRankAsLeaf();
    }
    else//==
    {
     return find_sum_lower_than_aux(tree,root->getLeft(),Salary);
    }
 }
//max boundary is in the left sub - we only want the sum of the nodes before it so we don't add something 
 if(root->getData()->getSalary() < Salary)
 {
    
    return find_sum_lower_than_aux(tree,root->getLeft(),Salary);

 }

//max boundary is in the right - we want all of nodes that before max_boundary so we add 
return root->getRank()-root->getRight()->getRank()+find_sum_lower_than_aux(tree,root->getRight(),Salary);


//not checked yet 
}



//we can use this function in SumofBump ALSO!!
static double find_sum_lower_than(AVLTree<shared_ptr<Employee>,EmployeeComparebySalary>* tree,int Salary)
{

return find_sum_lower_than_aux(tree,tree->root,Salary);

}
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
                //there are not enough employees
                if(employees_by_salary.getNum_of_nodes()<m)return FAILURE;
                SumbumpGradeFromTree(&employees_by_salary,employees_by_salary.getRoot(),m);
            }
        }else{
           Company* c= getCompanyById(companyID);
           // company is not existed or there are not enough employees
           if(!c || c->employees_by_salary.getNum_of_nodes()<m )return FAILURE;          
            SumbumpGradeFromTree(&c->employees_by_salary,c->employees_by_salary.getRoot(),m);
        }
        return SUCCESS;
    }

  static AVLNode<shared_ptr<Employee>,EmployeeComparebySalary>*  find_m_node(AVLNode<shared_ptr<Employee>,EmployeeComparebySalary>* root,int m)
    {   
        // found or leaf 
        if(1==m )return root;

        
        if(root->getSub_tree_size()==m)
         return find_m_node(root->getRight(),m-root->getLeft()->getSub_tree_size()-1);
        
        if(root->getSub_tree_size()>m)
        {
            if(root->getLeft()->getSub_tree_size() < m)return find_m_node(root->getRight(),m-root->getLeft()->getSub_tree_size()-1);
            if(root->getLeft()->getSub_tree_size() >=m)return find_m_node(root->getLeft(),m);
        }
  

       // if there are enough nodes it will not arrive here  
   return nullptr;

    
    }
    

    int City::SumbumpGradeFromTree(AVLTree<shared_ptr<Employee>,EmployeeComparebySalary>* tree,AVLNode<shared_ptr<Employee>,EmployeeComparebySalary>* root,int m)
    {
        
AVLNode<shared_ptr<Employee>,EmployeeComparebySalary>* m_element=find_m_node(root,m);
double sum=0;

//sum+=find_sum_lower_than(tree,)

return 0 ;
       



    }


    StatusType City::AverageBumpGradeBetweenSalaryByGroup( int companyID, int lowerSalary, int higherSalary)
    {
        double grades_sum_salary_0=0;
        int num_of_zeros=0;
        AVLTree<shared_ptr<Employee>,EmployeeComparebySalary>* tree=nullptr;
        Company* c_ptr=nullptr;
        if(higherSalary<0 || lowerSalary<0 || lowerSalary>higherSalary || companyID > this->num_of_companies || companyID<0)return INVALID_INPUT;
        if(companyID==0){
            
               
           tree=&(this->employees_by_salary);
grades_sum_salary_0=this->sum_of_zero_employees_grade;
num_of_zeros=this->employees_with_zero_salary;

        }
        else//positive
        {
            c_ptr=this->Companies->findd(companyID);
            grades_sum_salary_0=c_ptr->sum_of_zero_employees_grade;
            num_of_zeros=c_ptr->employees_with_zero_salary;

        }

    if(num_of_zeros==0 && tree->getNum_of_nodes()==0)
    {
return FAILURE;
    }
double toRtn=0;
    if(tree->getNum_of_nodes()!=0){
        double first=find_sum_lower_than(tree,lowerSalary);
        double last=find_sum_lower_than(tree,higherSalary);

        int num_first=find_how_many_lower_than(tree,tree->root,lowerSalary);
        int num_last=find_how_many_lower_than(tree,tree->root,higherSalary);

       
       toRtn=(grades_sum_salary_0 + last-first)/(num_of_zeros + num_last-num_first+1);
    
    }else
    {
        toRtn=(grades_sum_salary_0)/(num_of_zeros);  
    }

    //printing ... maybe we must add it to some parameter and print with c printf

        return SUCCESS;


    }




    
    
    void City::destroyCity()
    {
  
    }
    City::~City()
    {
       delete Companies;
    }


    /*
    if(m_element->getParent()->getLeft()==m_element)//if it is left son of parent we must add to sum only left rank of it + if is there another left side 
{
    double s= (m_element->getRight() ? m_element->getRight()->getRank(): 0 );
    sum+=(m_element->getRank()-s);
    AVLNode<shared_ptr<Employee>,EmployeeComparebySalary>* current= m_element;
    while(current->getParent())current=current->getParent();
    sum+=(current->getRankAsLeaf()+current->getLeft()->getRank());

    
}
if(m_element->getParent()->getRight()==m_element)
{
    sum+=m_element->getLeft()->getRank();
}*/
