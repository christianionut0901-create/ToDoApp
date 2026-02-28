#include <iostream>
#include <string>
#include <vector>

class Task {
public:
    std::string description;
    bool done;

    explicit Task(const std::string& desc)
        : description(desc), done(false) {}
};

class TodoList {
public:
    std::vector<Task> tasks;

    void addTask(const std::string& description) {
        if (description.empty()) {
            std::cout << "Description cannot be empty\n";
            return;
        }
        tasks.emplace_back(description);
    }

    void printTasks() const {
        if (tasks.empty()) {
            std::cout << "No tasks yet\n";
            return;
        }

        std::cout << "\n----- TASK LIST -----\n";

        for (size_t i = 0; i < tasks.size(); ++i) {
            std::cout << i + 1 << ". " << tasks[i].description
                      << (tasks[i].done ? " [DONE]\n" : " [TODO]\n");
        }

        std::cout << "---------------------\n";
    }

    void markDone(size_t index) {
        if (index < tasks.size()) {
            if (tasks[index].done) {
                std::cout << "Task already completed\n";
                return;
            }
            tasks[index].done = true;
            std::cout << "Task marked as done\n";
        } else {
            std::cout << "Invalid index\n";
        }
    }

    void deleteTask(size_t index) {
        if (tasks.empty()) {
            std::cout << "No tasks to delete\n";
            return;
        }

        if (index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
            std::cout << "Task deleted\n";
        } else {
            std::cout << "Invalid index\n";
        }
    }

    void editTask(size_t index, const std::string& newDescription) {
        if (index < tasks.size()) {
            tasks[index].description = newDescription;
            std::cout << "Task updated\n";
        } else {
            std::cout << "Invalid index\n";
        }
    }
    void searchTasks(const std::string& keyword) const {
        bool found = false;

        for (size_t i = 0; i < tasks.size(); ++i) {
            if (tasks[i].description.find(keyword) != std::string::npos) {
                std::cout << i << ": " << tasks[i].description
                          << (tasks[i].done ? " [DONE]\n" : " [TODO]\n");
                found = true;
            }
        }

        if (!found) {
            std::cout << "No matching tasks\n";
        }
    }
};

int main() {
    TodoList todo;

    while (true) {
        std::cout << "\n1 Add task\n"
                  << "2 View tasks\n"
                  << "3 Mark task done\n"
                  << "4 Delete task\n"
                  << "5 Edit task\n"
                  << "6 Search tasks\n"
                  << "7 Exit\n"
                  << "Choose: ";

        int choice = 0;
        std::cin >> choice;
        std::cin.ignore(10000, '\n');

        if (choice == 1) {
            std::cout << "Description: ";
            std::string desc;
            std::getline(std::cin, desc);
            todo.addTask(desc);
            std::cout << "Task added\n";
        }
        else if (choice == 2) {
            todo.printTasks();
        }
        else if (choice == 3) {
            size_t index;
            std::cout << "Enter task index: ";
            std::cin >> index;
            std::cin.ignore(10000, '\n');
            todo.markDone(index);
        }
        else if (choice == 4) {
            size_t index;
            std::cout << "Enter task index to delete: ";
            std::cin >> index;
            std::cin.ignore(10000, '\n');
            todo.deleteTask(index);
        }
        else if (choice == 5) {
            size_t index;
            std::cout << "Enter task index to edit: ";
            std::cin >> index;
            std::cin.ignore(10000, '\n');

            std::cout << "New description: ";
            std::string newDesc;
            std::getline(std::cin, newDesc);

            todo.editTask(index, newDesc);
        }
        else if (choice == 6) {
            std::cout << "Keyword: ";
            std::string keyword;
            std::getline(std::cin >> std::ws, keyword);
            todo.searchTasks(keyword);
        }
        else if (choice == 7) {
            break;
        }
    }

    return 0;
}
