


	
#目标文件
SRC    :=  $(shell find . -iname '*.c' -o -iname '*.cpp')

OBJ := $(patsubst %.c,%.o, $(patsubst %.cpp,%.o, $(SRC))) 
#编译选项


#程序名
PROGRAM = libVideoSaver.so
StaticLIb = libVideoSaver.a


CC := gcc
CXX := g++
AR := ar
STRIP := strip
#C/C++代码的宏定义
CFLAG := -DLINUX  -D_GNU_SOURCE -Wno-psabi -O2

CXXFLAG := $(CFLAG)

#连接库路径
LIBPATH := ./lib

OUT_PUT_PATH := ./bin

LDFLAG := -L$(LIBPATH)\
       -lpthread\
       -lrt\
       -ldl

TEMPLIB :=temp.a

	   
#编译规则
all:$(PROGRAM)
static:$(StaticLIb)

INC := -I.\
		-I./libAVI \
		-I./libMp4	\
		-I./utilityTool
		

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
	
	
$(PROGRAM):$(OBJ)
	$(Q)$(CXX) $(LDFLAG) -shared -fPIC  -o $(PROGRAM) $(OBJ) -Wl,-Bstatic -lmp4v2 -Wl,-Bdynamic
#	$(Q)rm *.o
	$(Q)mkdir -p $(OUT_PUT_PATH)
	$(Q)cp $@ $(OUT_PUT_PATH)/$@
	
$(StaticLIb):$(OBJ)
	$(Q)$(AR) -r $(StaticLIb) $(OBJ) $(LIBPATH)/*.o
	$(Q)mkdir -p $(OUT_PUT_PATH)
	$(Q)cp $@ $(OUT_PUT_PATH)/$@

clean:
	$(Q)rm -rf $(PROGRAM) $(LIBPATH)/$(PROGRAM) $(OBJ)  *.o *.bak
	
	
	
	
	
	
	
	
	
