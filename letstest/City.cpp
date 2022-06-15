#include "City.h"
#include <cmath>
Company *City::getOriginalCompany(int id)
{
    Company **ptr = this->Companies->pointers;

    if (id <= 0 || id > this->Companies->n)
        return nullptr;

    return ptr[id];
}
template<typename K, typename V>
static void printBT1(const std::string& prefix, const AVLNode<K, V>* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout  <<node->getData()->getId()<< ",salary"<<node->getData()->getSalary()<< ",RANK:"<<node->getRank()<<",sub:"<<node->getSub_tree_size()<<endl;

        // enter the next tree level - left and right branch
        printBT1( prefix + (isLeft ? "│   " : "    "), node->getLeft(), true);
        printBT1( prefix + (isLeft ? "│   " : "    "), node->getRight(), false);
    }
}

template<typename K, typename V>
static void printBT(const AVLTree<K, V>& node)
{
  std::cout << "start-tree" << std::endl;
    printBT1("", node.getRoot(), false);
}
Company *City::getCompanyById(int id)
{
    return this->Companies->findd(id);
}

StatusType City::CompanyValue(int companyID)
{

    if (companyID <= 0 || companyID > this->num_of_companies)
        return INVALID_INPUT;
    Company *ptr = this->getOriginalCompany(companyID);
    
    if (!ptr)
        return FAILURE;

    double value_to_print=ptr->getValue();
    //(*standing) = &(ptr->value); // THERE WILL BE SOME PRECISION ISSUES
   // printf("CompanyValue: %.1f\n",value_to_print);
    printf("CompanyValue: %.1f\n", floor(10 * value_to_print + 0.5f) / 10);
    return SUCCESS;
}

shared_ptr<Employee> City::GetEmployee(int id)
{
    ListNode<shared_ptr<Employee>>* to_return = allEmployees->find(id);
if(!to_return)return nullptr;

shared_ptr<Employee> rtn=to_return->data;

    return rtn;
}

void City::updateEmployee(shared_ptr<Employee> em, int EmployeeID, int SalaryIncrease, int BumpGrade)
{
    // shared_ptr

    int new_grade = em->getGrade();
    if (BumpGrade > 0)
    {
        new_grade += BumpGrade;
    }
    em->setGrade(new_grade);
}

City::City(int k)
{

    this->Companies = new UnionFind<Company>(k+1);
    this->num_of_companies = k;
    this->num_of_employees = 0;
    this->employees_with_zero_salary = 0;
    this->sum_of_zero_employees_grade = 0;
    this->employees_by_salary = AVLTree<shared_ptr<Employee>, EmployeeComparebySalary>();
    this->allEmployees = new  HashTable<shared_ptr<Employee>>();
}
City::~City()
{
    //delete this->employees_by_salary;
     
    delete this->allEmployees;
    delete this->Companies;
  
}

StatusType City::AddEmployee(int EmployeeID, int CompanyID, int Grade)
{
    // check conditions are valid
    if (CompanyID <= 0 || EmployeeID <= 0 || Grade < 0|| CompanyID > num_of_companies)
    {
        return INVALID_INPUT;
    }
    if (!getCompanyById(CompanyID))
        return FAILURE;
    // check the company is exist in the system
    Company *company_to_update = getCompanyById(CompanyID);
    if (!company_to_update)
    {
        return FAILURE;
    }

    if (GetEmployee(EmployeeID))
        return FAILURE;
    // employee_to_check(nullptr);

    shared_ptr<Employee> employee_to_check = make_shared<Employee>(EmployeeID, Grade,0, CompanyID, company_to_update);
    allEmployees->insert(EmployeeID, employee_to_check);
    company_to_update->addEmployeeToCompany(employee_to_check);
    employees_with_zero_salary++;
    sum_of_zero_employees_grade += Grade;
    num_of_employees++;

    return SUCCESS;
}

StatusType City::RemoveEmployee(int EmployeeID)
{
    if (EmployeeID <= 0)
    {
        return INVALID_INPUT;
    }

    // check if is there an employee with the same id in the city
    shared_ptr<Employee> employee_to_remove = this->GetEmployee(EmployeeID);
    if (!employee_to_remove)
    {
        return FAILURE;
    }


    if (employee_to_remove->getSalary() == 0)
    {
        employees_with_zero_salary--;
        sum_of_zero_employees_grade -= employee_to_remove->getGrade();
    }
    else
    {
        employees_by_salary.AVLRemoveVal(employee_to_remove);
    }
    employee_to_remove->getCompany()->RemoveEmployee(EmployeeID);
    //printBT(employee_to_remove->getCompany()->employees_by_salary);
    this->num_of_employees--;

        allEmployees->remove(EmployeeID);
    return SUCCESS;
}

