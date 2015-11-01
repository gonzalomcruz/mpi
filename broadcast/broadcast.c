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
    int rank, message = 0;

    // Initialize MPI environment
    MPI_Init (&argc, &argv);

    // Get rank
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);

    if (rank == 0) message = 999;

    // Perform broadcast
    MPI_Bcast(&message, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf ("[%i] Message received \"%i\"\n",
             rank, message);

    // Finalize MPI environment
    MPI_Finalize();

    return 0;
}
