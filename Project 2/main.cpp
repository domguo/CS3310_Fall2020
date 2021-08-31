/*
 * CS3310 Project 2
 * Search for kth Value
 *
 * Dominic Guo
 *
 * Professor Gilbert Young
 *
 * Due December 1st, 2020
 *
*/

#include <iostream>
#include <cstdlib>
#include <chrono>

using namespace std;

void printarr(int*, int);
void swap(int[], int, int);
int* mergesort(int*, int);
int* merge(int*, int*, int, int);
int* quicksort(int*, int, int);
int* iquicksort(int*, int, int);
int partition(int*, int, int);
int partition2(int*, int, int, int);
int partition3(int*, int, int, int);
int selectkth1(int*, int, int);
int selectkth2(int*, int, int, int);
int selectkth3(int*, int, int, int);
int selectkth4(int*, int, int);


int main()
{
    //Initialize variables
    int sizes[10] = {10, 20, 50, 100, 200, 500, 1000, 2000, 5000};  //Size of arrays
    int runs = 100;                                                 //Number of runs per k, per array size
    double selectkth1time;                                          //Time totals per algo
    double selectkth2time;
    double selectkth3time;
    double selectkth4time;

    //For loop iterates through all array sizes and runs
    for(int i = 0; i < sizeof(sizes); i++)
    {
        //Zero out times
        selectkth1time = 0;
        selectkth2time = 0;
        selectkth3time = 0;
        selectkth4time = 0;

        //Create new array and fill it with random numbers up to array size
        int* arr = new int[sizes[i]];

        for(int i = 0; i < sizes[i]; i++)
            arr[i] = rand() % sizes[i];

        //Run Select 1-4 for k = 1, run number of times
        //Each loop collects the total run time for each algorithm
        for(int j = 0; j < runs; j++)
        {
            auto start_time = chrono::high_resolution_clock::now();

            selectkth1(arr, sizes[i], 1);

            auto end_time = chrono::high_resolution_clock::now();

            selectkth1time += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        }

        for(int j = 0; j < runs; j++)
        {
            auto start_time = chrono::high_resolution_clock::now();

            selectkth2(arr, 1, 0, sizes[i]);

            auto end_time = chrono::high_resolution_clock::now();

            selectkth2time += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        }

        for(int j = 0; j < runs; j++)
        {
            auto start_time = chrono::high_resolution_clock::now();

            selectkth3(arr, 1, 0, sizes[i]-1);

            auto end_time = chrono::high_resolution_clock::now();

            selectkth3time += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        }


//        for(int j = 0; j < runs; j++)
//        {
//            auto start_time = chrono::high_resolution_clock::now();

//            selectkth4(arr, sizes[i], 1);

//            auto end_time = chrono::high_resolution_clock::now();

//            selectkth4time += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
//        }

        //////////

        //Run Select 1-4 for k = n/4, run number of times
        for(int j = 0; j < runs; j++)
        {
            auto start_time = chrono::high_resolution_clock::now();

            selectkth1(arr, sizes[i], sizes[i]/4);

            auto end_time = chrono::high_resolution_clock::now();

            selectkth1time += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        }

        for(int j = 0; j < runs; j++)
        {
            auto start_time = chrono::high_resolution_clock::now();

            selectkth2(arr, sizes[i]/4, 0, sizes[i]);

            auto end_time = chrono::high_resolution_clock::now();

            selectkth2time += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        }

        for(int j = 0; j < runs; j++)
        {
            auto start_time = chrono::high_resolution_clock::now();

            selectkth3(arr, sizes[i]/4, 0, sizes[i]-1);

            auto end_time = chrono::high_resolution_clock::now();

            selectkth3time += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        }


//        for(int j = 0; j < runs; j++)
//        {
//            auto start_time = chrono::high_resolution_clock::now();

//            selectkth4(arr, sizes[i], sizes[i]/4);

//            auto end_time = chrono::high_resolution_clock::now();

//            selectkth4time += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
//        }

        //////////

        //Run Select 1-4 for k = n/2, run times
        for(int j = 0; j < runs; j++)
        {
            auto start_time = chrono::high_resolution_clock::now();

            selectkth1(arr, sizes[i], sizes[i]/2);

            auto end_time = chrono::high_resolution_clock::now();

            selectkth1time += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        }

        for(int j = 0; j < runs; j++)
        {
            auto start_time = chrono::high_resolution_clock::now();

            selectkth2(arr, sizes[i]/2, 0, sizes[i]);

            auto end_time = chrono::high_resolution_clock::now();

            selectkth2time += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        }

        for(int j = 0; j < runs; j++)
        {
            auto start_time = chrono::high_resolution_clock::now();

            selectkth3(arr, sizes[i]/2, 0, sizes[i]-1);

            auto end_time = chrono::high_resolution_clock::now();

            selectkth3time += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        }


//        for(int j = 0; j < runs; j++)
//        {
//            auto start_time = chrono::high_resolution_clock::now();

//            selectkth4(arr, sizes[i], sizes[i]/2);

//            auto end_time = chrono::high_resolution_clock::now();

//            selectkth4time += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
//        }

        /////////

        //Run Select 1-4 for k = 3n/4, for run number of times
        for(int j = 0; j < runs; j++)
        {
            auto start_time = chrono::high_resolution_clock::now();

            selectkth1(arr, sizes[i], (3 * sizes[i]/4));

            auto end_time = chrono::high_resolution_clock::now();

            selectkth1time += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        }

        for(int j = 0; j < runs; j++)
        {
            auto start_time = chrono::high_resolution_clock::now();

            selectkth2(arr, (3 * sizes[i]/4), 0, sizes[i]);

            auto end_time = chrono::high_resolution_clock::now();

            selectkth2time += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        }

        for(int j = 0; j < runs; j++)
        {
            auto start_time = chrono::high_resolution_clock::now();

            selectkth3(arr, (3 * sizes[i]/4), 0, sizes[i]-1);

            auto end_time = chrono::high_resolution_clock::now();

            selectkth3time += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        }


//        for(int j = 0; j < runs; j++)
//        {
//            auto start_time = chrono::high_resolution_clock::now();

//            selectkth4(arr, sizes[i], (3 * sizes[i]/4));

//            auto end_time = chrono::high_resolution_clock::now();

//            selectkth4time += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
//        }

        ////////

        //Run Select 1-4 for k = n, run number of times
        for(int j = 0; j < runs; j++)
        {
            auto start_time = chrono::high_resolution_clock::now();

            selectkth1(arr, sizes[i], sizes[i]);

            auto end_time = chrono::high_resolution_clock::now();

            selectkth1time += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        }

        for(int j = 0; j < runs; j++)
        {
            auto start_time = chrono::high_resolution_clock::now();

            selectkth2(arr, sizes[i], 0, sizes[i]);

            auto end_time = chrono::high_resolution_clock::now();

            selectkth2time += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        }

        for(int j = 0; j < runs; j++)
        {
            auto start_time = chrono::high_resolution_clock::now();

            selectkth3(arr, sizes[i], 0, sizes[i]-1);

            auto end_time = chrono::high_resolution_clock::now();

            selectkth3time += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        }


//        for(int j = 0; j < runs; j++)
//        {
//            auto start_time = chrono::high_resolution_clock::now();

//            selectkth4(arr, sizes[i], sizes[i]);

//            auto end_time = chrono::high_resolution_clock::now();

//            selectkth4time += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
//        }

        cout << "selectkth1 total time for array size " << sizes[i] << ": " << selectkth1time << endl;
        cout << "selectkth1 average time for array size " << sizes[i] << ": " << selectkth1time/500 << endl;

        cout << "selectkth2 total time for array size " << sizes[i] << ": " << selectkth2time << endl;
        cout << "selectkth2 average time for array size " << sizes[i] << ": " << selectkth2time/500 << endl;

        cout << "selectkth3 total time for array size " << sizes[i] << ": " << selectkth3time << endl;
        cout << "selectkth3 average time for array size " << sizes[i] << ": " << selectkth3time/500 << endl;

//        cout << "selectkth4 total time for array size " << sizes[i] << ": " << selectkth4time << endl;
//        cout << "selectkth4 average time for array size " << sizes[i] << ": " << selectkth3time/500 << endl;

        cout << endl;
    }


    return 0;
}

