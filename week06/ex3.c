#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
 * Round Robin Algorithm.
 */
AlgorithmMetrics* schedule_round_robin(ProcessInfo* processes, int n, int quantum) {
    AlgorithmMetrics* metrics = malloc(sizeof(AlgorithmMetrics));
    metrics->process_number = n;
    metrics->completion_times = malloc(sizeof(int) * n);
    metrics->turnaround_times = malloc(sizeof(int) * n);
    metrics->waiting_times = malloc(sizeof(int) * n);
    int current_time = 0;

    if (n > 0) {
        int min_arrival_time = processes[0].arrival_time;
        for (int i = 1; i < n; i++) {
            if (processes[i].arrival_time < min_arrival_time) {
                min_arrival_time = processes[i].arrival_time;
            }
        }
        current_time = min_arrival_time;
    }

    bool* arrived = malloc(sizeof(bool) * n);
    int* remaining_burst_times = malloc(sizeof(int) * n);
    ProcessInfo* queue = malloc(sizeof(ProcessInfo) * n);
    for (int i = 0; i < n; i++) {
        remaining_burst_times[i] = processes[i].burst_time;
        arrived[i] = false;
    }

    int queue_size = 0;
    int done_count = 0;
    int previous_preempted_process = -1;
    while (done_count < n) {
        for (int i = 0; i < n; i++) {
            if (!arrived[i] && processes[i].arrival_time <= current_time) {
                arrived[i] = true;
                queue[queue_size++] = processes[i];
            }
        }

        if (previous_preempted_process != -1) {
            queue[queue_size++] = processes[previous_preempted_process];
            previous_preempted_process = -1;
        }

        if (queue_size > 0) {
            ProcessInfo current_process = queue[0];
            for (int i = 0; i < queue_size - 1; i++) {
                queue[i] = queue[i + 1];
            }
            queue_size--;

            int i = current_process.number - 1;

            if (remaining_burst_times[i] <= quantum) {
                current_time += remaining_burst_times[i];
                remaining_burst_times[i] = 0;
                done_count++;

                metrics->completion_times[i] = current_time;
                metrics->turnaround_times[i] = current_time - processes[i].arrival_time;
                metrics->waiting_times[i] = metrics->turnaround_times[i] - processes[i].burst_time;
            } else {
                current_time += quantum;
                remaining_burst_times[i] -= quantum;
                previous_preempted_process = i;
            }
        } else {
            current_time++;
        }
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

    free(remaining_burst_times);
    free(arrived);
    free(queue);

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

    int quantum;
    while (1) {
        printf("Enter the quantum: ");
        scanf("%d", &quantum);
        if (quantum > 0) {
            break;
        }
    }

    AlgorithmMetrics* metrics = schedule_round_robin(processes, number_of_processes, quantum);
    print_metrics(metrics, processes, "Round Robin");

    free_metrics(metrics);
    free(processes);

    return 0;
}
