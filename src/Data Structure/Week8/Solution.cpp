#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

class Sort {
public:
    Sort(const std::vector<int>& r) : data(r), length(r.size()), comparisons(0), movements(0) {}

    void InsertSort();
    void ShellSort();
    void BubbleSort();
    void QuickSort(int first, int last);
    void SelectSort();
    void HeapSort();
    void MergeSort1(int first, int last);
    void MergeSort2();

    void resetCounters();
    void displayMetrics(const std::string& algorithm);
    void Print() const;

private:
    std::vector<int> data;
    int length;
    int comparisons;
    int movements;

    int Partition(int first, int last);
    void Sift(int k, int last);
    void Merge(int first1, int last1, int last2);
    void MergePass(int h);
};

// 重置比较次数与移动次数
void Sort::resetCounters() {
    comparisons = 0;
    movements = 0;
}

// 打印比较次数与移动次数
void Sort::displayMetrics(const std::string& algorithm) {
    std::cout << algorithm << " - Comparisons: " << comparisons
              << ", Movements: " << movements << std::endl;
}

// 打印当前数组（仅用于调试）
void Sort::Print() const {
    for (auto num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// 插入排序
void Sort::InsertSort() {
    resetCounters();
    for (int i = 1; i < length; ++i) {
        int temp = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > temp) {
            data[j + 1] = data[j];
            --j;
            comparisons++;
            movements++;
        }
        data[j + 1] = temp;
        movements++;
    }
}

// 希尔排序（ShellSort）
void Sort::ShellSort() {
    resetCounters();
    for (int gap = length / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < length; ++i) {
            int temp = data[i];
            int j = i;
            while (j >= gap) {
                comparisons++;
                if (data[j - gap] > temp) {
                    data[j] = data[j - gap];
                    movements++;
                    j -= gap;
                } else {
                    break;
                }
            }
            data[j] = temp;
            movements++;
        }
    }
}

// 冒泡排序（BubbleSort）
void Sort::BubbleSort() {
    resetCounters();
    for (int i = 0; i < length - 1; ++i) {
        for (int j = 0; j < length - 1 - i; ++j) {
            comparisons++;
            if (data[j] > data[j + 1]) {
                // 拆解swap为两次赋值，分别记移动
                int temp = data[j];
                data[j] = data[j + 1];
                movements++;
                data[j + 1] = temp;
                movements++;
            }
        }
    }
}

// 快速排序辅助函数 Partition
int Sort::Partition(int first, int last) {
    int pivot = data[last];
    int i = first - 1;
    for (int j = first; j < last; ++j) {
        comparisons++;
        if (data[j] <= pivot) {
            i++;
            // swap作为3次操作
            int temp = data[i];
            data[i] = data[j];
            data[j] = temp;
            movements += 3;
        }
    }
    // pivot
    int temp = data[i + 1];
    data[i + 1] = data[last];
    data[last] = temp;
    movements += 3;

    return i + 1;
}

// 快速排序
void Sort::QuickSort(int first, int last) {
    if (first < last) {
        int pivotIndex = Partition(first, last);
        QuickSort(first, pivotIndex - 1);
        QuickSort(pivotIndex + 1, last);
    }
}

