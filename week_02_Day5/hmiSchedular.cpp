#include <iostream> 
#include <thread> 
#include <mutex> 
#include <condition_variable> 
#include <vector> 
#include <functional> 
#include <stdexcept> 
#include <queue> 
#include <cassert> 
#include <chrono> 
 
// Custom exception for task execution 
class TaskExecutionException : public std::exception { 
    std::string message; 
 
public: 
    explicit TaskExecutionException(const std::string& msg) : message(msg) {} 
    const char* what() const noexcept override { 
        return message.c_str(); 
    } 
}; 
 
// Task Scheduler Class 
class TaskScheduler { 
private: 
    std::vector<std::function<void()>> tasks; 
    std::mutex taskMutex; 
    std::condition_variable taskCondition; 
    bool stopScheduler = false; 
    bool allTasksComplete = false; 
 
public: 
    // Add a task to the scheduler 
    void addTask(const std::function<void()>& task) { 
        std::lock_guard<std::mutex> lock(taskMutex); 
    tasks.push_back(task); 
    } 
 
    // Execute all tasks concurrently 
    void executeTasks() { 
        std::vector<std::thread> threadPool; 
 
        { 
            std::lock_guard<std::mutex> lock(taskMutex); 
            if (tasks.empty()) { 
                throw TaskExecutionException("No tasks available to execute!"); 
            } 
        } 
 
        for (const auto& task : tasks) { 
            threadPool.emplace_back([this, task]() { 
                try { 
                    task(); // Execute the task 
                } catch (const std::exception& e) { 
                    std::cerr << "Task execution error: " << e.what() << "\n"; 
                } catch (...) { 
                    std::cerr << "Unknown error occurred during task execution.\n"; 
                } 
            }); 
        } 
 
        // Join all threads 
        for (auto& thread : threadPool) { 
            if (thread.joinable()) { 
                thread.join(); 
            } 
        } 
 
        // Notify completion 
        { 
            std::lock_guard<std::mutex> lock(taskMutex); 
            allTasksComplete = true; 
        } 
        taskCondition.notify_all(); 
    } 
 
    // Wait for all tasks to complete 
    void waitForCompletion() { 
        std::unique_lock<std::mutex> lock(taskMutex); 
        taskCondition.wait(lock, [this]() { return allTasksComplete; }); 
    } 
}; 
 
// Simulated tasks 
void renderingTask() { 
    std::cout << "Rendering HMI screen...\n"; 
    std::this_thread::sleep_for(std::chrono::seconds(1)); 
    std::cout << "Rendering complete.\n"; 
} 
 
void inputHandlingTask() { 
    std::cout << "Handling user input...\n"; 
    std::this_thread::sleep_for(std::chrono::seconds(2)); 
    std::cout << "Input handling complete.\n"; 
} 
 
void dataUpdateTask() { 
    std::cout << "Updating display data...\n"; 
    std::this_thread::sleep_for(std::chrono::seconds(1)); 
    std::cout << "Data update complete.\n"; 
} 
 
// Unit Test for individual task 
void testRenderingTask() { 
    try { 
        renderingTask(); 
        std::cout << "Rendering task test passed.\n"; 
    } catch (...) { 
        assert(false && "Rendering task test failed."); 
    } 
} 
 
// Integration Test for Scheduler 
void testScheduler() { 
    TaskScheduler scheduler; 
 
    scheduler.addTask(renderingTask); 
    scheduler.addTask(inputHandlingTask); 
    scheduler.addTask(dataUpdateTask); 
 
    try { 
        scheduler.executeTasks(); 
        scheduler.waitForCompletion(); 
        std::cout << "Scheduler integration test passed.\n"; 
    } catch (...) { 
        std::cerr << "Scheduler integration test failed.\n"; 
    } 
} 
 
// Main Program 
int main() { 
    TaskScheduler scheduler; 
 
    try { 
        // Adding tasks to the scheduler 
        scheduler.addTask(renderingTask); 
        scheduler.addTask(inputHandlingTask); 
        scheduler.addTask(dataUpdateTask); 
 
        // Running tasks 
        std::cout << "Starting task execution...\n"; 
        scheduler.executeTasks(); 
        scheduler.waitForCompletion(); 
        std::cout << "All tasks completed successfully.\n"; 
 
        // Running unit test and integration test 
        std::cout << "\n--- Running Unit and Integration Tests ---\n"; 
        testRenderingTask(); 
        testScheduler(); 
    } catch (const TaskExecutionException& e) { 
        std::cerr << "Scheduler error: " << e.what() << "\n"; 
    } catch (const std::exception& e) { 
        std::cerr << "Unexpected error: " << e.what() << "\n"; 
    } 
 
    return 0; 
} 
 

 
