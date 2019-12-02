# Note: since the object files are shared between libraries and since the object
# files are produced only once, but rely on different definitons to enable ISA
# features, the current way to handle this is to build one library at the time.
#
#    make libremill.a
#    make libremill_aarch64be.a -B
#    make libremill_aarch64.a -B
#    make libremill_x86.a -B
#    make libremill_x86_avx.a -B
#    make libremill_x86_avx512.a -B
#    make libremill_amd64.a -B
#    make libremill_amd64_avx.a -B
#    make libremill_amd64_avx512.a -B

AARCH64_TARGETS=\
	libremill_aarch64be.a \
	libremill_aarch64.a   \

X86_TARGETS=\
	libremill_x86.a          \
	libremill_x86_avx.a      \
	libremill_x86_avx512.a   \
	libremill_amd64.a        \
	libremill_amd64_avx.a    \
	libremill_amd64_avx512.a \

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

# === [ libremill_<ISA>.a ] ====================================================

# --- [ AArch64 ] --------------------------------------------------------------

libremill_aarch64be.a: ADDRESS_SIZE=64
libremill_aarch64be.a: LITTLE_ENDIAN=0

libremill_aarch64.a: ADDRESS_SIZE=64
libremill_aarch64.a: LITTLE_ENDIAN=1

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

libremill_aarch64.a libremill_aarch64be.a: ${OBJ_REMILL_AARCH64} ${DEPS_REMILL_AARCH64}
	ar qc $@ ${OBJ_REMILL_AARCH64}
	ranlib $@

#clang -shared -o $@ ${OBJ_REMILL_AARCH64}
#-L./ -lremill

# --- [ X86 ] ------------------------------------------------------------------

libremill_x86.a: ADDRESS_SIZE=32
libremill_x86.a: HAS_FEATURE_AVX=0
libremill_x86.a: HAS_FEATURE_AVX512=0

libremill_x86_avx.a: ADDRESS_SIZE=32
libremill_x86_avx.a: HAS_FEATURE_AVX=1
libremill_x86_avx.a: HAS_FEATURE_AVX512=0

libremill_x86_avx512.a: ADDRESS_SIZE=32
libremill_x86_avx512.a: HAS_FEATURE_AVX=1
libremill_x86_avx512.a: HAS_FEATURE_AVX512=1

libremill_amd64.a: ADDRESS_SIZE=64
libremill_amd64.a: HAS_FEATURE_AVX=0
libremill_amd64.a: HAS_FEATURE_AVX512=0

libremill_amd64_avx.a: ADDRESS_SIZE=64
libremill_amd64_avx.a: HAS_FEATURE_AVX=1
libremill_amd64_avx.a: HAS_FEATURE_AVX512=0

libremill_amd64_avx512.a: ADDRESS_SIZE=64
libremill_amd64_avx512.a: HAS_FEATURE_AVX=1
libremill_amd64_avx512.a: HAS_FEATURE_AVX512=1

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

libremill_x86.a libremill_x86_avx.a libremill_x86_avx512.a libremill_amd64.a libremill_amd64_avx.a libremill_amd64_avx512.a: ${OBJ_REMILL_X86} ${DEPS_REMILL_X86}
	ar qc $@ ${OBJ_REMILL_X86}
	ranlib $@

#clang -shared -o $@ ${OBJ_REMILL_X86}
#-L./ -lremill

# ______________________________________________________________________________

.PHONY: all clean

clean:
	$(RM) -v ${OBJ_REMILL} libremill.a ${AARCH64_TARGETS} ${X86_TARGETS}
