#目标文件
SRC    :=  $(shell find . -iname '*.c' -o -iname '*.cpp')

OBJ := $(patsubst %.c,%.o, $(patsubst %.cpp,%.o, $(SRC))) 
#编译选项


#程序名
PROGRAM = test_video_saver_ff


#CC := gcc
#CXX := g++
#AR := ar
#STRIP := strip
CC=
CXX=
AR=
STRIP=
#C/C++代码的宏定义
CFLAG := -DLINUX  -D_GNU_SOURCE -Wall -O2 -fPIC

CXXFLAG := $(CFLAG)

#连接库路径
#LIBPATH += ./lib
#OUTPUT_PATH += ./bin
#LIBPATH=-L../libvideo_saver_ff
LIBPATH=-L/home/huma/winShare/testLink
OUTPUT_PATH=

LDFLAG = -lpthread\
       -lrt\
       -ldl \
	   -lVideoSaver_ff

INC = -I.
INC +=-I./libvideo_saver

X86:CC += gcc
X86:CXX += g++
X86:AR += ar
X86:STRIP += strip
X86:LIBPATH +=
X86:OUTPUT_PATH += ./bin_x86
X86:$(PROGRAM)
		
		
_ARM:CC += arm-none-linux-gnueabi-gcc
_ARM:CXX += arm-none-linux-gnueabi-g++
_ARM:AR += arm-none-linux-gnueabi-ar
_ARM:STRIP += arm-none-linux-gnueabi-strip
_ARM:LIBPATH += ./lib_arm
_ARM:OUTPUT_PATH += ./bin_arm
_ARM:$(PROGRAM)
#编译规则
#all:$(PROGRAM)

#debug version
debug:	CFLAG += -g3
debug:	$(PROGRAM)

#release version
release:$(PROGRAM)

#依赖关系
Q := @
W := -w
#编译规则
.c.o:
	@echo "Compile $@"
	$(Q)$(CC) $(CFLAG) -o $@ -c $< $(INC) $(W)

.cpp.o:
	@echo "Compile $@"
	$(Q)$(CXX) $(CXXFLAG) -o $@ -c $< $(INC) $(W)
	
	
$(PROGRAM):$(OBJ)
	$(Q)$(CXX) -o $(PROGRAM) $(OBJ)  $(LIBPATH)  $(LDFLAG)
#	$(Q)rm *.o
	$(Q)mkdir -p $(OUTPUT_PATH)
	$(Q)cp $@ $(OUTPUT_PATH)/$@

clean:
	$(Q)rm -rf $(PROGRAM) $(OUTPUT_PATH)/$(PROGRAM) $(OBJ) 
