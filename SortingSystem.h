#ifndef SORTINGSYSTEM_H
#define SORTINGSYSTEM_H

#include <iostream>
#include <chrono>
#include <functional>
using namespace std;

template <typename T>
class SortingSystem
{
private:
    T *data;
    int size;
    void PrintStatus();
    void new_PrintStatus(int array[], int n);
    void visualization(T firstElement, T secondElement);
    void new_visualization(T first_element, T second_element, string action);

public:
    SortingSystem(int n);
    ~SortingSystem();

    void insertionSort();
    void selectionSort();
    void bubbleSort();
    void mergeSort(int start, int end);
    void merge(int start, int middle, int end);

    void displayData();
    void showMenu();
    void quickSort(int left, int right);
    int partition(int low, int high);
    void shellSort();
    void countSort();  // (7) Count Sort (Only for int)
    void radixSort();  // (8) Radix Sort (Only for int)
    void bucketSort(); 
    void measureSortTime(void (SortingSystem::*sortFunc)());
    void measureSortTime(void (SortingSystem::*sortFunc)(int, int), int start, int end); // Measure sorting time
};

//!--------------------------------------- IMPLEMENTATION✔✔
static int counter = 1;
template <typename T>
void SortingSystem<T>::visualization(T first_element, T second_element)
{
    if (first_element != second_element)
    {
        cout << first_element << " and " << second_element << " were swaped.\n";
    }
}
template <typename T>
void SortingSystem<T>::new_visualization(T first_element, T second_element, string action)
{
    if (action == "Shifted")
    {
        cout << first_element << " was shifted to replace " << second_element << "\n";
    }
    else if (action == "Inserted")
    {
        cout << first_element << " was inserted at its correct position\n";
    }
    else
    {
        cout << first_element << " and " << second_element << " were compared\n";
    }
}
template <typename T>
SortingSystem<T>::SortingSystem(int n)
{
    size = n;
    data = new T[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Enter data " << i + 1 << " : ";
        cin >> data[i];
    }
}
template <typename T>
SortingSystem<T>::~SortingSystem()
{
    delete[] data;
}
template <typename T>
void SortingSystem<T>::PrintStatus()
{
    cout << "\nIteration " << counter << ": ";
    cout << "[ ";
    for (int i = 0; i < size; i++)
    {
        cout << *(data + i) << " ";
    }
    cout << "]\n";
    counter++;
}
template <typename T>
void SortingSystem<T>::new_PrintStatus(int array[], int n)
{
    cout << "[ ";
    for (int i = 0; i < n; i++)
    {
        cout << *(array + i) << " ";
    }
    cout << "]\n";
}
template <typename T>
void SortingSystem<T>::bubbleSort()
{
    displayData();
    for (int i = 0; i < size; i++)
    {
        bool flag = false;
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (data[j] > data[j + 1])
            {
                swap(data[j], data[j + 1]);
                visualization(data[j], data[j + 1]);
                flag = true;
            }
        }
        PrintStatus();
        if (!flag)
        {
            return;
        }
    }
}
template <typename T>
void SortingSystem<T>::selectionSort()
{
    displayData();
    int min_index;
    for (int i = 0; i < size; i++)
    {
        min_index = i;
        for (int j = i + 1; j < size; j++)
        {
            if (data[j] < data[min_index])
            {
                min_index = j;
            }
        }
        swap(data[min_index], data[i]);
        visualization(data[min_index], data[i]);
        PrintStatus();
    }
}
template <typename T>
void SortingSystem<T>::insertionSort()
{
    displayData();
    for (int i = 1; i < size; i++)
    {
        T current_element = data[i];
        int index_of_starting_comparing = i - 1;
        while (index_of_starting_comparing >= 0 && data[index_of_starting_comparing] > current_element)
        {
            //! Shifting
            visualization(data[index_of_starting_comparing + 1], data[index_of_starting_comparing]);
            data[index_of_starting_comparing + 1] = data[index_of_starting_comparing];
            index_of_starting_comparing--;
        }
        //! Assigning the key(current_element) in the correct index in the array
        data[index_of_starting_comparing + 1] = current_element;
        visualization(data[index_of_starting_comparing + 1], current_element);
        PrintStatus();
    }
}
template <typename T>
void SortingSystem<T>::merge(int start, int middle, int end)
{
    //! declaration of the sizes of the two arrays
    int size_of_left_array = middle - start + 1;
    int size_of_right_array = end - middle;
    //! Creation the  dynamic arrays
    T *left_array = new T[size_of_left_array];
    T *right_array = new T[size_of_right_array];

    //! Loop to assigning the main array from the left array
    for (int i = 0, count = start; i < size_of_left_array; i++, count++)
    {
        left_array[i] = data[count];
    }
    // ?Loop to assigning the main array from the right array
    for (int i = 0, count = middle + 1; i < size_of_right_array; i++, count++)
    {
        right_array[i] = data[count];
    }

    // ?Counters to compare the element in the left and right array
    int i = 0, j = 0, count_main_array = start;

    //! Sorting and assigning the elements in the main array
    while (i < size_of_left_array && j < size_of_right_array)
    {
        if (left_array[i] < right_array[j])
        {
            visualization(data[count_main_array], left_array[i]);
            data[count_main_array] = left_array[i];
            i++;
            count_main_array++;
        }

        else if (left_array[i] > right_array[j])
        {
            visualization(data[count_main_array], right_array[j]);
            data[count_main_array] = right_array[j];
            j++;
            count_main_array++;
        }
    }

    // ?Fill the array if there are any elements left in the right or left array
    while (i < size_of_left_array)
    {
        visualization(data[count_main_array], left_array[i]);
        data[count_main_array] = left_array[i];
        i++;
        count_main_array++;
    }

    while (j < size_of_right_array)
    {
        visualization(data[count_main_array], right_array[j]);
        data[count_main_array] = right_array[j];
        j++;
        count_main_array++;
    }

    PrintStatus();
    delete[] left_array;
    delete[] right_array;
}
template <typename T>
void SortingSystem<T>::mergeSort(int start, int end)
{

    if (start < end)
    {

        int middle = (start + end) / 2;
        mergeSort(start, middle);
        mergeSort(middle + 1, end);
        merge(start, middle, end);
    }
}
template <typename T>
int SortingSystem<T>::partition(int low, int high)
{
    T pivot = data[high];
    cout << "\nThe pivot is: " << pivot << '\n';
    int index = low - 1;
    for (int i = low; i < high; i++)
    {
        if (data[i] <= pivot)
        {
            index++;
            swap(data[index], data[i]);
            visualization(data[index], data[i]);
        }
    }
    index++;
    swap(data[index], data[high]);
    visualization(data[index], data[high]);
    PrintStatus();
    return index;
}
template <typename T>
void SortingSystem<T>::quickSort(int left, int right)
{
    if (right > left)
    {
        int pivot = partition(left, right);
        quickSort(left, pivot - 1);
        quickSort(pivot + 1, right);
    }
}
template <typename T>
void SortingSystem<T>::shellSort()
{
    for (int gap = size / 2; gap > 0; gap /= 2)
    {
        cout << "Reducing gap to: " << gap << "\n";
        for (int i = gap; i < size; i++)
        {
            T temp = data[i];
            int j;
            cout << "Picking element: " << temp << "\n";
            // Compare and shift elements
            for (j = i; j >= gap && data[j - gap] > temp; j -= gap)
            {
                cout << "Comparing " << data[j - gap] << " with " << temp << "\n";
                new_visualization(data[j - gap], data[j], "Shifted");
                PrintStatus();
                data[j] = data[j - gap];
            }
            // Insert the element in the correct position
            cout << "Inserting " << temp << " at the correct position" << "\n";
            data[j] = temp;
            new_visualization(temp, data[j], "Inserted");
            PrintStatus();
        }
    }
}

