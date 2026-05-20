#include <iostream>
using namespace std;

int divide(int a, int b) {
    if (b == 0) {
        cout << "Error: Cannot divide by zero!" << endl;
        return 0;
    }
    return a / b;
}

int factorial(int n) {
    if (n < 0) {
        cout << "Error: Factorial of negative number is undefined!" << endl;
        return -1;
    }
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result = result * i;
    }
    return result;
}

int findMax(int arr[], int size) {
    if (size <= 0) {
        cout << "Error: Array is empty!" << endl;
        return -1;
    }
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int main() {
    int a, b;
    cout << "Enter two numbers for division: ";
    cin >> a >> b;
    cout << a << " / " << b << " = " << divide(a, b) << endl;
    
    int n;
    cout << "Enter a number for factorial: ";
    cin >> n;
    cout << "Factorial of " << n << " = " << factorial(n) << endl;
    
    int size;
    cout << "Enter array size: ";
    cin >> size;
    
    if (size > 0) {
        int arr[size];
        cout << "Enter " << size << " numbers: ";
        for (int i = 0; i < size; i++) {
            cin >> arr[i];
        }
        cout << "Max value = " << findMax(arr, size) << endl;
    } else {
        int arr[1];
        cout << "Max of empty array = " << findMax(arr, 0) << endl;
    }
    
    return 0;
}#include <iostream>
using namespace std;

int divide(int a, int b) {
    if (b == 0) {
        cout << "Error: Cannot divide by zero!" << endl;
        return 0;
    }
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
}#include <iostream>
#include <stdexcept>
using namespace std;

double divide(int a, int b) {
    if (b == 0) {
        throw runtime_error("Error: Division by zero!");
    }
    return static_cast<double>(a) / b;
}

int factorial(int n) {
    if (n < 0) {
        throw runtime_error("Error: Factorial of negative number is undefined!");
    }
    if (n > 12) {
        throw runtime_error("Error: Factorial would cause integer overflow!");
    }
    
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int findMax(int arr[], int size) {
    if (size <= 0) {
        throw runtime_error("Error: Array is empty!");
    }
    
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int main() {
    try {
        int x = 10, y = 2;
        cout << "10 / 2 = " << divide(x, y) << endl;
        
        cout << "Factorial of 5 = " << factorial(5) << endl;
        
        int arr[] = {3, 7, 2, 9, 1};
        int size = sizeof(arr) / sizeof(arr[0]);
        cout << "Max in array = " << findMax(arr, size) << endl;
        
        cout << "\nTesting error handling:" << endl;
        cout << "10 / 0 = " << divide(10, 0) << endl;
        
    } catch (const exception& e) {
        cerr << "Caught exception: " << e.what() << endl;
    }
    
    try {
        cout << "Factorial of -3 = " << factorial(-3) << endl;
    } catch (const exception& e) {
        cerr << "Caught exception: " << e.what() << endl;
    }
    
    return 0;
}#include <iostream>
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
