// Todo List Assignment – Git and Feature Branches
// Name: Cristian Ionut Dobre
// GitHub Repository: https://github.com/christianionut0901-create/ToDoApp

#include <iostream>
#include <string>
#include <vector>
#include <limits>

class Task {
public:
    std::string description;
    bool done;

    explicit Task(const std::string& desc)
        : description(desc), done(false) {}
};

class TodoList {
private:
    std::vector<Task> tasks;

public:
    bool addTask(const std::string& description) {
        if (description.empty()) {
            std::cout << "Description cannot be empty\n";
            return false;
        }
        tasks.emplace_back(description);
        return true;
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

    bool markDone(size_t indexZeroBased) {
        if (indexZeroBased >= tasks.size()) {
            std::cout << "Invalid index\n";
            return false;
        }
        if (tasks[indexZeroBased].done) {
            std::cout << "Task already completed\n";
            return false;
        }
        tasks[indexZeroBased].done = true;
        std::cout << "Task marked as done\n";
        return true;
    }

    bool deleteTask(size_t indexZeroBased) {
        if (tasks.empty()) {
            std::cout << "No tasks to delete\n";
            return false;
        }
        if (indexZeroBased >= tasks.size()) {
            std::cout << "Invalid index\n";
            return false;
        }
        tasks.erase(tasks.begin() + static_cast<long>(indexZeroBased));
        std::cout << "Task deleted\n";
        return true;
    }

    bool editTask(size_t indexZeroBased, const std::string& newDescription) {
        if (indexZeroBased >= tasks.size()) {
            std::cout << "Invalid index\n";
            return false;
        }
        if (newDescription.empty()) {
            std::cout << "Description cannot be empty\n";
            return false;
        }
        tasks[indexZeroBased].description = newDescription;
        std::cout << "Task updated\n";
        return true;
    }

    void searchTasks(const std::string& keyword) const {
        if (keyword.empty()) {
            std::cout << "Keyword cannot be empty\n";
            return;
        }

        bool found = false;
        for (size_t i = 0; i < tasks.size(); ++i) {
            if (tasks[i].description.find(keyword) != std::string::npos) {
                std::cout << i + 1 << ". " << tasks[i].description
                          << (tasks[i].done ? " [DONE]\n" : " [TODO]\n");
                found = true;
            }
        }

        if (!found) {
            std::cout << "No matching tasks\n";
        }
    }
};

static bool readInt(int& out) {
    if (!(std::cin >> out)) {
        return false;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true;
}

static bool readSizeT(size_t& out) {
    if (!(std::cin >> out)) {
        return false;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true;
}

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
        if (!readInt(choice)) {
            std::cout << "\nInput closed or invalid. Exiting.\n";
            return 0;
        }

        if (choice == 1) {
            std::cout << "Description: ";
            std::string desc;
            std::getline(std::cin, desc);

            if (todo.addTask(desc)) {
                std::cout << "Task added\n";
            }
        }
        else if (choice == 2) {
            todo.printTasks();
        }
        else if (choice == 3) {
            std::cout << "Enter task index: ";
            size_t indexOneBased = 0;

            if (!readSizeT(indexOneBased)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input\n";
                continue;
            }

            if (indexOneBased == 0) {
                std::cout << "Invalid index\n";
                continue;
            }

            todo.markDone(indexOneBased - 1);
        }
        else if (choice == 4) {
            std::cout << "Enter task index to delete: ";
            size_t indexOneBased = 0;

            if (!readSizeT(indexOneBased)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input\n";
                continue;
            }

            if (indexOneBased == 0) {
                std::cout << "Invalid index\n";
                continue;
            }

            todo.deleteTask(indexOneBased - 1);
        }
        else if (choice == 5) {
            std::cout << "Enter task index to edit: ";
            size_t indexOneBased = 0;

            if (!readSizeT(indexOneBased)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input\n";
                continue;
            }

            if (indexOneBased == 0) {
                std::cout << "Invalid index\n";
                continue;
            }

            std::cout << "New description: ";
            std::string newDesc;
            std::getline(std::cin, newDesc);

            todo.editTask(indexOneBased - 1, newDesc);
        }
        else if (choice == 6) {
            std::cout << "Keyword: ";
            std::string keyword;
            std::getline(std::cin, keyword);

            todo.searchTasks(keyword);
        }
        else if (choice == 7) {
            break;
        }
        else {
            std::cout << "Invalid choice\n";
        }
    }

    return 0;
}
