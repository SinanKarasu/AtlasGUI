//
//  main.cpp
//  AtlasCL
//
//  Created by Sinan Karasu on 6/20/25.
//

//#include <iostream>
//
//int main(int argc, const char * argv[]) {
//	// insert code here...
//	std::cout << "Hello, World!\n";
//	return EXIT_SUCCESS;
//}


//
//  main.cpp
//  AtlasCL
//
//  Created by Sinan Karasu on 6/13/25.
//


// We'll set up AtlasCL to write messages to a pipe, and have AtlasGUI read and display them.

// Step 1: In AtlasCL/main.cpp
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

//int main(int argc, const char * argv[]) {
//	// insert code here...
//	int count = 0;
//	while (true) {
//		cout << "[AtlasCL] Message " << count++ << endl;
//		cout.flush();
//		this_thread::sleep_for(chrono::seconds(2));
//	}
//	return EXIT_SUCCESS;
//}
//
//
// main.cc — merged version for AtlasCL and GUI heartbeat

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

// Dummy placeholder for actual interpreter logic
void runInterpreter() {
	std::cout << "[AtlasCL] Interpreter is running..." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	std::cout << "[AtlasCL] Interpreter finished." << std::endl;
}

// Heartbeat thread: emits periodic pulses for GUI to detect
void startHeartbeat(std::atomic<bool>& running) {
	while (running) {
		std::cout << "[Heartbeat] alive" << std::endl;
		std::cout.flush();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::cout << "[Heartbeat] done" << std::endl;
	std::cout.flush();
}

int main(int argc, char* argv[]) {
	std::atomic<bool> heartbeatRunning{true};
	
	// Launch heartbeat thread
	std::thread hb(startHeartbeat, std::ref(heartbeatRunning));
	
	// Run main interpreter logic
	runInterpreter();
	
	// Stop heartbeat and join
	heartbeatRunning = false;
	hb.join();
	
	return 0;
}
