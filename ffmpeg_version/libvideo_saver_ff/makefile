


	
#目标文件
SRC    :=  $(shell find . -iname '*.c' -o -iname '*.cpp')

OBJ := $(patsubst %.c,%.o, $(patsubst %.cpp,%.o, $(SRC))) 
#编译选项

MAJOR_VERSION = 1
MIDDLE_VERSION = 0
MINOR_VERSION = 1

#程序名
PROGRAM = libVideoSaver_ff.so
SO_NAME = $(PROGRAM).$(MAJOR_VERSION).$(MIDDLE_VERSION)
REAL_NAME =$(SO_NAME).$(MINOR_VERSION)
StaticLIb = libVideoSaver_ff.a


CC := gcc
CXX := g++
AR := ar
STRIP := strip
#C/C++代码的宏定义
CFLAG := -DLINUX -D_GNU_SOURCE -Wall -Wno-psabi -O2 -std=gnu++0x

CXXFLAG := $(CFLAG)

#连接库路径
LIBPATH =

OUT_PUT_PATH =

LDFLAG =

TEMPLIB :=temp.a

	   
#编译规则
X86:LIBPATH += /home/huma/winShare/ffmpeg-4.2.4/ffmpeg-4.2.4/build/lib
X86:OUT_PUT_PATH+= ./bin_x86
X86:$(REAL_NAME)
#X86:$(StaticLIb)

X64:LIBPATH += ./libFFmpeg/lib_x64/static
X64:OUT_PUT_PATH+= ./bin_x64
X64:$(PROGRAM)
#X64:$(StaticLIb)

all:$(PROGRAM)
static:$(StaticLIb)

INC := -I.\
	-I./libFFmpeg/include

LDFLAG += -L$(LIBPATH)\
	-lpthread \
	-lrt\
	-ldl \
	-lx264 \
	-lz \
	-llzma \
	-lavcodec \
	-lavformat \
	-lavutil \
	-lswresample
	
	# -Wl,--whole-archive \
	# -lavcodec \
	# -lavformat \
	# -lavutil \
	# -lswresample \
	# -lx264 \
	# -lz \
	# -llzma \
	# -Wl,--no-whole-archive

	# -Wl,-Bstatic \
	# -lavcodec \
	# -lavformat \
	# -lavutil \
	# -Wl,-Bdynamic

#依赖关系
Q := @
W := -w
#编译规则
.c.o:
	@echo "Compile $@"
	$(Q)$(CC) $(CFLAG) -fPIC -o $@ -c $< $(INC) $(W)

.cpp.o:
	@echo "Compile $@"
	$(Q)$(CXX) $(CXXFLAG) -fPIC -o $@ -c $< $(INC) $(W) 
	
	
$(REAL_NAME):$(OBJ)
	$(Q)$(CXX) -shared -Wl,-soname,$(SO_NAME) $(OBJ) -o $(REAL_NAME) $(LDFLAG)
#	$(Q)rm *.o
	$(Q)mkdir -p $(OUT_PUT_PATH)
	$(Q)cp $@ $(OUT_PUT_PATH)/$@
	
$(StaticLIb):$(OBJ)
	$(Q)$(AR) -r $(StaticLIb) $(OBJ)
	$(Q)mkdir -p $(OUT_PUT_PATH)
	$(Q)cp $@ $(OUT_PUT_PATH)/$@

clean:
	$(Q)rm -rf $(REAL_NAME) $(LIBPATH)/$(REAL_NAME) $(OBJ)  *.o *.bak
	
	
	
	
	
	
	
	
	
