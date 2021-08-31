/*
 * CS3310 Project 1
 * Matrix Multiplication
 *
 * Dominic Guo
 *
 * Professor Gilbert Young
 *
 * Due October 29th, 2020
 *
*/

//Libraries
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <chrono>

using namespace std;

//Function prototypes
void classicMult(int** firstMatrix, int** secondMatrix, int** mult, int n);
void divideAndConquerMult(int** firstMatrix, int** secondMatrix, int** mult, int n);
void strassenMult(int** firstMatrix, int** secondMatrix, int** mult, int n);
void printMatrices(int** matrix, int n);
void clearMatrix(int** matrix, int n);
void addMatrix(int** firstMatrix, int** secondMatrix, int** result, int n);
void subMatrix(int** firstMatrix, int** secondMatrix, int** result, int n);

int main()
{
    //Declare/initialize variables
    int size = 2048;            //Maximum size of matrices
    int sets = 500;             //Number of data sets to test
    int runs = 20;              //Number of runs per data set
    double classictime;         //Time counter for classic mult
    double dnctime;             //Time counter for dnc mult
    double strassentime;        //Time counter for strassen mult
    int** firstMatrix;          //Double int pointer to hold matrix 1
    int** secondMatrix;         //Double int pointer to hold matrix 2
    int** mult;                 //Double int pointer to hold resultant matrix

    //Create dynamic arrays for multiplication and results
    firstMatrix = new int* [size];
    secondMatrix = new int* [size];
    mult = new int* [size];

    //Makes each dynamic array 2 dimensional
    for(int i = 0; i < size; i++)
    {
        firstMatrix[i] = new int[size];
        secondMatrix[i] = new int[size];
        mult[i] = new int[size];
    }

    //Test function main loop. Will start with two 4x4 matrices, and work up by
    //powers of 2 until it hits size
    for(int n = 4; n <= size; n = n * 2)
    {
        //Reset timer counters
        classictime = 0;
        dnctime = 0;
        strassentime = 0;

        //Test function inner loop. Will test each algorithm 500 times per value n
        for(int count = 0; count < sets; count++)
        {

            //Fills firstMatrix and secondMatrix with random values from 1-10
            //using nested for loops
            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < n; j++)
                {
                    firstMatrix[i][j] = rand() % 10 + 1;
                    secondMatrix[i][j] = rand() % 10 + 1;
                    mult[i][j] = 0;
                }

            }


            //Runs classic Mult on current matrices 20 times
            //Gets start and end time difference and adds to counter
            for(int i = 0; i < runs; i++)
            {
                auto start_time = chrono::high_resolution_clock::now();

                classicMult(firstMatrix, secondMatrix, mult, n);

                auto end_time = chrono::high_resolution_clock::now();

                classictime += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();

                clearMatrix(mult, n);
            }


            //////////////////////////////////////////////////////////////


            //Runs Divide and Conquer Mult on current matrices 20 times
            //Gets start and end time difference and adds to counter
            for(int i = 0; i < runs; i++)
            {
                auto start_time = chrono::high_resolution_clock::now();

                divideAndConquerMult(firstMatrix, secondMatrix, mult, n);

                auto end_time = chrono::high_resolution_clock::now();

                dnctime += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();

                clearMatrix(mult, n);
            }



            /////////////////////////////////////////////////////////////


            //Runs Strassen Mult on current matrices 20 times
            //Gets start and end time difference and adds to counter
            for(int i = 0; i < runs; i++)
            {
                auto start_time = chrono::high_resolution_clock::now();

                strassenMult(firstMatrix, secondMatrix, mult, n);

                auto end_time = chrono::high_resolution_clock::now();

                strassentime += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();

                clearMatrix(mult, n);
            }


        }

        //Outputs resultant times to console
        cout << "n = " << n << endl;
        cout << "Classic Multiplication" << endl;
        cout << "Total time in seconds: " << classictime/1000000 << endl;
        cout << "Average time in seconds: " << classictime/500000000 << endl << endl;

        cout << "Divide And Conquer Multiplication" << endl;
        cout << "Total time in seconds: " << dnctime/1000000 << endl;
        cout << "Average time in seconds: " << dnctime/500000000 << endl << endl;

        cout << "Strassen Multiplication" << endl;
        cout << "Total time in seconds: " << strassentime/1000000 << endl;
        cout << "Average time in seconds: " << strassentime/500000000 << endl << endl << endl;
    }

    //Delete dynamic arrays
    delete[] firstMatrix;
    delete[] secondMatrix;
    delete[] mult;

    return 0;
}

