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

int main(int argc, const char * argv[]) {
	// insert code here...
	int count = 0;
	while (true) {
		cout << "[AtlasCL] Message " << count++ << endl;
		cout.flush();
		this_thread::sleep_for(chrono::seconds(2));
	}
	return EXIT_SUCCESS;
}
