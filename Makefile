##############################################################################
# Build global options
# NOTE: Can be overridden externally.
#

# Compiler options here.
ifeq ($(USE_OPT),)
  USE_OPT = -Og -ggdb -fomit-frame-pointer -falign-functions=16
endif

# C specific options here (added to USE_OPT).
ifeq ($(USE_COPT),)
  USE_COPT = 
endif

# C++ specific options here (added to USE_OPT).
ifeq ($(USE_CPPOPT),)
  USE_CPPOPT = -fno-rtti
endif

# Enable this if you want the linker to remove unused code and data.
ifeq ($(USE_LINK_GC),)
  USE_LINK_GC = yes
endif

# Linker extra options here.
ifeq ($(USE_LDOPT),)
  USE_LDOPT = --no-warn-rwx-segments --specs=nano.specs
endif

# Enable this if you want link time optimizations (LTO).
ifeq ($(USE_LTO),)
  USE_LTO = yes
endif

# Enable this if you want to see the full log while compiling.
ifeq ($(USE_VERBOSE_COMPILE),)
  USE_VERBOSE_COMPILE = yes
endif

#
# Build global options
##############################################################################

##############################################################################
# Architecture or project specific options
#

# Enables the use of FPU (no, softfp, hard).
ifeq ($(USE_FPU),)
  USE_FPU = no
endif

# FPU-related options.
ifeq ($(USE_FPU_OPT),)
  USE_FPU_OPT = -mfloat-abi=$(USE_FPU) -mfpu=fpv5-sp-d16
endif

#
# Architecture or project specific options
##############################################################################

##############################################################################
# Project, target, sources and paths
#

# Define project name here
PROJECT = minexam

# Target settings.
MCU  = cortex-m33

# Imported source files and paths.
BUILDDIR := ./build
DEPDIR   := ./.dep

GECKO_SDK = gecko-sdk

# Define linker script file here
# Originall one is for EFR32FG23 with 512k of flash and 64k od RAM
#LDSCRIPT = $(GECKO_SDK)/platform/Device/SiliconLabs/EFR32FG23/Source/GCC/efr32fg23.ld
LDSCRIPT = ld/efr32fg23.ld

# C sources that can be compiled in ARM or THUMB mode depending on the global
# setting.
CSRC = $(GECKO_SDK)/platform/Device/SiliconLabs/EFR32FG23/Source/system_efr32fg23.c \
       $(GECKO_SDK)/platform/Device/SiliconLabs/EFR32FG23/Source/startup_efr32fg23.c \
       src/hal_st_lld.c \
       src/main.c

# C++ sources that can be compiled in ARM or THUMB mode depending on the global
# setting.
CPPSRC = $(ALLCPPSRC)

# List ASM source files here.
ASMSRC = $(ALLASMSRC)

# List ASM with preprocessor source files here.
ASMXSRC = $(ALLXASMSRC)

# Inclusion directories.
INCDIR = $(ALLINC)

# Define C warning options here.
CWARN = -Wall -Wextra -Wundef -Wstrict-prototypes -Wcast-align=strict

# Define C++ warning options here.
CPPWARN = -Wall -Wextra -Wundef

#
# Project, target, sources and paths
##############################################################################

##############################################################################
# Start of user section
#

# List all user C define here, like -D_DEBUG=1
UDEFS = -DEFR32FG23A010F256GM48=1 \
        -USL_TRUSTZONE_SECURE \
        -DSL_TRUSTZONE_NONSECURE

# Define ASM defines here
UADEFS =

# List all user directories here
UINCDIR = $(GECKO_SDK)/platform/CMSIS/Core/Include \
          $(GECKO_SDK)/platform/Device/SiliconLabs/EFR32FG23/Include \
          $(GECKO_SDK)/platform/emlib/inc \
          $(GECKO_SDK)//platform/common/inc

# List the user directory to look for the libraries here
ULIBDIR =

# List all user libraries here
#ULIBS = -lgcc -lm -lc -lnosys
ULIBS =

#
# End of user section
##############################################################################

##############################################################################
# Common rules
#

RULESPATH = mk
include $(RULESPATH)/arm-none-eabi.mk
include $(RULESPATH)/rules.mk

#
# Common rules
##############################################################################

##############################################################################
# Custom rules
#

#
# Custom rules
##############################################################################
