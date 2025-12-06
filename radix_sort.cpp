#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace chrono;

// COUNTING SORT FOR RADIX SORT (sorts by specific digit)

void countingSortByDigit(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    vector<int> count(10, 0); // Digit range is 0-9
    
    // Count occurrences of each digit
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }
    
    // Calculate cumulative count 
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    
    // Build output array 
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }
    
    // Copy output to original array
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

// RADIX SORT (LSD - Least Significant Digit)
void radixSort(vector<int>& arr) {
    if (arr.empty()) return;
    
    // Find maximum number to determine number of digits
    int maxVal = *max_element(arr.begin(), arr.end());
    
    // Apply counting sort for each digit position
    // exp is 10^i where i is current digit position
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSortByDigit(arr, exp);
        
        // Optional: Show progress (comment out for performance testing)
        // cout << "After sorting by digit at position " << exp << ": ";
        // printArray(arr, "");
    }
}

// UTILITY FUNCTIONS

void printArray(const vector<int>& arr, const string& message) {
    cout << message;
    int limit = min(50, (int)arr.size());
    for (int i = 0; i < limit; i++) {
        cout << arr[i] << " ";
    }
    if (arr.size() > 50) cout << "... (" << arr.size() << " elements total)";
    cout << endl;
}

bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i - 1]) return false;
    }
    return true;
}

double getExecutionTime(void (*sortFunc)(vector<int>&), vector<int> arr) {
    auto start = high_resolution_clock::now();
    sortFunc(arr);
    auto end = high_resolution_clock::now();
    duration<double, milli> elapsed = end - start;
    return elapsed.count();
}

vector<int> generateRandomArray(int size, int maxValue) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % maxValue;
    }
    return arr;
}

vector<int> generateSortedArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
    return arr;
}

vector<int> generateReverseSortedArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = size - i - 1;
    }
    return arr;
}

// MAIN - TEST CASES

int main() {
    srand(time(0));
    
    cout << "         RADIX SORT (LSD) - TEST CASES\n\n";
    
    // TEST CASE 1: Small Array
    cout << "TEST CASE 1: Small Array\n\n";
    vector<int> arr1 = {170, 45, 75, 90, 802, 24, 2, 66};
    printArray(arr1, "Before sorting: ");
    radixSort(arr1);
    printArray(arr1, "After sorting:  ");
    cout << "Result: " << (isSorted(arr1) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 2: Array with Same Digits in Different Positions
    cout << "TEST CASE 2: Numbers with Same Digits\n\n";
    vector<int> arr2 = {329, 457, 657, 839, 436, 720, 355};
    printArray(arr2, "Before sorting: ");
    radixSort(arr2);
    printArray(arr2, "After sorting:  ");
    cout << "Result: " << (isSorted(arr2) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 3: Array with Different Number of Digits
    cout << "TEST CASE 3: Mixed Digit Lengths\n";
    vector<int> arr3 = {1, 22, 333, 4444, 55, 666, 7, 88, 9999};
    printArray(arr3, "Before sorting: ");
    radixSort(arr3);
    printArray(arr3, "After sorting:  ");
    cout << "Result: " << (isSorted(arr3) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 4: Already Sorted Array
    cout << "TEST CASE 4: Already Sorted Array\n\n";
    vector<int> arr4 = generateSortedArray(15);
    printArray(arr4, "Before sorting: ");
    double time4 = getExecutionTime(radixSort, arr4);
    radixSort(arr4);
    printArray(arr4, "After sorting:  ");
    cout << "Time taken: " << time4 << " ms\n";
    cout << "Result: " << (isSorted(arr4) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 5: Reverse Sorted Array
    cout << "TEST CASE 5: Reverse Sorted Array\n\n";
    vector<int> arr5 = generateReverseSortedArray(15);
    printArray(arr5, "Before sorting: ");
    double time5 = getExecutionTime(radixSort, arr5);
    radixSort(arr5);
    printArray(arr5, "After sorting:  ");
    cout << "Time taken: " << time5 << " ms\n";
    cout << "Result: " << (isSorted(arr5) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 6: Single Element
    cout << "TEST CASE 6: Single Element Array\n\n";
    vector<int> arr6 = {999};
    printArray(arr6, "Before sorting: ");
    radixSort(arr6);
    printArray(arr6, "After sorting:  ");
    cout << "Result: " << (isSorted(arr6) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 7: All Same Elements
    cout << "TEST CASE 7: All Same Elements\n\n";
    vector<int> arr7(10, 555);
    printArray(arr7, "Before sorting: ");
    radixSort(arr7);
    printArray(arr7, "After sorting:  ");
    cout << "Result: " << (isSorted(arr7) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 8: Performance - Small Numbers (1-2 digits)
    cout << "TEST CASE 8: Performance Test (1,000 elements, 1-2 digits)\n\n";
    vector<int> arr8 = generateRandomArray(1000, 100);
    double time8 = getExecutionTime(radixSort, arr8);
    radixSort(arr8);
    cout << "Array size: 1000\n";
    cout << "Value range: 0-99 (max 2 digits)\n";
    cout << "Time taken: " << time8 << " ms\n";
    cout << "Result: " << (isSorted(arr8) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 9: Performance - Medium Numbers (3-4 digits)
    cout << "TEST CASE 9: Performance Test (5,000 elements, 3-4 digits)\n\n";
    vector<int> arr9 = generateRandomArray(5000, 10000);
    double time9 = getExecutionTime(radixSort, arr9);
    radixSort(arr9);
    cout << "Array size: 5000\n";
    cout << "Value range: 0-9999 (max 4 digits)\n";
    cout << "Time taken: " << time9 << " ms\n";
    cout << "Result: " << (isSorted(arr9) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 10: Performance - Large Numbers (5-6 digits)
    cout << "TEST CASE 10: Performance Test (10,000 elements, 5-6 digits)\n\n";
    vector<int> arr10 = generateRandomArray(10000, 1000000);
    double time10 = getExecutionTime(radixSort, arr10);
    radixSort(arr10);
    cout << "Array size: 10000\n";
    cout << "Value range: 0-999999 (max 6 digits)\n";
    cout << "Time taken: " << time10 << " ms\n";
    cout << "Result: " << (isSorted(arr10) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 11: Array with Zeros
    cout << "TEST CASE 11: Array with Zeros\n\n";
    vector<int> arr11 = {0, 5, 0, 3, 0, 1, 0, 9, 0};
    printArray(arr11, "Before sorting: ");
    radixSort(arr11);
    printArray(arr11, "After sorting:  ");
    cout << "Result: " << (isSorted(arr11) ? "PASS " : "FAIL ") << "\n\n";
    
    cout << "                  ALL TESTS COMPLETED\n";
    
    return 0;
}