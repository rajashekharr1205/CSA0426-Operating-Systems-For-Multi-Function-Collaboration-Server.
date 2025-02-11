#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
};

void calculateTimes(struct Process processes[], int n) {
    int time = 0, completed = 0;
    int min_burst_time, shortest;
    int is_completed[100] = {0};
    
    while (completed != n) {
        min_burst_time = 9999;
        shortest = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && !is_completed[i]) {
                if (processes[i].burst_time < min_burst_time) {
                    min_burst_time = processes[i].burst_time;
                    shortest = i;
                }
                if (processes[i].burst_time == min_burst_time) {
                    if (processes[i].arrival_time < processes[shortest].arrival_time) {
                        shortest = i;
                    }
                }
            }
        }

        if (shortest != -1) {
            time += processes[shortest].burst_time;
            processes[shortest].completion_time = time;
            processes[shortest].turnaround_time = processes[shortest].completion_time - processes[shortest].arrival_time;
            processes[shortest].waiting_time = processes[shortest].turnaround_time - processes[shortest].burst_time;
            is_completed[shortest] = 1;
            completed++;
        } else {
            time++;
        }
    }
}

void printTable(struct Process processes[], int n) {
    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               processes[i].pid,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].completion_time,
               processes[i].turnaround_time,
               processes[i].waiting_time);
    }
}

void calculateAverageTimes(struct Process processes[], int n) {
    int total_turnaround_time = 0, total_waiting_time = 0;

    for (int i = 0; i < n; i++) {
        total_turnaround_time += processes[i].turnaround_time;
        total_waiting_time += processes[i].waiting_time;
    }

    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    calculateTimes(processes, n);
    printTable(processes, n);
    calculateAverageTimes(processes, n);

    return 0;
}

