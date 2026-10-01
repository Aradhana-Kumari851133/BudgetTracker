# include<iostream>
using namespace std;
#include<string>
#include<vector>
#include <unordered_map>
#include <fstream>
#include<climits>

class Expense {
private:
    int Amount;
    string Category;
    string Description;
    string date;

    public:
    Expense(int amount, string category, string description, string date) {
       this->Amount = amount;
        this->Category = category;
        this->Description = description;
        this->date = date;

    }
    void showExpense() {
    cout << "The amount is: " << Amount << endl;
    cout << "The category is: " << Category << endl;
    cout << "The description is: " << Description << endl;
    cout << "The date is: " << date << endl;
}
int getAmount() {
    return Amount;
}
string getCategory() {
    return Category;
}
string getDescription(){
    return Description;
}
string getDate() {
    return date;
}
void setAmount(int amount) {
    Amount = amount;
}

void setCategory(string category) {
    Category = category;
}

void setDescription(string description) {
    Description = description;
}

void setDate(string date) {
    this->date = date;
}
};

class BudgetTracker {
private:
    vector<Expense> expenses;
    int monthlyBudget;

public:
    void addExpense(Expense e1);
    void showAllExpenses();
    void deleteExpense();
    int calculateTotal();
    void setBudget(int budget) {
        monthlyBudget = budget;
    }
    void remainingBudget();
    void categoryTotal(string category);
    void editExpense();
    void searchByCategory(string category);
    void searchByDescription(string description);
    int expenseCount(){
     return   expenses.size();

    }
    double averageExpense();
    void categorySummary();
    void dateSummary();
    void highestExpense();
    void minimumExpense();
    void saveToFile();
    void loadFromFile();
    void monthlySummary();
    void dailySummary();
};

void BudgetTracker::showAllExpenses() {

    if(expenses.empty()) {
    cout << "No expenses found!" << endl;
    return;
     }
    for(int i = 0; i < expenses.size(); i++) {
    cout << "Expense index: " << i << endl;

        expenses[i].showExpense();
    }
}
void BudgetTracker::addExpense(Expense e1) {
    expenses.push_back(e1);
    saveToFile();

}

int BudgetTracker::calculateTotal() {
    int total = 0;

    for(int i = 0; i < expenses.size(); i++) {
        total += expenses[i].getAmount();
    }

    return total;

}

void BudgetTracker::deleteExpense() {

    if( expenses.size() == 0){
    cout << "No expenses to delete!" << endl;
    return;
    }
    int index;

    cout << "Enter expense index: ";
    cin >> index;

    if(index<0 || index >= expenses.size()){
        cout<<"Invalid expense index!"<<endl;
        return;
    }
    
    expenses.erase(expenses.begin() + index);
    saveToFile();

    cout<<"Expense deleted successfully!"<<endl;
}

void BudgetTracker::remainingBudget() {
    int remainingBudget = monthlyBudget - calculateTotal();
    if(remainingBudget < 0) {
    cout << "Budget exceeded by: ₹" << -remainingBudget << endl;
     }
   else {
    cout << "Budget remaining: ₹" << remainingBudget << endl;
    if(remainingBudget <= monthlyBudget * 0.10) {
    cout << "Warning: Your budget is almost exhausted!" << endl;
     }
     }
}

void BudgetTracker::categoryTotal(string category) {
    bool found = false;

    int total = 0;

    for(int i = 0; i < expenses.size(); i++) {
        if(expenses[i].getCategory() == category) {
            total += expenses[i].getAmount();
            found = true;

        }
    }

  if(!found) {
    cout << "Category not found!" << endl;
}
else {
    cout << "The amount of " << category << ": ₹" << total << endl;
}          


}

void BudgetTracker::searchByDescription(string description) {
    bool found = false;

    int total = 0;

    for(int i = 0; i < expenses.size(); i++) {
        if(expenses[i].getDescription() == description) {
            total += expenses[i].getAmount();
            found = true;

        }
    }

  if(!found) {
    cout << "Description not found!" << endl;
}
else {
    cout << "The amount of " << description << ": ₹" << total << endl;
}          


}

