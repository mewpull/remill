# Note: since the object files are shared between libraries and since the object
# files are produced only once, but rely on different definitons to enable ISA
# features, the current way to handle this is to build one library at the time.
#
#    make libremill_aarch64be.so -B
#    make libremill_aarch64.so -B
#    make libremill_x86.so -B
#    make libremill_x86_avx.so -B
#    make libremill_x86_avx512.so -B
#    make libremill_amd64.so -B
#    make libremill_amd64_avx.so -B
#    make libremill_amd64_avx512.so -B

AARCH64_TARGETS=\
	libremill_aarch64be.so \
	libremill_aarch64.so   \

X86_TARGETS=\
	libremill_x86.so          \
	libremill_x86_avx.so      \
	libremill_x86_avx512.so   \
	libremill_amd64.so        \
	libremill_amd64_avx.so    \
	libremill_amd64_avx512.so \

all: libremill.a  ${AARCH64_TARGETS} ${X86_TARGETS}

# === [ libremill.a ] ==========================================================

REMILL_LLVM_VERSION=9.0

REMILL_BUILD_SEMANTICS_DIR_X86=${PWD}/Arch/X86/Runtime/
REMILL_BUILD_SEMANTICS_DIR_AARCH64=${PWD}/Arch/AArch64/Runtime/
REMILL_INSTALL_SEMANTICS_DIR=/usr/share/remill/${REMILL_LLVM_VERSION}/semantics/

SRC_REMILL=\
	Arch/AArch64/Arch.cpp                 \
	Arch/AArch64/Decode.cpp               \
	Arch/AArch64/Extract.cpp              \
	Arch/Arch.cpp                         \
	Arch/Instruction.cpp                  \
	Arch/Name.cpp                         \
	Arch/X86/Arch.cpp                     \
	BC/Annotate.cpp                       \
	BC/DeadStoreEliminator.cpp            \
	BC/IntrinsicTable.cpp                 \
	BC/Lifter.cpp                         \
	BC/Optimizer.cpp                      \
	BC/Util.cpp                           \
	OS/Compat.cpp                         \
	OS/FileSystem.cpp                     \
	OS/OS.cpp                             \

OBJ_REMILL=$(SRC_REMILL:.cpp=.o)

%.o: %.cpp
	clang -c -fPIC -I../ -DREMILL_LLVM_VERSION='"${REMILL_LLVM_VERSION}"' -DREMILL_BUILD_SEMANTICS_DIR_X86='"${REMILL_BUILD_SEMANTICS_DIR_X86}"' -DREMILL_BUILD_SEMANTICS_DIR_AARCH64='"${REMILL_BUILD_SEMANTICS_DIR_AARCH64}"' -DREMILL_INSTALL_SEMANTICS_DIR='"${REMILL_INSTALL_SEMANTICS_DIR}"' -o $@ $<

libremill.a: $(OBJ_REMILL)
	ar qc $@ $^
	ranlib $@

# === [ libremill_<ISA>.so ] ===================================================

# --- [ AArch64 ] --------------------------------------------------------------

libremill_aarch64be.so: ADDRESS_SIZE=64
libremill_aarch64be.so: LITTLE_ENDIAN=0

libremill_aarch64.so: ADDRESS_SIZE=64
libremill_aarch64.so: LITTLE_ENDIAN=1

REMILL_AARCH64_DEFINITIONS=-DADDRESS_SIZE=${ADDRESS_SIZE} -DLITTLE_ENDIAN=${LITTLE_ENDIAN}

# * remill/Arch/Runtime/Intrinsics.cpp: included by remill/Arch/<ISA>/Runtime/BasicBlock.cpp
# * remill/Arch/<ISA>/Semantics/*.cpp:  included by remill/Arch/<ISA>/Runtime/Instructions.cpp

SRC_REMILL_AARCH64=\
	Arch/AArch64/Runtime/BasicBlock.cpp   \
	Arch/AArch64/Runtime/Instructions.cpp \

OBJ_REMILL_AARCH64=$(SRC_REMILL_AARCH64:.cpp=.o)

