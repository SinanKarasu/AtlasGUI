//
//  main.cpp
//  AtlasCL
//
//  Created by Sinan Karasu on 6/20/25.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

#include "Visitors.h"
#include "astream.h"
#include "TpsContext.h"
#include <dlfcn.h>

TedlSymbolDictionary deviceEquivalence;
TedlSymbolDictionary monitorEquivalence;
ExecEnv execEnv;
std::ofstream debugtrace;
astream sout;
class TedlParser;
TedlParser *TEDL = 0;
ASTBase *TEDLroot = 0;
void *deviceDriverLibraryHandle = 0;
extern int G_Equivalence_insantiated;

// Heartbeat thread
void startHeartbeat(std::atomic<bool>& running) {
	while (running) {
		std::cout << "[Heartbeat] alive" << std::endl;
		std::cout.flush();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::cout << "[Heartbeat] done" << std::endl;
	std::cout.flush();
}

int mainFunction(int argc, char* argv[]) {
	evalVisitor go;
	TpsContext tpsContext;
	
	if (argc <= 1) {
		execEnv.help();
		return 0;
	}
	execEnv.ProcessArgs(argc - 1, &argv[1]);
	
	std::string dbd;
	if (execEnv.dbDirectory()) {
		dbd = std::string(execEnv.dbDirectory()) + "/";
	} else {
		std::string pathcopy(argv[0]);
		dbd = pathcopy.substr(pathcopy.find_last_of("/\\") + 1) + "/";
		if (dbd.length() == 0) dbd = ".";
	}
	
	debugtrace.open("debug.log");
	sout.open("output.log");
	
	ParseTpsContext(execEnv.cfFile(), tpsContext);
	
	if (!tpsContext.DeviceDriver.empty()) {
		deviceDriverLibraryHandle = dlopen(tpsContext.DeviceDriver.c_str(), RTLD_LAZY);
		if (!deviceDriverLibraryHandle) {
			std::cerr << "Device Library Error " << dlerror() << std::endl;
		}
	}
	
	if (tpsContext.AteConfiguration != "NONE")
		tedlmain(tpsContext.AteConfiguration, dbd);
	
	for (const auto& module : tpsContext.AdapterConfiguration)
		if (module != "NONE") tedlmain(module, dbd);
	
	for (const auto& module : tpsContext.AtlasModules)
		if (module != "NONE") atlasmain(module, dbd, 1);
	
	AST *Root = atlasmain(tpsContext.AtlasTps, dbd, 0);
	if (Root) {
		go.Execute(Root, 0);
		return 0;
	} else {
		std::cerr << " ***************aborting due to errors*****" << std::endl;
		return 1;
	}
}

int main(int argc, char* argv[]) {
	std::atomic<bool> heartbeatRunning{true};
	std::thread hb(startHeartbeat, std::ref(heartbeatRunning));
	
	int result = mainFunction(argc, argv);
	
	heartbeatRunning = false;
	hb.join();
	
	return result;
}
