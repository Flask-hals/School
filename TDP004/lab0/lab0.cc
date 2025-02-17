#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
using namespace std;

int main()
{
    int number {};
    float dnumber {}; 
    char single_char {};
    string in_string {};

    cout << "Skriv in ett heltal: ";
    cin >> number;
    cout << "Du skrev in talet: " << number << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Skriv in fem heltal: ";
    cin >> number;
    cout << "Du skrev in talen: " << number << ", ";
    cin >> number;
    cout << number << ", ";
    cin >> number;
    cout << number << ", ";
    cin >> number;
    cout << number << ", ";
    cin >> number;
    cout << number << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Skriv in ett flyttal: ";
    cin >> dnumber;
    cout << setprecision(3) << fixed << "Du skrev in flyttalet: " << dnumber << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Skriv in ett heltal och ett flyttal: ";
    cin >> number;
    cin >> dnumber;
    cout << "Du skrev in heltalet:";
    cout <<  setw(10) << number << endl;
    cout << "Du skrev in flyttalet:";
    cout << setw(9) << dnumber << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Skriv in ett flyttal och ett heltal: ";
    cin >> dnumber;
    cin >> number;
    cout << "Du skrev in heltalet:";
    cout <<  setw(10) << setfill('-') << number << endl;
    cout << "Du skrev in flyttalet:";
    cout << setw(9) << dnumber << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Skriv in ett tecken: ";
    cin >> single_char;
    cout << "Du skrev in tecknet: " << single_char << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Skriv in en sträng: ";
    cin >> in_string;
    cout << "Strängen " << "'" << in_string << "'" << " har " 
        << size(in_string) << " tecken." << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Skriv in ett heltal och en sträng: ";
    cin >> number;
    cin >> in_string;
    cout << "Du skrev in talet " << "|" << number << "|" 
        << " och strängen " << "|" << in_string << "|." << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Skriv in en sträng och ett flyttal: ";
    cin >> in_string;
    cin >> dnumber;
    cout << "Du skrev in " << '"' << dnumber << '"' << " och " 
        << '"' << in_string << '"' << '.' << endl;

    cout << "Skriv in en hel rad med text: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, in_string);
    cout << "Du skrev in textraden: " << "'" << in_string << "'" << endl;

    cout << "Skriv in en textrad som slutar med ett negativt heltal: ";
    getline(cin, in_string, '-');
    cin >> number;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Du skrev in textraden: " << "'" << in_string << "'" 
        << " och heltalet " << "'-" << number << "'" << endl;

    return 0;

}