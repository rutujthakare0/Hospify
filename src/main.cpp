#include <string>
#include "hospitalSystem.cpp"
string currentUserRole="none";
int pin=123;
int rec_pin=124;
int admin_pin=1234;
using namespace std;

int main() {
    HospitalSystem hs;
    hs.start();
    return 0;
}