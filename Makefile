#
# PCCTS makefile for: atlas
#
# PCCTS release 1.33
# Project: t
# C++ output
# DLG scanner

# The following filenames must be consistent with ANTLR/DLG flags
DEVTOOLS    = ../../DevTools
PCCTS       = $(DEVTOOLS)/pccts
SMCPLUSPLUS = $(DEVTOOLS)/smcplusplus

ANTLR_H     = $(PCCTS)/h
BIN         = $(PCCTS)/bin
ANTLR       = $(BIN)/antlr
DLG         = $(BIN)/dlg
SMC         = $(SMCPLUSPLUS)/smc

PCCTS_SRCS := \
  $(ANTLR_H)/AParser.cpp \
  $(ANTLR_H)/ASTBase.cpp \
  $(ANTLR_H)/ATokenBuffer.cpp \
  $(ANTLR_H)/DLexerBase.cpp \
  $(ANTLR_H)/PCCTSAST.cpp


PCCTS_OBJS := $(patsubst $(ANTLR_H)/%.cpp,build/obj/%.o,$(PCCTS_SRCS))


GRAMMAR	= ./Grammar
GENERATED	= ./Generated
SOURCES = ./Sources

OBJDIR = build/obj

# CCC			= clang++
# 
# CFLAGS = -g -Wall -I. -I$(ANTLR_H) -I$(GENERATED)
# CFLAGS += -IInclude
# 
# LDFLAGS = -lpthread
# 
# CC		= $(CCC)
# CCFLAGS		=  -std=c++20 -Wall -g $(CFLAGS)


# Compiler
CCC = clang++

# Include paths and base flags
CFLAGS = -g -Wall -I. -I$(ANTLR_H) -I$(GENERATED)
CFLAGS += -IInclude

# Linker flags
LDFLAGS = -lpthread

# C++ compilation flags for .cc files
CCFLAGS = -std=c++20 -Wall -g $(CFLAGS)

# C++ compilation flags for .cpp files (suppress unused warnings)
CPPFLAGS = -std=c++20 $(CFLAGS) -g -Wno-unused-parameter -Wno-unused-variable 


#######################Atlas stuff #################

AFLAGS_ATLAS	= -ge -gt -CC -ft AtlasTokens.h -fl AtlasDLG.dlg -k 4  -prc on -mrhoist on -rl 80000 -o $(GENERATED)
DFLAGS_ATLAS	= -C2 -CC -ci -cl AtlasDLG -o $(GENERATED)
GRM_ATLAS	= $(addprefix $(GRAMMAR)/, \
		tokens.g atlas1.g verbs.g atlas2.g expression.g comparison.g \
		)

