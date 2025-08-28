#include <iostream>
using namespace std;

int main() {
    int n, target;
    bool found= false;
    cout<<"enter the length of array (it should be between 2 to 104)";
    cin>>n;

    int A[n];

    cout << "Hello World!" << endl;
    cout<<"enter the values of array";
    for(int i=0;i<n;i++){
       cin>>A[i];
    }
    cout<<"Enter the value of target you wanna get to adding digits of this array";
    cin>>target;

    for(int i=0; i<n && !found; i++){
        for(int j=i+1; j<n;j++){
            if(target == A[i]+A[j]){
                cout<<i<<" "<<j;
                found = true;
                break;
            }
        }
    }

    return 0;
}