// 选择排序（SelectSort）
void Sort::SelectSort() {
    resetCounters();
    for (int i = 0; i < length - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < length; ++j) {
            comparisons++;
            if (data[j] < data[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            // 拆解swap为两次赋值
            int temp = data[i];
            data[i] = data[minIndex];
            movements++;
            data[minIndex] = temp;
            movements++;
        }
    }
}

// 堆排序辅助函数 Sift
void Sort::Sift(int k, int last) {
    int i = k;
    int j = 2 * i + 1;
    int temp = data[i];
    while (j <= last) {
        if (j < last && data[j] < data[j + 1]) {
            j++;
        }
        comparisons++;
        if (temp >= data[j]) {
            break;
        }
        data[i] = data[j];
        movements++;
        i = j;
        j = 2 * i + 1;
    }
    data[i] = temp;
    movements++;
}

// 堆排序
void Sort::HeapSort() {
    resetCounters();
    for (int i = length / 2 - 1; i >= 0; --i) {
        Sift(i, length - 1);
    }
    for (int i = length - 1; i > 0; --i) {
        int temp = data[0];
        data[0] = data[i];
        data[i] = temp;
        movements += 3;
        Sift(0, i - 1);
    }
}

// 归并辅助函数 Merge
void Sort::Merge(int first1, int last1, int last2) {
    std::vector<int> temp(last2 - first1 + 1);
    int i = first1, j = last1 + 1, k = 0;
    while (i <= last1 && j <= last2) {
        comparisons++;
        if (data[i] <= data[j]) {
            temp[k++] = data[i++];
        } else {
            temp[k++] = data[j++];
        }
        movements++;
    }
    while (i <= last1) {
        temp[k++] = data[i++];
        movements++;
    }
    while (j <= last2) {
        temp[k++] = data[j++];
        movements++;
    }
    for (k = 0, i = first1; i <= last2; ++i, ++k) {
        data[i] = temp[k];
        movements++;
    }
}

// 归并排序（递归）
void Sort::MergeSort1(int first, int last) {
    if (first < last) {
        int mid = (first + last) / 2;
        MergeSort1(first, mid);
        MergeSort1(mid + 1, last);
        Merge(first, mid, last);
    }
}

// 归并排序辅助函数 MergePass
void Sort::MergePass(int h) {
    for (int i = 0; i + h < length; i += 2 * h) {
        int mid = i + h - 1;
        int last = std::min(i + 2 * h - 1, length - 1);
        Merge(i, mid, last);
    }
}

// 归并排序
void Sort::MergeSort2() {
    resetCounters();
    for (int h = 1; h < length; h *= 2) {
        MergePass(h);
    }
}


int main() {
    std::vector<int> data(1000);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10000);

    for (int &num : data) {
        num = dis(gen);
    }

    {
        Sort sorter(data);
        auto start = std::chrono::high_resolution_clock::now();
        sorter.InsertSort();
        auto end = std::chrono::high_resolution_clock::now();
        sorter.displayMetrics("Insertion Sort");
        std::chrono::duration<double, std::milli> diff = end - start;
        std::cout << "Time: " << diff.count() << " ms\n\n";
    }

    {
        Sort sorter(data);
        auto start = std::chrono::high_resolution_clock::now();
        sorter.ShellSort();
        auto end = std::chrono::high_resolution_clock::now();
        sorter.displayMetrics("Shell Sort");
        std::chrono::duration<double, std::milli> diff = end - start;
        std::cout << "Time: " << diff.count() << " ms\n\n";
    }

    {
        Sort sorter(data);
        auto start = std::chrono::high_resolution_clock::now();
        sorter.BubbleSort();
        auto end = std::chrono::high_resolution_clock::now();
        sorter.displayMetrics("Bubble Sort");
        std::chrono::duration<double, std::milli> diff = end - start;
        std::cout << "Time: " << diff.count() << " ms\n\n";
    }

    {
        Sort sorter(data);
        auto start = std::chrono::high_resolution_clock::now();
        sorter.QuickSort(0, data.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();
        sorter.displayMetrics("Quick Sort");
        std::chrono::duration<double, std::milli> diff = end - start;
        std::cout << "Time: " << diff.count() << " ms\n\n";
    }

    {
        Sort sorter(data);
        auto start = std::chrono::high_resolution_clock::now();
        sorter.SelectSort();
        auto end = std::chrono::high_resolution_clock::now();
        sorter.displayMetrics("Selection Sort");
        std::chrono::duration<double, std::milli> diff = end - start;
        std::cout << "Time: " << diff.count() << " ms\n\n";
    }

    {
        Sort sorter(data);
        auto start = std::chrono::high_resolution_clock::now();
        sorter.HeapSort();
        auto end = std::chrono::high_resolution_clock::now();
        sorter.displayMetrics("Heap Sort");
        std::chrono::duration<double, std::milli> diff = end - start;
        std::cout << "Time: " << diff.count() << " ms\n\n";
    }

    {
        Sort sorter(data);
        auto start = std::chrono::high_resolution_clock::now();
        sorter.MergeSort1(0, data.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();
        sorter.displayMetrics("Merge Sort (Recursive)");
        std::chrono::duration<double, std::milli> diff = end - start;
        std::cout << "Time: " << diff.count() << " ms\n\n";
    }

    {
        Sort sorter(data);
        auto start = std::chrono::high_resolution_clock::now();
        sorter.MergeSort2();
        auto end = std::chrono::high_resolution_clock::now();
        sorter.displayMetrics("Merge Sort (Non-Recursive)");
        std::chrono::duration<double, std::milli> diff = end - start;
        std::cout << "Time: " << diff.count() << " ms\n\n";
    }

    return 0;
}