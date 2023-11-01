#include <cstdlib>
#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>
#include <cctype>
using namespace std;

class MonthlyBudget
{
public:
    double housing;
    double utilites;
    double houseHold;
    double transportation;
    double food;
    double medical;
    double insurance;
    double entertainment;
    double clothinng;
    double misc;
    void describeProgram();
    void getMonths(int &months);
    void getMonthlyBudget(fstream &budgetFile, int months);
    void getMonthlyExpenses(fstream &expenseFile, int months);
    void getMonthlyReport(fstream &budgetFile, fstream &expenseFile, int months);
};

class MonthlyExpenses : public MonthlyBudget
{
public:
    double housingEx;
    double utilitesEx;
    double householdEx;
    double transportationEx;
    double foodEx;
    double medicalEx;
    double insuranceEx;
    double entertainmentEx;
    double clothinngEx;
    double miscEx;
};

void MonthlyBudget::MonthlyBudget::describeProgram()
{
    cout << "--------------------------------------------------------------------\n";
    cout << "|                       EXPENSE MANAGEMENT SYSTEM                            |\n";
    cout << "--------------------------------------------------------------------\n";
}

void MonthlyBudget::getMonths(int &months)
{
    cout << "How many months would you like to have analyzed? ";
    cin >> months;
    cout << "--------------------------------------------------------------------\n";

    while (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter valid input ";
        cin >> months;
    }
}

void MonthlyBudget::getMonthlyBudget(fstream &budgetFile, int months)
{
    MonthlyBudget mb;
    int count = 1;

    budgetFile.open("budget.bin", ios::out | ios::binary);
    if (budgetFile.fail())
    {
        cout << "Could not find file: budget.bin \n";
        system("read"); // act as system("PAUSE")
    }

    try
    {
        do
        {
            cout << "            Enter monthly BUDGET for month " << count << "\n";
            cout << "--------------------------------------------------------------------\n";
            cout << "1.Housing          : ";
            cin >> mb.housing;
            cout << "2.Utilities        : ";
            cin >> mb.utilites;
            cout << "3.Household        : ";
            cin >> mb.houseHold;
            cout << "4.Transportation   : ";
            cin >> mb.transportation;
            cout << "5.Food and Dinning : ";
            cin >> mb.food;
            cout << "6.Medical          : ";
            cin >> mb.medical;
            cout << "7.Insurance        : ";
            cin >> mb.insurance;
            cout << "8.Entertainment    : ";
            cin >> mb.entertainment;
            cout << "9.Clothing         : ";
            cin >> mb.clothinng;
            cout << "10.Miscellaneous   : ";
            cin >> mb.misc;
            cout << "--------------------------------------------------------------------\n";

            budgetFile.write(reinterpret_cast<char *>(&mb), sizeof(mb));
            count++;
            months--;
        } while (months != 0);
    }

    catch (...)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Error, invalid input entered.";
    }

    budgetFile.close();
}

void MonthlyBudget::getMonthlyExpenses(fstream &expenseFile, int months)
{
    MonthlyExpenses me;
    int count = 1;

    expenseFile.open("expenses.bin", ios::out | ios::binary);
    if (expenseFile.fail())
    {
        cout << "Could not open expenses.bin \n";
        system("read");
    }
    try
    {
        do
        {
            cout << "               Enter monthly EXPENSE for month " << count << "\n";
            cout << "--------------------------------------------------------------------\n";
            cout << "1.Housing          : ";
            cin >> me.housingEx;
            cout << "2.Utilities        : ";
            cin >> me.utilitesEx;
            cout << "3.Household        : ";
            cin >> me.householdEx;
            cout << "4.Transportation   : ";
            cin >> me.transportationEx;
            cout << "5.Food and Dinning : ";
            cin >> me.foodEx;
            cout << "6.Medical          : ";
            cin >> me.medicalEx;
            cout << "7.Insurance        : ";
            cin >> me.insuranceEx;
            cout << "8.Entertainment    : ";
            cin >> me.entertainmentEx;
            cout << "9.Clothing         : ";
            cin >> me.clothinngEx;
            cout << "10.Miscellaneous   : ";
            cin >> me.miscEx;
            cout << "--------------------------------------------------------------------\n";

            expenseFile.write(reinterpret_cast<char *>(&me), sizeof(me));
            count++;
            months--;
        } while (months != 0);
    }

    catch (...)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Error, invalid input entered.";
    }
    expenseFile.close();
}

