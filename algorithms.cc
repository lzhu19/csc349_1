#include "algorithms.h"
#include <limits>
#include <algorithm> // For std::min_element, std::max_element
#include <vector>    // For std::vector

/**
 * SELECTION SORT
 * Logic: Find the smallest, move it to the new list, repeat.
 */
std::vector<int> SelectionSort(std::vector<int> A) {
    std::vector<int> B;

    // init iterator for min value
    std::vector<int>::iterator smallest;

    while (!A.empty()) {
        /* C++ HINT: 
           1. Use std::min_element(A.begin(), A.end()) to find the "iterator" to the minimum.
           2. To get the actual integer value from an iterator 'it', use *it.
           3. To remove an element by its iterator, use A.erase(it).
        */
        
        // TODO: Find min, push to B, erase from A

        smallest = std::min_element(A.begin(), A.end()); // create iterator
        B.push_back(*smallest); // put element at back of B
        A.erase(smallest); // erase element from A at smallest

    }
    return B;
}

/**
 * MERGE (Helper for MergeSort)
 * Logic: Combine two already-sorted lists into one.
 */
std::vector<int> Merge(std::vector<int> left, std::vector<int> right) {
    std::vector<int> result;
    // C++ HINT: Use two size_t variables (i and j) to track your position in 
    // the left and right vectors.
    
    // TODO: Compare left[i] and right[j], push the smaller one to 'result'
    // Don't forget to push any remaining elements after one side is empty!

    // edge case, empty vector inputs
    if (right.empty()) return left;
    if (left.empty()) return right;

    int i=0, j=0; // two pointer
    while (i < left.size() && j < right.size()) { // while there are contents in both vectors
        
        if (left.at(i) <= right.at(j)) { // compare minimums and add whichever is smaller to result
            result.push_back(left.at(i));
            i++;
        } else {
            result.push_back(right.at(j));
            j++;
        }
    }

    while (i < left.size()) { // remaining stuff in left vector
        result.push_back(left.at(i));
        i++;
    }

    while (j < right.size()) { // remaining stuff in right vector
        result.push_back(right.at(j));
        j++;
    }

    return result;
}

/**
 * MERGE SORT
 * Logic: Split in half, recurse, then merge.
 */
std::vector<int> MergeSort(std::vector<int> A) {
    // Base Case: A list of 1 (or 0) is already sorted
    if (A.size() <= 1) return A;

    /* C++ HINT:
       To "slice" a vector in C++, you can use this constructor:
       std::vector<int> sub_vector(start_iterator, end_iterator);
       Example: std::vector<int> left(A.begin(), A.begin() + mid);
    */

    // TODO: 
    // 1. Find the middle index
    // 2. Create 'left' and 'right' vectors using the slice hint above
    // 3. Recursive calls: MergeSort(left) and MergeSort(right)
    // 4. Return Merge() of the two sorted results

    int mid = A.size() / 2; // middle index

    // create left and right subvectors
    std::vector<int> left(A.begin(), A.begin()+mid);
    std::vector<int> right(A.begin() + mid, A.end());

    // recursive call on both left and right subvectors
    std::vector<int> sorted_left = MergeSort(left);
    std::vector<int> sorted_right = MergeSort(right);

    // merge the left and right subvectors and return result
    return Merge(sorted_left, sorted_right);
}

/**
 * COUNTING SORT
 * Logic: Count how many times each number appears.
 */
std::vector<int> CountingSort(std::vector<int> A) {
    if (A.empty()) return {};

    /* C++ HINT:
       1. To handle negative numbers, find the min and max values first.
       2. Your range is (max - min + 1).
       3. When counting, the index for value 'x' in your frequency vector 
          should be (x - min_value).
    */

    // TODO:
    // 1. Find min and max values in A
    // 2. Create a frequency vector 'T' initialized to zeros: std::vector<int> T(range, 0);
    // 3. Fill B by iterating through T and adding the original values back in order

    // minimum and maximum values
    int min_val = *std::min_element(A.begin(), A.end());
    int max_val = *std::max_element(A.begin(), A.end());
    int range = max_val - min_val + 1;

    std::vector<int> T(range, 0); // initialize frequency array of zeros
    std::vector<int> B; // empty output sequence

    // fill frequency array
    for (int i=0; i<A.size(); i++) { // for every value in A

        // the value A.at(i) is related to the index the frequency will be stored in T
        int val = A.at(i); // value at index i in A
        int newI = val - min_val; // translate the value to an index for T
        T.at(newI) = T.at(newI) + 1; // increment the value at newI in T by 1
    }

    // once frequency array is finished, sort with frequency array
    for (int i = 0; i < range; i++) { 
        for (int j=1; j<=T.at(i); j++) {
            B.push_back(i);
        }
    }

    return B; 
}