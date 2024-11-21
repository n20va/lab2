#include <Python.h>
#include <iostream>
#include <filesystem>
#include "../tests/tests.h"
#include "menu.h"
#include "../ArraySequence/ArraySequence/ArraySequence.h"


bool is_initialized = false;


std::string replace_build_path(const std::string& path) {
    std::string to_find = "/labarat1/cmake-build-debug";
    std::string to_replace = "/labarat1";
    size_t pos = path.find(to_find);
    if (pos != std::string::npos) {
        std::string new_path = path;
        new_path.replace(pos, to_find.length(), to_replace);
        return new_path;
    }
    return path;
}


void showPlot() {
    if (!is_initialized) {
        Py_Initialize();
        is_initialized = true;
    }
    std::string sys_path_command = replace_build_path(std::filesystem::current_path());
    sys_path_command = "sys.path.append('" + sys_path_command + "/tests" +  "')";
    PyRun_SimpleString("import sys");
    PyRun_SimpleString(sys_path_command.c_str());
    PyRun_SimpleString("if 'plot_performance' in sys.modules: del sys.modules['plot_performance']");
    PyObject *name, *load_module, *func, *callfunc;
    name = PyUnicode_FromString((char*)"plot_performance");
    load_module = PyImport_Import(name);
    if (load_module != nullptr) {
        func = PyObject_GetAttrString(load_module, "main");
        if (PyCallable_Check(func)) {
            callfunc = PyObject_CallObject(func, nullptr);
            if (callfunc != nullptr) {
                std::cout << "Python script executed successfully." << std::endl;
                Py_DECREF(callfunc);
            } else {
                PyErr_Print();
                std::cerr << "Error calling Python function." << std::endl;
            }
            Py_DECREF(func);
        } else {
            std::cerr << "Function 'main' not found in Python script." << std::endl;
            PyErr_Print();
        }
        Py_DECREF(load_module);
    } else {
        PyErr_Print();
        std::cerr << "Failed to load Python module." << std::endl;
    }
    Py_DECREF(load_module);
}


void showHandTestActions() {
    std::cout << "\n1. create ArraySequence" << std::endl;
    std::cout << "2. append item" << std::endl;
    std::cout << "3. insert item" << std::endl;
    std::cout << "4. remove item" << std::endl;
    std::cout << "5. get item" << std::endl;
    std::cout << "6. set item" << std::endl;
    std::cout << "7. get subsequence" << std::endl;
    std::cout << "8. clear" << std::endl;
    std::cout << "9. print sequence" << std::endl;
    std::cout << "10. exit\n" << std::endl;
}


