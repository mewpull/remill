all: libremill.a

# === [ libremill.a ] ==========================================================

REMILL_LLVM_VERSION=9.0

REMILL_BUILD_SEMANTICS_DIR_X86=${PWD}/Arch/X86/Runtime
REMILL_BUILD_SEMANTICS_DIR_AARCH64=${PWD}/Arch/AArch64/Runtime
REMILL_INSTALL_SEMANTICS_DIR=/usr/share/remill/${REMILL_LLVM_VERSION}/semantics/

SRC_REMILL=\
	Arch/AArch64/Arch.cpp      \
	Arch/AArch64/Decode.cpp    \
	Arch/AArch64/Extract.cpp   \
	Arch/Arch.cpp              \
	Arch/Instruction.cpp       \
	Arch/Name.cpp              \
	Arch/X86/Arch.cpp          \
	BC/Annotate.cpp            \
	BC/DeadStoreEliminator.cpp \
	BC/IntrinsicTable.cpp      \
	BC/Lifter.cpp              \
	BC/Optimizer.cpp           \
	BC/Util.cpp                \
	OS/Compat.cpp              \
	OS/FileSystem.cpp          \
	OS/OS.cpp                  \

OBJ_REMILL=$(SRC_REMILL:.cpp=.o)

%.o: %.cpp
	clang -c -fPIC -I../ -DREMILL_LLVM_VERSION='"${REMILL_LLVM_VERSION}"' -DREMILL_BUILD_SEMANTICS_DIR_X86='"${REMILL_BUILD_SEMANTICS_DIR_X86}"' -DREMILL_BUILD_SEMANTICS_DIR_AARCH64='"${REMILL_BUILD_SEMANTICS_DIR_AARCH64}"' -DREMILL_INSTALL_SEMANTICS_DIR='"${REMILL_INSTALL_SEMANTICS_DIR}"' -o $@ $<

libremill.a: $(OBJ_REMILL)
	ar rc $@ $^
	ranlib $@

.PHONY: all clean

clean:
	$(RM) -v ${OBJ_REMILL} libremill.a
