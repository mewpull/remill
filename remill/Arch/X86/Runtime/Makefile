X86_TARGETS=\
	x86.bc          \
	x86_avx.bc      \
	x86_avx512.bc   \
	amd64.bc        \
	amd64_avx.bc    \
	amd64_avx512.bc \

# Note: since the object files are common to all runtimes and since the object
# files are produced only once, but rely on different definitons to enable ISA
# features, the current way to handle this is to build one runtime at the time.
#
#    make x86.bc -B
#    make x86_avx.bc -B
#    make x86_avx512.bc -B
#    make amd64.bc -B
#    make amd64_avx.bc -B
#    make amd64_avx512.bc -B

#all: x86.bc x86_avx.bc x86_avx512.bc amd64.bc amd64_avx.bc amd64_avx512.bc
all:
	make x86.bc          -B
	make x86_avx.bc      -B
	make x86_avx512.bc   -B
	make amd64.bc        -B
	make amd64_avx.bc    -B
	make amd64_avx512.bc -B

# --- [ X86 ] ------------------------------------------------------------------

x86.bc: ADDRESS_SIZE=32
x86.bc: HAS_FEATURE_AVX=0
x86.bc: HAS_FEATURE_AVX512=0

x86_avx.bc: ADDRESS_SIZE=32
x86_avx.bc: HAS_FEATURE_AVX=1
x86_avx.bc: HAS_FEATURE_AVX512=0

x86_avx512.bc: ADDRESS_SIZE=32
x86_avx512.bc: HAS_FEATURE_AVX=1
x86_avx512.bc: HAS_FEATURE_AVX512=1

amd64.bc: ADDRESS_SIZE=64
amd64.bc: HAS_FEATURE_AVX=0
amd64.bc: HAS_FEATURE_AVX512=0

amd64_avx.bc: ADDRESS_SIZE=64
amd64_avx.bc: HAS_FEATURE_AVX=1
amd64_avx.bc: HAS_FEATURE_AVX512=0

amd64_avx512.bc: ADDRESS_SIZE=64
amd64_avx512.bc: HAS_FEATURE_AVX=1
amd64_avx512.bc: HAS_FEATURE_AVX512=1

REMILL_X86_DEFINITIONS=-DADDRESS_SIZE=${ADDRESS_SIZE} -DHAS_FEATURE_AVX=${HAS_FEATURE_AVX} -DHAS_FEATURE_AVX512=${HAS_FEATURE_AVX512}

# * remill/Arch/Runtime/Intrinsics.cpp: included by remill/Arch/<ISA>/Runtime/BasicBlock.cpp
# * remill/Arch/<ISA>/Semantics/*.cpp:  included by remill/Arch/<ISA>/Runtime/Instructions.cpp

SRC_REMILL_X86=\
	BasicBlock.cpp   \
	Instructions.cpp \

LL_REMILL_X86=$(SRC_REMILL_X86:.cpp=.ll)

DEPS_REMILL_X86=$(wildcard ../Semantics/*.cpp)

${X86_TARGETS}: ${LL_REMILL_X86}
	llvm-link -o $@ $^

BasicBlock.ll: BasicBlock.cpp
	clang -c -S -emit-llvm -O0 -g3 -I../../../../ ${REMILL_X86_DEFINITIONS} -o $@ $<

Instructions.ll: Instructions.cpp
	clang -c -S -emit-llvm -O3 -g0 -I../../../../ ${REMILL_X86_DEFINITIONS} -o $@ $<

# ______________________________________________________________________________

.PHONY: all clean

clean:
	$(RM) -v ${X86_TARGETS} ${LL_REMILL_X86}
