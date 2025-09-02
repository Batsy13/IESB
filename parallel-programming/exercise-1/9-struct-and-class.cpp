#include <iostream>
#include <iomanip>

struct Student
{
    std::string name;
    int age;
};

class BankAccount
{
private:
    double value = 0;

public:
    void deposit(double value)
    {
        this->value += value;
        std::cout << "Adding amount: $" << std::setprecision(2) << std::fixed  << value;
    }

    void withdraw(double value)
    {
        if (value > this->value)
        {
            std::cout << "Insufficient amount";
            return;
        }
        else
        {
            this->value -= value;
            std::cout << "Withdrawing value: $" << std::setprecision(2) << std::fixed  << value;
        }
    }

    void showAccount()
    {
        std::cout << "\nCurrent amount: $" << std::setprecision(2) << std::fixed << this->value << "\n";
    }
};

int main()
{

    // A )

    Student student;

    std::cout << "Enter your name: " << std::endl;
    std::getline(std::cin, student.name);

    std::cout << "Enter your age: " << std::endl;
    std::cin >> student.age;

    std::cout << "Your name is: " << student.name << std::endl;
    std::cout << "Your age: " << student.age << std::endl;

    // B )

    BankAccount myAccount;

    myAccount.deposit(1000);
    myAccount.showAccount();
    myAccount.withdraw(200);
    myAccount.showAccount();

    return 0;
}