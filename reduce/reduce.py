#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# The MIT License (MIT)

# Copyright (c) 2016 Denis Aoki

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

from mpi4py import MPI
import numpy

ARRAY_SIZE = 10
values = [9, 3, 2, 5, 20, 4, 6, 1, 8, 7]
comm = MPI.COMM_WORLD

# Perform reduce with MPI.SUM operation
def reduce_sum(rank, start, end):
    sum_local = numpy.array(0, 'i')
    sum = numpy.array(0, 'i')
    for i in range(start, end):
        sum_local += values[i]
    comm.Reduce([sum_local, MPI.INT], [sum, MPI.INT], op=MPI.SUM, root=0)
    if rank == 0:
        print "Using MPI.SUM: Value: %d" % sum

# Perform reduce with MPI.MAX operation
def reduce_max(rank, start, end):
    max_local = numpy.array(0, 'i')
    max = numpy.array(0, 'i')
    for i in range(start, end):
        if values[i] > max_local:
            max_local = numpy.array(values[i], 'i')
    comm.Reduce([max_local, MPI.INT], [max, MPI.INT], op=MPI.MAX, root=0)
    if rank == 0:
        print "Using MPI.MAX: value: {}".format(max)

# Perform reduce with MPI.MIN operation
def reduce_min(rank, start, end):
    min_local = numpy.array(values[start], 'i')
    min = numpy.array(0, 'i')
    for i in range(start, end):
        if values[i] < min_local:
            min_local = numpy.array(values[i], 'i')
    comm.Reduce([min_local, MPI.INT], [min, MPI.INT], op=MPI.MIN, root=0)
    if rank == 0:
        print "Using MPI.MIN: value: {}".format(min)


# Get rank, size and processor name
rank = MPI.COMM_WORLD.Get_rank()
size = MPI.COMM_WORLD.Get_size()

# Number of values that each process will calculate
sizeBlock = ARRAY_SIZE/size
# Offset for begin and end of calculation in the array
start = rank * sizeBlock
end = start + sizeBlock
# if is the last process, the end offset must be the end of ARRAY */
if rank == size - 1:
    end = ARRAY_SIZE

if rank == 0:
    print "Array: {}".format(values)

reduce_sum(rank, start, end)
reduce_max(rank, start, end)
reduce_min(rank, start, end)