void BudgetTracker::editExpense() {

    if(expenses.size() == 0) {
        cout << "No expenses to edit!" << endl;
        return;
    }

    int index;

    cout << "Enter expense index: ";
    cin >> index;

    if(index < 0 || index >= expenses.size()) {
        cout << "Invalid expense index!" << endl;
        return;
    }

     cout << "What do you want to edit?" << endl;
      cout << "1. Amount" << endl;
      cout << "2. Category" << endl;
     cout << "3. Description" << endl;
       cout << "4. Date" << endl;
      cout << "5. Cancel" << endl;

      int choice;
cout << "Enter your choice: ";
cin >> choice;
bool edited = false;
switch(choice) {

    case 1: {
        int newAmount;

        cout << "Enter new amount: ";
        cin >> newAmount;

        expenses[index].setAmount(newAmount);

        cout << "Amount updated successfully!" << endl;
         edited = true;

        break;
    }

    case 2: {
        string newCategory;

        cout << "Enter new category: ";
        cin >> newCategory;

        expenses[index].setCategory(newCategory);

        cout << "Category updated successfully!" << endl;
        edited = true;

        break;
    }

    case 3: {
        string newDescription;

        cout << "Enter new description: ";
        cin.ignore();
        getline(cin, newDescription);

        expenses[index].setDescription(newDescription);

        cout << "Description updated successfully!" << endl;
         edited = true;

        break;
    }

    case 4: {
        string newDate;

        cout << "Enter new date: ";
        cin >> newDate;

        expenses[index].setDate(newDate);

        cout << "Date updated successfully!" << endl;
        edited = true;

        break;
    }

    case 5:
        cout << "Edit cancelled." << endl;
        break;

    default:
        cout << "Invalid choice!" << endl;
}
    if(edited){
    saveToFile();
      }
}

void BudgetTracker::searchByCategory(string category) {

    bool found = false;

    for(int i = 0; i < expenses.size(); i++) {

        if(expenses[i].getCategory() == category) {
            cout << "Expense index: " << i << endl;
            expenses[i].showExpense();
            found = true;
        }
    }

    if(!found) {
        cout << "No expenses found in this category." << endl;
    }
}
double BudgetTracker::averageExpense() {

    if(expenses.size() == 0) {
        return 0;
    }

    return (double)calculateTotal() / expenseCount();
}

void BudgetTracker::categorySummary() {

    if(expenses.size() == 0) {
        cout << "No expenses found!" << endl;
        return;
    }

    unordered_map<string, int> categoryMap;

    for(int i = 0; i < expenses.size(); i++) {

    categoryMap[expenses[i].getCategory()] += expenses[i].getAmount();

    }
    for(auto i : categoryMap) {
    cout << i.first << ": ₹" << i.second << endl;
    }

}

void BudgetTracker::dateSummary() {
    unordered_map<string, int> dateMap;

    for(int i = 0; i < expenses.size(); i++) {
        dateMap[expenses[i].getDate()] += expenses[i].getAmount();
    }

    for(auto i : dateMap) {
        cout << i.first << ": ₹" << i.second << endl;
    }
}
void BudgetTracker::highestExpense() {

    if(expenses.size() == 0) {
        cout << "No expenses found!" << endl;
        return;
    }

    // yahan highest expense find karo
    int highestExpense = 0;

for(int i = 0; i < expenses.size(); i++) {
    if(expenses[i].getAmount() > highestExpense) {
        highestExpense = expenses[i].getAmount();
    }
}
cout << "Highest Expense: ₹" << highestExpense << endl;
}

void BudgetTracker::minimumExpense() {

    if(expenses.size() == 0) {
        cout << "No expenses found!" << endl;
        return;
    }

    // yahan highest expense find karo
    int minimumExpense = INT_MAX;

for(int i = 0; i < expenses.size(); i++) {
    if(expenses[i].getAmount() < minimumExpense) {
        minimumExpense = expenses[i].getAmount();
    }
}
cout << "Minimum Expense: ₹" << minimumExpense << endl;
}

void BudgetTracker::saveToFile() {

    ofstream file("expenses.txt");

    if(!file) {
        cout << "File could not be opened!" << endl;
        return;
    }

    // yahan expenses ko file mein save karna hai
   for(int i = 0; i < expenses.size(); i++) {

    file << expenses[i].getAmount() << endl;
    file << expenses[i].getCategory() << endl;
    file << expenses[i].getDescription() << endl;
    file << expenses[i].getDate() << endl;


}
    file.close();

    cout << "Expenses saved successfully!" << endl;
}

void BudgetTracker::loadFromFile() {

    ifstream file("expenses.txt");

    if(!file) {
        cout << "No saved expenses found!" << endl;
        return;
    }

    expenses.clear();

    int amount;
    string category, description, date;

    while(file >> amount) {

        file >> category;
        file.ignore();
        getline(file, description);
        file >> date;

        if(file.fail()) {
            cout << "Incomplete expense data found!" << endl;
            break;
        }

        Expense e(amount, category, description, date);
        expenses.push_back(e);
    }

    file.close();

    cout << "Expenses loaded successfully!" << endl;
}

void BudgetTracker::monthlySummary() {

    string month, year;

    cout << "Enter month: ";
    cin >> month;

    cout << "Enter year: ";
    cin >> year;

    int total = 0;

    // yahan expenses check karni hain
    for(int i = 0; i < expenses.size(); i++) {
    string date = expenses[i].getDate();
    
    if(date.substr(3, 2) == month &&
         date.substr(6, 4) == year) {
    
          total += expenses[i].getAmount();
     }
   } 
   cout << "Total expenses for " << month << "-" << year
     << ": ₹" << total << endl;
}


