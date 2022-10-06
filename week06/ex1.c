#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int number;
    int arrival_time;
    int burst_time;
} ProcessInfo;

typedef struct {
    int process_number;
    int* completion_times;
    int* turnaround_times;
    int* waiting_times;
    float avg_turnaround_time;
    float avg_waiting_time;
} AlgorithmMetrics;

void sort_by_arrival_time(ProcessInfo* processes, int num_processes) {
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_processes - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                ProcessInfo temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

/**
 * First Come First Serve (FCFS) Algorithm.
 */
AlgorithmMetrics* schedule_fcfs(ProcessInfo* processes, int n) {
    sort_by_arrival_time(processes, n);

    AlgorithmMetrics* metrics = malloc(sizeof(AlgorithmMetrics));
    metrics->process_number = n;
    metrics->completion_times = malloc(sizeof(int) * n);
    metrics->turnaround_times = malloc(sizeof(int) * n);
    metrics->waiting_times = malloc(sizeof(int) * n);

    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        int exit_time = current_time + processes[i].burst_time;

        metrics->completion_times[i] = exit_time;
        metrics->turnaround_times[i] = exit_time - processes[i].arrival_time;
        metrics->waiting_times[i] = metrics->turnaround_times[i] - processes[i].burst_time;

        current_time = exit_time;
    }

    // Calculate average turnaround time and waiting time.
    float avg_turnaround_time = 0;
    float avg_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        avg_turnaround_time += metrics->turnaround_times[i];
        avg_waiting_time += metrics->waiting_times[i];
    }
    metrics->avg_turnaround_time = avg_turnaround_time / n;
    metrics->avg_waiting_time = avg_waiting_time / n;

    return metrics;
}

void print_metrics(
    AlgorithmMetrics* metrics,
    ProcessInfo* processes,
    char* algorithm_name
) {
    printf("=== Metrics for \"%s\" ===\n", algorithm_name);

    printf("Completion times (CT):\n");
    for (int i = 0; i < metrics->process_number; i++) {
        printf("  P%d: %d\n", processes[i].number, metrics->completion_times[i]);
    }
    printf("\n");

    printf("Turnaround times (TAT):\n");
    for (int i = 0; i < metrics->process_number; i++) {
        printf("  P%d: %d\n", processes[i].number, metrics->turnaround_times[i]);
    }
    printf("\n");

    printf("Waiting times (WT):\n");
    for (int i = 0; i < metrics->process_number; i++) {
        printf("  P%d: %d\n", processes[i].number, metrics->waiting_times[i]);
    }
    printf("\n");

    printf("Average turnaround time: %f\n", metrics->avg_turnaround_time);
    printf("Average waiting time: %f\n", metrics->avg_waiting_time);

    printf("========================================\n");
}

void free_metrics(AlgorithmMetrics* metrics) {
    free(metrics->completion_times);
    free(metrics->turnaround_times);
    free(metrics->waiting_times);
    free(metrics);
}

int main() {
    int number_of_processes;
    ProcessInfo* processes;

    while (1) {
        printf("Enter the number of processes: ");
        scanf("%d", &number_of_processes);
        if (number_of_processes > 0) {
            break;
        }
    }

    processes = (ProcessInfo*) malloc(number_of_processes * sizeof(ProcessInfo));

    for (int i = 0; i < number_of_processes; i++) {
        printf("#%d: <arrival_time> <burst_time>: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].number = i + 1;
    }

    AlgorithmMetrics* metrics = schedule_fcfs(processes, number_of_processes);
    print_metrics(metrics, processes, "FCFS");

    free_metrics(metrics);
    free(processes);

    return 0;
}