//This function prints the entire array out with a space inbetween values
void printarr(int* arr, int n)
{
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
}

//This function takes in two integers and swaps them
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

//Merge Sort function, calls itself recursively per algorithm
int* mergesort(int *a, int n)
{
    //Create new arrays for the split
    int* arr1 = new int[n/2];
    int* arr2 = new int[n-(n/2)];

    //Variable for half of the size of main array
    int half = n-(n/2);

    //Copy values over into new arrays
    for(int i = 0; i < n/2; i++)
        arr1[i] = a[i];

    for(int i = 0; i < half; i++)
        arr2[i] = a[i+(n/2)];

    //Base case
    if(n == 1)
        return a;

    //Otherwise, recursively call mergesort again with smaller arrays
    arr1 = mergesort(arr1, n/2);
    arr2 = mergesort(arr2, n-(n/2));

    //Merge arrays back together, sorted
    return merge(arr1, arr2, n/2, n-(n/2));
}

//Merge Sort helper function combines the arrays back together
int* merge(int *a, int *b, int n1, int n2)
{
    //Create new array, counter variables
    int* arr = new int[n1+n2];
    int count1 = 0;
    int count2 = 0;
    int arrcount = 0;

    //While the two feeder arrays are not empty...
    while(count1 < n1 && count2 < n2)
    {
        //Find the smallest value, add to main array, and decrement the array it came from
        if(a[count1] < b[count2])
        {
            arr[arrcount] = a[count1];
            count1++;
        }

        else
        {
            arr[arrcount] = b[count2];
            count2++;
        }

        arrcount++;
    }

    //If array a still has values left, fill them in
    while(count1 < n1)
    {
        arr[arrcount] = a[count1];
        arrcount++;
        count1++;
    }

    //If array b still has values left, fill them in
    while(count2 < n2)
    {
        arr[arrcount] = b[count2];
        arrcount++;
        count2++;
    }

    //Return the new, combined array
    return arr;
}

