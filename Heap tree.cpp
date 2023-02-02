/*
Insertion and Deletion in Heaps
    Difficulty Level : Easy
                           Last Updated : 01 Nov,
                       2022 Read
                           Discuss

                               Deletion in Heap

                                   Given a Binary Heap and an element present in the given Heap.The task is to delete an element from this Heap.

                       The standard deletion operation on Heap is to delete the element present at the root node of the Heap.That is if it is a Max Heap,
                       the standard deletion operation will delete the maximum element and if it is a Min heap,
                       it will delete the minimum element.

                       Process of Deletion : Since deleting an element at any intermediary position in the heap can be costly,
                       so we can simply replace the element to be deleted by the last element and delete the last element of the Heap.

                           Replace the root or
                           element to be deleted by the last element.Delete the last element from the Heap.Since,
                       the last element is now placed at the position of the root node.So,
                       it may not follow the heap property.Therefore,
                       heapify the last node placed at the position of root.Illustration :

    Suppose the Heap is a Max -
                           Heap as : 10 /
                               5 3 /
                               2 4

                               The element to be deleted is root,
                       i.e.10.

                       Process : The last element is 4.

                                 Step 1 : Replace the last element with root,
                       and delete it.4 /
                           5 3 /
                           2

                           Step 2 : Heapify root.Final Heap : 5 /
                           4 3 /
                           2 Implementation :
*/
// C++ program for implement deletion in Heaps

#include <iostream>

    using namespace std;

// To heapify a subtree rooted with node i which is
// an index of arr[] and n is the size of heap
void heapify(int arr[], int n, int i)
{
    int largest = i;   // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Function to delete the root from Heap
void deleteRoot(int arr[], int &n)
{
    // Get the last element
    int lastElement = arr[n - 1];

    // Replace root with last element
    arr[0] = lastElement;

    // Decrease size of heap by 1
    n = n - 1;

    // heapify the root node
    heapify(arr, n, 0);
}

/* A utility function to print array of size n */
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}

// Driver Code
int main()
{
    // Array representation of Max-Heap
    //     10
    //    /  \
    //   5    3
    //  / \
    // 2   4
    int arr[] = {10, 5, 3, 2, 4};

    int n = sizeof(arr) / sizeof(arr[0]);

    deleteRoot(arr, n);

    printArray(arr, n);

    return 0;
}

/*
Time complexity: O(logn) where n is no of elements in the heap

Auxiliary Space: O(n)
 */