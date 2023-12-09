#include <iostream>
#include <Windows.h>


class SortStrategy {
public:
    virtual void sort(int arr[], int size) const = 0;
    virtual ~SortStrategy() = default;
};


class BubbleSort : public SortStrategy {
public:
    void sort(int arr[], int size) const override {
        
        for (int i = 0; i < size - 1; ++i) {
            for (int j = 0; j < size - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
};


class QuickSort : public SortStrategy {
public:
    void sort(int arr[], int size) const override {
        
        quickSort(arr, 0, size - 1);
    }

private:
    void quickSort(int arr[], int low, int high) const {
        if (low < high) {
            int pivot = partition(arr, low, high);
            quickSort(arr, low, pivot - 1);
            quickSort(arr, pivot + 1, high);
        }
    }

    int partition(int arr[], int low, int high) const {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; ++j) {
            if (arr[j] < pivot) {
                ++i;
                std::swap(arr[i], arr[j]);
            }
        }

        std::swap(arr[i + 1], arr[high]);
        return i + 1;
    }
};


class SortingContext {
private:
    SortStrategy* strategy;

public:
    SortingContext(SortStrategy* strategy) : strategy(strategy) {}

    void setStrategy(SortStrategy* newStrategy) {
        strategy = newStrategy;
    }

    void performSort(int arr[], int size) const {
        strategy->sort(arr, size);
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int arr[] = { 5, 2, 8, 7, 1, 3, 6, 4 };
    int size = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Масив до сортування: ";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;

    BubbleSort bubbleSort;
    QuickSort quickSort;

    SortingContext context(&bubbleSort);
    context.performSort(arr, size);

    std::cout << "Масив після сортування бульбашкою: ";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;

    context.setStrategy(&quickSort);
    context.performSort(arr, size);

    std::cout << "Масив після швидкого сортування: ";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;

    return 0;
}