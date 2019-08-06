#include <iostream>
#include <string>
#include <memory>

class IMMutableEmployee {
private:
    int m_id;
    std::string m_firstName;
    std::string m_lastName;
    double m_salary;

public:
    IMMutableEmployee(
        int id,
        const std::string& firstName,
        const std::string& lastName,
        const double& salary);

    IMMutableEmployee();

    const int& Id() const { return m_id;}
    const std::string& FirstName() const { return m_firstName;}
    const std::string LastName() const { return m_lastName;}
    const double Salary() const { return m_salary;}


    const std::shared_ptr<IMMutableEmployee> SetId(const int& id) const {
        return std::make_shared<IMMutableEmployee>(id, m_firstName, m_lastName, m_salary);
    }

    const std::shared_ptr<IMMutableEmployee> SetFirstName(const std::string& firstName) const {
        return std::make_shared<IMMutableEmployee>(m_id, firstName, m_lastName, m_salary);
    }

    const std::shared_ptr<IMMutableEmployee> SetLastName(const std::string& lastName) const {
        return std::make_shared<IMMutableEmployee>(m_id, m_firstName, lastName, m_salary);
    }

    const std::shared_ptr<IMMutableEmployee> SetSalary(const int& salary) const {
        return std::make_shared<IMMutableEmployee>(m_id, m_firstName, m_lastName, salary);
    }

};

IMMutableEmployee::IMMutableEmployee() :m_id(0), m_salary(0){}
IMMutableEmployee::IMMutableEmployee(int id,
        const std::string& firstName,
        const std::string& lastName,
        const double& salary) :m_id(id), m_firstName(firstName), m_lastName(lastName), m_salary(salary){}


void showEmployee(std::shared_ptr<IMMutableEmployee> p);

int main()
{

  std::string first = "Frankie";
  std::string last = "HolloyWood";
  double d = 1500.0;

  std::shared_ptr<IMMutableEmployee> me = std::make_shared<IMMutableEmployee>(0,first,last,d);

  showEmployee(me);

  std::shared_ptr<IMMutableEmployee> m2 = std::make_shared<IMMutableEmployee>(); m2 = m2->SetId(100);
  std::shared_ptr<IMMutableEmployee> m3 = m2->SetFirstName("James");
  std::shared_ptr<IMMutableEmployee> m4 = m3->SetLastName("DIO");
  std::shared_ptr<IMMutableEmployee> m5 = m4->SetSalary(2000.0);


  showEmployee(m5);

  return 0;
}

void showEmployee(std::shared_ptr<IMMutableEmployee> p)
{
    std::cout<<p->Id()<<std::endl;
    std::cout<<p->FirstName()<<std::endl;
    std::cout<<p->LastName()<<std::endl;
    std::cout<<p->Salary()<<std::endl;
}