StatusType City::PromoteEmployee(int EmployeeID, int BumpGrade)
{

    if (EmployeeID <= 0)
    {
        return INVALID_INPUT;
    }
    shared_ptr<Employee> to_update = GetEmployee(EmployeeID);
    if (!to_update)
    {
        return FAILURE;
    }
    if(BumpGrade>0)
    {
        to_update->setGrade(to_update->getGrade() + BumpGrade);
        if(to_update->getSalary() != 0)
        {
            to_update->getCompany()->employees_by_salary.AVLRemoveVal(to_update);
            to_update->getCompany()->employees_by_salary.AVLInsert(to_update,to_update->getGrade());
            employees_by_salary.AVLRemoveVal(to_update);
            employees_by_salary.AVLInsert(to_update,to_update->getGrade());
        }
//to_update->getCompany()->employees_by_salary.updateRanksAbove(to_update->getCompany()->employees_by_salary.find(to_update->getCompany()->employees_by_salary.getRoot(),to_update),to_update->getGrade());
//employees_by_salary.updateRanksAbove(employees_by_salary.find(employees_by_salary.getRoot(),to_update),to_update->getGrade());
        if (to_update->getSalary() == 0)
        {
            to_update->getCompany()->sum_of_zero_employees_grade += BumpGrade;
            this->sum_of_zero_employees_grade += BumpGrade;
        }
    }
    //if(to_update->getId()==469)cout<<"grade of 469 :"<<to_update->getGrade()<<endl;
    return SUCCESS;
}

StatusType City::EmployeeSalaryIncrease(int employeeID, int salaryIncrease)
{
    if (employeeID <= 0 || salaryIncrease <= 0)
    {
        return INVALID_INPUT;
    }
    shared_ptr<Employee> ptr = GetEmployee(employeeID);
    if (!ptr)
    {
        return FAILURE;
    }
    // was not in tree
    if (ptr->getSalary() == 0)
    {
       
        ptr->setSalary(salaryIncrease);
        ptr->getCompany()->employees_by_salary.AVLInsert(ptr, ptr->getGrade());
        this->employees_by_salary.AVLInsert(ptr, ptr->getGrade());

        // removing from zeros
        ptr->getCompany()->employees_with_zero_salary--;
        ptr->getCompany()->sum_of_zero_employees_grade -= ptr->getGrade();
        this->employees_with_zero_salary--;
        this->sum_of_zero_employees_grade -= ptr->getGrade();

    } // was in tree
    else
    {

        ptr->getCompany()->employees_by_salary.AVLRemoveVal(ptr);
        this->employees_by_salary.AVLRemoveVal(ptr);
        ptr->setSalary(ptr->getSalary() + salaryIncrease);
        ptr->getCompany()->employees_by_salary.AVLInsert(ptr, ptr->getGrade());
        this->employees_by_salary.AVLInsert(ptr, ptr->getGrade());

    }

    return SUCCESS;
}

