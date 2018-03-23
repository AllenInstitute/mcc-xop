#	Copyright 2017 WaveMetrics, Inc.

#	Permission is hereby granted, free of charge, to any person obtaining a copy of this software
#	and associated documentation files (the "Software"), to deal in the Software without restriction,
#	including without limitation the rights to use, copy, modify, merge, publish, distribute,
#	sublicense, and/or sell copies of the Software, and to permit persons to whom the Software
#	is furnished to do so, subject to the following conditions:

#	The above copyright notice and this permission notice shall be included
#	in all copies or substantial portions of the Software.

#	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
#	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
#	PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
#	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
#	CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
#	OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

# This XOP does *not* use Qt.
#### Architecture related stuff (32 or 64-bit detection)
contains(QMAKE_TARGET.arch,x86_64) {
	ARCH_IS_64_BIT = 1
}
else {
	contains(QMAKE_HOST.arch, x86_64): {
		# Due to https://bugreports.qt-project.org/browse/QTBUG-22686,
		# when executed from the command line (such as on the buildbot),
		# a 64-bit version of qmake has QMAKE_TARGET.arch=x86
		# so the build will be 32-bit when it should be
		# 64 bit. Therefore we add this additional test.
		# 64 bit build:
		ARCH_IS_64_BIT = 1
	}
	else {
		ARCH_IS_64_BIT = 0
	}
}

CONFIG -= qt

DESTDIR = $$quote($$PWD/win)

greaterThan(ARCH_IS_64_BIT, 0) {
	#64 bit
	PLATFORM_DIR = win64
}
else {
	#32 bit
	PLATFORM_DIR = win32
}

DESTDIR = $$quote(../win/$${PLATFORM_DIR})

# Define the name of the XOP. The name is used below to
# set the value of TARGET as well as other variables.
# For example, if XOP_NAME=Test, the actual XOP
# file will be named Test.xop for a 32-bit build
# and Test-64.xop for a 64-bit build.
# XOP_NAME should not contain spaces!!!!
XOP_NAME = MultiClamp700xCommander

# set this to the location of the "XOPSupport" folder
XOPSUPPORT_PATH = "$$quote($$PWD/../XOPSupport)"

INCLUDEPATH += $$quote($$PWD/.)
INCLUDEPATH += $$quote($$PWD/src)
INCLUDEPATH += $$quote($$PWD/src/AxMultiClampMsg_SDK)


# all source files to compile
SOURCES += src/MultiClamp700xCommander.cpp
SOURCES += src/MultiClamp700xCommander_Functions.cpp
SOURCES += src/MultiClamp700xCommander_Operations.cpp


# all header files to compile
HEADERS += src/MultiClamp700xCommander.h
HEADERS += src/MultiClamp700xCommander_Functions.h
HEADERS += src/MultiClamp700xCommander_Operations.h
HEADERS += src/AxMultiClampMsg_SDK/AxMultiClampMsg.h

# NOTE: This XOP is Windows only.
HEADERS += src/resource.h

# Windows XOP resource file (*not* Qt resources). Include the extension.
WIN_RESOURCE = src/MultiClamp700xCommander.rc
WIN_CUSTOM_RESOURCE = src/MultiClamp700xCommanderWinCustom.rc
OTHER_FILES += $${WIN_RESOURCE}
OTHER_FILES += $${WIN_CUSTOM_RESOURCE}

# These definitions indicate that the XOP supports long wave names.
# RC_DEFINES += XOP_LONG_NAMES_AND_PATHS=1	# For the resource compiler (windows only)
# DEFINES += XOP_LONG_NAMES_AND_PATHS=1		# For the C/C++ compiler.


#--------------------------------------------------------------------------
#
# Everything below this line should not need to be modified (eventually...)
#
#--------------------------------------------------------------------------

TEMPLATE = lib

# #defines
DEFINES += WITH_IGOR HAVE_INLINE

CONFIG += plugin

DEFINES -= UNICODE		# Qt defines this by default, but we want MBCS instead of UNICODE
DEFINES += _MBCS
DEFINES += _CRT_SECURE_NO_WARNINGS
DEFINES += _CRT_SECURE_NO_DEPRECATE
DEFINES += _WINDOWS
DEFINES += _USRDLL
DEFINES += _WINDLL



INCLUDEPATH += $${XOPSUPPORT_PATH}

##################
# Dependency paths =================
##################
DEPENDPATH += .
# Moved DEPENDPATH to after INCLUDEPATH so that the full contents
# of INCLUDEPATH can be added to DEPENDPATH. If we don't do this,
# changes to a header file in one directory won't trigger a recompile
# of files that include that header which live in another directory.
# This often leads to crashes that are extremely difficult to track
# down.
# See http://lists.trolltech.com/qt-interest/2006-03/thread00323-0.html for a bit
# more information on this.
DEPENDPATH += $${INCLUDEPATH}

# Name of the XOP (without extension)
TARGET = $${XOP_NAME}
TARGET_EXT = .xop

# Compiler related
# Set various flags to match VC settings of
# projects that ship with the XOP toolkit.

# Default calling convention
QMAKE_CFLAGS += -Gd
QMAKE_CXXFLAGS += -Gd

# Use Multi-Threaded runtime library.
# QMAKE_CFLAGS_DEBUG += /MTd
# QMAKE_CXXFLAGS_DEBUG += /MTd
# QMAKE_CFLAGS_DEBUG -= -MDd
# QMAKE_CXXFLAGS_DEBUG -= -MDd
#
# QMAKE_CFLAGS_RELEASE += /MT
# QMAKE_CXXFLAGS_RELEASE += /MT
# QMAKE_CFLAGS_RELEASE -= -MD
# QMAKE_CXXFLAGS_RELEASE -= -MD

QMAKE_CFLAGS_RELEASE += /MP /Zi

# Linker flags
QMAKE_LFLAGS_DEBUG += /NODEFAULTLIB:libcmt	# Using this flag in release mode results in lots of linker errors.
QMAKE_LFLAGS += /LARGEADDRESSAWARE	# XOP Toolkit documentation says to add this
QMAKE_LFLAGS += /DYNAMICBASE:NO

# External libraries
QMAKE_LIBDIR += $${XOPSUPPORT_PATH}
QMAKE_LIBDIR += $${XOPSUPPORT_PATH}/VC

greaterThan(ARCH_IS_64_BIT, 0) {
    # Name of the XOP (without extension)
    TARGET = $${XOP_NAME}64
    LIBS += -lIGOR64
}
else {
    # Name of the XOP (without extension)
    TARGET = $${XOP_NAME}
    LIBS += -lIGOR
}

LIBS += version.lib		# Required by XOP toolkit.


# When you don't use Qt, you need to manually specify to link
# against these libraries.
LIBS += kernel32.lib
LIBS += user32.lib
LIBS += gdi32.lib
LIBS += winspool.lib
LIBS += comdlg32.lib
LIBS += advapi32.lib
LIBS += shell32.lib
LIBS += ole32.lib
LIBS += oleaut32.lib
LIBS += uuid.lib
LIBS += odbc32.lib
LIBS += odbccp32.lib


# Compile the resource file as well.
RC_INCLUDEPATH += $$XOPSUPPORT_PATH
RC_INCLUDEPATH += $$quote($$PWD/src)
RC_FILE += $${WIN_RESOURCE}
