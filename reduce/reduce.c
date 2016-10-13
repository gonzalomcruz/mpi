// The MIT License (MIT)
//
// Copyright (c) 2016 Denis Aoki
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

#define ARRAY_SIZE 10
const int values[10] = {9, 3, 2, 5, 20, 4, 6, 1, 8, 7};

// Perform MPI_Reduce with MPI_SUM operation
void reduce_sum(int rank, int start, int end){
	int i, sum_local = 0, sum;
	for(i = start; i < end; i++){
		sum_local += values[i];
	}
	MPI_Reduce(&sum_local, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if(rank == 0){
		printf("Using MPI_SUM: Value: %d\n", sum);
	}
}

// Perform MPI_Reduce with MPI_MAX operation
void reduce_max(int rank, int start, int end) {
	int i, max_local = 0, max;
	for(i = start; i < end; i++){
		if(values[i] > max_local)
			max_local = values[i];
	}
	MPI_Reduce(&max_local, &max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	if(rank == 0){
		printf("Using MPI_MAX: Value: %d\n", max);
	}
}

// Perfom MPI_Reduce with MPI_MIN operation
void reduce_min(int rank, int start, int end) {
	int i, min_local = values[start], min;
	for(i = start; i < end; i++){
		if(values[i] < min_local){
			min_local = values[i];
		}
	}
	MPI_Reduce(&min_local, &min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
	if(rank == 0){
		printf("Using MPI_MIN: Value: %d\n", min);
	}
}

// Print the array
void print_array() {
	int i;
	printf("Array: ");
	for(i = 0; i < ARRAY_SIZE; i++){
		printf("%d ", values[i]);
	}
	printf("\n");
}

int main(int argc, char* argv[]) {
	int rank, size;
	int start, end, sizeBlock;

	// Initialize MPI environment
	MPI_Init (&argc, &argv);
   	// Get rank
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);
	// Get num process
	MPI_Comm_size (MPI_COMM_WORLD, &size);

	if(size > 10){
		fprintf(stderr, "Number of processes must be <= 10 in order to run this example\n");
		MPI_Abort(MPI_COMM_WORLD, 1);
	}

	// Number of values that each process will calculate
	sizeBlock = ARRAY_SIZE/size;
	// Offset for begin and end of calculation in the array
   	start = rank * sizeBlock;
   	end = start + sizeBlock;
	/*   if is the last process, the end offset must be the end of ARRAY */
  	if(rank == size - 1) {
		end = ARRAY_SIZE;
	}

	if(rank == 0){
		print_array();
	}

	reduce_sum(rank, start, end);
	reduce_max(rank, start, end);
	reduce_min(rank, start, end);

	// Finalize MPI environment
	MPI_Finalize();
	return 0;
}

