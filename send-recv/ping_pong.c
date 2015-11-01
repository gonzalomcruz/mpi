// The MIT License (MIT)

// Copyright (c) 2015 Gonzalo Martín

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, step_count = 0;

    const int MAX_STEPS = 100;

    // Initialize MPI environment
    MPI_Init (&argc, &argv);

    // Get rank, size and processor name
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    MPI_Comm_size (MPI_COMM_WORLD, &size);

    if (size != 2) {
        fprintf(stderr, "Number of processes must be 2 in order to run this example\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    while (step_count < MAX_STEPS) {
        if (rank % 2 == 0) {
            step_count ++;
            MPI_Send(&step_count, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            printf("[%i] Sent and incremented step count %i to process 1\n",
                    rank, step_count);
        } else if (rank % 2 == 1) {
            MPI_Recv(&step_count, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("[%i] Received step count %i from process 0\n",
                    rank, step_count);
        }
    }

    // Finalize MPI environment
    MPI_Finalize();

    return 0;
}
