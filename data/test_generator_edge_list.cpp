#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    cout << n << " " << n*(n-1)/2 << endl;
    for (int i = 0; i < n; ++i){
    	cerr << i << endl;
    	for (int j = i+1; j < n; ++j){
    	    cout << i+1 << " " << j+1 << endl;
    	}
    }
    return 0;
}
