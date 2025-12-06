#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace chrono;

// COUNTING SORT IMPLEMENTATION

void countingSort(vector<int>& arr) {
    if (arr.empty()) return;
    
    // Find the range of input data
    int maxVal = *max_element(arr.begin(), arr.end());
    int minVal = *min_element(arr.begin(), arr.end());
    int range = maxVal - minVal + 1;
    
    // Create count array to store frequency of each element
    vector<int> count(range, 0);
    
    // Store count of each element
    for (int i = 0; i < arr.size(); i++) {
        count[arr[i] - minVal]++;
    }
    
    // Modify count array to store actual positions
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }
    
    // Build the output array
    vector<int> output(arr.size());
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i] - minVal] - 1] = arr[i];
        count[arr[i] - minVal]--;
    }
    
    // Copy output array to original array
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = output[i];
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
    
    cout << "            COUNTING SORT - TEST CASES\n";
    
    // TEST CASE 1: Small Array
    cout << "TEST CASE 1: Small Array\n\n";
    vector<int> arr1 = {4, 2, 2, 8, 3, 3, 1, 9, 5};
    printArray(arr1, "Before sorting: ");
    countingSort(arr1);
    printArray(arr1, "After sorting:  ");
    cout << "Result: " << (isSorted(arr1) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 2: Array with Duplicates
    cout << "TEST CASE 2: Array with Many Duplicates\n\n";
    vector<int> arr2 = {5, 2, 2, 7, 1, 5, 3, 2, 5, 1, 7, 3, 5};
    printArray(arr2, "Before sorting: ");
    countingSort(arr2);
    printArray(arr2, "After sorting:  ");
    cout << "Result: " << (isSorted(arr2) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 3: Already Sorted Array
    cout << "TEST CASE 3: Already Sorted Array\n\n";
    vector<int> arr3 = generateSortedArray(15);
    printArray(arr3, "Before sorting: ");
    double time3 = getExecutionTime(countingSort, arr3);
    countingSort(arr3);
    printArray(arr3, "After sorting:  ");
    cout << "Time taken: " << time3 << " ms\n";
    cout << "Result: " << (isSorted(arr3) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 4: Reverse Sorted Array
    cout << "TEST CASE 4: Reverse Sorted Array\n\n";
    vector<int> arr4 = generateReverseSortedArray(15);
    printArray(arr4, "Before sorting: ");
    double time4 = getExecutionTime(countingSort, arr4);
    countingSort(arr4);
    printArray(arr4, "After sorting:  ");
    cout << "Time taken: " << time4 << " ms\n";
    cout << "Result: " << (isSorted(arr4) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 5: Single Element
    cout << "TEST CASE 5: Single Element Array\n\n";
    vector<int> arr5 = {42};
    printArray(arr5, "Before sorting: ");
    countingSort(arr5);
    printArray(arr5, "After sorting:  ");
    cout << "Result: " << (isSorted(arr5) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 6: All Same Elements
    cout << "TEST CASE 6: All Same Elements\n\n";
    vector<int> arr6(10, 7);
    printArray(arr6, "Before sorting: ");
    countingSort(arr6);
    printArray(arr6, "After sorting:  ");
    cout << "Result: " << (isSorted(arr6) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 7: Performance Small Range, Large Array
    cout << "TEST CASE 7: Performance Test (1,000 elements, range 0-99)\n\n";
    vector<int> arr7 = generateRandomArray(1000, 100);
    double time7 = getExecutionTime(countingSort, arr7);
    countingSort(arr7);
    cout << "Array size: 1000\n";
    cout << "Value range: 0-99\n";
    cout << "Time taken: " << time7 << " ms\n";
    cout << "Result: " << (isSorted(arr7) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 8: Performance - Medium Range, Large Array
    cout << "TEST CASE 8: Performance Test (5,000 elements, range 0-999)\n\n";
    vector<int> arr8 = generateRandomArray(5000, 1000);
    double time8 = getExecutionTime(countingSort, arr8);
    countingSort(arr8);
    cout << "Array size: 5000\n";
    cout << "Value range: 0-999\n";
    cout << "Time taken: " << time8 << " ms\n";
    cout << "Result: " << (isSorted(arr8) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 9: Performance - Large Array
    cout << "TEST CASE 9: Performance Test (10,000 elements, range 0-9999)\n\n";
    vector<int> arr9 = generateRandomArray(10000, 10000);
    double time9 = getExecutionTime(countingSort, arr9);
    countingSort(arr9);
    cout << "Array size: 10000\n";
    cout << "Value range: 0-9999\n";
    cout << "Time taken: " << time9 << " ms\n";
    cout << "Result: " << (isSorted(arr9) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 10: Negative Numbers
    cout << "TEST CASE 10: Array with Negative Numbers\n\n";
    vector<int> arr10 = {-5, 3, -2, 8, -1, 0, 4, -3, 2};
    printArray(arr10, "Before sorting: ");
    countingSort(arr10);
    printArray(arr10, "After sorting:  ");
    cout << "Result: " << (isSorted(arr10) ? "PASS " : "FAIL ") << "\n\n";
    
    cout << "                  ALL TESTS COMPLETED\n";
    
    return 0;
}