/**
 * file: driver-proj6.cpp
 * author: Luke Smith
 * course: CSI 3334
 * assignment: project 6
 * due date: December 4, 2022
 *
 * Driver for implementing the network system.
 */

#include <iostream>
#include "graph-proj6.h"
#include "arrayheap-prof-proj6.h"
using namespace std;

int main() {
    ArrayHeap<Process> batch;
    int numProcess = 0;
    int id = 0;
    int startTime = 0, sysClock = 0;
    int complete = 0, failed = 0;

    cin >> numProcess;
    cin >> startTime;
    while(numProcess != 0) {
        Process task(id);

        if(startTime > sysClock && batch.getNumItems() == 0){
            sysClock = startTime;
        }

        if (id == 0) {

            cin >> task;
            batch.insert(task);
            id++;
            cin >> startTime;
        }

        if (startTime <= sysClock) {
            do {
                task = Process(id++);
                cin >> task;
                batch.insert(task);
//                cout << "inserted" << endl;
//                batch.checkOrder();

            } while (cin >> startTime && startTime <= sysClock);
        }

        while (batch.getNumItems() > 0 && ((cin.fail() && numProcess)
                                           || startTime > sysClock)) {
            if (batch.getMinItem().canComplete(sysClock)) {
                cout << "running process id " << batch.getMinItem().getId()
                     << " at " << sysClock << endl;
                task = batch.getMinItem();
                sysClock = task.run(sysClock);
                complete++;
            }
            else {
                cout << "skipping process id " << batch.getMinItem().getId()
                     << " at " << sysClock << endl;
                sysClock++;
                failed++;
            }
            batch.removeMinItem();
            //batch.checkOrder();
            numProcess--;
        }
    }

    cout << "final clock is                 " << sysClock << endl;
    cout << "number of processes run is     " << complete << endl;
    cout << "number of processes skipped is " << failed << endl;

    return 0;
}
