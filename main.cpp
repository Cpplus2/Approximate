#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

string parseDouble(double flop, int precisiondex);
string parseFraction(double fraction, int precisiondex);
string parseInt(int whole);
double fastExponentiation(double base, double exponent, double accumulator);


//Plus Point: Reset cursor after every iteration or derivation of polynomial sequence
class Polynomial{

    private:

        int degree;
        double * coefficients;

        int order;
        double * efficients;

    public:

        Polynomial()
        {
            Polynomial(0);
        }

        Polynomial(int deg)
        {
            Polynomial(deg, nullptr);
        }

        Polynomial(int deg, double * weights)
        {
            degree = deg;
            if(deg)
                coefficients = new double[degree];

            for(int counter = 0; counter < degree; counter++)
                coefficients[counter] = weights[counter];
        }

        void setDegree(int deg)
        {
            degree = deg;
        }

        void setCoefficients(double * weights, int cardinality)
        {
            for(int counter = 0; counter < cardinality; counter++)
                coefficients[counter] = weights[counter];
        }

        void setOrder(int ord)
        {
            if(ord > degree)
                cout << "Warning! The order of derivative is higher than the degree of the polynomial. " << endl;

            order = ord;
            efficients = new double[order];
        }

        int getOrder()
        {
            return order;
        }

        int getDegree()
        {
            return degree;
        }

        double getCoefficients()
        {
            cout << "The coefficients are: {";
            for(int counter = 0; counter < degree-1; counter++)
                cout << coefficients[counter] << ", ";

            cout << coefficients[degree-1] << "}" << endl;
        }

        double getCoefficient(int index)
        {
            cout << "The coefficient of the " << (index == 1 ? "1st" : (index == 2 ? "2nd" : ((index == 3) ? "3rd" : to_string(index) + "th"))) << " term: " << coefficients[index] << endl;
        }

        string f(char input, int index)
        {
            if(index == degree - 1)
                return parseDouble(coefficients[index], 1) + " = 0";

            return (coefficients[index] == 1 ? "": parseDouble(coefficients[index], 1) ) + input + (index == (degree - 2) ? "": "^" + parseInt(degree - index - 1) ) + " + " + f(input, index + 1);
        }

        //Solving polynomial as f(x), where x->n
        double f(double n, int index)               //index = degree - 1, as degree terms for a polynomial
        {
            if(index < degree)
                return (coefficients[index] * fastExponentiation(n, degree - index, 1) ) + f(n, index + 1);

            return coefficients[index];
        }

        //Not testable
        string f_derived(char input, int index)
        {
            if(index == degree - 2)
                return parseDouble(coefficients[index] * (degree - index - 1), 1) + " = 0";

            double temp = coefficients[index] * (degree - index - 1);

            return ((int)temp == temp && temp == 1 ? "": parseDouble(coefficients[index]  * (degree - index - 1), 1)) + input + (index == (degree - 3) ? "": "^" + parseInt(degree - index - 2) ) + " + " + f_derived(input, index + 1);
        }

        //Not testable
        double f_derived(double n, int order)
        {
            return 0.0;
        }
};

int main()
{
    //Preword
    cout << "This program expesses the Newton Raphson method of making precise approximations. " << endl << endl;
    cout << "The equation of the nonlinear equation is represented in the following format: a1x + a2x^2 + ... + anx^n " << endl;
    cout << "where n is the degree of the polynomial with the domain constraints { 0 < n < inf }" << endl << endl << endl;

    //Polynomial representation
    cout << "The polynomial is represented as a function of x, f(x)." << endl << endl;

    cout << "Enter the degree of the polynomial: ";

    int n;
    for(cin >> n; n < 0; cin >> n)  //Exception handle
        cout << "Sorry! The degree of the polynomial cannot be negative. Please try again. " << endl << endl << "Enter the degree of the polynomial: ";

    //Coefficient representation
    char alpha = '`';
    double * coefficients = new double[n+1]; //coefficients[n] = constant

    //Input -> coefficients
    for(int count = 0; count <= n; count++)
    {
        int num = 0;
        cout << "Enter " << (++alpha) << ": ";
        cin >> coefficients[alpha-97];
    }
    cout << endl;

    Polynomial polynomial(n+1, coefficients);

    cout << endl << "Choose one of the following: [1] f(x) (2) f(n) [3] f'(x) [4] f'(n) (4) 2nd or Higher order derivative" << endl;
    cout << "Enter your choice: "; int choice; cin >> choice;

    int p = 0;
    switch(choice)
    {
        case 1:
            cout << endl << "f(x) = " << polynomial.f('x', 0) << endl;
            break;

        case 2:
            cout << "Enter n: ";
            cin >> n;
            cout << "f'(x) = ";
            //cout << print(coefficients, n-1); //derive
            break;

        case 3:
            cout << endl << endl << "f(x) = " << polynomial.f('x', 0) << endl;
            cout << endl << endl << "f'(x) = " << polynomial.f_derived('x', 0);
            //cout << print(coefficients, n-1); //derive

            //cout << f(n, 1);
            break;

        case 4:
            cout << "Second / Higher Order Derivative " << endl << endl;
            cout << "The highest order derivative that can be calculated for a polynomial function is its degree. " << endl;
            cout << "Which order derivative would you like to calculate? [p < ]" << n << "]" << endl;
            cout << "Enter p: ";
            for(cin >> p; p >= n; cin >> p)
                cout << "Sorry! The derivative order you have mentioned is incalculable. Please try again. [p < ]" << n << "]" << endl << endl << "Enter p: ";

            break;

        default:
            cout << "Sorry! The option you have entered is invalid. " << endl;
    }

    cout << endl << endl << "Thank you for using this program! " << endl << endl;

    return 0;
}

//2 Recursive Calls: Parsing -> double TO string
string parseDouble(double flop, int precisiondex)
{
    return parseInt((int) flop) + "." + parseFraction(flop - (int) flop, precisiondex);
}

//Recursive version: Parsing -> fraction TO string
string parseFraction(double fraction, int precisiondex)
{
/*
    Base Case#1: The floating point value has reached its leftmost digit
    if(fraction == (int)fraction && fraction == 0)
        return "";
*/
    //Recursive Case
    if(precisiondex != 0)
    {
        //Extraction of fractional portion
        fraction -= (int)fraction;
        //Temporary Characterization of Rightmost Digit for String Concatenation Compatibility
        char character = (fraction * 10 + 48);
        //Recursive Trace
        return character + parseFraction(fraction * 10, precisiondex-1);
    }
    //Base Case#2: The floating point value has reached its indicated precision
    return "";
}

//Recursive version: integer TO string
string parseInt(int whole)      //time complexity: O(log n)
{
    //Base Case: All digits of the integer has been traversed.
    if(whole == 0)
        return "";

    //Temporary Characterization of Rightmost Digit for String Concatenation Compatibility
    char character = (whole % 10 + 48);

    //Recursive Case:
    return parseInt(whole / 10) + character;
}

//Fast Exponentiation
int fastExponent(int base, int exponent, int accumulator)
{
    if(exponent == 0)
        return accumulator;
    else if(exponent % 2 == 0)
        return fastExponent(base * base, exponent/2, accumulator);

    return fastExponent(base, exponent-1, base * accumulator);
}
