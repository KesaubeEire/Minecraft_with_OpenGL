# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.12.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.12.3/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/w/CLionProjects/MineCraft_OpenGL_Version

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/w/CLionProjects/MineCraft_OpenGL_Version

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/local/Cellar/cmake/3.12.3/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/local/Cellar/cmake/3.12.3/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local/fast

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/local/Cellar/cmake/3.12.3/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/local/Cellar/cmake/3.12.3/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/local/Cellar/cmake/3.12.3/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/local/Cellar/cmake/3.12.3/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components

.PHONY : list_install_components/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/local/Cellar/cmake/3.12.3/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/local/Cellar/cmake/3.12.3/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/w/CLionProjects/MineCraft_OpenGL_Version/CMakeFiles /Users/w/CLionProjects/MineCraft_OpenGL_Version/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/w/CLionProjects/MineCraft_OpenGL_Version/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named L_7_2_RenderText

# Build rule for target.
L_7_2_RenderText: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 L_7_2_RenderText
.PHONY : L_7_2_RenderText

# fast build rule for target.
L_7_2_RenderText/fast:
	$(MAKE) -f CMakeFiles/L_7_2_RenderText.dir/build.make CMakeFiles/L_7_2_RenderText.dir/build
.PHONY : L_7_2_RenderText/fast

#=============================================================================
# Target rules for targets named MCOG_001

# Build rule for target.
MCOG_001: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 MCOG_001
.PHONY : MCOG_001

# fast build rule for target.
MCOG_001/fast:
	$(MAKE) -f CMakeFiles/MCOG_001.dir/build.make CMakeFiles/MCOG_001.dir/build
.PHONY : MCOG_001/fast

#=============================================================================
# Target rules for targets named uninstall

# Build rule for target.
uninstall: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 uninstall
.PHONY : uninstall

# fast build rule for target.
uninstall/fast:
	$(MAKE) -f dependencies/GLFW/CMakeFiles/uninstall.dir/build.make dependencies/GLFW/CMakeFiles/uninstall.dir/build
.PHONY : uninstall/fast

#=============================================================================
# Target rules for targets named glfw

# Build rule for target.
glfw: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 glfw
.PHONY : glfw

# fast build rule for target.
glfw/fast:
	$(MAKE) -f dependencies/GLFW/src/CMakeFiles/glfw.dir/build.make dependencies/GLFW/src/CMakeFiles/glfw.dir/build
.PHONY : glfw/fast

GLAD/src/glad.o: GLAD/src/glad.c.o

.PHONY : GLAD/src/glad.o

# target to build an object file
GLAD/src/glad.c.o:
	$(MAKE) -f CMakeFiles/L_7_2_RenderText.dir/build.make CMakeFiles/L_7_2_RenderText.dir/GLAD/src/glad.c.o
	$(MAKE) -f CMakeFiles/MCOG_001.dir/build.make CMakeFiles/MCOG_001.dir/GLAD/src/glad.c.o
.PHONY : GLAD/src/glad.c.o

GLAD/src/glad.i: GLAD/src/glad.c.i

.PHONY : GLAD/src/glad.i

# target to preprocess a source file
GLAD/src/glad.c.i:
	$(MAKE) -f CMakeFiles/L_7_2_RenderText.dir/build.make CMakeFiles/L_7_2_RenderText.dir/GLAD/src/glad.c.i
	$(MAKE) -f CMakeFiles/MCOG_001.dir/build.make CMakeFiles/MCOG_001.dir/GLAD/src/glad.c.i
.PHONY : GLAD/src/glad.c.i

GLAD/src/glad.s: GLAD/src/glad.c.s

.PHONY : GLAD/src/glad.s

# target to generate assembly for a file
GLAD/src/glad.c.s:
	$(MAKE) -f CMakeFiles/L_7_2_RenderText.dir/build.make CMakeFiles/L_7_2_RenderText.dir/GLAD/src/glad.c.s
	$(MAKE) -f CMakeFiles/MCOG_001.dir/build.make CMakeFiles/MCOG_001.dir/GLAD/src/glad.c.s
.PHONY : GLAD/src/glad.c.s

MC_Src/BaseStage.o: MC_Src/BaseStage.cpp.o

.PHONY : MC_Src/BaseStage.o

# target to build an object file
MC_Src/BaseStage.cpp.o:
	$(MAKE) -f CMakeFiles/MCOG_001.dir/build.make CMakeFiles/MCOG_001.dir/MC_Src/BaseStage.cpp.o
.PHONY : MC_Src/BaseStage.cpp.o

MC_Src/BaseStage.i: MC_Src/BaseStage.cpp.i

.PHONY : MC_Src/BaseStage.i

# target to preprocess a source file
MC_Src/BaseStage.cpp.i:
	$(MAKE) -f CMakeFiles/MCOG_001.dir/build.make CMakeFiles/MCOG_001.dir/MC_Src/BaseStage.cpp.i
.PHONY : MC_Src/BaseStage.cpp.i

MC_Src/BaseStage.s: MC_Src/BaseStage.cpp.s

.PHONY : MC_Src/BaseStage.s

# target to generate assembly for a file
MC_Src/BaseStage.cpp.s:
	$(MAKE) -f CMakeFiles/MCOG_001.dir/build.make CMakeFiles/MCOG_001.dir/MC_Src/BaseStage.cpp.s
.PHONY : MC_Src/BaseStage.cpp.s

OldRef/L_7_2_RenderingText.o: OldRef/L_7_2_RenderingText.cpp.o

.PHONY : OldRef/L_7_2_RenderingText.o

# target to build an object file
OldRef/L_7_2_RenderingText.cpp.o:
	$(MAKE) -f CMakeFiles/L_7_2_RenderText.dir/build.make CMakeFiles/L_7_2_RenderText.dir/OldRef/L_7_2_RenderingText.cpp.o
.PHONY : OldRef/L_7_2_RenderingText.cpp.o

OldRef/L_7_2_RenderingText.i: OldRef/L_7_2_RenderingText.cpp.i

.PHONY : OldRef/L_7_2_RenderingText.i

# target to preprocess a source file
OldRef/L_7_2_RenderingText.cpp.i:
	$(MAKE) -f CMakeFiles/L_7_2_RenderText.dir/build.make CMakeFiles/L_7_2_RenderText.dir/OldRef/L_7_2_RenderingText.cpp.i
.PHONY : OldRef/L_7_2_RenderingText.cpp.i

OldRef/L_7_2_RenderingText.s: OldRef/L_7_2_RenderingText.cpp.s

.PHONY : OldRef/L_7_2_RenderingText.s

# target to generate assembly for a file
OldRef/L_7_2_RenderingText.cpp.s:
	$(MAKE) -f CMakeFiles/L_7_2_RenderText.dir/build.make CMakeFiles/L_7_2_RenderText.dir/OldRef/L_7_2_RenderingText.cpp.s
.PHONY : OldRef/L_7_2_RenderingText.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... install/local"
	@echo "... install/strip"
	@echo "... install"
	@echo "... list_install_components"
	@echo "... L_7_2_RenderText"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... MCOG_001"
	@echo "... uninstall"
	@echo "... glfw"
	@echo "... GLAD/src/glad.o"
	@echo "... GLAD/src/glad.i"
	@echo "... GLAD/src/glad.s"
	@echo "... MC_Src/BaseStage.o"
	@echo "... MC_Src/BaseStage.i"
	@echo "... MC_Src/BaseStage.s"
	@echo "... OldRef/L_7_2_RenderingText.o"
	@echo "... OldRef/L_7_2_RenderingText.i"
	@echo "... OldRef/L_7_2_RenderingText.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

