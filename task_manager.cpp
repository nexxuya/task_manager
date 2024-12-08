#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <Windows.h>

// Model
class TaskModel 
{
private:
    std::vector<std::string> tasks;

public:
    void addTask(const std::string& task) {
        tasks.push_back(task);
    }

    std::vector<std::string> getTasks() const {
        return tasks;
    }

    void removeTask(const std::string& task) {
        auto it = std::find(tasks.begin(), tasks.end(), task);
        if (it != tasks.end()) {
            tasks.erase(it);
        }
    }
};

// View
class TaskView 
{
public:
    void displayTasks(const std::vector<std::string>& tasks) const {
        std::cout << "Ваші завдання:" << std::endl;
        for (size_t i = 0; i < tasks.size(); ++i) {
            std::cout << i + 1 << ". " << tasks[i] << std::endl;
        }
    }

    void displayMessage(const std::string& message) const {
        std::cout << message << std::endl;
    }
};

// Controller
class TaskController 
{
private:
    TaskModel& model;
    TaskView& view;

public:
    TaskController(TaskModel& m, TaskView& v) : model(m), view(v) {}

    void addTask(const std::string& task) {
        model.addTask(task);
        view.displayMessage("Завдання '" + task + "' додано.");
    }

    void showTasks() {
        view.displayTasks(model.getTasks());
    }

    void deleteTask(const std::string& task) {
        const auto& tasks = model.getTasks();
        if (std::find(tasks.begin(), tasks.end(), task) != tasks.end()) {
            model.removeTask(task);
            view.displayMessage("Завдання '" + task + "' видалено.");
        }
        else {
            view.displayMessage("Завдання '" + task + "' не знайдено.");
        }
    }
};

// Основна програма
int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    TaskModel model;
    TaskView view;
    TaskController controller(model, view);

    while (true) {
        std::cout << "\n1. Додати завдання" << std::endl;
        std::cout << "2. Показати завдання" << std::endl;
        std::cout << "3. Видалити завдання" << std::endl;
        std::cout << "4. Вийти" << std::endl;
        std::cout << "Оберіть дію: ";

        int choice;
        std::cin >> choice;

        std::cin.ignore();

        if (choice == 1) {
            std::cout << "Введіть завдання: ";
            std::string task;
            std::getline(std::cin, task);
            controller.addTask(task);
        }
        else if (choice == 2) {
            controller.showTasks();
        }
        else if (choice == 3) {
            std::cout << "Введіть завдання для видалення: ";
            std::string task;
            std::getline(std::cin, task);
            controller.deleteTask(task);
        }
        else if (choice == 4) {
            std::cout << "До побачення!" << std::endl;
            break;
        }
        else {
            std::cout << "Неправильний вибір. Спробуйте ще раз." << std::endl;
        }
    }

    return 0;
}
