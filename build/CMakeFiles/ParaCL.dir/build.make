# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jorik/study/PARACL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jorik/study/PARACL/build

# Include any dependencies generated for this target.
include CMakeFiles/ParaCL.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ParaCL.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ParaCL.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ParaCL.dir/flags.make

parser.cxx: ../parser.yy
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/jorik/study/PARACL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "[BISON][parser] Building parser with bison 3.5.2"
	cd /home/jorik/study/PARACL && /usr/local/bin/bison -d -o /home/jorik/study/PARACL/build/parser.cxx parser.yy

parser.hxx: parser.cxx
	@$(CMAKE_COMMAND) -E touch_nocreate parser.hxx

lexer.cxx: ../scanner.ll
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/jorik/study/PARACL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "[FLEX][lexer] Building scanner with flex 2.6.4"
	cd /home/jorik/study/PARACL && /usr/bin/flex -o/home/jorik/study/PARACL/build/lexer.cxx scanner.ll

CMakeFiles/ParaCL.dir/calc++.cxx.o: CMakeFiles/ParaCL.dir/flags.make
CMakeFiles/ParaCL.dir/calc++.cxx.o: ../calc++.cxx
CMakeFiles/ParaCL.dir/calc++.cxx.o: CMakeFiles/ParaCL.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jorik/study/PARACL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ParaCL.dir/calc++.cxx.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ParaCL.dir/calc++.cxx.o -MF CMakeFiles/ParaCL.dir/calc++.cxx.o.d -o CMakeFiles/ParaCL.dir/calc++.cxx.o -c /home/jorik/study/PARACL/calc++.cxx

CMakeFiles/ParaCL.dir/calc++.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ParaCL.dir/calc++.cxx.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jorik/study/PARACL/calc++.cxx > CMakeFiles/ParaCL.dir/calc++.cxx.i

CMakeFiles/ParaCL.dir/calc++.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ParaCL.dir/calc++.cxx.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jorik/study/PARACL/calc++.cxx -o CMakeFiles/ParaCL.dir/calc++.cxx.s

CMakeFiles/ParaCL.dir/driver.cxx.o: CMakeFiles/ParaCL.dir/flags.make
CMakeFiles/ParaCL.dir/driver.cxx.o: ../driver.cxx
CMakeFiles/ParaCL.dir/driver.cxx.o: CMakeFiles/ParaCL.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jorik/study/PARACL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ParaCL.dir/driver.cxx.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ParaCL.dir/driver.cxx.o -MF CMakeFiles/ParaCL.dir/driver.cxx.o.d -o CMakeFiles/ParaCL.dir/driver.cxx.o -c /home/jorik/study/PARACL/driver.cxx

CMakeFiles/ParaCL.dir/driver.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ParaCL.dir/driver.cxx.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jorik/study/PARACL/driver.cxx > CMakeFiles/ParaCL.dir/driver.cxx.i

CMakeFiles/ParaCL.dir/driver.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ParaCL.dir/driver.cxx.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jorik/study/PARACL/driver.cxx -o CMakeFiles/ParaCL.dir/driver.cxx.s

CMakeFiles/ParaCL.dir/parser.cxx.o: CMakeFiles/ParaCL.dir/flags.make
CMakeFiles/ParaCL.dir/parser.cxx.o: parser.cxx
CMakeFiles/ParaCL.dir/parser.cxx.o: CMakeFiles/ParaCL.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jorik/study/PARACL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/ParaCL.dir/parser.cxx.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ParaCL.dir/parser.cxx.o -MF CMakeFiles/ParaCL.dir/parser.cxx.o.d -o CMakeFiles/ParaCL.dir/parser.cxx.o -c /home/jorik/study/PARACL/build/parser.cxx

CMakeFiles/ParaCL.dir/parser.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ParaCL.dir/parser.cxx.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jorik/study/PARACL/build/parser.cxx > CMakeFiles/ParaCL.dir/parser.cxx.i

CMakeFiles/ParaCL.dir/parser.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ParaCL.dir/parser.cxx.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jorik/study/PARACL/build/parser.cxx -o CMakeFiles/ParaCL.dir/parser.cxx.s

CMakeFiles/ParaCL.dir/lexer.cxx.o: CMakeFiles/ParaCL.dir/flags.make
CMakeFiles/ParaCL.dir/lexer.cxx.o: lexer.cxx
CMakeFiles/ParaCL.dir/lexer.cxx.o: parser.hxx
CMakeFiles/ParaCL.dir/lexer.cxx.o: CMakeFiles/ParaCL.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jorik/study/PARACL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/ParaCL.dir/lexer.cxx.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ParaCL.dir/lexer.cxx.o -MF CMakeFiles/ParaCL.dir/lexer.cxx.o.d -o CMakeFiles/ParaCL.dir/lexer.cxx.o -c /home/jorik/study/PARACL/build/lexer.cxx

CMakeFiles/ParaCL.dir/lexer.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ParaCL.dir/lexer.cxx.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jorik/study/PARACL/build/lexer.cxx > CMakeFiles/ParaCL.dir/lexer.cxx.i

CMakeFiles/ParaCL.dir/lexer.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ParaCL.dir/lexer.cxx.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jorik/study/PARACL/build/lexer.cxx -o CMakeFiles/ParaCL.dir/lexer.cxx.s

# Object files for target ParaCL
ParaCL_OBJECTS = \
"CMakeFiles/ParaCL.dir/calc++.cxx.o" \
"CMakeFiles/ParaCL.dir/driver.cxx.o" \
"CMakeFiles/ParaCL.dir/parser.cxx.o" \
"CMakeFiles/ParaCL.dir/lexer.cxx.o"

# External object files for target ParaCL
ParaCL_EXTERNAL_OBJECTS =

ParaCL: CMakeFiles/ParaCL.dir/calc++.cxx.o
ParaCL: CMakeFiles/ParaCL.dir/driver.cxx.o
ParaCL: CMakeFiles/ParaCL.dir/parser.cxx.o
ParaCL: CMakeFiles/ParaCL.dir/lexer.cxx.o
ParaCL: CMakeFiles/ParaCL.dir/build.make
ParaCL: CMakeFiles/ParaCL.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jorik/study/PARACL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable ParaCL"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ParaCL.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ParaCL.dir/build: ParaCL
.PHONY : CMakeFiles/ParaCL.dir/build

CMakeFiles/ParaCL.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ParaCL.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ParaCL.dir/clean

CMakeFiles/ParaCL.dir/depend: lexer.cxx
CMakeFiles/ParaCL.dir/depend: parser.cxx
CMakeFiles/ParaCL.dir/depend: parser.hxx
	cd /home/jorik/study/PARACL/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jorik/study/PARACL /home/jorik/study/PARACL /home/jorik/study/PARACL/build /home/jorik/study/PARACL/build /home/jorik/study/PARACL/build/CMakeFiles/ParaCL.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ParaCL.dir/depend