void MonthlyBudget::getMonthlyReport(fstream &budgetFile, fstream &expenseFile, int months)
{
    MonthlyBudget mb;
    MonthlyExpenses me;
    ofstream toFile;

    budgetFile.open("budget.bin", ios::in | ios::binary);
    if (budgetFile.fail())
    {
        cout << "Could not open budget.bin";
        system("read");
    }
    budgetFile.read(reinterpret_cast<char *>(&mb), sizeof(mb));

    expenseFile.open("expenses.bin", ios::in | ios::binary);
    if (expenseFile.fail())
    {
        cout << "Could not open expenses.bin (getMonthlyReport function)";
        system("read");
    }
    expenseFile.read(reinterpret_cast<char *>(&me), sizeof(me));

    while (!expenseFile.eof() && !budgetFile.eof())
    {

        cout << fixed << showpoint << setprecision(2);
        cout << "--------------------------------------------------------------------\n";
        cout << left << setw(14) << "Category";
        cout << right << setw(11) << "Budget";
        cout << right << setw(14) << "Spent";
        cout << right << setw(19) << "   Over(-)/Under \n";
        cout << "--------------------------------------------------------------------\n";

        cout << left << setw(14) << "Housing";
        cout << right << setw(11) << mb.housing;
        cout << right << setw(14) << me.housingEx;
        cout << right << setw(14) << (mb.housing - me.housingEx) << "\n";

        cout << left << setw(14) << "Utilities";
        cout << right << setw(11) << mb.utilites;
        cout << right << setw(14) << me.utilitesEx;
        cout << right << setw(14) << (mb.utilites - me.utilitesEx) << "\n";

        cout << left << setw(14) << "House Hold";
        cout << right << setw(11) << mb.houseHold;
        cout << right << setw(14) << me.householdEx;
        cout << right << setw(14) << (mb.houseHold - me.householdEx) << "\n";

        cout << left << setw(14) << "Transportation";
        cout << right << setw(11) << mb.transportation;
        cout << right << setw(14) << me.transportationEx;
        cout << right << setw(14) << (mb.transportation - me.transportationEx) << "\n";

        cout << left << setw(14) << "Food";
        cout << right << setw(11) << mb.food;
        cout << right << setw(14) << me.foodEx;
        cout << right << setw(14) << (mb.food - me.foodEx) << "\n";

        cout << left << setw(14) << "Medical";
        cout << right << setw(11) << mb.medical;
        cout << right << setw(14) << me.medicalEx;
        cout << right << setw(14) << (mb.medical - me.medicalEx) << "\n";

        cout << left << setw(14) << "Insurance";
        cout << right << setw(11) << mb.insurance;
        cout << right << setw(14) << me.insuranceEx;
        cout << right << setw(14) << (mb.insurance - me.insuranceEx) << "\n";

        cout << left << setw(14) << "Entertainment";
        cout << right << setw(11) << mb.entertainment;
        cout << right << setw(14) << me.entertainmentEx;
        cout << right << setw(14) << (mb.entertainment - me.entertainmentEx) << "\n";

        cout << left << setw(14) << "Clothing";
        cout << right << setw(11) << mb.clothinng;
        cout << right << setw(14) << me.clothinngEx;
        cout << right << setw(14) << (mb.clothinng - me.clothinngEx) << "\n";

        cout << left << setw(14) << "Miscellaneous";
        cout << right << setw(11) << mb.misc;
        cout << right << setw(14) << me.miscEx;
        cout << right << setw(14) << (mb.misc - me.miscEx) << "\n";

        cout << "--------------------------------------------------------------------\n";
        cout << "For the month you are over budget by ₹" << (mb.housing + mb.utilites + mb.houseHold + mb.transportation + mb.food + mb.medical + mb.insurance + mb.entertainment + mb.clothinng + mb.misc) - (me.housingEx + me.utilitesEx + me.householdEx + me.transportationEx + me.foodEx + me.medicalEx + me.insuranceEx + me.entertainmentEx + me.clothinngEx + me.miscEx) << "\n";

        toFile.open("results.txt", ios::app);
        toFile << fixed << showpoint << setprecision(2);
        toFile << "--------------------------------------------------------------------\n";
        toFile << left << setw(14) << "Category";
        toFile << right << setw(11) << "Budget";
        toFile << right << setw(14) << "Spent";
        toFile << right << setw(19) << "   Over(-)/Under \n";
        toFile << "--------------------------------------------------------------------\n";

        toFile << left << setw(14) << "Housing";
        toFile << right << setw(11) << mb.housing;
        toFile << right << setw(14) << me.housingEx;
        toFile << right << setw(14) << (mb.housing - me.housingEx) << "\n";

        toFile << left << setw(14) << "Utilities";
        toFile << right << setw(11) << mb.utilites;
        toFile << right << setw(14) << me.utilitesEx;
        toFile << right << setw(14) << (mb.utilites - me.utilitesEx) << "\n";

        toFile << left << setw(14) << "House Hold";
        toFile << right << setw(11) << mb.houseHold;
        toFile << right << setw(14) << me.householdEx;
        toFile << right << setw(14) << (mb.houseHold - me.householdEx) << "\n";

        toFile << left << setw(14) << "Transportation";
        toFile << right << setw(11) << mb.transportation;
        toFile << right << setw(14) << me.transportationEx;
        toFile << right << setw(14) << (mb.transportation - me.transportationEx) << "\n";

        toFile << left << setw(14) << "Food";
        toFile << right << setw(11) << mb.food;
        toFile << right << setw(14) << me.foodEx;
        toFile << right << setw(14) << (mb.food - me.foodEx) << "\n";

        toFile << left << setw(14) << "Medical";
        toFile << right << setw(11) << mb.medical;
        toFile << right << setw(14) << me.medicalEx;
        toFile << right << setw(14) << (mb.medical - me.medicalEx) << "\n";

        toFile << left << setw(14) << "Insurance";
        toFile << right << setw(11) << mb.insurance;
        toFile << right << setw(14) << me.insuranceEx;
        toFile << right << setw(14) << (mb.insurance - me.insuranceEx) << "\n";

        toFile << left << setw(14) << "Entertainment";
        toFile << right << setw(11) << mb.entertainment;
        toFile << right << setw(14) << me.entertainmentEx;
        toFile << right << setw(14) << (mb.entertainment - me.entertainmentEx) << "\n";

        toFile << left << setw(14) << "Clothing";
        toFile << right << setw(11) << mb.clothinng;
        toFile << right << setw(14) << me.clothinngEx;
        toFile << right << setw(14) << (mb.clothinng - me.clothinngEx) << "\n";

        toFile << left << setw(14) << "Miscellaneous";
        toFile << right << setw(11) << mb.misc;
        toFile << right << setw(14) << me.miscEx;
        toFile << right << setw(14) << (mb.misc - me.miscEx) << "\n";
        toFile.close();

        expenseFile.read(reinterpret_cast<char *>(&me), sizeof(me));
        budgetFile.read(reinterpret_cast<char *>(&mb), sizeof(mb));
    }

    budgetFile.close();
    expenseFile.close();
}

int main()
{
    int months = 1;
    fstream budgetFile, expenseFile;
    MonthlyExpenses a;

    a.describeProgram();
    a.getMonths(months);
    a.getMonthlyBudget(budgetFile, months);
    a.getMonthlyExpenses(expenseFile, months);
    a.getMonthlyReport(budgetFile, expenseFile, months);

    return 0;
}
