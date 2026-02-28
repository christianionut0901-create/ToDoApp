#include <iostream>
#include <string>
#include <vector>

class Task {
public:
    std::string description;
    bool done;

    Task(const std::string& desc)
        : description(desc), done(false) {}
};

class TodoList {
public:
    std::vector<Task> tasks;

    void addTask(const std::string& description) {
        tasks.push_back(Task(description));
    }

    void printTasks() const {
        if (tasks.empty()) {
            std::cout << "No tasks yet\n";
            return;
        }

        for (size_t i = 0; i < tasks.size(); i++) {
            std::cout << i << ": " << tasks[i].description
                      << (tasks[i].done ? " [DONE]\n" : " [TODO]\n");
        }
    }
};

int main() {
    TodoList todo;

    while (true) {
        std::cout << "\n1 Add task\n2 View tasks\n3 Exit\nChoose: ";
        int choice = 0;
        std::cin >> choice;
        std::cin.ignore(10000, '\n');

        if (choice == 1) {
            std::cout << "Description: ";
            std::string desc;
            std::getline(std::cin, desc);
            todo.addTask(desc);
            std::cout << "Task added\n";
        } else if (choice == 2) {
            todo.printTasks();
        } else if (choice == 3) {
            break;
        } else {
            std::cout << "Invalid choice\n";
        }
    }

    return 0;
}
