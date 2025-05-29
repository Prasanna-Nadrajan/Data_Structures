#!/bin/python3

import math
import os
import random
import re
import sys

def insertionSort1(n, arr):
    # Write your code here
    for i in range(1,n):
        key=arr[i]
        temp=i-1
        while(temp>=0 and key<arr[temp]):
            arr[temp+1]=arr[temp]
            print(*arr)
            temp-=1
        arr[temp+1]=key
    print(*arr)

if __name__ == '__main__':
    n = int(input().strip())

    arr = list(map(int, input().rstrip().split()))

    insertionSort1(n, arr)
