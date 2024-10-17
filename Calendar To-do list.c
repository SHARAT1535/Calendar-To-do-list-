#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char *months[] =
{
    " ",
    "\n\n\nJanuary",
    "\n\n\nFebruary",
    "\n\n\nMarch",
    "\n\n\nApril",
    "\n\n\nMay",
    "\n\n\nJune",
    "\n\n\nJuly",
    "\n\n\nAugust",
    "\n\n\nSeptember",
    "\n\n\nOctober",
    "\n\n\nNovember",
    "\n\n\nDecember"
};

struct Task {
    char description[100];
    int isDone;
    char priority;
};

int inputyear(void);
int determinedaycode(int year);
int determineleapyear(int year);
void displayMonth(int year, int month, int daycode);
void addTask(struct Task list[], int *count, const char *description, char priority);
void listTasks(struct Task list[], int count, bool reverse);
void sortTasksByPriority(struct Task list[], int count);
void markTaskDone(struct Task list[], int count, int taskIndex);
void deleteLowestPriorityTasks(struct Task list[], int *count);

int main(void) {
    int year, daycode, leapyear, month;
    year = inputyear();
    daycode = determinedaycode(year);
    determineleapyear(year);
    printf("Enter the month (1 for January, 2 for February, etc.): ");
    scanf("%d", &month);
    if (month >= 1 && month <= 12)
    {
        displayMonth(year, month, daycode);
        struct Task dayTasks[31][10];
        int taskCounts[31] = {0};
        int day;
        while (1) {
            printf("Enter the day to manage tasks (1-%d, 0 to exit): ", days_in_month[month]);
            scanf("%d", &day);

            if (day == 0) {
                break;
            }
            if (day >= 1 && day <= days_in_month[month]) {
                int choice;
                while (1) {
                    printf("\nTo-Do List Program\n");
                    printf("1. Add Task\n");
                    printf("2. List Tasks\n");
                    printf("3. Sort Tasks by Priority (Highest to Lowest)\n");
                    printf("4. Sort Tasks by Priority (Lowest to Highest)\n");
                    printf("5. Mark Task as Done\n");
                    printf("6. Delete Lowest Priority Tasks\n");
                    printf("7. Exit\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);
                    switch (choice) {
                        case 1:
                            printf("Enter task description: ");
                            char description[100];
                            scanf(" %[^\n]s", description);
                            char priority;
                             printf("Enter task priority (A=Highest, B=Medium, C=Low, D=Delegated): ");
                            scanf(" %c", &priority);
                            addTask(dayTasks[day - 1], &taskCounts[day - 1], description, priority);
                            break;
                        case 2:
                            listTasks(dayTasks[day - 1], taskCounts[day - 1], false);
                            break;
                        case 3:
                            sortTasksByPriority(dayTasks[day - 1], taskCounts[day - 1]);
                            listTasks(dayTasks[day - 1], taskCounts[day - 1], false);
                            break;
                        case 4:
                            sortTasksByPriority(dayTasks[day - 1], taskCounts[day - 1]);
                            listTasks(dayTasks[day - 1], taskCounts[day - 1], true);
                            break;
                        case 5:
                            if (taskCounts[day - 1] > 0) {
                                int taskIndex;
                                printf("Enter the index of the task to mark as done: ");
                                scanf("%d", &taskIndex);
                                markTaskDone(dayTasks[day - 1], taskCounts[day - 1], taskIndex);
                            } else {
                                printf("No tasks to mark as done.\n");
                            }
                            break;
                        case 6:
                            deleteLowestPriorityTasks(dayTasks[day - 1], &taskCounts[day - 1]);
                            listTasks(dayTasks[day - 1], taskCounts[day - 1], false);
                            break;
                        case 7:
                            exit(0);
                        default:
                            printf("Invalid choice. Please try again.\n");
                    }
                }
            }
            else
            {
                printf("Invalid day input.\n");
            }
        }
    }
    else
    {
        printf("Invalid month input.\n");
    }
    printf("\n");
    return 0;
}

// Function definitions

int inputyear (void)
{ int year;
  while (1)
    {
        printf("Enter a year between 2022 and 2024: ");
        scanf("%d", &year);

        if (year >= 2022 && year <= 2024)
        {
            return year;
        }
        else
        {
            printf("Invalid year. Please enter a year between 2022 and 2024.\n");
}}
}

int determinedaycode(int year) {
    int daycode;
    int d1, d2, d3;
    d1 = (year - 1) / 4;
    d2 = (year - 1) / 100;
    d3 = (year - 1) / 400;
    daycode = (year + d1 - d2 + d3) % 7;
    return daycode;
}

int determineleapyear(int year) {
    if (year % 4 == FALSE && year % 100 != FALSE || year % 400 == FALSE) {
        days_in_month[2] = 29;
        return TRUE;
    } else {
        days_in_month[2] = 28;
        return FALSE;
    }
}

void displayMonth(int year, int month, int daycode) {
    printf("%s %d\n", months[month], year);
    printf("Sun Mon Tue Wed Thu Fri Sat\n");

    int currentDay = 1;

    // Print leading spaces
    for (int space = 0; space < daycode; space++) {
        printf("    ");
    }

    while (currentDay <= days_in_month[month]) {
        for (int day = 0; day < 7 && currentDay <= days_in_month[month]; day++) {
            printf("%3d ", currentDay);
            currentDay++;
        }
        printf("\n");
    }
    printf("\n");
}

void addTask(struct Task list[], int *count, const char *description, char priority) {
    if (*count < 100) {
        while ((priority < 'A' || priority > 'D') && (priority < 'a' || priority > 'd')) {
            printf("Invalid priority. Enter priority (A=Highest, B=Next Highest, C=Ok, D=Lowest): ");
            scanf(" %c", &priority);
        }

        struct Task newTask;
        strcpy(newTask.description, description);
        newTask.isDone = 0;
        newTask.priority = priority;
        list[*count] = newTask;
        (*count)++;

        printf("Task added: %s\n", description);
    } else {
        printf("Task list is full. Remove some tasks to add more.\n");
    }
}

void listTasks(struct Task list[], int count, bool reverse) {
    printf("To-Do List:\n");
    if (!reverse) {
        for (int i = 0; i < count; i++) {
            printf("%d. %s [%s] (Priority: %c)\n", i + 1, list[i].description, list[i].isDone ? "Done" : "Not Done", list[i].priority);
        }
    } else {
        for (int i = count - 1; i >= 0; i--) {
            printf("%d. %s [%s] (Priority: %c)\n", count - i, list[i].description, list[i].isDone ? "Done" : "Not Done", list[i].priority);
        }
    }
}

void sortTasksByPriority(struct Task list[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (list[i].priority > list[j].priority) {
                struct Task temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
}

void markTaskDone(struct Task list[], int count, int taskIndex) {
    if (taskIndex >= 1 && taskIndex <= count) {
        list[taskIndex - 1].isDone = 1;
        printf("Task marked as done: %s\n", list[taskIndex - 1].description);
    } else {
        printf("Invalid task index.\n");
    }
}
void deleteLowestPriorityTasks(struct Task list[], int *count) {
    if (*count > 0) {
        char lowestPriority = 'D',chara='d'; // Set the lowest priority to 'D'
        int i = 0;
        while (i < *count) {
            if (list[i].priority == lowestPriority || list[i].priority ==chara ) {
                for (int j = i; j < *count - 1; j++) {
                    list[j] = list[j + 1];
                }
                (*count)--;
            } else {
                i++;
            }
        }

        printf("Lowest priority tasks deleted.\n");
    } else {
        printf("No tasks to delete.\n");
    }
}
