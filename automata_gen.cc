#include "automata_gen.h"


void Automata::print(){
	for(int i=0; i<this->t.size(); ++i){
		std::cout << this->t[i];
		if(i%2==1){
			std::cout << std::endl;
		} else {
			std::cout << " ";
		}
	}
	std::cout << std::endl;
}

int Automata::run(std::string input, bool do_print){
	if(do_print) std::cout << "Run automaton: " << std::endl;
	if(do_print) this->print();
	int state = 0; //Initial state
	for(int i=0; i<input.size(); ++i){
		if(input[i] != '0' && input[i]!='1') {
			throw "Invalid input";
		}
		int character = int(input[i]) - int('0');
		int newState = t[state * 2 + character];
		if(do_print)
			std::cout << "q" << state << ", " << character
				 << " -> q" << newState << std::endl;
		state = newState;
	}
	if(do_print)
		std::cout << "Running finished, final state: "
			 << state << std::endl << std::endl;
	return state;
}