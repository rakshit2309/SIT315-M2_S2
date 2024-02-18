
#include <iostream>
#include <thread>
#include <chrono>
using namespace std::chrono;
using namespace std;

const int NUM_THREADS = 4; // Number of threads to use
const int SIZE = 100000000; // Size of arrays


void randomVector(int vector[], int size) {
    for (int i = 0; i < size; i++) {
        vector[i] = rand() % 100; 
    }
}

// Function to add corresponding elements of two arrays and store the result in a third array
void addParts(int v1[], int v2[], int v3[], int start, int end) {
    // Loop through the specified range of indices
    for (int i = start; i < end; i++) {
        // Add the corresponding elements of v1 and v2, and store the result in v3
        v3[i] = v1[i] + v2[i];
    }
}

// Main function
int main() {
    srand(time(0)); 

    // Declare arrays v1, v2, and v3 and Allocate memory for array v1 v2 v3
    int* v1 = new int[SIZE]; 
    int* v2 = new int[SIZE]; 
    int* v3 = new int[SIZE]; 

    
    randomVector(v1, SIZE);
    randomVector(v2, SIZE);

    thread threads[NUM_THREADS];

    // Start measuring the execution time
    auto start = chrono::high_resolution_clock::now();

    // Calculate the number of elements per thread
    int partSize = SIZE / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        // Calculate the start index for the current thread's part
        int startIdx = i * partSize;

        // Calculate the end index for the current thread's part
        int endIdx;
        // If this is the last thread, set the end index to the size of the arrays
        if (i == NUM_THREADS - 1) {
            endIdx = SIZE;
        } else { // Otherwise, calculate the end index based on the chunk size
            endIdx = startIdx + partSize;
        }

        // Create a thread for the current chunk of data and execute the addParts function
        threads[i] = thread(addParts, v1, v2, v3, startIdx, endIdx);
    }

    // Wait for all threads to finish executing
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }

    // Stop measuring the execution time
    auto stop = chrono::high_resolution_clock::now();

    // Calculate the duration of the execution
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;

    // Free the memory allocated for arrays v1, v2, and v3
    delete[] v1;
    delete[] v2;
    delete[] v3;

    
    return 0;
}
