#!/usr/bin/env python
# -*- coding: utf-8 -*-

# The MIT License (MIT)

# Copyright (c) 2015 Gonzalo Martín

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
import sys

# Get rank, size and processor name
rank = MPI.COMM_WORLD.Get_rank()
size = MPI.COMM_WORLD.Get_size()
processor_name = MPI.Get_processor_name()

if size < 2:
    print "Number of processes must be larger than 1 in order to run this example"
    MPI.COMM_WORLD.Abort(1)

if rank == 0:
    token = 1
    MPI.COMM_WORLD.send(token, dest=rank+1)
    token = 0
    print "[%d] Token sent to process %d" % (rank, rank+1)
    token = MPI.COMM_WORLD.recv(source=size-1)
    print "[%d] Token received from process %d" % (rank, size-1)
else:
    token = MPI.COMM_WORLD.recv(source=rank-1)
    print "[%d] Token received from process %d" % (rank, rank-1)
    dest = 0 if rank == size - 1 else rank + 1
    MPI.COMM_WORLD.send(token, dest=dest)
    token = 0
    print "[%d] Token sent to process %d" % (rank, dest)