FSM_FILES := $(wildcard FSM/*.sm)
FSM_BASENAMES := $(notdir $(basename $(FSM_FILES)))

SMC_SPAWN_CC := $(FSM_BASENAMES:%=$(GENERATED)/%.cpp)
SMC_SPAWN_H  := $(FSM_BASENAMES:%=$(GENERATED)/%.h)
SMC_SPAWN_O  := $(FSM_BASENAMES:%=$(OBJDIR)/%.o)


$(GENERATED)/%.cpp $(GENERATED)/%.h: FSM/%.sm
	@echo "Generating from $<"
	$(SMC) -x cpp -o $(GENERATED) $<

# SMC_SPAWN_CC = $(SMC_SPAWN:%=$(GENERATED)/%.cc)
# SMC_SPAWN_H  = $(SMC_SPAWN:%=$(GENERATED)/%.h)
# SMC_SPAWN_O  = $(SMC_SPAWN:%=$(GENERATED)/%.o)



FNAMES	 =		$(addprefix $(GENERATED)/,			\
		verbs				\
		atlas1				\
		atlas2				\
		expression			\
		comparison			\
		AtlasParser			\
		AtlasDLG			\
		tedl	\
		)

FNAMES	 +=		$(addprefix $(GENERATED)/,			\
		TedlParser \
		)


#FNAMES	+=					\
#		$(SMC_SPAWN)

FNAMES	+=	$(addprefix $(SOURCES)/,			\
		ArrayObject			\
		ASTVector			\
		StringVector			\
		DFSContext			\
		Visitors			\
		ActionAST			\
		AtlasAST			\
		AtlasDefinitions		\
		AtlasSupport			\
		AtlasToken			\
		BasicTypeAST			\
		BuiltinFunctionAST		\
		Dictionary			\
		LabelAST			\
		NounsModifiersDimensions	\
		MnemonicsDB			\
		OperatorAST			\
		Scope				\
		SignalActionAST			\
		SignalOperatorAST		\
		SignalTypeAST			\
		EventTypeAST			\
		SignalVerbAST			\
		DataBusVerbAST			\
		ResourceAST			\
		VirtualResourceAST		\
		VirtualDataBusAST		\
		ATEResourceAST			\
		ATEActionAST			\
		ATEFieldTypeAST			\
		GateConnEventAST		\
		astream				\
		InitList			\
		VerbAST				\
		atlasmain			\
		main				\
		Resource			\
		ResourceContextBASE		\
		AnalogResourceContext		\
		DataBusResourceContext		\
		Sensor				\
		SourceLoad			\
		EventMonitor			\
		DataBus				\
		DataBusTypeAST			\
		DataBusActionAST		\
		TimerObject			\
		Signal				\
		getToken			\
		NestedTokenStream		\
		ExecEnv				\
		AtlasBox	\
		)

FNAMES	+=	$(ANTLR_H)/AParser		\
		$(ANTLR_H)/DLexerBase		\
		$(ANTLR_H)/ASTBase		\
		$(ANTLR_H)/PCCTSAST		\
		$(ANTLR_H)/ATokenBuffer

AFLAGS_TEDL	= -CC -gxt -ft AtlasTokens.h -gx -gt -w2 -k 2 -prc on -rl 80000 -o $(GENERATED)

GRM_TEDL	= $(addprefix $(GRAMMAR)/, \
			tokens.g tedl.g \
		)

# 		TedlParser			\


FNAMES	+=	$(addprefix $(SOURCES)/,			\
		Graph				\
		Equivalence			\
		EdgeList			\
		Search				\
		SimulateCircuit			\
		Association			\
		SwitchModel			\
		BusNode				\
		Circuit				\
		CompositeDevice			\
		Contact				\
		ConfigurationModels		\
		AdaptationModels		\
		DeviceModels			\
		ConfigurationModel		\
		AdaptationModel			\
		TPSHardware			\
		DeviceModel			\
		Device				\
		DevicePath			\
		DevicePortNode			\
		TAGContext			\
		Edge				\
		ExceptionTypes			\
		Impedance			\
		InterfaceConnectorNode		\
		AdapterConnectorNode		\
		LoadDevicePortNode		\
		NodeName			\
		PathNode			\
		PathNodeList			\
		PointSourceNode			\
		DeviceReferencePortNode		\
		ResourceList			\
		SensorDevicePortNode		\
		Set				\
		SourceDevicePortNode		\
		UutConnectorNode		\
		SwitchContactNode		\
		VertexDictionary		\
		TedlDictionary			\
		Vertex				\
		VertexStack			\
		VertexList			\
		Wire				\
		TwoTerm				\
		ResistiveEdge			\
		CapacitiveEdge			\
		InductiveEdge			\
		GraphContext			\
		BFS				\
		NodeFunc			\
		EdgeFunc			\
		DebugEnv			\
		)
					
		

FNAMES	+=	$(addprefix $(SOURCES)/,			\
		TedlSupport		\
		tedlmain		\
		TedlSignalVerbAST	\
		TedlSignalVerbVisitor	\
		TedlDataBusTypeAST	\
		TedlExchangeVerbAST	\
		TedlExchangeVerbVisitor	\
		TedlDeviceAST		\
		TedlCompAST	\
		ReverseMap \
		)

FNAMES	+=	$(addprefix $(SOURCES)/,			\
		CodeGenVisitor \
		)
  
# OBJECTS	=	$(FNAMES:%=%.o)	
OBJECTS = $(addprefix $(OBJDIR)/, $(notdir $(FNAMES:=.o)))

OBJECTS := $(sort $(OBJECTS))


################### Generated stuff #############################

ANTLR_ATLAS_SPAWN	= $(addprefix $(GENERATED)/, \
			verbs.cpp	atlas1.cpp	atlas2.cpp	\
			expression.cpp	comparison.cpp	\
			AtlasParser.cpp	AtlasDLG.cpp	AtlasParser.h	AtlasTokens.h	\
			AtlasDLG.h	AtlasDLG.dlg \
)

ANTLR_TEDL_SPAWN	= $(addprefix $(GENERATED)/, \
			tedl.cpp	TedlParser.cpp	TedlParser.h \
)
			
# $(GENERATED):
# 	mkdir -p $@

TARGET = bin/AtlasCL


################### Dependencies ################################
all: build
build: $(TARGET)
install: 
	@echo "📦 Installing (placeholder)..."
# Optional fallback if unknown action is passed
.DEFAULT:
	@echo "⚠️ Unknown action: $@"
	@exit 0

$(TARGET):	$(SMC_SPAWN_O)	$(OBJECTS) | bin
	$(CCC) $(CCFLAGS) -o $(TARGET)  $(SMC_SPAWN_O) $(OBJECTS)  -ldl  -lpthread
	

# $(TARGET): | bin
bin:
	mkdir -p bin
	
$(OBJECTS): $(ANTLR_ATLAS_SPAWN) $(ANTLR_TEDL_SPAWN) $(SMC_SPAWN)

################## Atlas stuff ##################################

$(ANTLR_ATLAS_SPAWN):	$(GRM_ATLAS) 
	$(ANTLR) $(AFLAGS_ATLAS) $(GRM_ATLAS)
	$(DLG) $(DFLAGS_ATLAS) $(GENERATED)/AtlasDLG.dlg

################## Tedl stuff ###################################

$(ANTLR_TEDL_SPAWN):		$(GRM_TEDL)
	$(ANTLR) $(AFLAGS_TEDL) $(GRM_TEDL)

##	$(DLG) $(DFLAGS_TEDL) TedlDLG.dlg

################### *.Dependencies ##############################
##TedlStd.h:	TedlTokens.h

$(SMC_SPAWN_O):	$(SMC_SPAWN_CC)


build/obj/%.o: ../../DevTools/pccts/h/%.cpp
	@mkdir -p $(dir $@)
	$(CCC) $(CCFLAGS) -c $< -o $@

#################################################################

clean:
	-rm -f $(OBJECTS) *.o $(GENERATED)/*.o *.pch core $(ANTLR_ATLAS_SPAWN) $(DLG_ATLAS_SPAWN)
	-rm -f $(ANTLR_TEDL_SPAWN) $(DLG_TEDL_SPAWN)
	-rm -f $(SMC_SPAWN_CC) $(SMC_SPAWN_H)
	-rm -rf Templates.DB ir.out .make.state
	-rm -rf $(GENERATED)/*.cpp
	
scrub: clean
	-rm -f $(TARGET)

print-vars:
	@echo "OBJECTS = $(OBJECTS)"
	@echo "SMC_SPAWN_O = $(SMC_SPAWN_O)"


check-dupes:
	@echo "Checking for duplicate .o files..."
	@echo "$(OBJECTS)" | tr ' ' '\n' | sort | uniq -d

.KEEP_STATE:

.SUFFIXES: .cpp .sm

# .cpp.o:
# 	$(CCC) -c $(CCFLAGS) -o $*.o $<
# 
# .cc.o:
# 	$(CCC) -c $(CCFLAGS) -o $*.o $<
# 

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CCC) -c $(CPPFLAGS) -o $@ $<

$(OBJDIR)/%.o: %.cc | $(OBJDIR)
	$(CCC) -c $(CCFLAGS) -o $@ $<
	
$(OBJDIR)/%.o: $(GENERATED)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CCC) $(CPPFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(GENERATED)/%.cc
	@mkdir -p $(OBJDIR)
	$(CCC) $(CCFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SOURCES)/%.cc
	@mkdir -p $(OBJDIR)
	$(CCC) $(CCFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SOURCES)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CCC) $(CPPFLAGS) -c $< -o $@


	
$(GENERATED):
	mkdir -p $@