template <typename T>
void SortingSystem<T>::countSort()
{

    // getting the maximum number in the array
    int max = data[0];
    for (int i = 0; i < size; i++)
    {
        if (data[i] > max)
        {
            max = data[i];
        }
    }
    // declaration of the arrays
    int *frequency_array = new int[max + 1]();
    int *prefix_sum_array = new int[max + 1]();
    int *output_array = new int[size]();

    // frequency array algorithm
    for (int i = 0; i < size; i++)
    {
        frequency_array[data[i]]++;
    }
    // filling the prefix sum array
    prefix_sum_array[0] = frequency_array[0];
    for (int i = 1; i <= max; i++)
    {
        prefix_sum_array[i] = prefix_sum_array[i - 1] + frequency_array[i];
        cout << "Adding " << prefix_sum_array[i] << " to the prefix sum array \n";
    }
    cout << "The predix sum array is ready\n";
    new_PrintStatus(prefix_sum_array, max + 1);
    // performing the counting sort
    for (int i = size - 1; i >= 0; i--)
    {
        prefix_sum_array[data[i]]--;
        int new_position = prefix_sum_array[data[i]];
        output_array[new_position] = data[i];
        cout << "Adding " << data[i] << " in the correct position\n";
        new_PrintStatus(output_array, size);
    }
    for (size_t i = 0; i < size; i++)
    {
        data[i] = output_array[i];
    }
    delete[] frequency_array;
    delete[] prefix_sum_array;
    delete[] output_array;
}
template <typename T>
void SortingSystem<T>::radixSort()
{
    // Find the maximum number to determine the number of digits
    int max = data[0];
    for (int i = 1; i < size; i++)
        if (data[i] > max)
            max = data[i];

    // Apply counting sort for digits
    for (int exp = 1; max / exp > 0; exp *= 10)
    {
        cout << "Sorting by digit place: " << exp << "\n";
        int frequency_array[10] = {0};
        int output_array[size];

        // Count occurrences of each digit
        for (int i = 0; i < size; i++)
        {
            int digit = (data[i] / exp) % 10;
            frequency_array[digit]++;
            cout << "Counting digit " << digit << " in " << data[i] << "\n";
        }

        // perform prefix sum
        for (int i = 1; i < 10; i++)
            frequency_array[i] += frequency_array[i - 1];

        // Build the output array in a stable manner
        for (int i = size - 1; i >= 0; i--)
        {
            int digit = (data[i] / exp) % 10;
            frequency_array[digit]--;
            int new_position = frequency_array[digit];
            output_array[new_position] = data[i];

            cout << "Placing " << data[i] << " at position " << new_position << "\n";
            visualization(data[i], output_array[new_position]);
        }

        // return the sorted array to data array
        for (int i = 0; i < size; i++)
        {
            cout << "Updating data[" << i << "] to " << output_array[i] << "\n";
            visualization(data[i], output_array[i]);
            data[i] = output_array[i];
        }
    }
}
template <typename T>
void SortingSystem<T>::bucketSort()
{

    T **b = new T *[size];
    int *bucket_sizes = new int[size]();
    for (int i = 0; i < size; i++)
    {
        b[i] = new T[size];
    }

    for (int i = 0; i < size; i++)
    {
        if constexpr (std::is_integral<T>::value)
        {
            int bi = (data[i] * size);
            if (bi >= size)
                bi = size - 1;
            b[bi][bucket_sizes[bi]++] = data[i];
        }
    }

    for (int i = 0; i < size; i++)
    {
        if (bucket_sizes[i] > 0)
        {
            sort(b[i], b[i] + bucket_sizes[i]);
            for (int j = 0; j < bucket_sizes[i]; j++)
            {
                cout << b[i][j] << " ";
            }
            cout << endl;
        }
    }
    int index = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < bucket_sizes[i]; j++)
        {
            data[index++] = b[i][j];
        }
    }
    for (int i = 0; i < size; i++)
    {
        cout << data[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < size; i++)
    {
        delete[] b[i];
    }
    delete[] b;
    delete[] bucket_sizes;
    PrintStatus();
}

