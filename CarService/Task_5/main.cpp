#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include "Scheduler.hpp"
#include "../Task_4/Semaphore.hpp"
#include "../Task_2/Services.hpp"

using namespace std;
namespace fs = std::filesystem;

void runGenerator(const fs::path& binDir) {
    fs::path genPath = binDir / "generator.exe";

    if (fs::exists(genPath)) {
        cout << "Launching Generator" << endl;
        string cmd = "\"" + genPath.string() + "\"";
        std::system(cmd.c_str()); //Launches generator.exe
    } else {
        cerr << "Error: Could not find generator executable at " << genPath << endl;
    }
}

int main(int argc, char** argv) {
    // Determine where we are running from to find the generator
    fs::path selfPath = fs::absolute(argv[0]);
    fs::path binDir = selfPath.parent_path();

    // Launch Generator in a background thread
    thread generatorThread([binDir]() {
        runGenerator(binDir);
    });
    generatorThread.detach(); // Allow it to run independently

    cout << "Car Service Application (Async)" << endl;
    cout << "Waiting for generator to produce cars in 'queue' folder..." << endl;

    // 1. Initialize the Semaphore (The Controller)
    Semaphore semaphore;

    // 2. Initialize the Scheduler
    Scheduler scheduler(semaphore, "queue");

    // 3. Start the background tasks
    // Scan every 300ms, Serve every 2 second
    scheduler.start(300, 2000);

    // 4. Main loop: Monitor for completion
    while (true) {
        if (scheduler.isFinished()) {
            cout << "\nFinish signal detected!" << endl;
            
            // Give a moment for final processing
            this_thread::sleep_for(chrono::seconds(2));
            
            // One final serve to ensure queue is empty
            semaphore.serveAll();
            
            break;
        }
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    // 5. Stop scheduler
    scheduler.stop();

    // 6. Print Final Statistics
    cout << "\nFinal Statistics" << endl;
    cout << "Electric Cars Served: " << semaphore.getElectric() << endl;
    cout << "Gas Cars Served:      " << semaphore.getGas() << endl;
    cout << "People Served:        " << semaphore.getPeople() << endl;
    cout << "Robots Served:        " << semaphore.getRobots() << endl;

    return 0;
}
