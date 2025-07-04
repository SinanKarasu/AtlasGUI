//
//  TpsContext.cc
//  AtlasCL
//
//  Created by Sinan Karasu on 7/3/25.
//

#include "TpsContext.h"

extern TedlSymbolDictionary	deviceEquivalence;

extern TedlSymbolDictionary	monitorEquivalence;

extern ExecEnv execEnv;




std::string getConfStr(std::ifstream & conf){
	std::string x;
	if(!conf.eof()){
		conf >> x;
		return x;
	} else {
		return "";
	}
}


std::string getQuotedConfStr(std::ifstream & conf){
	std::string x;
	char ch;
	
	while(!conf.eof() && conf.peek()==' ')conf.get(ch);
	if(!conf.eof() && conf.peek()=='\''){
		conf.get(ch);x+=ch;
		while(!conf.eof() && conf.get(ch)){
			x+=ch;
			if(ch=='\''){
				//cout << "GOT " << x << endl;
				return x;
			}
		}
	}
	return "";
}


int skipStr(std::ifstream & conf, const std::string & skip) {
	return !conf.eof() && getConfStr(conf) == skip;
}

int ParseTpsContext(std::string contextFile,TpsContext & tpsContext)
{
	std::ifstream conf(contextFile);
	
	if(!conf){
		std::cerr << "File:" << contextFile << " Not found " << std::endl;
		exit(1);
	}
	
	//int LineNo=1;
	std::string token;
	
	while((token=getConfStr(conf))!="") {
		if(token=="ATE"){
			if(getConfStr(conf)=="CONFIGURATION"){
				skipStr(conf,":");
				tpsContext.AteConfiguration=getConfStr(conf);
			} else {
				std::cerr << "ATE CONFIGURATION expected" << std::endl;
				exit(1);
			}
		} else if(token=="ADAPTER"){
			if(getConfStr(conf)=="CONFIGURATION"){
				skipStr(conf,":");
				tpsContext.AdapterConfiguration.push_back(getConfStr(conf));
			} else {
				std::cerr << "ADAPTER CONFIGURATION expected" << std::endl;
				exit(1);
			}
		} else if(token=="DRIVER"){
			if(getConfStr(conf)=="LIBRARY"){
				skipStr(conf,":");
				tpsContext.DeviceDriver=getConfStr(conf);
			} else {
				std::cerr << "DRIVER LIBRARY expected" << std::endl;
				exit(1);
			}
		} else if(token=="UUT"){
			if(getConfStr(conf)=="P/N"){
				skipStr(conf,":");
				tpsContext.UutPartNo=getConfStr(conf);
			} else {
				std::cerr << "UUT P/N expected" << std::endl;
				exit(1);
			}
		} else if(token=="ATLAS"){
			std::string name;
			if((name=getConfStr(conf))=="TPS"){
				skipStr(conf,":");
				tpsContext.AtlasTps=getConfStr(conf);
			} else if(name=="MODULE"){
				skipStr(conf,":");
				tpsContext.AtlasModules.push_back(getConfStr(conf));
			} else {
				std::cerr << "ATLAS TPS or MODULE expected" << std::endl;
				exit(1);
			}
		} else if(token=="DEVICE"){
			std::string virt_dev=getQuotedConfStr(conf);
			skipStr(conf,"=");
			std::string real_dev=getConfStr(conf);
			
			deviceEquivalence[virt_dev] = new DeviceEquivalence(real_dev);
		} else if(token=="EVENT"){
			skipStr(conf,"MONITOR");
			std::string virt_mon=getQuotedConfStr(conf);
			skipStr(conf,"=");
			std::string real_dev=getConfStr(conf);
			std::string real_cap=getConfStr(conf);
			deviceEquivalence[virt_mon] = new DeviceEquivalence(real_dev,real_cap);
			monitorEquivalence[virt_mon] = new DeviceEquivalence(real_dev,real_cap);
		}
	}
	return 1;
}


int tedlmain(  std::string model ,const std::string & dbd);

AST *
atlasmain( std::string  v ,const std::string & dbd,int mode);

extern void * deviceDriverLibraryHandle;
