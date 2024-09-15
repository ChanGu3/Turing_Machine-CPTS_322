# The makefile creates the objects from their respective directories into a directory called /objectfiles
#     and builds the executable from all these objects inside of /objectfiles
# 
# This make file can also remove all the object files within the directory /objectfiles
#
# Run executable with	./TuringMachine
#
BINS = TuringMachine

CXXFLAGS = -g -Wall

LDFLAGS = -g 

.PHONY: default
default: $(BINS)

# CREATION OF OBJECT FILES (START)
#
objectfiles/crash.o: typedef/crash.cpp typedef/crash.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

objectfiles/uppercase.o: typedef/uppercase.cpp typedef/uppercase.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

objectfiles/commands.o: commands.cpp commands.h typedef/command_t.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

objectfiles/input_strings.o: input_strings.cpp input_strings.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

objectfiles/configuration_settings.o: configuration_settings.cpp configuration_settings.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

objectfiles/tape.o: turingmachine_parts/tape.cpp turingmachine_parts/tape.h typedef/uppercase.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

objectfiles/tape_alphabet.o: turingmachine_parts/tape_alphabet.cpp turingmachine_parts/tape_alphabet.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

objectfiles/input_alphabet.o: turingmachine_parts/input_alphabet.cpp turingmachine_parts/input_alphabet.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

objectfiles/states.o: turingmachine_parts/states.cpp turingmachine_parts/states.h typedef/uppercase.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

objectfiles/final_states.o: turingmachine_parts/final_states.cpp turingmachine_parts/final_states.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

objectfiles/transition.o: turingmachine_parts/transition.cpp turingmachine_parts/transition.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

objectfiles/transition_function.o: turingmachine_parts/transition_function.cpp turingmachine_parts/transition_function.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

objectfiles/turing_machine.o: turing_machine.cpp turing_machine.h \
	turingmachine_parts/tape.h turingmachine_parts/tape_alphabet.h turingmachine_parts/input_alphabet.h \
    turingmachine_parts/states.h turingmachine_parts/final_states.h turingmachine_parts/transition.h \
	turingmachine_parts/transition_function.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

objectfiles/main.o: main.cpp commands.h input_strings.h configuration_settings.h turing_machine.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
#
# CREATION OF OBJECT FILES (END)

# CLEAR ALL OBJECT FILES FOR TM IN DIRECTORY objectfiles/
.PHONY: clean
clean:
	rm -f core* objectfiles/*.o *~

# CREATE EXECUTABLE FROM OBJECT FILES IN DIRECTORY objectfiles/
TuringMachine: objectfiles/main.o objectfiles/commands.o objectfiles/input_strings.o objectfiles/configuration_settings.o \
	objectfiles/turing_machine.o objectfiles/tape.o objectfiles/tape_alphabet.o objectfiles/input_alphabet.o \
	objectfiles/states.o objectfiles/final_states.o objectfiles/transition.o objectfiles/transition_function.o \
	objectfiles/uppercase.o objectfiles/crash.o
	$(CXX) $(LDFLAGS) $^ -o $@


# CLEAR EXECUTABLE
.PHONY: immaculate
immaculate: clean
	rm -f $(BINS)
