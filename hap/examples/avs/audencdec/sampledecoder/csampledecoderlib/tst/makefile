# Makefile for QDSP6 Platform only 

ROOT = ../../../../../..

# Compiler, Linker and Simulator
CC		= qdsp6-gcc
CXX		= qdsp6-g++
LD		= qdsp6-g++
CFLAGS =  -O0 -g -Wall -mv4 "-DCAPI_EXAMPLE_STANDALONE" $(INCLUDES)
LDFLAGS = -mv4
LLIBS   = -lqdsp

# Directory Structure
# Common Sources

# Add your sources here
SRC_DIR +=./ \
		  ../src \
		  ../../SampleDecoderLib/src \

OBJ_DIR = obj

EXE_DIR = ./

# Includes
# Common Includes
INCLUDES = \
			-I$(ROOT)/elite/common/EliteCmnUtils/inc \
			-I$(ROOT)/elite/common/qurt_elite/inc \
			-I$(ROOT)/Audio/drivers/hw/avtimer/hal/common/inc \
			-I$(ROOT)/Audio/drivers/hw/avtimer/avtimer_driver/inc \
			-I$(ROOT)/qurt/install/MMv4/include \
			-I$(ROOT)/qurt/install/MMv4/include/qube \
			-I$(ROOT)/qurt/config/MMv4 \
			-I$(ROOT)/qurt/config/MMv4/include \
			-I$(ROOT)/qurt/config/MMv4/include/qube \
			-I$(ROOT) \
			-I$(ROOT)/corebsp/services/common/inc \
			-I$(ROOT)/corebsp/services/corebsp_utils/src \
			-I$(ROOT)/corebsp/services/diag/inc \
			-I$(ROOT)/api/Core/inc \
			-I$(ROOT)/api/utils \
			-I$(ROOT)/api/Audio/inc

# Add your includes here
INCLUDES += -I./ \
			-I../inc \
			-I../src \
			-I../../SampleDecoderLib/inc \
			-I../tst

EXEC = $(EXE_DIR)/SampleDecoder.exe

# List all Source Files here
CPP_SOURCES_LIST := $(foreach dir,$(SRC_DIR),$(notdir $(wildcard $(dir)/*.cpp)))
C_SOURCES_LIST := $(foreach dir,$(SRC_DIR),$(notdir $(wildcard $(dir)/*.c)))
ASM_SOURCES_LIST := $(foreach dir,$(SRC_DIR),$(notdir $(wildcard $(dir)/*.S)))

SRC_CPP_OBJS   = $(CPP_SOURCES_LIST:%.cpp=$(OBJ_DIR)/%.o)
SRC_C_OBJS   = $(C_SOURCES_LIST:%.c=$(OBJ_DIR)/%.o)
SRC_ASM_OBJS = $(ASM_SOURCES_LIST:%.S=$(OBJ_DIR)/%.o)

VPATH = $(SRC_DIR)

$(EXEC): $(SRC_ASM_OBJS) $(SRC_CPP_OBJS) $(SRC_C_OBJS)
	$(LD) $(LDFLAGS) -o $@ $^ $(LLIBS) 

# Clean up command
clean: 
	rm -rf $(OBJ_DIR)
	rm -f $(EXEC) stats.txt

$(OBJ_DIR)/%.o:%.cpp $(OBJ_DIR)/exists
	$(CXX) $(CFLAGS) "-D__FILENAME__=\"`basename $<`\"" -c -o $(OBJ_DIR)/$(notdir $@) $<

$(OBJ_DIR)/%.o:%.S $(OBJ_DIR)/exists
	$(CXX) $(CFLAGS) "-D__FILENAME__=\"`basename $<`\""  -c -o $(OBJ_DIR)/$(notdir $@) $<

$(OBJ_DIR)/%.o:%.c $(OBJ_DIR)/exists
	$(CC) $(CFLAGS) "-D__FILENAME__=\"`basename $<`\"" -c -o $(OBJ_DIR)/$(notdir $@) $<

$(OBJ_DIR)/exists:
	mkdir -p $(OBJ_DIR)
	touch $(OBJ_DIR)/exists

test:
	qdsp6-sim SampleDecoder.exe -- -i ./vectors/input.raw -o ./vectors/output.raw
	