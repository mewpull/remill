AARCH64_TARGETS=\
	aarch64be.bc \
	aarch64.bc   \

# Note: since the object files are common to all runtimes and since the object
# files are produced only once, but rely on different definitons to enable ISA
# features, the current way to handle this is to build one runtime at the time.
#
#    make aarch64be.bc -B
#    make aarch64.bc   -B

#all: aarch64be.bc aarch64.bc
all:
	make aarch64be.bc -B
	make aarch64.bc   -B

# --- [ AArch64 ] --------------------------------------------------------------

aarch64be.bc: ADDRESS_SIZE=64
aarch64be.bc: LITTLE_ENDIAN=0

aarch64.bc: ADDRESS_SIZE=64
aarch64.bc: LITTLE_ENDIAN=1

REMILL_AARCH64_DEFINITIONS=-DADDRESS_SIZE=${ADDRESS_SIZE} -DLITTLE_ENDIAN=${LITTLE_ENDIAN}

# * remill/Arch/Runtime/Intrinsics.cpp: included by remill/Arch/<ISA>/Runtime/BasicBlock.cpp
# * remill/Arch/<ISA>/Semantics/*.cpp:  included by remill/Arch/<ISA>/Runtime/Instructions.cpp

SRC_REMILL_AARCH64=\
	BasicBlock.cpp   \
	Instructions.cpp \

LL_REMILL_AARCH64=$(SRC_REMILL_AARCH64:.cpp=.ll)

DEPS_REMILL_AARCH64=$(wildcard ../Semantics/*.cpp)

${AARCH64_TARGETS}: ${LL_REMILL_AARCH64}
	llvm-link -o $@ $^

BasicBlock.ll: BasicBlock.cpp
	clang -c -S -emit-llvm -O0 -g3 -I../../../../ ${REMILL_AARCH64_DEFINITIONS} -o $@ $<

Instructions.ll: Instructions.cpp
	clang -c -S -emit-llvm -O3 -g0 -I../../../../ ${REMILL_AARCH64_DEFINITIONS} -o $@ $<

# ______________________________________________________________________________

.PHONY: all clean

clean:
	$(RM) -v ${AARCH64_TARGETS} ${LL_REMILL_AARCH64}