static double mofa3_reshon_find_how_many_lower_than(AVLTree<shared_ptr<Employee>, EmployeeComparebySalary> *tree, AVLNode<shared_ptr<Employee>, EmployeeComparebySalary> *root, int Salary)
{
    if (!root)
        return 0; // check this when using the function in avg function

    // we arrived boundary - maybe there are more than one with Salary==Salary
    if (root->getData()->getSalary() == Salary)
    {

        if (root->getLeft()&&(root->getLeft()->getData()->getSalary() > Salary))
        {
             if(root->getRight())
           {
            return root->getSub_tree_size()-root->getRight()->getSub_tree_size();
           }else
           {
               return root->getSub_tree_size();
           }
        }
        else if(root->getLeft())//==
        {

           return mofa3_reshon_find_how_many_lower_than(tree, root->getLeft(), Salary);
        }
        else//no left
        {
            return 1;//ROOT->GETSUBTREESIZE IS NOT TRUE TO USE
        }
    }
    // max boundary is in the left sub - we only want the sum of the nodes before it so we don't add something
    if (root->getData()->getSalary() < Salary)
    {

        return mofa3_reshon_find_how_many_lower_than(tree, root->getLeft(), Salary);
    }

    // max boundary is in the right - we want all of nodes that before max_boundary so we add
   if(root->getRight() &&root->getLeft())return root->getSub_tree_size() - root->getRight()->getSub_tree_size() +mofa3_reshon_find_how_many_lower_than(tree, root->getRight(), Salary);
    if(root->getRight()) return root->getSub_tree_size() - root->getRight()->getSub_tree_size();
     if(root->getLeft())return root->getSub_tree_size() + mofa3_reshon_find_how_many_lower_than(tree, root->getRight(), Salary);
     return root->getSub_tree_size();
}
static double find_how_many_lower_than(AVLTree<shared_ptr<Employee>, EmployeeComparebySalary> *tree, AVLNode<shared_ptr<Employee>, EmployeeComparebySalary> *root, int Salary)
{
    if (!root)
        return 0; // check this when using the function in avg function

    // we arrived boundary - maybe there are more than one with Salary==Salary
    if (root->getData()->getSalary() == Salary)
    {

        if (root->getLeft()&&(root->getLeft()->getData()->getSalary() > Salary))
        {
            if(root->getRight()&& root->getRight()->getData()->getSalary()==Salary)
           { return root->getSub_tree_size()-root->getRight()->getSub_tree_size()+find_how_many_lower_than(tree,root->getRight(),Salary);
           }else if(root->getRight())
           {
            return root->getSub_tree_size()-root->getRight()->getSub_tree_size();
           }else
           {
               return root->getSub_tree_size();
           }
        }
        else //==
        {

            if(root->getRight()&& root->getRight()->getData()->getSalary()==Salary)
           { return root->getSub_tree_size()-root->getRight()->getSub_tree_size()+find_how_many_lower_than(tree,root->getRight(),Salary);//1+find
           }else if(root->getRight())
           {
            return root->getSub_tree_size()-root->getRight()->getSub_tree_size();//1
           }else
           {
               return root->getSub_tree_size();
           }
        }
    }
    // max boundary is in the left sub - we only want the sum of the nodes before it so we don't add something
    if (root->getData()->getSalary() < Salary)
    {

        return find_how_many_lower_than(tree, root->getLeft(), Salary);
    }

    // max boundary is in the right - we want all of nodes that before max_boundary so we add
   if(root->getRight() &&root->getLeft())return root->getSub_tree_size() - root->getRight()->getSub_tree_size() + find_how_many_lower_than(tree, root->getRight(), Salary);
    if(root->getRight()) return root->getSub_tree_size() - root->getRight()->getSub_tree_size();
     if(root->getLeft())return root->getSub_tree_size() + find_how_many_lower_than(tree, root->getRight(), Salary);
     return root->getSub_tree_size();
}

/*static double find_sum_lower_than_aux(AVLTree<shared_ptr<Employee>, EmployeeComparebySalary> *tree, AVLNode<shared_ptr<Employee>, EmployeeComparebySalary> *root, int Salary)
{
    if (!root)
        return 0; // check this when using the function in avg function

    // we arrived boundary - maybe there are more than one with Salary==Salary
    if (root->getData()->getSalary() == Salary)
    {

        if (root->getLeft() && (root->getLeft()->getData()->getSalary() > Salary))
        {
            return root->getRank() - root->getRankAsLeaf();
        }
        else //==
        {
            return find_sum_lower_than_aux(tree, root->getLeft(), Salary);
        }
    }
    // max boundary is in the left sub - we only want the sum of the nodes before it so we don't add something
    if (root->getData()->getSalary() < Salary)
    {

        return find_sum_lower_than_aux(tree, root->getLeft(), Salary);
    }

    // max boundary is in the right - we want all of nodes that before max_boundary so we add
     if(root->getRight() &&root->getLeft())return root->getRank() - root->getRight()->getRank() + find_sum_lower_than_aux(tree, root->getRight(), Salary);
   //  if(root->getRight()) return root->getRank() - root->getRight()->getRank();
     if(root->getLeft())return root->getRank() + find_sum_lower_than_aux(tree, root->getRight(), Salary);
     return root->getRank();
    // not checked yet
}

// we can use this function in SumofBump ALSO!!
static double find_sum_lower_than(AVLTree<shared_ptr<Employee>, EmployeeComparebySalary> *tree, int Salary)
{

    return find_sum_lower_than_aux(tree, tree->root, Salary);

}*/
StatusType City::AcquireCompany(int AcquirerID, int TargetID, double Factor)
{
    if (AcquirerID <= 0 || TargetID <= 0 || AcquirerID == TargetID || Factor < 1.0 || TargetID > num_of_companies)
        return INVALID_INPUT;
    if (!getCompanyById(AcquirerID) || !getCompanyById(TargetID))
        return FAILURE;
    Company *Acquirer_ptr = getCompanyById(AcquirerID);
    if (!Acquirer_ptr)
        return FAILURE;
    Company *Target_ptr = getCompanyById(TargetID);
    if (!Target_ptr)
        return FAILURE;

    if (!Acquirer_ptr->moveEmployees(&Target_ptr->employees_by_salary, Target_ptr, Factor))
        return FAILURE; // dont forget employee with no salary
        
      

    this->Companies->unioun_groups_no_checking(AcquirerID,TargetID);
    
    
    return SUCCESS;
}


