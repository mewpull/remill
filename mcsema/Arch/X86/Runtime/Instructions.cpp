/* Copyright 2015 Peter Goodman (peter@trailofbits.com), all rights reserved. */

#include "mcsema/Arch/Runtime/Types.cpp"

#include "mcsema/Arch/X86/Runtime/State.h"
#include "mcsema/Arch/X86/Runtime/Types.h"

// Define the `PushValue` and `PopValue` helpers.
#include "mcsema/Arch/X86/Semantics/POP.h"
#include "mcsema/Arch/X86/Semantics/PUSH.h"

#include "mcsema/Arch/X86/Semantics/FLAGS.h"
#include "mcsema/Arch/X86/Semantics/BINARY.h"
#include "mcsema/Arch/X86/Semantics/BITBYTE.h"
#include "mcsema/Arch/X86/Semantics/CALL_RET.h"
#include "mcsema/Arch/X86/Semantics/CMOV.h"
#include "mcsema/Arch/X86/Semantics/COND_BR.h"
#include "mcsema/Arch/X86/Semantics/CONVERT.h"
#include "mcsema/Arch/X86/Semantics/DATAXFER.h"
#include "mcsema/Arch/X86/Semantics/INTERRUPT.h"
#include "mcsema/Arch/X86/Semantics/FMA.h"
#include "mcsema/Arch/X86/Semantics/LOGICAL.h"
#include "mcsema/Arch/X86/Semantics/MISC.h"
#include "mcsema/Arch/X86/Semantics/ROTATE.h"
#include "mcsema/Arch/X86/Semantics/SHIFT.h"
#include "mcsema/Arch/X86/Semantics/STRINGOP.h"
#include "mcsema/Arch/X86/Semantics/UNCOND_BR.h"
#include "mcsema/Arch/X86/Semantics/XOP.h"