DEPS_REMILL_AARCH64=$(wildcard Arch/AArch64/Semantics/*.cpp)

Arch/AArch64/Runtime/BasicBlock.o: Arch/AArch64/Runtime/BasicBlock.cpp
	clang -c -O0 -g3 -I../ ${REMILL_AARCH64_DEFINITIONS} -o $@ $<

Arch/AArch64/Runtime/Instructions.o: Arch/AArch64/Runtime/Instructions.cpp
	clang -c -O3 -g0 -I../ ${REMILL_AARCH64_DEFINITIONS} -o $@ $<

libremill_aarch64.so libremill_aarch64be.so: ${OBJ_REMILL_AARCH64} ${DEPS_REMILL_AARCH64}
	clang -shared -o $@ ${OBJ_REMILL_AARCH64}

# --- [ X86 ] ------------------------------------------------------------------

libremill_x86.so: ADDRESS_SIZE=32
libremill_x86.so: HAS_FEATURE_AVX=0
libremill_x86.so: HAS_FEATURE_AVX512=0

libremill_x86_avx.so: ADDRESS_SIZE=32
libremill_x86_avx.so: HAS_FEATURE_AVX=1
libremill_x86_avx.so: HAS_FEATURE_AVX512=0

libremill_x86_avx512.so: ADDRESS_SIZE=32
libremill_x86_avx512.so: HAS_FEATURE_AVX=1
libremill_x86_avx512.so: HAS_FEATURE_AVX512=1

libremill_amd64.so: ADDRESS_SIZE=64
libremill_amd64.so: HAS_FEATURE_AVX=0
libremill_amd64.so: HAS_FEATURE_AVX512=0

libremill_amd64_avx.so: ADDRESS_SIZE=64
libremill_amd64_avx.so: HAS_FEATURE_AVX=1
libremill_amd64_avx.so: HAS_FEATURE_AVX512=0

libremill_amd64_avx512.so: ADDRESS_SIZE=64
libremill_amd64_avx512.so: HAS_FEATURE_AVX=1
libremill_amd64_avx512.so: HAS_FEATURE_AVX512=1

REMILL_X86_DEFINITIONS=-DADDRESS_SIZE=${ADDRESS_SIZE} -DHAS_FEATURE_AVX=${HAS_FEATURE_AVX} -DHAS_FEATURE_AVX512=${HAS_FEATURE_AVX512}

# * remill/Arch/Runtime/Intrinsics.cpp: included by remill/Arch/<ISA>/Runtime/BasicBlock.cpp
# * remill/Arch/<ISA>/Semantics/*.cpp:  included by remill/Arch/<ISA>/Runtime/Instructions.cpp

SRC_REMILL_X86=\
	Arch/X86/Runtime/BasicBlock.cpp   \
	Arch/X86/Runtime/Instructions.cpp \

OBJ_REMILL_X86=$(SRC_REMILL_X86:.cpp=.o)

DEPS_REMILL_X86=$(wildcard Arch/X86/Semantics/*.cpp)

Arch/X86/Runtime/BasicBlock.o: Arch/X86/Runtime/BasicBlock.cpp
	clang -c -fPIC -O0 -g3 -I../ ${REMILL_X86_DEFINITIONS} -o $@ $<

Arch/X86/Runtime/Instructions.o: Arch/X86/Runtime/Instructions.cpp
	clang -c -fPIC -O3 -g0 -I../ ${REMILL_X86_DEFINITIONS} -o $@ $<

libremill_x86.so libremill_x86_avx.so libremill_x86_avx512.so libremill_amd64.so libremill_amd64_avx.so libremill_amd64_avx512.so: ${OBJ_REMILL_X86} ${DEPS_REMILL_X86}
	clang -shared -o $@ ${OBJ_REMILL_X86}

# ______________________________________________________________________________

.PHONY: all clean

clean:
	$(RM) -v ${OBJ_REMILL} libremill.a ${AARCH64_TARGETS} ${X86_TARGETS}
