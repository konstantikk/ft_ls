# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /home/professor/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7660.37/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/professor/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7660.37/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/professor/ft_ls

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/professor/ft_ls/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ft_ls.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ft_ls.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ft_ls.dir/flags.make

CMakeFiles/ft_ls.dir/ft_ls_v1/src/main.c.o: CMakeFiles/ft_ls.dir/flags.make
CMakeFiles/ft_ls.dir/ft_ls_v1/src/main.c.o: ../ft_ls_v1/src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/professor/ft_ls/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ft_ls.dir/ft_ls_v1/src/main.c.o"
	/usr/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ft_ls.dir/ft_ls_v1/src/main.c.o   -c /home/professor/ft_ls/ft_ls_v1/src/main.c

CMakeFiles/ft_ls.dir/ft_ls_v1/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ft_ls.dir/ft_ls_v1/src/main.c.i"
	/usr/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/professor/ft_ls/ft_ls_v1/src/main.c > CMakeFiles/ft_ls.dir/ft_ls_v1/src/main.c.i

CMakeFiles/ft_ls.dir/ft_ls_v1/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ft_ls.dir/ft_ls_v1/src/main.c.s"
	/usr/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/professor/ft_ls/ft_ls_v1/src/main.c -o CMakeFiles/ft_ls.dir/ft_ls_v1/src/main.c.s

CMakeFiles/ft_ls.dir/ft_ls_v1/src/print.c.o: CMakeFiles/ft_ls.dir/flags.make
CMakeFiles/ft_ls.dir/ft_ls_v1/src/print.c.o: ../ft_ls_v1/src/print.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/professor/ft_ls/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/ft_ls.dir/ft_ls_v1/src/print.c.o"
	/usr/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ft_ls.dir/ft_ls_v1/src/print.c.o   -c /home/professor/ft_ls/ft_ls_v1/src/print.c

CMakeFiles/ft_ls.dir/ft_ls_v1/src/print.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ft_ls.dir/ft_ls_v1/src/print.c.i"
	/usr/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/professor/ft_ls/ft_ls_v1/src/print.c > CMakeFiles/ft_ls.dir/ft_ls_v1/src/print.c.i

CMakeFiles/ft_ls.dir/ft_ls_v1/src/print.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ft_ls.dir/ft_ls_v1/src/print.c.s"
	/usr/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/professor/ft_ls/ft_ls_v1/src/print.c -o CMakeFiles/ft_ls.dir/ft_ls_v1/src/print.c.s

# Object files for target ft_ls
ft_ls_OBJECTS = \
"CMakeFiles/ft_ls.dir/ft_ls_v1/src/main.c.o" \
"CMakeFiles/ft_ls.dir/ft_ls_v1/src/print.c.o"

# External object files for target ft_ls
ft_ls_EXTERNAL_OBJECTS =

ft_ls: CMakeFiles/ft_ls.dir/ft_ls_v1/src/main.c.o
ft_ls: CMakeFiles/ft_ls.dir/ft_ls_v1/src/print.c.o
ft_ls: CMakeFiles/ft_ls.dir/build.make
ft_ls: ../ft_ls_v1/libft/libft.a
ft_ls: CMakeFiles/ft_ls.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/professor/ft_ls/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable ft_ls"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ft_ls.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ft_ls.dir/build: ft_ls

.PHONY : CMakeFiles/ft_ls.dir/build

CMakeFiles/ft_ls.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ft_ls.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ft_ls.dir/clean

CMakeFiles/ft_ls.dir/depend:
	cd /home/professor/ft_ls/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/professor/ft_ls /home/professor/ft_ls /home/professor/ft_ls/cmake-build-debug /home/professor/ft_ls/cmake-build-debug /home/professor/ft_ls/cmake-build-debug/CMakeFiles/ft_ls.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ft_ls.dir/depend

