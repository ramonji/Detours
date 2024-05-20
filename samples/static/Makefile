##############################################################################
##
##  Makefile for Detours Test Programs.
##
##  Microsoft Research Detours Package
##
##  Copyright (c) Microsoft Corporation.  All rights reserved.
##

!include ..\common.mak

LIBS=$(LIBS) kernel32.lib

all: dirs \
    $(BIND)\static.exe \
!IF $(DETOURS_SOURCE_BROWSING)==1
    $(OBJD)\static.bsc
!ENDIF

clean:
    -del *~ 2> nul
    -del $(BIND)\static.* 2> nul
    -rmdir /q /s $(OBJD) 2>nul

realclean: clean
    -rmdir /q /s $(OBJDS) 2>nul

dirs:
    @if not exist $(BIND) mkdir $(BIND) && echo.   Created $(BIND)
    @if not exist $(OBJD) mkdir $(OBJD) && echo.   Created $(OBJD)

$(OBJD)\static.obj : static.cpp

$(BIND)\static.exe : $(OBJD)\static.obj $(DEPS)
    cl $(CFLAGS) /Fe$@ /Fd$(@R).pdb $(OBJD)\static.obj \
        /link $(LINKFLAGS) $(LIBS) /subsystem:console

$(OBJD)\static.bsc : $(OBJD)\static.obj
    bscmake /v /n /o $@ $(OBJD)\static.sbr

##############################################################################

test: $(BIND)\static.exe
    @echo.
    $(BIND)\static.exe
    @echo.

################################################################# End of File.
