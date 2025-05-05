#include <iostream>
using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int executionTime;
    Process* next;
};

int currentTime = 0;
int totalWaitingTime = 0;
int totalTurnaroundTime = 0;
int processCount = 0;

void addProcess(Process*& front, Process*& rear, int id, int arrival, int execTime) {
    Process* newProcess = new Process();
    newProcess->id = id;
    newProcess->arrivalTime = arrival;
    newProcess->executionTime = execTime;
    newProcess->next = NULL;

    if (front == NULL || arrival < front->arrivalTime) {
        newProcess->next = front;
        front = newProcess;
        if (rear == NULL) rear = newProcess;
        return;
    }

    Process* current = front;
    while (current->next != NULL && current->next->arrivalTime <= arrival) {
        current = current->next;
    }

    newProcess->next = current->next;
    current->next = newProcess;
    if (newProcess->next == NULL) rear = newProcess;
}

void deleteProcess(Process*& front) {
    if (front != NULL) {
        Process* temp = front;
        front = front->next;
        delete temp;
    }
}

void showFCFS(Process* front) {
    cout << "\nProcess\tArrival\tExec\tWait\tTurnaround\n";
    while (front != NULL) {
        if (currentTime < front->arrivalTime) {
            currentTime = front->arrivalTime;
        }
        int waitingTime = currentTime - front->arrivalTime;
        int turnaroundTime = waitingTime + front->executionTime;

        totalWaitingTime += waitingTime;
        totalTurnaroundTime += turnaroundTime;

        cout << "P" << front->id << "\t"
             << front->arrivalTime << "\t"
             << front->executionTime << "\t"
             << waitingTime << "\t"
             << turnaroundTime << "\n";
             currentTime += front->executionTime;
             processCount++;
        deleteProcess(front);
    }
}

void computeAverages() {
    float avgWaitingTime = (float)totalWaitingTime / processCount;
    float avgTurnaroundTime = (float)totalTurnaroundTime / processCount;

    cout << "\nAverage Waiting Time: " << avgWaitingTime;
    cout << "\nAverage Turnaround Time: " << avgTurnaroundTime << "\n";
}

int main() {
    cout<<"|--------------FCFS Algorithm--------------|\n|---------Mihoubi Youcef L2 GRP 10---------|"<<endl;

    Process* front = NULL;
    Process* rear = NULL;

    int numProcesses;
    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    for (int i = 1; i <= numProcesses; i++) {
        int arrivalTime, executionTime;
        cout << "Enter arrival time and execution time for Process " << i << " (separated by space): ";
        cin >> arrivalTime >> executionTime;
        addProcess(front, rear, i, arrivalTime, executionTime);
    }

    cout << "\nFCFS : ";
    showFCFS(front);
    computeAverages();

    return 0;
}
