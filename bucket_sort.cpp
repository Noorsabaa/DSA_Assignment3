#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace chrono;

// BUCKET SORT IMPLEMENTATION

void bucketSort(vector<int>& arr) {
    if (arr.empty()) return;
    
    int n = arr.size();
    
    // Find minimum and maximum values
    int minVal = *min_element(arr.begin(), arr.end());
    int maxVal = *max_element(arr.begin(), arr.end());
    
    // Calculate range
    int range = maxVal - minVal + 1;
    
    // Create buckets (number of buckets = array size for optimal distribution)
    int bucketCount = n;
    vector<vector<int>> buckets(bucketCount);
    
    // Distribute elements into buckets
    for (int i = 0; i < n; i++) {
        // Calculate bucket index based on value
        int bucketIndex = (int)((double)(arr[i] - minVal) / range * (bucketCount - 1));
        buckets[bucketIndex].push_back(arr[i]);
    }
    
    // Sort individual buckets using STL sort (can use insertion sort too)
    for (int i = 0; i < bucketCount; i++) {
        sort(buckets[i].begin(), buckets[i].end());
    }
    
    // Concatenate all buckets back into original array
    int index = 0;
    for (int i = 0; i < bucketCount; i++) {
        for (int j = 0; j < buckets[i].size(); j++) {
            arr[index++] = buckets[i][j];
        }
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

vector<int> generateUniformArray(int size, int maxValue) {
    // Generate uniformly distributed data (best case for bucket sort)
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = (i * maxValue) / size;
    }
    // Shuffle for randomness
    random_shuffle(arr.begin(), arr.end());
    return arr;
}

vector<int> generateSkewedArray(int size) {
    // Generate skewed data (worst case for bucket sort)
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10; // All values in small range
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
    
    cout << "              BUCKET SORT - TEST CASES\n";
    
    // TEST CASE 1: Small Array 
    cout << "TEST CASE 1: Small Array\n\n";
    vector<int> arr1 = {42, 32, 33, 52, 37, 47, 51};
    printArray(arr1, "Before sorting: ");
    bucketSort(arr1);
    printArray(arr1, "After sorting:  ");
    cout << "Result: " << (isSorted(arr1) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 2: Array with Duplicates
    cout << "TEST CASE 2: Array with Duplicates\n\n";
    vector<int> arr2 = {5, 2, 8, 2, 9, 1, 5, 5, 3};
    printArray(arr2, "Before sorting: ");
    bucketSort(arr2);
    printArray(arr2, "After sorting:  ");
    cout << "Result: " << (isSorted(arr2) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 3: Uniformly Distributed Data (Best Case)
    cout << "TEST CASE 3: Uniformly Distributed Data (Best Case)\n\n";
    vector<int> arr3 = generateUniformArray(20, 100);
    printArray(arr3, "Before sorting: ");
    bucketSort(arr3);
    printArray(arr3, "After sorting:  ");
    cout << "Result: " << (isSorted(arr3) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 4: Already Sorted Array
    cout << "TEST CASE 4: Already Sorted Array\n\n";
    vector<int> arr4 = generateSortedArray(15);
    printArray(arr4, "Before sorting: ");
    double time4 = getExecutionTime(bucketSort, arr4);
    bucketSort(arr4);
    printArray(arr4, "After sorting:  ");
    cout << "Time taken: " << time4 << " ms\n";
    cout << "Result: " << (isSorted(arr4) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 5: Reverse Sorted Array
    cout << "TEST CASE 5: Reverse Sorted Array\n\n";
    vector<int> arr5 = generateReverseSortedArray(15);
    printArray(arr5, "Before sorting: ");
    double time5 = getExecutionTime(bucketSort, arr5);
    bucketSort(arr5);
    printArray(arr5, "After sorting:  ");
    cout << "Time taken: " << time5 << " ms\n";
    cout << "Result: " << (isSorted(arr5) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 6: Single Element
    cout << "TEST CASE 6: Single Element Array\n\n";
    vector<int> arr6 = {99};
    printArray(arr6, "Before sorting: ");
    bucketSort(arr6);
    printArray(arr6, "After sorting:  ");
    cout << "Result: " << (isSorted(arr6) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 7: All Same Elements
    cout << "TEST CASE 7: All Same Elements\n\n";
    vector<int> arr7(10, 50);
    printArray(arr7, "Before sorting: ");
    bucketSort(arr7);
    printArray(arr7, "After sorting:  ");
    cout << "Result: " << (isSorted(arr7) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 8: Skewed Data (Many elements in small range)
    cout << "TEST CASE 8: Skewed Data (Worst Case)\n\n";
    vector<int> arr8 = generateSkewedArray(20);
    printArray(arr8, "Before sorting: ");
    bucketSort(arr8);
    printArray(arr8, "After sorting:  ");
    cout << "Result: " << (isSorted(arr8) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 9: Performance - Uniform Distribution
    cout << "TEST CASE 9: Performance Test (1,000 elements, uniform)\n\n";
    vector<int> arr9 = generateUniformArray(1000, 10000);
    double time9 = getExecutionTime(bucketSort, arr9);
    bucketSort(arr9);
    cout << "Array size: 1000\n";
    cout << "Distribution: Uniform\n";
    cout << "Time taken: " << time9 << " ms\n";
    cout << "Result: " << (isSorted(arr9) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 10: Performance - Random Distribution
    cout << "TEST CASE 10: Performance Test (5,000 elements, random)\n\n";
    vector<int> arr10 = generateRandomArray(5000, 10000);
    double time10 = getExecutionTime(bucketSort, arr10);
    bucketSort(arr10);
    cout << "Array size: 5000\n";
    cout << "Distribution: Random\n";
    cout << "Time taken: " << time10 << " ms\n";
    cout << "Result: " << (isSorted(arr10) ? "PASS " : "FAIL ") << "\n\n";
    
    // TEST CASE 11: Large Array
    cout << "TEST CASE 11: Performance Test (10,000 elements)\n\n";
    vector<int> arr11 = generateRandomArray(10000, 100000);
    double time11 = getExecutionTime(bucketSort, arr11);
    bucketSort(arr11);
    cout << "Array size: 10000\n";
    cout << "Value range: 0-99999\n";
    cout << "Time taken: " << time11 << " ms\n";
    cout << "Result: " << (isSorted(arr11) ? "PASS ✓" : "FAIL ✗") << "\n\n";
    
    cout << "                  ALL TESTS COMPLETED\n";
    
    return 0;
}