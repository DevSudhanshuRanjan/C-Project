#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_TASKS 50
#define MAX_LEN 50

typedef struct {
    char task[MAX_LEN];
} Task;

typedef struct {
    char userId[MAX_LEN];
    char password[MAX_LEN];
    Task tasks[MAX_TASKS];
    int taskCount;
} User;

void signup(User users[], int *userCount);
void login(User users[], int *userCount);
int isUserIdExists(User users[], int userCount, char userId[]);
void addData(User *user);
void showData(User *user);
void deleteData(User *user);

int main() {
    User users[MAX_USERS];
    int userCount = 0;
    int choice;

    while (1) {
        printf("\n--- TO-DO LIST ---\n");
        printf("1. Login\n");
        printf("2. Signup\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline left in the buffer
        switch (choice) {
            case 1:
                login(users, &userCount);
                break;
            case 2:
                signup(users, &userCount);
                break;
            case 3:
                printf("Exiting... Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

void signup(User users[], int *userCount) {
    if (*userCount >= MAX_USERS) {
        printf("User list is full. Cannot add more users.\n");
        return;
    }

    User newUser;
    printf("\n--- SIGNUP ---\n");
    printf("Enter User ID: ");
    scanf("%s", newUser.userId);

    if (isUserIdExists(users, *userCount, newUser.userId)) {
        printf("User ID already exists. Please try a different one.\n");
        return;
    }

    printf("Enter Password: ");
    scanf("%s", newUser.password);

    newUser.taskCount = 0;

    users[*userCount] = newUser;
    (*userCount)++;
    printf("Signup successful! You can now login.\n");
}

void login(User users[], int *userCount) {
    if (*userCount == 0) {
        printf("No users available. Redirecting to signup...\n");
        signup(users, userCount);
        return;
    }

    printf("\n--- LOGIN ---\n");
    printf("Select a User ID from the list below:\n");

    for (int i = 0; i < *userCount; i++) {
        printf("%d. %s\n", i + 1, users[i].userId);
    }

    int selectedUser;
    printf("Enter the number corresponding to your User ID: ");
    scanf("%d", &selectedUser);

    if (selectedUser < 1 || selectedUser > *userCount) {
        printf("Invalid selection. Returning to main menu.\n");
        return;
    }

    int userIndex = selectedUser - 1;

    char password[MAX_LEN];
    printf("Enter your Password: ");
    scanf("%s", password);

    if (strcmp(users[userIndex].password, password) == 0) {
        printf("Login successful! Welcome, %s!\n", users[userIndex].userId);

        while (1) {
            int choice;
            printf("\n--- USER MENU ---\n");
            printf("1. Add Task\n");
            printf("2. Show Tasks\n");
            printf("3. Delete Task\n");
            printf("4. Logout\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    addData(&users[userIndex]);
                    break;
                case 2:
                    showData(&users[userIndex]);
                    break;
                case 3:
                    deleteData(&users[userIndex]);
                    break;
                case 4:
                    printf("Logging out...\n");
                    return;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
    } else {
        printf("Invalid password. Please try again.\n");
    }
}

int isUserIdExists(User users[], int userCount, char userId[]) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].userId, userId) == 0) {
            return 1;
        }
    }
    return 0;
}

void addData(User *user) {
    if (user->taskCount >= MAX_TASKS) {
        printf("Task list is full. Cannot add more tasks.\n");
        return;
    }

    printf("Enter the task: ");
    getchar(); // Consume leftover newline
    scanf("%[^\n]", user->tasks[user->taskCount].task);

    user->taskCount++;
    printf("Task added successfully!\n");
}

void showData(User *user) {
    if (user->taskCount == 0) {
        printf("No tasks available.\n");
        return;
    }

    printf("\n--- TASKS ---\n");
    for (int i = 0; i < user->taskCount; i++) {
        printf("%d. %s\n", i + 1, user->tasks[i].task);
    }
}

void deleteData(User *user) {
    if (user->taskCount == 0) {
        printf("No tasks available to delete.\n");
        return;
    }

    int taskNumber;
    printf("\n--- DELETE TASK ---\n");
    showData(user);
    printf("Enter the task number to delete: ");
    scanf("%d", &taskNumber);

    if (taskNumber < 1 || taskNumber > user->taskCount) {
        printf("Invalid task number. Please try again.\n");
        return;
    }

    for (int i = taskNumber - 1; i < user->taskCount - 1; i++) {
        strcpy(user->tasks[i].task, user->tasks[i + 1].task);
    }
    user->taskCount--;

    printf("Task deleted successfully!\n");
}
