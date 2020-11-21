# All Targets
all: cTrace

# Tool invocations
# Executable "cTrace" depends on the files main.o Session.o Graph.o Agent.o Tree.o
cTrace: bin/main.o  bin/Session.o   bin/Graph.o bin/Agent.o bin/Tree.o
	@echo 'Building target: cTrace'
	@echo 'Invoking: C++ Linker'
	g++ -o bin/main.o bin/Session.o bin/Graph.o bin/Agent.o bin/Tree.o
	@echo 'Finished building target: cTrace'
	@echo ' '

#main.o Depends on the source and header files src/main.cpp include/Session.h
bin/main.o: src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp

#Session.o Depends on the source and header files.... 
bin/Session.o: src/Session.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Session.o src/Session.cpp

#Graph.o Depends on the source and header files.... 
bin/Graph.o: src/Graph.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Graph.o src/Graph.cpp

#Agent.o Depends on the source and header files.... 
bin/Agent.o: src/Agent.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Agent.o src/Agent.cpp


#Tree.o Depends on the source and header files.... 
bin/Tree.o: src/Tree.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Tree.o src/Tree.cpp

#FiveRuleTester.o Depends on the source and header files.... 
bin/FiveRuleTester.o: src/FiveRuleTester.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/FiveRuleTester.o src/FiveRuleTester.cpp

#Tester.o Depends on the source and header files.... 
bin/Tester.o: src/Tester.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Tester.o src/Tester.cpp




#Clean the build directory
clean: 
	rm -f bin/*
