#include <iostream>
#include <string>
#include <memory>

class MutableEmployee {
private:
    int m_id;
    std::string m_firstName;
    std::string m_lastName;
    double m_salary;

public:
    MutableEmployee(
        int id,
        const std::string& firstName,
        const std::string& lastName,
        const double& salary);

    MutableEmployee();

    void SetId(const int id);
    void setFirstName(const std::string& FirstName);
    void setLastName(const std::string& LastName);
    void setSalary(const double& salary);

    int Id() const { return m_id;}
    std::string FirstName() const { return m_firstName;}
    std::string LastName() const { return m_lastName;}
    double Salary() const { return m_salary;}
};

MutableEmployee::MutableEmployee() :m_id(0), m_salary(0){}
MutableEmployee::MutableEmployee(int id,
        const std::string& firstName,
        const std::string& lastName,
        const double& salary) :m_id(id), m_firstName(firstName), m_lastName(lastName), m_salary(salary){}

void MutableEmployee::SetId(const int id) {m_id = id;}
void MutableEmployee::setFirstName(const std::string& FirstName) {m_firstName = FirstName;}
void MutableEmployee::setLastName(const std::string& LastName){m_lastName = LastName;}
void MutableEmployee::setSalary(const double& salary) { m_salary = salary;}

void showEmployee(std::shared_ptr<MutableEmployee> p);

int main()
{

  std::string first = "Frankie";
  std::string last = "HolloyWood";
  double d = 1500.0;

  std::shared_ptr<MutableEmployee> me = std::make_shared<MutableEmployee>(0,first,last,d);

  showEmployee(me);

  me->SetId(11);
  me->setFirstName("Ronnie");
  me->setLastName("James DIO");
  me->setSalary(1800.0);

  showEmployee(me);

  return 0;
}

void showEmployee(std::shared_ptr<MutableEmployee> p)
{
    std::cout<<p->Id()<<std::endl;
    std::cout<<p->FirstName()<<std::endl;
    std::cout<<p->LastName()<<std::endl;
    std::cout<<p->Salary()<<std::endl;
}
