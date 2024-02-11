#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm> // Required for remove_if function

struct Task {
    std::string description;
    std::string dueDate;
    int priority;
    bool completed;
};

// Function prototypes
void loadTasksFromFile(const std::string& filename, std::vector<Task>& tasks);
void saveTasksToFile(const std::string& filename, const std::vector<Task>& tasks);
void printTasks(const std::vector<Task>& tasks);
void addTask(std::vector<Task>& tasks);
void removeTask(std::vector<Task>& tasks, int index);
void markTaskAsComplete(std::vector<Task>& tasks, int index);
void clearCompletedTasks(std::vector<Task>& tasks);

int main() {
    const std::string filename = "todo.txt";
    std::vector<Task> tasks;
    loadTasksFromFile(filename, tasks);

    std::cout << "Welcome to the To-Do List Manager!\n";

    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. View Tasks\n";
        std::cout << "2. Add Task\n";
        std::cout << "3. Remove Task\n";
        std::cout << "4. Mark Task as Complete\n";
        std::cout << "5. Clear Completed Tasks\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                printTasks(tasks);
                break;
            case 2:
                addTask(tasks);
                break;
            case 3: {
                int index;
                std::cout << "Enter the index of the task to remove: ";
                std::cin >> index;
                removeTask(tasks, index);
                break;
            }
            case 4: {
                int index;
                std::cout << "Enter the index of the task to mark as complete: ";
                std::cin >> index;
                markTaskAsComplete(tasks, index);
                break;
            }
            case 5:
                clearCompletedTasks(tasks);
                break;
            case 6:
                saveTasksToFile(filename, tasks);
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

// Function to load tasks from a file into the tasks vector
void loadTasksFromFile(const std::string& filename, std::vector<Task>& tasks) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file for reading\n";
        return;
    }

    Task task;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        iss >> task.description >> task.dueDate >> task.priority >> task.completed;
        tasks.push_back(task);
    }

    file.close();
}

// Function to save tasks from the tasks vector into a file
void saveTasksToFile(const std::string& filename, const std::vector<Task>& tasks) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file for writing\n";
        return;
    }

    for (const auto& task : tasks) {
        file << task.description << ' ' << task.dueDate << ' ' << task.priority << ' ' << task.completed << '\n';
    }

    file.close();
}

// Function to print all tasks in the tasks vector
void printTasks(const std::vector<Task>& tasks) {
    std::cout << "\nTo-Do List:\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << i + 1 << ". ";
        std::cout << "Description: " << tasks[i].description << ", ";
        std::cout << "Due Date: " << tasks[i].dueDate << ", ";
        std::cout << "Priority: " << tasks[i].priority << ", ";
        std::cout << "Completed: " << (tasks[i].completed ? "Yes" : "No") << "\n";
    }
}

// Function to add a new task to the tasks vector
void addTask(std::vector<Task>& tasks) {
    Task task;
    std::cout << "Enter task description: ";
    std::cin.ignore(); // Ignore newline character left in the input buffer
    std::getline(std::cin, task.description);
    std::cout << "Enter due date: ";
    std::cin >> task.dueDate;
    std::cout << "Enter priority (1-10): ";
    std::cin >> task.priority;
    task.completed = false;
    tasks.push_back(task);
    std::cout << "Task added successfully.\n";
}

// Function to remove a task from the tasks vector
void removeTask(std::vector<Task>& tasks, int index) {
    if (index >= 1 && index <= static_cast<int>(tasks.size())) {
        tasks.erase(tasks.begin() + index - 1);
        std::cout << "Task removed successfully.\n";
    } else {
        std::cout << "Invalid task index.\n";
    }
}

// Function to mark a task as complete in the tasks vector
void markTaskAsComplete(std::vector<Task>& tasks, int index) {
    if (index >= 1 && index <= static_cast<int>(tasks.size())) {
        tasks[index - 1].completed = true;
        std::cout << "Task marked as complete.\n";
    } else {
        std::cout << "Invalid task index.\n";
    }
}

// Function to clear completed tasks from the tasks vector
void clearCompletedTasks(std::vector<Task>& tasks) {
    tasks.erase(std::remove_if(tasks.begin(), tasks.end(), [](const Task& task) {
        return task.completed;
    }), tasks.end());
    std::cout << "Completed tasks cleared.\n";
}
