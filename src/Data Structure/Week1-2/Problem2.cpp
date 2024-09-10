#include <bits/stdc++.h>
#include <chrono>
using namespace std;

// Recursive Algorithm
void RecursivePrint(int n) {
    if (n > 0) {
        RecursivePrint(n - 1);
        cout << n << " ";
    }
}

// Iterative Algorithm 
inline void IterativePrint(int n) {
    for (register int i = 1; i <= n; ++i) {
        cout << i << " ";
    }
}

int main() {
    int n;
    int ave_recursive_duration = 0, ave_iterative_duration = 0;
    cout << "Enter the value of n: ";
    cin >> n;
    
    for (int i=1;i<=10;i++){
    	cout<<"Running Test #"<<i<<":\n";
		// Measure time for IterativePrint
	    auto start_iterative = chrono::high_resolution_clock::now();
	    IterativePrint(n);
	    auto end_iterative = chrono::high_resolution_clock::now();
	    cout << "\nIterativePrint completed.\n";
	    		
	    // Measure time for RecursivePrint
	    auto start_recursive = chrono::high_resolution_clock::now();
	    RecursivePrint(n);
	    auto end_recursive = chrono::high_resolution_clock::now();
	    cout << "\nRecursivePrint completed.\n";
	
	    
	
	    // Calculate the elapsed time for both approaches
	    auto recursive_duration = chrono::duration_cast<chrono::milliseconds>(end_recursive - start_recursive).count();
	    auto iterative_duration = chrono::duration_cast<chrono::milliseconds>(end_iterative - start_iterative).count();
	
	    // Display time taken by both approaches
	    cout << "Time taken by RecursivePrint: " << recursive_duration << " ms" << endl;
	    cout << "Time taken by IterativePrint: " << iterative_duration << " ms" << endl;
	    ave_recursive_duration += recursive_duration;
	    ave_iterative_duration += iterative_duration;
	}
	
	cout << "Average Time taken by RecursivePrint: " << ave_recursive_duration/10.0 << " ms" << endl;
	cout << "Average Time taken by IterativePrint: " << ave_iterative_duration/10.0 << " ms" << endl;
    return 0;
}

