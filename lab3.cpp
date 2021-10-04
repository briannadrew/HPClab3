// Name: lab3.cpp
// Author: Brianna Drew
// ID: #0622446
// Date Created: 2021-09-27
// Last Modified: 2021-10-04

// libraries
#include <iostream>
#include <cmath>
#include <omp.h>
using namespace std;

// main function
int main()
{
  // define variables
  const int size = 256;
  double* sinTable = new double[256];
  double sum = 0.0, isum = 0.0;

  // parallelized
  #pragma omp parallel private(isum)
  {
    int n;
    #pragma omp for
    for(n=0; n<size; n++)
    {
      // calculate and insert element into array
      sinTable[n] = std::sin(2 * M_PI * n / size);
      // double current element in array
      sinTable[n] = sinTable[n] * 2;
      // update the sum for each individual thread
      isum = isum + sinTable[n];
    }
    #pragma omp critical
    {
      // only one thread at a time may add their sum to the total sum
      sum += isum;
    }
  }

  // print sum and exit
  cout<<"Sum: "<<sum<<endl;
  cout<<"Jobs done";
  return 0;
}