void handTestArraySequence() {
    std::cout << "In this mode you can test ArraySequence only with int items" << std::endl;
    ArraySequence<int> sequence;
    int action = 0;
    while (action != 10) {
        showHandTestActions();
        std::cout << "Select an action: ";
        std::cin >> action;
        switch (action) {
            case 1: {
                sequence = ArraySequence<int>();
                std::cout << "ArraySequence created!" << std::endl;
                break;
            }
            case 2: {
                int item;
                std::cout << "Enter item to append: ";
                std::cin >> item;
                sequence.Append(item);
                std::cout << "Item appended!" << std::endl;
                break;
            }
            case 3: {
                int item, index;
                std::cout << "Enter item to insert: ";
                std::cin >> item;
                std::cout << "Enter index: ";
                std::cin >> index;
                while (index < 0 || index > sequence.GetLength()) {
                    std::cout << "Invalid index. Please enter a number from 0 to " << sequence.GetLength() - 1 << ": ";
                    std::cin >> index;
                }
                sequence.InsertAt(item, index);
                std::cout << "Item inserted!" << std::endl;
                break;
            }
            case 4: {
                int index;
                std::cout << "Enter index: ";
                std::cin >> index;
                while (index < 0 || index >= sequence.GetLength()) {
                    std::cout << "Invalid index. Please enter a number from 0 to " << sequence.GetLength() - 1 << ": ";
                    std::cin >> index;
                }
                int item = sequence.Get(index);
                std::cout << "Item at index " << index << ": " << item << std::endl;
                break;
            }
            case 5: {
                int index;
                std::cout << "Enter index to remove: ";
                std::cin >> index;
                while (index < 0 || index >= sequence.GetLength()) {
                    std::cout << "Invalid index. Please enter a number from 0 to " << sequence.GetLength() - 1 << ": ";
                    std::cin >> index;
                }
                sequence.RemoveAt(index);
                std::cout << "Item removed!" << std::endl;
                break;
            }
            case 6: {
                int startIndex, endIndex;
                std::cout << "Enter start index: ";
                std::cin >> startIndex;
                while (startIndex < 0 || startIndex >= sequence.GetLength()) {
                    std::cout << "Invalid index. Please enter a number from 0 to " << sequence.GetLength() - 1 << ": ";
                    std::cin >> startIndex;
                }
                std::cout << "Enter end index: ";
                std::cin >> endIndex;
                while (endIndex < startIndex || endIndex > sequence.GetLength()){
                    std::cout << "Invalid index. Please enter a number from " << startIndex <<" to " << sequence.GetLength() - 1 << ": ";
                    std::cin >> endIndex;
                }
                ArraySequence<int>* subsequence = sequence.GetSubsequence(startIndex, endIndex);
                std::cout << "Subsequence: ";
                for (int i = 0; i < subsequence->GetLength(); i++) {
                    std::cout << subsequence->Get(i) << " ";
                }
                std::cout << std::endl;
                delete subsequence;
                break;
            }
            case 7: {
                std::cout << "Sequence length: " << sequence.GetLength() << std::endl;
                break;
            }
            case 8: {
                sequence.Clear();
                std::cout << "Sequence cleared!" << std::endl;
                break;
            }
            case 9:
                std::cout << "Sequence: ";
                for (int i = 0; i < sequence.GetLength(); ++i) {
                    std::cout << sequence.Get(i) << " ";
                }
                std::cout << std::endl;
                break;
            case 10:
                std::cout << "Exiting..." << std::endl;
            default:
                std::cout << "Enter a number between 1 and 10" << std::endl;
        }
    }
}


void showActions() {
    std::cout << "\n1. Run tests" << std::endl;
    std::cout << "2. Run performance test" << std::endl;
    std::cout << "3. Show last performance test result" << std::endl;
    std::cout << "4. Start hand testing ArraySequence with SmartPtr" << std::endl;
    std::cout << "5. Exit\n" << std::endl;
}


enum Choice {
    RUN_TESTS = 1,
    RUN_PERFORMANCE_TEST = 2,
    SHOW_LAST_PERFORMANCE_TEST_RESULT = 3,
    START_HAND_TESTING = 4,
    EXIT = 5
};


void runAnyAction(Choice choice) {
    switch (choice) {
        case RUN_TESTS:
            runTests();
            break;
        case RUN_PERFORMANCE_TEST:
            runPerformanceTest();
            showPlot();
            break;
        case SHOW_LAST_PERFORMANCE_TEST_RESULT:
            showPlot();
            break;
        case START_HAND_TESTING:
            handTestArraySequence();
            break;
        default:
            break;
    }
}


void runMenu() {
    int choice = 0;
    while (choice < EXIT) {
        showActions();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "error:( yuo entered not a number..." << std::endl;
            std::cin.clear();
            // Игнорировать оставшийся ввод до конца строки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        while (choice < 1 || choice > 5) {
            std::cout << "Invalid choice. Please enter a number from 1 to 5: ";
            std::cin >> choice;
        }
        runAnyAction(static_cast<Choice>(choice));
    }
    if (is_initialized) {
        Py_Finalize();
        is_initialized = false;
    }
}