//Outputs the matrix to the console
void printMatrices(int** matrix, int n)
{
    //Nested for loop to iterate through all rows and cols of matrices
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            //Outputs current value to console
            cout << setw(5) << matrix[i][j] << " ";

        cout << endl;
    }

    cout << endl;
}

//Sets all values in matrix to 0
void clearMatrix(int** matrix, int n)
{
    //Nested for loop to iterate through all rows and cols of matrices
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            //Set every value to 0
            matrix[i][j] = 0;
}

//Adds one matrix to another, sets the result to result
void addMatrix(int** firstMatrix, int** secondMatrix, int** result, int n)
{
    //Nested for loop to iterate through all rows and cols of matrices
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            //Adds value in firstMatrix and secondMatrix, assigns to result
            result[i][j] = firstMatrix[i][j] + secondMatrix[i][j];
}

//Subtracts one matrix from another, sets the result to result
void subMatrix(int** firstMatrix, int** secondMatrix, int** result, int n)
{
    //Nested for loop to iterate through all rows and cols of matrices
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            //Subtracts value in secondMatrix from firstMatrix, assigns to result
            result[i][j] = firstMatrix[i][j] - secondMatrix[i][j];
}

//Classic matrix multiplication algorithm
//mult must start with 0
void classicMult(int** firstMatrix, int** secondMatrix, int** mult, int n)
{
    int i, j, k;

    // Multiplying matrix using 3 for-loop algorithm, setting result to mult
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            for(k=0; k < n; k++)
                mult[i][j] += firstMatrix[i][k] * secondMatrix[k][j];

}

//Divide and Conquer matrix multiplication algorithm
void divideAndConquerMult(int** firstMatrix, int** secondMatrix, int** mult, int n)
{
    //Set half to n/2 (submatrix size)
    int half = n/2;

    //Declare dynamic arrays
    int** A11 = new int* [half];
    int** A12 = new int* [half];
    int** A21 = new int* [half];
    int** A22 = new int* [half];
    int** B11 = new int* [half];
    int** B12 = new int* [half];
    int** B21 = new int* [half];
    int** B22 = new int* [half];
    int** C11 = new int* [half];
    int** C12 = new int* [half];
    int** C21 = new int* [half];
    int** C22 = new int* [half];
    int** temp1 = new int* [half];
    int** temp2 = new int* [half];

    //Make all arrays 2 dimensional
    for(int i = 0; i < half; i++)
    {
        A11[i] = new int [half];
        A12[i] = new int [half];
        A21[i] = new int [half];
        A22[i] = new int [half];
        B11[i] = new int [half];
        B12[i] = new int [half];
        B21[i] = new int [half];
        B22[i] = new int [half];
        C11[i] = new int [half];
        C12[i] = new int [half];
        C21[i] = new int [half];
        C22[i] = new int [half];
        temp1[i] = new int [half];
        temp2[i] = new int [half];
    }

    //Split array into A11, A12, etc
    //Set temp arrays to 0
    for(int i = 0; i < half; i++)
        for(int j = 0; j < half; j++)
        {
            A11[i][j] = firstMatrix[i][j];
            A12[i][j] = firstMatrix[i][j+half];
            A21[i][j] = firstMatrix[i+half][j];
            A22[i][j] = firstMatrix[i+half][j+half];
            B11[i][j] = secondMatrix[i][j];
            B12[i][j] = secondMatrix[i][j+half];
            B21[i][j] = secondMatrix[i+half][j];
            B22[i][j] = secondMatrix[i+half][j+half];
            temp1[i][j] = 0;
            temp2[i][j] = 0;
        }

    //If n is 4 (submatrices are 2x2), split and calculate using standard
    //matrix multiplication
    if(n == 4)
    {
        classicMult(A11, B11, temp1, 2);
        classicMult(A12, B21, temp2, 2);
        addMatrix(temp1, temp2, C11, 2);

        clearMatrix(temp1, 2);
        clearMatrix(temp2, 2);

        classicMult(A11, B12, temp1, 2);
        classicMult(A12, B22, temp2, 2);
        addMatrix(temp1, temp2, C12, 2);

        clearMatrix(temp1, 2);
        clearMatrix(temp2, 2);

        classicMult(A21, B11, temp1, 2);
        classicMult(A22, B21, temp2, 2);
        addMatrix(temp1, temp2, C21, 2);

        clearMatrix(temp1, 2);
        clearMatrix(temp2, 2);

        classicMult(A21, B12, temp1, 2);
        classicMult(A22, B22, temp2, 2);
        addMatrix(temp1, temp2, C22, 2);
    }

    //If matrices are larger, calculate using dnc algo
    //using recursive calls
    else
    {
        //Calculate C11
        divideAndConquerMult(A11, B11, temp1, half);
        divideAndConquerMult(A12, B21, temp2, half);
        addMatrix(temp1, temp2, C11, half);

        //Clear matrices
        clearMatrix(temp1, half);
        clearMatrix(temp2, half);

        //Calculate C12
        divideAndConquerMult(A11, B12, temp1, half);
        divideAndConquerMult(A12, B22, temp2, half);
        addMatrix(temp1, temp2, C12, half);

        //Clear matrices
        clearMatrix(temp1, half);
        clearMatrix(temp2, half);

        //Calculate C21
        divideAndConquerMult(A21, B11, temp1, half);
        divideAndConquerMult(A22, B21, temp2, half);
        addMatrix(temp1, temp2, C21, half);

        //Clear matrices
        clearMatrix(temp1, half);
        clearMatrix(temp2, half);

        //Calculate C22
        divideAndConquerMult(A21, B12, temp1, half);
        divideAndConquerMult(A22, B22, temp2, half);
        addMatrix(temp1, temp2, C22, half);
    }

    //Consolidate C11, C12, C21, C22 into mult
    for(int i = 0; i < half; i++)
        for(int j = 0; j < half; j++)
        {
            mult[i][j] = C11[i][j];
            mult[i][j+half] = C12[i][j];
            mult[i+half][j] = C21[i][j];
            mult[i+half][j+half] = C22[i][j];
        }

    //Delete dynamic arrays
    for(int i = 0; i < half; i++)
    {
        delete A11[i];
        delete A12[i];
        delete A21[i];
        delete A22[i];
        delete B11[i];
        delete B12[i];
        delete B21[i];
        delete B22[i];
        delete C11[i];
        delete C12[i];
        delete C21[i];
        delete C22[i];
        delete temp1[i];
        delete temp2[i];
    }

    delete[] A11;
    delete[] A12;
    delete[] A21;
    delete[] A22;
    delete[] B11;
    delete[] B12;
    delete[] B21;
    delete[] B22;
    delete[] C11;
    delete[] C12;
    delete[] C21;
    delete[] C22;
    delete[] temp1;
    delete[] temp2;
}

