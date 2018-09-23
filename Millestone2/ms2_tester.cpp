/**********************************************************
  * Name: Yuru Ciou
  * Student ID: 115895179
  * Seneca email: yciou@myseneca.ca
  * Date of Completion: 2018/07/16
  **********************************************************/
#include <iostream>
#include "ErrorState.h"

using namespace std;
using namespace AMA;

int main() {
    ErrorState T("Testing Error State Module");
    ErrorState e;
    int ret = 0;
    bool ok = true;
    cout << T << endl << e << endl << "isClear(): " << (e.isClear() ? "Passed!" : "Failed!") << endl;
    if (!e.isClear()) ok = false;
    cout << endl;
    cout << "===========| Long Message\r";
    for (int i = 0; i < 10000000; i++) {
        if (i % 1000000 == 0) {
            cout << "*";
            cout.flush();
        }
        e.message("Some error message that is really long long  long  long  long  long  long  long"
                  " long  long  long  long  long  long  long  long  long  long  long  long  long"
                  " long  long  long  long  long  long  long  long  long  long  long  long  long"
                  " long  long  long  long  long  long  long  long  long  long  long  long  long"
                  " long  long  long  long  long  long  long  long  long  long  long  long  long"
                  " long  long  long  long  long  long  long  long  long  long  long  long  long"
                  " long  long  long  long  long  long  long  long  long  long  long  long  long"
                  " long  long  long  long  long  long  long  long  long  long  long  long  long"
                  " long  long  long  long  long  long  long  long  long  long  long  long  long"
                  " long  long  long  long  long  long  long  long  long  long  long  long  long"
                  " long  long  long  long  long  long  long  long  long  long  long  long  long"
                  " long  long  long  long  long  long  long  long  long  long  long  long  long"
                  " long  long  long  long  long  long  long  long  long  long  long  long  long"
                  " long  long  long  long  long  long  long  long  long  long  long  long  long"
                  " long  long  long  long  long  long  long  long  long  long  long  long  long"
                  " long  long  long  long  long  long  long  long  long  long  long  long  long"
                  " long  long  long  long  long  long  long  long  long  long  long  long  long"
                  " long  long  long  long  long  long  long  long  long  long  long  long  long"
                  " long  long  long  long  long  long  long  long  long  long  long  long  long");
    }
    cout << '*' << endl;
    cout << e << endl << "isClear(): " << (e.isClear() ? "Failed!" : "Passed!") << endl;
    if (e.isClear()) ok = false;
    cout << endl;
    
    e.message("Short Message");
    cout << e << endl << e.message() << endl << "isClear(): " << (e.isClear() ? "Failed!" : "Passed!") << endl;
    if (e.isClear()) ok = false;
    
    e.clear();
    cout << e << endl << "isClear(): " << (e.isClear() ? "Passed!" : "Failed!") << endl;
    if (!e.isClear()) ok = false;
    cout << endl;
    
    if (ok) {
        cout << "You passed all the tests!" << endl;
    }
    else {
        cout << "You did not pass all the tests, keep working on your project!" << endl;
        ret = 1;
    }
    
    return ret;
}
