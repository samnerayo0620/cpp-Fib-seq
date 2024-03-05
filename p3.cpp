// Samuel Nerayo
// c3500 - HW3
// Fib-Seq

#include <cstdlib>
#include <pthread.h>
#include <iostream>

using namespace std;
//Fib array global declaration
int *fib_seqs;

//Calculating Fib seq using thread function
void* fibonacci(void* arg) {
    //Convert arg into int
    int n = *((int*)arg);
    //dynamic allocation memory for fib_array
    int *fibArray = new int[n];

    // checking n > 0 , then set the fibArray at index 0 = 0
    if (n > 0) {
        fibArray[0] = 0;
    }

    // checking n > 1 , then set the fibArray at index 1 = 1
    if (n > 1) {
        fibArray[1] = 1;
    }
    // Calculating fib seq using fib formula and store it
    for (int i = 2; i < n; i++) {
        fibArray[i] = fibArray[i - 1] + fibArray[i - 2];
    }
    //Free memory
    return (void*) fibArray;
}

int main(int argc, char** argv) {
    //Check if arg number are provided correctly
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <num>" << endl;
        exit(0);
    }

    //check user input
    int num = atoi(argv[1]);

    if (num <= 0) {
        cout << "Error: input must be a positive number" << endl;
        exit(0);
    }

    // Dynamically allocate for fib array in the global
    fib_seqs = new int[num];

    //creating pthread
    pthread_t tid;
    int rc = pthread_create(&tid, NULL, fibonacci, (void*)&num);
    if (rc) {
        cout << "Error: thread can't be created: " << rc << endl;
        exit(0);
    }

    //wait  till thread complete
    void* res;
    rc = pthread_join(tid, &res);
    if (rc) {
        cout << "Error: thread unable to join: " << rc << endl;
        exit(-1);
    }

    // copy result
    int* fibArray = (int*) res;
    for (int i = 0; i < num; i++) {
        fib_seqs[i] = fibArray[i];
    }

    //delete fibArray
    delete[] fibArray;

    //Print out the fib sequence
    cout << "Fibonacci Series are: ";
    for (int i = 0; i < num; i++) {
        cout << fib_seqs[i] << " ";
    }
    cout << endl;

   // Free the fib_seqs
    delete[] fib_seqs;
    return 0;
}
