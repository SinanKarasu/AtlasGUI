
//#include	<fstream>
//#include	"NounsModifiersDimensions.h"
////#include	"Globals.h"
//#include	"TedlDictionary.h"
#include	"Visitors.h"
//
#include	<dlfcn.h>
//#include	<libgen.h>
#include	"astream.h"
//#include	"ExecEnv.h"

#include	"TpsContext.h"

#ifdef HELLO_FROM_XCCONFIG
#warning "HELLO_FROM_XCCONFIG is defined"
#endif


#ifndef ATLASCL

void *deviceDriverLibraryHandle = 0;


TedlSymbolDictionary	deviceEquivalence;

TedlSymbolDictionary	monitorEquivalence;

ExecEnv execEnv;

std::ofstream debugtrace;
astream sout;
class TedlParser;
TedlParser *	TEDL=0;
ASTBase		*	TEDLroot = 0;

extern int G_Equivalence_insantiated;



//int skipStr(std::ifstream & conf,const std::string & skip){
//	std::string x;
//	if(!conf.eof()){
//		if(getConfStr(conf)==skip){
//			return 1;
//		} else {
//			return 0;
//		}
//	}
//	return 0;
//}


int main( int argc, char* argv[] )
{

	evalVisitor	go;

	TpsContext tpsContext;
	
	if ( argc <= 1 ) {
		execEnv.help();
		return 0 ;
	}
	execEnv.ProcessArgs(argc-1, &(argv[1]));
	
	std::string dbd;

	if(execEnv.dbDirectory()){
		dbd=std::string(execEnv.dbDirectory());
		dbd=dbd+"/";
	} else {
		std::string pathcopy(argv[0]);
		//dbd=std::string(dirname(pathcopy));
		dbd = pathcopy.substr(pathcopy.find_last_of("/\\") + 1);

		if(dbd.length()==0){
			dbd=dbd+".";
		}
		dbd=dbd+"/";
		//free(pathcopy);
	}

	//debugtrace.open("debugtrace");

    debugtrace.open("debug.log");
		
    sout.open("output.log");
	
	ParseTpsContext(execEnv.cfFile(),tpsContext);

	if(tpsContext.DeviceDriver !=""){
		deviceDriverLibraryHandle=dlopen(tpsContext.DeviceDriver.c_str(), RTLD_LAZY );
		if(deviceDriverLibraryHandle==0){
			std::cerr << "Device Library Error " << dlerror() << std::endl;
		}
	}
	

	if(tpsContext.AteConfiguration !="NONE"){
		tedlmain(  tpsContext.AteConfiguration ,dbd);
	}
	
	
	//1
	
	for (const auto& module : tpsContext.AdapterConfiguration) {
        if (module != "NONE") {
            tedlmain(module, dbd);
        }
    }
////	StringListIterator slit( tpsContext.AdapterConfiguration );
////	
////	while(++slit){
////		if(slit.key()!="NONE"){
////			tedlmain(  slit.key(),dbd );
////		}
////	}	
	//

// 2
	for (const auto& module : tpsContext.AtlasModules) {
        if (module != "NONE") {
            atlasmain(module, dbd, 1);
        }
    }
////	StringListIterator mlit( tpsContext.AtlasModules);
////	
////	while(++mlit){
////		if(mlit.key()!="NONE"){
////			atlasmain(  mlit.key(),dbd ,1);
////		}
////	}		
////	//

	AST *Root=atlasmain( tpsContext.AtlasTps ,dbd,0 );
	if ( Root ){
		go.Execute( Root, 0 );
		// report:cerr << "Equivalences:" << G_Equivalence_insantiated << endl;
		return 0;
	} else {
		std::cerr << " ***************aborting due to errors*****" << std::endl;
		return 1;
	}
	
	//ModifierDictionaryIterator mit( *modifierDictionary);
	//while(++mit){
	//	//delete mit.key();
	//	delete mit.value();
	//}
	
}

#endif