//Quicksort algorithm using recursive calls
int* quicksort(int *arr, int low, int high)
{
    if (low < high)
    {
        //Call the partition function, setting value to pi
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }

    return arr;
}

int* iquicksort(int *arr, int l, int h)
{
    // Create an auxiliary stack
    int stack[h - l + 1];

    // initialize top of stack
    int top = -1;

    // push initial values of l and h to stack
    stack[++top] = l;
    stack[++top] = h;

    // Keep popping from stack while is not empty
    while (top >= 0) {
        // Pop h and l
        h = stack[top--];
        l = stack[top--];

        // Set pivot element at its correct position
        // in sorted array
        int p = partition(arr, l, h);

        // If there are elements on left side of pivot,
        // then push left side to stack
        if (p - 1 > l) {
            stack[++top] = l;
            stack[++top] = p - 1;
        }

        // If there are elements on right side of pivot,
        // then push right side to stack
        if (p + 1 < h) {
            stack[++top] = p + 1;
            stack[++top] = h;
        }
    }

    return arr;
}

//Partition helper function for QuickSort
int partition(int *arr, int low, int high)
{
    //Assign pivot to v
    int v = arr[low];
    int j = low;

    //Sort the sub array based on pivot
    //Lower values below it, higher values above it
    for(int i = low + 1; i <= high; i++)
    {
        if(arr[i] < v)
        {
            j++;
            swap(&arr[i], &arr[j]);
        }
    }

    //Swap last values and return the pivot used
    int value = j;
    swap(&arr[low], &arr[value]);
    return value;

}

