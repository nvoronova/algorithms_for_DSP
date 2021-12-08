#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    cout << n << endl;
    for (int i = 0; i < n; ++i){
    	cout << n-1 << " ";
    	if ((i * 100)%n == 0){
    	    cerr << i*100/n << " percents done" << endl;
    	} 
    	for (int j = 0; j < n; ++j){
    	    if (i != j)
    	    	cout << j << " ";
    	}
    	cout << endl;
    }
    return 0;
}
