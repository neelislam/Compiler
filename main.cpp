#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    string input = "5+s";

    for(char ch : input){
         if(ch >= '0' && ch <= '9'){
           cout << ch << ": digit" << endl;
         }
        else if(ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            cout << ch << ": operator" << endl;
        }
        else if(ch >= 64 && ch <= 90 || ch >= 97 && ch <= 122) {
            cout << ch << ": Digit" << endl;
        }
        else{
            cout << ch << ": unknown symbol" << endl;
        }
    }
    return 0;
}
