#include <iostream>
using namespace std;

int main() {
    int a;
    int b;

    cout << "Enter a value for 'a': ";
    cin >> a;

    cout << "Enter a value for 'b' (greater than 1): ";
    cin >> b;

    int c = a * b; // Vulnerabilidade de Integer Overflow
    /*
    If a malicious user provides a value of 'b' greater than 1, 
    they can cause an Integer Overflow and manipulate the program's behavior unpredictably. 
    This can be particularly dangerous if the program relies on these calculations' 
    results to make critical decisions or access sensitive data.
*/
    cout << "The product of a and b is " << c << endl;

    return 0;
}
