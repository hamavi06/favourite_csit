#include <iostream>
using namespace std;

int divide(int a, int b) {
    return a / b;
}

int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result = result * i;
    }
    return result;
}

int findMax(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int main() {
    int x = 10, y = 0;
    cout << "10 / 0 = " << divide(x, y) << endl;
    
    cout << "Factorial of -5 = " << factorial(-5) << endl;
    
    int emptyArray[5];
    cout << "Max of empty array = " << findMax(emptyArray, 0) << endl;
    
    return 0;
}