void BudgetTracker::dailySummary() {

    string enterdate;

    cout << "Enter date: ";
    cin >> enterdate;

    int total = 0;

    for(int i = 0; i < expenses.size(); i++) {

        string expensedate = expenses[i].getDate();

        if(expensedate == enterdate) {
            total += expenses[i].getAmount();
        }
    }

    cout << "Total expenses for " << enterdate
         << ": ₹" << total << endl;
}


int main(){
/*Expense e1(500, "Food", "Lunch", "17-09-2026");
Expense e2(250, "Travel", "Metro", "18-09-2026");
Expense e3(1200, "Clothes", "T-Shirt", "19-09-2026");
//e1.showExpense();

BudgetTracker b1;
b1.addExpense(e1);
b1.addExpense(e2);
b1.addExpense(e3);

b1.showAllExpenses();
//expenses.push_back(e1);
b1.calculateTotal();
b1.deleteExpense();
b1.showAllExpenses();
b1.setBudget(10000);
b1.remainingBudget();
b1.categoryTotal("Food");*/

BudgetTracker b1;
b1.loadFromFile();

    int choice;

    do {
        cout << "\n===== Budget Tracker =====" << endl;
        cout << "1. Add Expense" << endl;
        cout << "2. Show All Expenses" << endl;
        cout << "3. Calculate Total" << endl;
        cout << "4. Delete Expense" << endl;
        cout << "5. Set Budget" << endl;
        cout << "6. Remaining Budget" << endl;
        cout << "7. Category Total" << endl;
        cout << "8. Exit" << endl;
        cout << "9. Edit Expense" << endl;
        cout<<"10. Search Expense by category"<<endl;
        cout << "11. Total Number of Expenses" << endl;
        cout<<"12.Average Expenses"<<endl;
        cout << "13. Category Summary" << endl;
        cout << "14. Highest Expense" << endl;
        cout << "15. Minimum Expense" << endl;
        cout << "16. Date Summary" << endl;
        cout<<"17. Search Expense by description"<<endl;
        cout << "18. Monthly Summary" << endl;
        cout << "19. Daily Summary" << endl;



        cout << "Enter your choice: ";
        cin >> choice;

      cout << "DEBUG choice = " << choice << endl;

switch(choice){
    case 1: {
    int amount;
    bool valid = false;

    string category;
    string description;
    string date;

  do {
      cout << "Enter amount: ";
        cin >> amount;

     if(cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input! Please enter a valid amount." << endl;
    }
     else if(amount <= 0) {
         cout << "Amount must be greater than 0." << endl;
      }

    else {
        valid = true;
    }

   } while(!valid);

    cout << "Enter category: ";
    cin >> category;

    cout << "Enter description: ";
    cin.ignore();
    getline(cin, description);

    cout << "Enter date: ";
    cin >> date;

    Expense e(amount, category, description, date);

    b1.addExpense(e);

    break;
   }
   case 2:
    b1.showAllExpenses();
    break;

   case 3:
   cout << "Total expenses: ₹" << b1.calculateTotal() << endl;
    break;

   case 4:
    b1.deleteExpense();
    break;

    case 5: {
    int budget;

    do {
    cout << "Enter monthly budget: ";
    cin >> budget;

    if(budget <= 0) {
        cout << "Budget must be greater than 0." << endl;
      }

   } while(budget <= 0);

   b1.setBudget(budget);
    break;
     }

   case 6:
    b1.remainingBudget();
    break;

    case 7: {
    string category;

    cout << "Enter category: ";
    cin >> category;

    b1.categoryTotal(category);
    break;
   }

   case 8:
        cout << "Exiting..." << endl;
        break;

 case 9:
    b1.editExpense();
    break;

   case 10:{
      string category;
     cout<<"Enter category:";
     cin>>category;
       b1.searchByCategory(category);
         break;
   }

    case 11:{
    cout << "Total number of expenses: "
         << b1.expenseCount() << endl;
       break;
     }
 case 12:
    cout << "Average expense: ₹" << b1.averageExpense() << endl;
    break;

case 13:
    b1.categorySummary();
    break;
case 14:
    b1.highestExpense();
    break;
case 15:
    b1.minimumExpense();
    break;
case 16:
    b1.dateSummary();
    break;
case 17:{
      string description;
     cout<<"Enter description:";
     cin>>description;
       b1.searchByDescription(description);
         break;
   }
case 18:
    b1.monthlySummary();
    break;
case 19:
    b1.dailySummary();
    break;

    default:
        cout << "Invalid choice!" << endl;
}
 

    } while(choice != 8);


    return 0;
}
 