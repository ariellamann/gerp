# Ariella Mann {amann04} and Ben Rowland {browla01}
#########################################################
#                 PROJECT 4: gerp				        #
#########################################################
#

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

# This rule builds the gerp program
gerp: main.cpp TheHash.o Gerp.o DirNode.o FSTree.o 
	$(CXX) $(CXXFLAGS) -O2 -ggdb3 main.cpp TheHash.o Gerp.o DirNode.o \
					   FSTree.o -o gerp

# This rule builds the TheHash.o
TheHash.o: TheHash.cpp TheHash.h 
	$(CXX) $(CXXFLAGS) -c TheHash.cpp

# This rule builds the Gerp.o
Gerp.o: Gerp.cpp Gerp.h DirNode.h TheHash.h FSTree.h 
	$(CXX) $(CXXFLAGS) -c Gerp.cpp

# This rule builds the FSTreeTraversal.o
FSTreeTraversal.o: FSTreeTraversal.cpp DirNode.h FSTree.h
	$(CXX) $(CXXFLAGS) -c FSTreeTraversal.cpp

# This rule builds the treetraversal for phaseone
treeTraversal: FSTreeTraversal.o DirNode.o FSTree.o
	$(CXX) $(CXXFLAGS) FSTreeTraversal.o DirNode.o FSTree.o -o treeTraversal

provide:
	provide comp15 proj4_gerp Makefile README main.cpp \
	FSTreeTraversal.cpp stringProcessing.cpp stringProcessing.h \
	TheHash.h TheHash.cpp Gerp.h Gerp.cpp \
	test_input.txt test_input2.txt test_input3.txt\