template <typename T>
void SortingSystem<T>::displayData()
{

    cout << "\nYour Sorted data: \n";
    cout << "[ ";
    for (int i = 0; i < size; i++)
    {
        cout << *(data + i) << " ";
    }
    cout << "]\n";
}
template <typename T>
void SortingSystem<T>::measureSortTime(void (SortingSystem<T>::*sortFunc)(int, int), int start, int end)
{
    auto startTime = chrono::high_resolution_clock::now();

    (this->*sortFunc)(start, end);

    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = endTime - startTime;

    cout << "Sorting completed in " << duration.count() << " ms\n";
}
template <typename T>
void SortingSystem<T>::measureSortTime(void (SortingSystem<T>::*sortFunc)())
{
    auto startTime = chrono::high_resolution_clock::now();
    (this->*sortFunc)();
    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = endTime - startTime;
    cout << "Sorting completed in " << duration.count() << " ms\n";
}

template <typename T>
void SortingSystem<T>::showMenu()
{
    while (true)
    {
        cout << "Select a sorting algorithm:\n";
        cout << "1. Insertion Sort\n";
        cout << "2. Selection Sort\n";
        cout << "3. Bubble Sort\n";
        cout << "4. Shell Sort\n";
        cout << "5. Merge Sort\n";
        cout << "6. Quick Sort\n";
        cout << "7. Count Sort (Only for integers)\n";
        cout << "8. Radix Sort (Only for integers)\n";
        cout << "9. Bucket Sort\n";
        cout << "0. Exit\n";
        cout << "Enter your choice (1-9): ";
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            insertionSort();
            measureSortTime(&SortingSystem<T>::insertionSort);
            counter = 1;
            break;
        case 2:
            selectionSort();
            measureSortTime(&SortingSystem<T>::selectionSort);
            counter = 1;
            break;
        case 3:
            bubbleSort();
            measureSortTime(&SortingSystem<T>::bubbleSort);
            counter = 1;
            break;
        case 4:
            shellSort();
            measureSortTime(&SortingSystem<T>::shellSort);
            counter = 1;
            break;
        case 5:
            mergeSort(0, size - 1);
            measureSortTime(&SortingSystem<T>::mergeSort, 0, size - 1);
            counter = 1;
            break;
        case 6:
            quickSort(0, size - 1);
            measureSortTime(&SortingSystem<T>::quickSort, 0, size - 1);
            counter = 1;
            break;
        case 7:
            if constexpr (std::is_integral<T>::value)
            {
                countSort();
                measureSortTime(&SortingSystem<T>::countSort);
                counter = 1;
            }
            else
            {
                cout << "Sorry, but this algorithm is just for integer values\n";
            }
            break;
        case 8:
            if constexpr (std::is_integral<T>::value)
            {
                radixSort();
                measureSortTime(&SortingSystem<T>::radixSort);
                counter = 1;
            }
            else
            {
                cout << "Sorry, but this algorithm is just for integer values\n";
            }
            break;
        case 9:
            if constexpr (std::is_integral<T>::value)
            {
                bucketSort();
                measureSortTime(&SortingSystem<T>::bucketSort);
                counter = 1;
                break;
            }
            else
            {
                cout << "Sorry, but this algorithm is just for numeric values\n";
            }

        case 0:
            cout << "Thank you for using the sorting system! Goodbye!\n";
            return;
        default:
            cout << "Please, enter a valid input!\n";
            continue;
        }

        displayData();
        break;
    }
}
#endif
