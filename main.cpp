#include <iostream>

#include <string>

#include <vector>

#include <fstream>

using namespace std;

class Employee {
  private: string Name;
  string Role;
  string Branch;
  int EmployeeNumber;
  string PhoneNumber;
  double hour;
  double HourlyWage; // New member variable for hourly wage

  public:
    // Member function declarations
    void SetInfo(string name, string role, string branch, int employeeNumber, string phoneNumber, double hours);
  void SetHourlyWage(double wage); // New function to set hourly wage
  void DisplayInfo() const;
  string GetName() const;
  string GetRole() const;
  int GetEmployeeNumber() const;
  string GetPhoneNumber() const;
  string GetBranch() const {
    return Branch;
  }
  double GetHour() const {
    return hour;
  }
  double CalculateSalary() const; // New function to calculate salary based on hours worked
  void WriteToFile(ofstream & outputFile) const;
  static Employee ReadFromFile(ifstream & inputFile);
};

void Employee::WriteToFile(ofstream & outputFile) const {
  outputFile << Name << endl;
  outputFile << Role << endl;
  outputFile << Branch << endl;
  outputFile << EmployeeNumber << endl;
  outputFile << PhoneNumber << endl;
  outputFile << hour << endl;
  // Write other member variables if needed
}
Employee Employee::ReadFromFile(ifstream & inputFile) {
  Employee emp;
  getline(inputFile, emp.Name);
  getline(inputFile, emp.Role);
  getline(inputFile, emp.Branch);
  inputFile >> emp.EmployeeNumber;
  inputFile.ignore(); // Clear newline
  getline(inputFile, emp.PhoneNumber);
  inputFile >> emp.hour;
  inputFile.ignore(); // Clear newline
  // Read other member variables if needed
  return emp;
}

string Employee::GetName() const {
  return Name;
}

string Employee::GetRole() const {
  return Role;
}

int Employee::GetEmployeeNumber() const {
  return EmployeeNumber;
}

string Employee::GetPhoneNumber() const {
  return PhoneNumber;
}

void Employee::SetHourlyWage(double wage) {
  HourlyWage = wage;
}

void Employee::SetInfo(string name, string role, string branch, int employeeNumber, string phoneNumber, double hours) {
  Name = name;
  Role = role;
  Branch = branch;
  EmployeeNumber = employeeNumber;
  PhoneNumber = phoneNumber;
  hour = hours;
}

void Employee::DisplayInfo() const {
  cout << "Name: " << Name << endl;
  cout << "Role: " << Role << endl;
  cout << "Employee Number: " << EmployeeNumber << endl;
  cout << "Phone Number: " << PhoneNumber << endl;
  cout << "Hourly Wage: " << HourlyWage << endl;
  // You can add other details here as needed
}

double Employee::CalculateSalary() const {
  // Calculate the salary based on the hours worked and hourly wage
  return hour * HourlyWage;
}

bool AuthenticateUser(const string & username,
  const string & password) {
  // You can replace this with your actual authentication logic
  return (username == "admin" && password == "password");
}

int main() {
    string username, password;
    
    cout << "Login Page" << endl;
    cout << "Username: ";
    cin >> username;
    
    cout << "Password: ";
    cin >> password;
    
    cin.ignore();
    
    if (!AuthenticateUser(username, password)) {
        cout << "Invalid login credentials. Exiting..." << endl;
        return 1;
    }else{
        vector < Employee > employees; // Use a vector to store employee records
        int choice;
        ifstream inputFile("employee.txt");
        if (!inputFile) {
            cout << "File does not exist. Creating a new file." << endl;
            ofstream newFile("employee.txt");
            newFile.close();
            inputFile.open("employee.txt");
            if (!inputFile) {
                cout << "Unable to create or open input file." << endl;
                return 1;
            }
        }
        while (!inputFile.eof()) {
            Employee emp = Employee::ReadFromFile(inputFile);
            employees.push_back(emp);
        }
        inputFile.close();
        
        do {
            cout << "Menu:" << endl;
            cout << "1. Set Employee Information" << endl;
            cout << "2. Display Employee Information" << endl;
            cout << "3. Search Employee Information" << endl; // Added a new option for searching
            cout << "4. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1: {
                    string name, role, branch, phoneNumber;
                    int employeeNumber;
                    double hours;
                    
                    cout << "Enter name: ";
                    cin.ignore();
                    getline(cin, name);
                    
                    cout << "Enter role: ";
                    getline(cin, role);
                    
                    cout << "Enter branch: ";
                    getline(cin, branch);
                    
                    cout << "Enter employee number: ";
                    cin >> employeeNumber;
                    
                    cout << "Enter phone number: ";
                    cin.ignore();
                    getline(cin, phoneNumber);
                    
                    cout << "Enter hours worked: ";
                    cin >> hours;
                    
                    Employee emp;
                    emp.SetInfo(name, role, branch, employeeNumber, phoneNumber, hours);
                    employees.push_back(emp); // Store employee in the vector
                    break;
                }
                case 2: {
                    cout << "Displaying all employee information:" << endl;
                    for (const Employee & emp: employees) {
                        emp.DisplayInfo();
                        cout << endl;
                    }
                    break;
                }
                case 3: { // Search Employee Information
                    cout << "Enter search term (Employee Number, Phone Number, or Name): ";
                    cin.ignore(); // Clear newline from previous input
                    string searchTerm;
                    getline(cin, searchTerm);
                    
                    cout << "Search results:" << endl;
                    bool found = false;
                    
                    for (const Employee & emp: employees) {
                        if (to_string(emp.GetEmployeeNumber()) == searchTerm ||
                            emp.GetPhoneNumber() == searchTerm ||
                            emp.GetName() == searchTerm) {
                            emp.DisplayInfo();
                            found = true;
                            cout << endl;
                        }
                    }
                    
                    if (!found) {
                        cout << "No matching records found." << endl;
                    }
                    break;
                }
                    
                case 4:
                    cout << "Exiting the program." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please select again." << endl;
                    break;
            }
            
            // Clear the input buffer
            cin.clear();
            cin.ignore(numeric_limits < streamsize > ::max(), '\n');
        } while (choice != 4);
        
        ofstream outputFile("employee.txt");
        if (!outputFile) {
            cout << "Unable to open output file." << endl;
            return 1;
        }
        for (const Employee & emp: employees) {
            emp.WriteToFile(outputFile);
        }
        outputFile.close();
        return 0;
    }
}