void strassenMult(int** firstMatrix, int** secondMatrix, int** mult, int n)
{
    //Set half to n/2 (submatrix size)
    int half = n/2;

    //Declare dynamic arrays
    int** A11 = new int* [half];
    int** A12 = new int* [half];
    int** A21 = new int* [half];
    int** A22 = new int* [half];
    int** B11 = new int* [half];
    int** B12 = new int* [half];
    int** B21 = new int* [half];
    int** B22 = new int* [half];
    int** C11 = new int* [half];
    int** C12 = new int* [half];
    int** C21 = new int* [half];
    int** C22 = new int* [half];
    int** temp1 = new int* [half];
    int** temp2 = new int* [half];
    int** P = new int* [half];
    int** Q = new int* [half];
    int** R = new int* [half];
    int** S = new int* [half];
    int** T = new int* [half];
    int** U = new int* [half];
    int** V = new int* [half];

    //Make all the arrays 2 dimensional
    for(int i = 0; i < half; i++)
    {
        A11[i] = new int [half];
        A12[i] = new int [half];
        A21[i] = new int [half];
        A22[i] = new int [half];
        B11[i] = new int [half];
        B12[i] = new int [half];
        B21[i] = new int [half];
        B22[i] = new int [half];
        C11[i] = new int [half];
        C12[i] = new int [half];
        C21[i] = new int [half];
        C22[i] = new int [half];
        temp1[i] = new int [half];
        temp2[i] = new int [half];
        P[i] = new int [half];
        Q[i] = new int [half];
        R[i] = new int [half];
        S[i] = new int [half];
        T[i] = new int [half];
        U[i] = new int [half];
        V[i] = new int [half];
    }

    //Split array into A11, A12, etc
    //Set other arrays to 0
    for(int i = 0; i < half; i++)
        for(int j = 0; j < half; j++)
        {
            A11[i][j] = firstMatrix[i][j];
            A12[i][j] = firstMatrix[i][j+half];
            A21[i][j] = firstMatrix[i+half][j];
            A22[i][j] = firstMatrix[i+half][j+half];
            B11[i][j] = secondMatrix[i][j];
            B12[i][j] = secondMatrix[i][j+half];
            B21[i][j] = secondMatrix[i+half][j];
            B22[i][j] = secondMatrix[i+half][j+half];
            temp1[i][j] = 0;
            temp2[i][j] = 0;
            P[i][j] = 0;
            Q[i][j] = 0;
            R[i][j] = 0;
            S[i][j] = 0;
            T[i][j] = 0;
            U[i][j] = 0;
            V[i][j] = 0;

        }

    //If n is 4 (submatrices are 2x2), split and calculate using standard
    //matrix multiplication
    if(n == 4)
    {
        //Calcuate C11
        classicMult(A11, B11, temp1, 2);
        classicMult(A12, B21, temp2, 2);
        addMatrix(temp1, temp2, C11, 2);

        //Clear temp matrices
        clearMatrix(temp1, 2);
        clearMatrix(temp2, 2);

        //Calculate C12
        classicMult(A11, B12, temp1, 2);
        classicMult(A12, B22, temp2, 2);
        addMatrix(temp1, temp2, C12, 2);

        //Clear temp matrices
        clearMatrix(temp1, 2);
        clearMatrix(temp2, 2);

        //Calculate C21
        classicMult(A21, B11, temp1, 2);
        classicMult(A22, B21, temp2, 2);
        addMatrix(temp1, temp2, C21, 2);

        //Clear matrices
        clearMatrix(temp1, 2);
        clearMatrix(temp2, 2);

        //Calculate C22
        classicMult(A21, B12, temp1, 2);
        classicMult(A22, B22, temp2, 2);
        addMatrix(temp1, temp2, C22, 2);
    }

    //If the matrices are larger, calculate using Strassen algo
    //using recursive calls
    else
    {
        //Calculate P
        addMatrix(A11, A22, temp1, half);
        addMatrix(B11, B22, temp2, half);
        strassenMult(temp1, temp2, P, half);

        //Clear matrices
        clearMatrix(temp1, half);
        clearMatrix(temp2, half);

        //Calculate Q
        addMatrix(A21, A22, temp1, half);
        strassenMult(temp1, B11, Q, half);

        //Clear matrix
        clearMatrix(temp1, half);

        //Calculate R
        subMatrix(B12, B22, temp1, half);
        strassenMult(A11, temp1, R, half);

        //Clear matrix
        clearMatrix(temp1, half);

        //Calculate S
        subMatrix(B21, B11, temp1, half);
        strassenMult(A22, temp1, S, half);

        //Clear matrix
        clearMatrix(temp1, half);

        //Calculate T
        addMatrix(A11, A12, temp1, half);
        strassenMult(temp1, B22, T, half);

        //Clear matrix
        clearMatrix(temp1, half);

        //Calculate U
        subMatrix(A21, A11, temp1, half);
        addMatrix(B11, B12, temp2, half);
        strassenMult(temp1, temp2, U, half);

        //Clear matrices
        clearMatrix(temp1, half);
        clearMatrix(temp2, half);

        //Calculate V
        subMatrix(A12, A22, temp1, half);
        addMatrix(B21, B22, temp2, half);
        strassenMult(temp1, temp2, V, half);

        //Clear matrices
        clearMatrix(temp1, half);
        clearMatrix(temp2, half);

        //Calculate C11
        addMatrix(P, S, temp1, half);
        subMatrix(temp1, T, temp2, half);
        addMatrix(temp2, V, C11, half);

        //Clear matrices
        clearMatrix(temp1, half);
        clearMatrix(temp2, half);

        //Calculate C12
        addMatrix(R, T, C12, half);

        //Calculate C21
        addMatrix(Q, S, C21, half);

        //Calculate C22
        addMatrix(P, R, temp1, half);
        subMatrix(temp1, Q, temp2, half);
        addMatrix(temp2, U, C22, half);

    }

    //Consolidate C11, C12, C21, C22 into mult
    for(int i = 0; i < half; i++)
        for(int j = 0; j < half; j++)
        {
            mult[i][j] = C11[i][j];
            mult[i][j+half] = C12[i][j];
            mult[i+half][j] = C21[i][j];
            mult[i+half][j+half] = C22[i][j];
        }

    //Delete all dynamic arrays
    for(int i = 0; i < half; i++)
    {
        delete A11[i];
        delete A12[i];
        delete A21[i];
        delete A22[i];
        delete B11[i];
        delete B12[i];
        delete B21[i];
        delete B22[i];
        delete C11[i];
        delete C12[i];
        delete C21[i];
        delete C22[i];
        delete temp1[i];
        delete temp2[i];
        delete P[i];
        delete Q[i];
        delete R[i];
        delete S[i];
        delete T[i];
        delete U[i];
        delete V[i];
    }

    delete[] A11;
    delete[] A12;
    delete[] A21;
    delete[] A22;
    delete[] B11;
    delete[] B12;
    delete[] B21;
    delete[] B22;
    delete[] C11;
    delete[] C12;
    delete[] C21;
    delete[] C22;
    delete[] temp1;
    delete[] temp2;
    delete[] P;
    delete[] Q;
    delete[] R;
    delete[] S;
    delete[] T;
    delete[] U;
    delete[] V;
}