StatusType City::SumOfBumpGradeBetweenTopWorkersByGroup(int companyID, int m)
{
    // need to check companyID< k meaning
    if (companyID < 0 || m <= 0 ||companyID > num_of_companies)
        return INVALID_INPUT;
    long long int  sum_to_print = 0;
    if (companyID == 0)
    {
        if (this->num_of_employees < m)
        {
            return FAILURE;
        }
        else
        {
            // there are not || companyID>=this->num_of_companiesugh employees
            if (employees_by_salary.getNum_of_nodes() < m)
               return FAILURE;
               
            sum_to_print = SumbumpGradeFromTree(&employees_by_salary,employees_by_salary.getRoot(), m);
        }
    }else
        {
            Company *c = getCompanyById(companyID);
            // company is not existed or there are not enough employees
         //   cout<<"treesize:"<<c->employees_by_salary.getNum_of_nodes() <<endl;

      //AcquireCompany 2 1    cerr<<"sumofbump:"<<endl;
//cerr<<c->Employees->num_of_nodes<<endl;
//cerr<<c->employees_with_zero_salary<<endl;

            if (!c || c->employees_by_salary.getNum_of_nodes()< m)
                return FAILURE;
            sum_to_print = SumbumpGradeFromTree(&c->employees_by_salary , c->employees_by_salary.getRoot(), m);
             //printBT(c->employees_by_salary);
            //    cout<<"num of employees in tree: "<< c->employees_by_salary.getNum_of_nodes()<<endl;
            //cout<<"num of nodes in hashtable: "<< c->Employees->num_of_nodes << endl;
            //cout<<"employees with zero salary"<<c->employees_with_zero_salary<<endl; 
           // if(c->getId()==4&&m==3)printBT(c->employees_by_salary);
        }

    printf("SumOfBumpGradeBetweenTopWorkersByGroup: %lld\n",sum_to_print);
   



    return SUCCESS;
}

AVLNode<shared_ptr<Employee>, EmployeeComparebySalary> *Select(AVLNode<shared_ptr<Employee>, EmployeeComparebySalary> *root, int m)
{
    // found or leaf
    if (1 == m)
        return root;

    if (root->getSub_tree_size() == m)
        return Select(root->getRight(), m - root->getLeft()->getSub_tree_size() - 1);

    if (root->getSub_tree_size() > m)
    {
        if (root->getLeft()->getSub_tree_size() < m)
            return Select(root->getRight(), m - root->getLeft()->getSub_tree_size() - 1);
        if (root->getLeft()->getSub_tree_size() >= m)
            return Select(root->getLeft(), m);
    }
    // if there are enough nodes it will not arrive here
    return nullptr;
}
// double City::sumRank(AVLNode<shared_ptr<Employee>,EmployeeComparebySalary>* root,int m)
// {
//     if(m==0)
//     {
//         return 0;
//     }
//     if(root->getSub_tree_size()==m)
//     {
//         return root->getRank();
//     }
//     if(root->getLeft()->getSub_tree_size()>=m)
//     {
//         return sumRank(root->getLeft(),m);
//     }else{
//         return root->getRankAsLeaf()+root->getLeft()->getRank()
//                 +sumRank(root->getRight(),m-root->getLeft()->getSub_tree_size()-1);
//     }
// }

double City::SumbumpGradeFromTree(AVLTree<shared_ptr<Employee>, EmployeeComparebySalary> *tree, AVLNode<shared_ptr<Employee>, EmployeeComparebySalary> *root, int m)
{
   // int NumOfEmployees=tree->getNum_of_nodes();
           
            /*double sum=0;
             AVLNode<shared_ptr<Employee>,EmployeeComparebySalary>* ptr=tree->getMaxNode();
            for(int i=0;i<m &&i<tree->getNum_of_nodes() ;i++  )
            {
                
            //   if(ptr->getData()) 
              sum+=ptr->getRankAsLeaf();
              ptr=tree->the_next_node_iterating(ptr);
            }
            return sum;*/
            
   
    if (  m == 0 )
    {
        return 0;
    }
    if (root->getSub_tree_size() == m)
    {
        return root->getRank();
    }
    if (root->getLeft()&&(root->getLeft()->getSub_tree_size() >= m))
    {
        return SumbumpGradeFromTree(tree,root->getLeft(), m);
    }
     if(root->getLeft()&&root->getRight())return root->getRankAsLeaf() + root->getLeft()->getRank() + SumbumpGradeFromTree(tree,root->getRight(), m - root->getLeft()->getSub_tree_size()- 1 );
   // if(root->getLeft()&&root->getRight())return root->getRankAsLeaf() + root->getLeft()->getRank() + SumbumpGradeFromTree(tree,root->getRight(), m - root->getLeft()->getSub_tree_size()- 1 );
     if(root->getLeft())return root->getRankAsLeaf() + root->getLeft()->getRank();
      if(root->getRight())return root->getRankAsLeaf()+SumbumpGradeFromTree(tree,root->getRight(), m - 1);
      return root->getRankAsLeaf();
}

