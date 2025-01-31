#include <cstdlib>
#include <cstdio>
#include <vector>
#include <queue>

struct Task {
    unsigned int identifier, count;
    std::vector<int> steps;
};

int main() {
    unsigned int num_tasks, step, total_time = 0;
    scanf("%d", &num_tasks);

    Task *tasks = (Task *)malloc(sizeof(Task) * num_tasks);
    std::queue<Task> task_queue;

    for (unsigned int idx = 0; idx < num_tasks; idx++) {
        scanf("%d", &tasks[idx].count);
        tasks[idx].identifier = idx + 1;
    }

    for (unsigned int idx = 0; idx < num_tasks; idx++) {
        for (unsigned int step_idx = 0; step_idx < tasks[idx].count; step_idx++) {
            scanf("%d", &step);
            tasks[idx].steps.push_back(step);
        }
        task_queue.push(tasks[idx]);
    }

    while (!task_queue.empty()) {
        unsigned int current_step = 0;
        Task current_task = task_queue.front();
        task_queue.pop();

        while (current_task.count > 0 && current_task.steps[current_step] != 1) {
            current_task.count--;
            total_time += 10;
            current_step++;
        }

        if (current_task.count == 0) {
            printf("%d (%d)\n", current_task.identifier, total_time);
        } else {
            current_task.steps[current_step] = 0;
            for (unsigned int idx = 0; idx < current_task.count; idx++) {
                current_task.steps[idx] = current_task.steps[current_step++];
            }
            task_queue.push(current_task);
        }
    }

    for (unsigned int idx = 0; idx < num_tasks; idx++) {
        tasks[idx].steps.clear();
    }

    free(tasks);
    return 0;
}
