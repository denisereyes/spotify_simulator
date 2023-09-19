# Use the first FLAGS definition for debugging, the 2nd for optimizing your code
FLAGS = -Wall -Wextra -g

CA = 5
LASTNAME = Nasir
BU_USERID = znasir1
GITHUB_USERID = zainasir
TEAM_NAME = valgrind
EXECUTABLE = CA5

## ADD TARGETS TO SEPARATELY COMPILE YOUR CODE FOR CA3 AND CREATE AN EXECUTABLE.

replaceme:
	echo "Did you remember to set the variables in the makefile?!"

tar: clean
	cd .. && tar -cvzf CA$(CA)_$(LASTNAME)_$(TEAM_NAME).tar.gz cs240-spring21-ca$(CA)-$(TEAM_NAME) && cd -

scrub: clean
	rm ~* *.swp *\#

run: $(EXECUTABLE)
	./$(EXECUTABLE)

memcheck: $(EXECUTABLE)
	valgrind --track-origins=yes --leak-check=full ./$(EXECUTABLE) $(inputdir) $(workdir)

$(EXECUTABLE):	$(EXECUTABLE).o Song.o User.o GraphNode.o System.o
	g++ $(EXECUTABLE).o Song.o User.o GraphNode.o System.o -o $(EXECUTABLE) $(FLAGS)

$(EXECUTABLE).o:	$(EXECUTABLE).cpp
	g++ -c $(EXECUTABLE).cpp
Song.o:	Song.cpp
	g++ -c Song.cpp
User.o: User.cpp
	g++ -c User.cpp
GraphNode.o: GraphNode.cpp
	g++ -c GraphNode.cpp
System.o: System.cpp
	g++ -c System.cpp
# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o $(EXECUTABLE)
