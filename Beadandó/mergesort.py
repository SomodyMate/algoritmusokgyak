from multiprocessing import Process, Pipe
import time, random, sys


def mergesort(listfromarray):
    if len(listfromarray) <= 1:
        return listfromarray
    ind = len(listfromarray)//2
    return merge(mergesort(listfromarray[:ind]), mergesort(listfromarray[ind:]))


def mergeSortParallel(listfromarray, conn, processNumber):
    if processNumber <= 0 or len(listfromarray) <= 1:
        conn.send(mergesort(listfromarray))
        conn.close()
        return
    ind = len(listfromarray)//2
    pLeft, cLeft = Pipe()
    leftProc = Process(target=mergeSortParallel, args=(listfromarray[:ind], cLeft, processNumber - 1))
    pRight, cRight = Pipe()
    rightProc = Process(target=mergeSortParallel, args=(listfromarray[ind:], cRight, processNumber - 1))
    leftProc.start()
    rightProc.start()
    conn.send(merge(pLeft.recv(), pRight.recv()))
    conn.close()
    leftProc.join()
    rightProc.join()

def merge(left, right):
    temp = []
    left_index = right_index = 0
    while left_index < len(left) and right_index < len(right):
        if left[left_index] <= right[right_index]:
            temp.append(left[left_index])
            left_index += 1
        else:
            temp.append(right[right_index])
            right_index += 1
    if left_index == len(left):
        temp.extend(right[right_index:])
    else:
        temp.extend(left[left_index:])
    return temp

def main():
    N = 10000
    while N<100000:
        print('size:',N)
        array = [random.random() for x in range(N)]
        listfromarray = list(array)
        start = time.time()
        listfromarray = mergesort(listfromarray)
        time_elapsed = time.time() - start
        print('mergesort: \t\t\t\t\t%f seconds' % (time_elapsed))
        listfromarray = list(array)
        start = time.time()
        pconn, cconn = Pipe()
        process = Process(target=mergeSortParallel, args=(listfromarray, cconn, 3))
        process.start()
        listfromarray = pconn.recv()
        process.join()
        time_elapsed = time.time() - start
        print('mergesort parallel version:\t\t\t%f seconds' % (time_elapsed))
        listfromarray = list(array)
        start = time.time()
        listfromarray = sorted(listfromarray)
        time_elapsed = time.time() - start
        print('python built in sorting algorythm:\t\t%f seconds\n' % (time_elapsed))
        N+=10000

if __name__ == '__main__':
    main()
