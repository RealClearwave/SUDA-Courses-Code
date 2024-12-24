#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace chrono;

int sequentialSearch(const vector<int> &arr, int key, int &comparisons) {
    comparisons = 0;
    for (size_t i = 0; i < arr.size(); ++i) {
        comparisons++;
        if (arr[i] == key) return i;
    }
    return -1;
}

int binarySearchIterative(const vector<int> &arr, int key, int &comparisons) {
    comparisons = 0;
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        comparisons++;
        int mid = left + (right - left) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int binarySearchRecursiveHelper(const vector<int> &arr, int key, int left, int right, int &comparisons) {
    if (left > right) return -1;
    comparisons++;
    int mid = left + (right - left) / 2;
    if (arr[mid] == key) return mid;
    else if (arr[mid] < key)
        return binarySearchRecursiveHelper(arr, key, mid + 1, right, comparisons);
    else
        return binarySearchRecursiveHelper(arr, key, left, mid - 1, comparisons);
}

int binarySearchRecursive(const vector<int> &arr, int key, int &comparisons) {
    comparisons = 0;
    return binarySearchRecursiveHelper(arr, key, 0, arr.size() - 1, comparisons);
}

void testSearchAlgorithms() {
    int n;
    cout << "请输入线性表大小 n: ";
    cin >> n;

    vector<int> arr(n);
    srand(time(0));
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 100000;
    }

    sort(arr.begin(), arr.end());

    long long totalComparisonsSeq = 0, totalComparisonsBin = 0, totalComparisonsBinRec = 0;
    int successCountSeq = 0, failCountSeq = 0;
    int successCountBin = 0, failCountBin = 0;
    int successCountBinRec = 0, failCountBinRec = 0;

    int key = arr[rand() % n];
    cout << "查找关键字: " << key << "\n";

    int comparisonsSeq = 0;
    auto startSeq = high_resolution_clock::now();
    int resultSeq = sequentialSearch(arr, key, comparisonsSeq);
    auto endSeq = high_resolution_clock::now();
    auto durationSeq = duration_cast<microseconds>(endSeq - startSeq).count();
    totalComparisonsSeq += comparisonsSeq;
    if (resultSeq != -1) successCountSeq++;
    else failCountSeq++;

    int comparisonsBin = 0;
    auto startBin = high_resolution_clock::now();
    int resultBin = binarySearchIterative(arr, key, comparisonsBin);
    auto endBin = high_resolution_clock::now();
    auto durationBin = duration_cast<microseconds>(endBin - startBin).count();
    totalComparisonsBin += comparisonsBin;
    if (resultBin != -1) successCountBin++;
    else failCountBin++;

    int comparisonsBinRec = 0;
    auto startBinRec = high_resolution_clock::now();
    int resultBinRec = binarySearchRecursive(arr, key, comparisonsBinRec);
    auto endBinRec = high_resolution_clock::now();
    auto durationBinRec = duration_cast<microseconds>(endBinRec - startBinRec).count();
    totalComparisonsBinRec += comparisonsBinRec;
    if (resultBinRec != -1) successCountBinRec++;
    else failCountBinRec++;

    cout << "\n查找结果:\n";
    cout << "顺序查找: " << (resultSeq != -1 ? "成功" : "失败") 
         << " | 耗时: " << durationSeq << " 毫秒\n";
    cout << "二分查找(非递归): " << (resultBin != -1 ? "成功" : "失败") 
         << " | 耗时: " << durationBin << " 毫秒\n";
    cout << "二分查找(递归): " << (resultBinRec != -1 ? "成功" : "失败") 
         << " | 耗时: " << durationBinRec << " 毫秒\n";

    cout << "\n性能总结:\n";
    cout << "顺序查找: 成功 " << successCountSeq << " 次, 失败 " << failCountSeq 
         << " 次, 平均比较次数: " << (double)totalComparisonsSeq / (successCountSeq + failCountSeq) << "\n";
    cout << "二分查找(非递归): 成功 " << successCountBin << " 次, 失败 " << failCountBin 
         << " 次, 平均比较次数: " << (double)totalComparisonsBin / (successCountBin + failCountBin) << "\n";
    cout << "二分查找(递归): 成功 " << successCountBinRec << " 次, 失败 " << failCountBinRec 
         << " 次, 平均比较次数: " << (double)totalComparisonsBinRec / (successCountBinRec + failCountBinRec) << "\n";
}

int main() {
    srand(time(0));
    testSearchAlgorithms();
    return 0;
}