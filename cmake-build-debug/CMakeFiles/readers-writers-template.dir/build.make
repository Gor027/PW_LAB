# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /home/Gor027/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/192.7142.39/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/Gor027/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/192.7142.39/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/Gor027/MIM/PW/C_threads/przykłady15

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/Gor027/MIM/PW/C_threads/przykłady15/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/readers-writers-template.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/readers-writers-template.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/readers-writers-template.dir/flags.make

CMakeFiles/readers-writers-template.dir/readers-writers-template.c.o: CMakeFiles/readers-writers-template.dir/flags.make
CMakeFiles/readers-writers-template.dir/readers-writers-template.c.o: ../readers-writers-template.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/Gor027/MIM/PW/C_threads/przykłady15/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/readers-writers-template.dir/readers-writers-template.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/readers-writers-template.dir/readers-writers-template.c.o   -c /home/Gor027/MIM/PW/C_threads/przykłady15/readers-writers-template.c

CMakeFiles/readers-writers-template.dir/readers-writers-template.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/readers-writers-template.dir/readers-writers-template.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/Gor027/MIM/PW/C_threads/przykłady15/readers-writers-template.c > CMakeFiles/readers-writers-template.dir/readers-writers-template.c.i

CMakeFiles/readers-writers-template.dir/readers-writers-template.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/readers-writers-template.dir/readers-writers-template.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/Gor027/MIM/PW/C_threads/przykłady15/readers-writers-template.c -o CMakeFiles/readers-writers-template.dir/readers-writers-template.c.s

# Object files for target readers-writers-template
readers__writers__template_OBJECTS = \
"CMakeFiles/readers-writers-template.dir/readers-writers-template.c.o"

# External object files for target readers-writers-template
readers__writers__template_EXTERNAL_OBJECTS =

readers-writers-template: CMakeFiles/readers-writers-template.dir/readers-writers-template.c.o
readers-writers-template: CMakeFiles/readers-writers-template.dir/build.make
readers-writers-template: liberr.a
readers-writers-template: CMakeFiles/readers-writers-template.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/Gor027/MIM/PW/C_threads/przykłady15/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable readers-writers-template"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/readers-writers-template.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/readers-writers-template.dir/build: readers-writers-template

.PHONY : CMakeFiles/readers-writers-template.dir/build

CMakeFiles/readers-writers-template.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/readers-writers-template.dir/cmake_clean.cmake
.PHONY : CMakeFiles/readers-writers-template.dir/clean

CMakeFiles/readers-writers-template.dir/depend:
	cd /home/Gor027/MIM/PW/C_threads/przykłady15/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/Gor027/MIM/PW/C_threads/przykłady15 /home/Gor027/MIM/PW/C_threads/przykłady15 /home/Gor027/MIM/PW/C_threads/przykłady15/cmake-build-debug /home/Gor027/MIM/PW/C_threads/przykłady15/cmake-build-debug /home/Gor027/MIM/PW/C_threads/przykłady15/cmake-build-debug/CMakeFiles/readers-writers-template.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/readers-writers-template.dir/depend