//Partition Helper function ver 2
int partition2(int *arr, int pivot, int low, int high)
{
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

//Partition helper function ver 3
int partition3(int *arr, int low, int high, int pivot)
{
    //Assign argument pivot as pivot
    int v = pivot;
    int j = low;

    //Sort the sub array based on pivot
    //Lower values below it, higher values above it
    for(int i = low + 1; i <= high; i++)
    {
        if(arr[i] < v)
        {
            j++;
            swap(&arr[i], &arr[j]);
        }
    }

    //Swap last values and return pivot
    int value = j;
    swap(&arr[low], &arr[value]);
    return value;

}

//Select 1 algorithm simply calls mergesort on the array and returns the kth element
int selectkth1(int* arr, int n, int k)
{
    int *sorted;

    sorted = mergesort(arr, n);

    return sorted[k];
}

//Select 2 algorithm uses the iterative quicksort algorithm, but returns the kth value
//when partition finds it
int selectkth2(int* arr, int k, int l, int h)
{
    // Create an auxiliary stack
    int stack[h - l + 1];

    // initialize top of stack
    int top = -1;

    // push initial values of l and h to stack
    stack[++top] = l;
    stack[++top] = h;

    // Keep popping from stack while is not empty
    while (top >= 0) {
        // Pop h and l
        h = stack[top--];
        l = stack[top--];

        // Set pivot element at its correct position
        // in sorted array
        int p = partition(arr, l, h);

        if(p == k)
            return arr[p];

        // If there are elements on left side of pivot,
        // then push left side to stack
        if (p - 1 > l && p > k) {
            stack[++top] = l;
            stack[++top] = p - 1;
        }

        // If there are elements on right side of pivot,
        // then push right side to stack
        if (p + 1 < h && p < k) {
            stack[++top] = p + 1;
            stack[++top] = h;
        }
    }
}

//Select 3 uses the recursive quicksort algorithm, but returns the kth value
//when partition finds it
int selectkth3(int* arr, int k, int low, int high)
{
    //Call partition
    int pi = partition(arr, low, high);

    //If pivot matches k, return value
    if(pi == k)
        return arr[pi];

    //If pivot is greater than k, recursively call selectkth3 on the lower half of the array
    else if(pi > k)
        return selectkth3(arr, k, low, pi - 1);

    //Otherwise, call selectkth3 on upper half of array
    else
        return selectkth3(arr, k, pi + 1, high);

}

int selectkth4(int* arr, int n, int k)
{
    //Set number of subarrays to split array into
    int r = 5;
    int sets = n/r;

    //If subarray size is greater than size of total array, sort the array and returnn the kth value
    if(n <= r)
    {
        int* sorted = mergesort(arr, n);
        return sorted[k];
    }

    //Create subarrays to split, and hold median values
    int arr2[sets][r];
    int arr3[sets];
    int index = 0;

    //Fill subarrays
    for(int i = 0; i < n; i++)
    {
        arr2[index][i % 5] = arr[i];

        if(i % 5 == 4)
            index++;
    }

    //Sort subarrays
    for(int i = 0; i < n/5; i++)
    {
        int* sorted = mergesort(arr2[i], 5);

        for(int j = 0; j < 5; j++)
            arr2[i][j] = sorted[j];
    }

    //Find median values and store into third subarray
    for(int i = 0; i < r; i++)
        arr3[i] = arr2[i][2];

    //Recursively call selectkth4 on subarray
    int v = selectkth4(arr3, sets, sets/2);

    int pivotposition = partition3(arr, 0, n, v);

    if(k == pivotposition)
        return arr[v];

    else if(k < pivotposition)
    {
        int left = n - (n - pivotposition);
        int s[left];
        for(int i = 0; i < left; i++)
            s[i] = arr[i];

        return selectkth4(s, left, k);
    }

    else
    {
        int s[n-pivotposition];
        for(int i = 0; i < (n - pivotposition); i++)
            s[i] = arr[i + pivotposition];

        return selectkth4(s, n - pivotposition, k);
    }

}