StatusType City::AverageBumpGradeBetweenSalaryByGroup(int companyID, int lowerSalary, int higherSalary)
{

    double grades_sum_salary_0 = 0;
    int num_of_zeros = 0;
    AVLTree<shared_ptr<Employee>, EmployeeComparebySalary> *tree = nullptr;
    Company *c_ptr = nullptr;
    if (higherSalary < 0 || lowerSalary < 0 || lowerSalary > higherSalary || companyID > this->num_of_companies || companyID < 0)
        return INVALID_INPUT;

    if (companyID == 0)
    {

        tree = &(this->employees_by_salary);
        grades_sum_salary_0 = this->sum_of_zero_employees_grade;
        num_of_zeros = this->employees_with_zero_salary;
   

    }
    else // positive
    {
        c_ptr = this->Companies->findd(companyID);

        grades_sum_salary_0 = c_ptr->sum_of_zero_employees_grade;
        num_of_zeros = c_ptr->employees_with_zero_salary;
        
    }
   
    if ((tree && num_of_zeros == 0 && tree->getNum_of_nodes() == 0) || (c_ptr && num_of_zeros == 0 && c_ptr->num_of_employees==0))
    {
        return FAILURE;
    }
    
    double toRtn = 0;
    if(!tree)tree=&c_ptr->employees_by_salary;
    if(companyID==43 && lowerSalary==701 && higherSalary==701)printBT(*tree);
    if (tree->getNum_of_nodes() != 0)
    {
        //double first = find_sum_lower_than(tree, lowerSalary);
        //double last = find_sum_lower_than(tree, higherSalary);

        int num_first = find_how_many_lower_than(tree, tree->root, lowerSalary);
        int num_last = mofa3_reshon_find_how_many_lower_than(tree, tree->root, higherSalary);
        double last = SumbumpGradeFromTree(tree,tree->root,num_last);
        double first =0;
        if(num_first!=num_last){first= SumbumpGradeFromTree(tree,tree->root,num_first);}
        else
        {
            if(num_first!=0){first=SumbumpGradeFromTree(tree,tree->root,num_first-1);}
            else{first=last=0;}
                
        }
        
       cout<<"num_first"<<num_first<<endl;
        cout<<"num_last"<<num_last<<endl;
        cout<<"frist"<<first<<endl;
        cout<<"last"<<last<<endl;
        int me5ane=1;
        if(lowerSalary==0)
        {
           
             if((num_of_zeros - num_first + num_last)!=0)me5ane=(num_of_zeros - num_first + num_last );
            toRtn = abs(grades_sum_salary_0 + last -first) / abs(me5ane) ;
        }else{

            if(( -num_first + num_last)!=0)me5ane=(  -num_first + num_last );

            toRtn = abs(  -first + last ) / abs(me5ane) ;      
            if(first==last)// first= last
            {
                
                toRtn = abs(first/num_first);
               
            }

            if(higherSalary >= tree->getMaxNode()->getData()->getSalary() && lowerSalary<=tree->getMinNode()->getData()->getSalary())
            {
              toRtn=abs((tree->getRoot()->getRank())/tree->getNum_of_nodes());
            }
            else if(lowerSalary >tree->getMaxNode()->getData()->getSalary())
            {toRtn=0;

            }   
        }
        
    }
    else 
    {
        if(lowerSalary==0)
        {
            toRtn = abs((grades_sum_salary_0) / (num_of_zeros));
        }else{
            toRtn=0;
        }
        
    }

    // maybe will be some precision issues
    // printing ... maybe we must add it to some parameter and print with c printf
    //printf("AverageBumpGradeBetweenSalaryByGroup: %.1f\n", toRtn);
   printf("AverageBumpGradeBetweenSalaryByGroup: %.1f\n", floor(10 * toRtn + 0.5f) / 10);
    return SUCCESS;
}

void City::destroyCity()
{
}

