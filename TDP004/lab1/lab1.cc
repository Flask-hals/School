#include <iostream>
#include <iomanip>

using namespace std;

float moms(float moms, float price) {
    return price * (0.01 * moms);
}

float price_moms(float moms, float price) {
    return price + moms;
}

void print(float first, float moms_price, float last) {
    cout << setw(10) << first;
    cout << setw(15) << moms_price;
    cout << setw(20) << last << endl;
}


int main() {
    float first_price {};
    float last_price {};
    float steps {};
    float moms_percentage {};
    float moms_price {};
    float final_price {};
    int counter {};

    cout << "INMATNINGSDEL" << setprecision(2) << fixed << endl;
    cout << setw(size("inmatningsdel")) << setfill('=') << " " << endl;


    cout << "Mata in första pris: ";
    cin >> first_price;
    while (first_price < 0) {
        cerr << "FEL: Första pris måste vara minst 0 (noll) kronor" << endl;
        cout << "Mata in första pris: ";
        cin >> first_price;
    }

    cout << "Mata in sista pris: ";
    cin >> last_price;
    while (last_price < first_price) {
        cerr << "FEL: Sista pris måste vara större än första pris" << endl;
        cout << "Mata in sista pris: ";
        cin >> last_price;
    }

    cout << "Mata in steglängd: ";
    cin >> steps;
    while (steps < 0.01f) {
        cerr << "FEL: Steglängd måste vara minst 0.01" << endl;
        cout << "Mata in steglängd: ";
        cin >> steps;
    }

    cout << "Mata in momsprocent: ";
    cin >> moms_percentage;
    while (moms_percentage < 0 || moms_percentage > 100) {
        cerr << "FEL: Momsprocent måste vara större än 0 (noll) och mindre än 100 (hundra)" << endl;
        cout << "Mata in momsprocent: ";
        cin >> moms_percentage;
    }

    cout << "MOMSTABELL" << endl;
    cout << setw(size("momstabell")) << " " << endl;

    cout << setw(10) << setfill(' ') << "Pris";
    cout << setw(15) << "Moms";
    cout << setw(20) << "Pris med moms" << endl;

    cout << setw(45) << setfill('-') << "-" << endl;
    cout << setfill(' ');

    for( float price {first_price}; price <= last_price; price = first_price + (counter * steps))
    {
        moms_price = moms(moms_percentage, price);
        final_price = price_moms(moms_price, price);
        print(price, moms_price, final_price);
        counter += 1;
    }
    return 0;
}