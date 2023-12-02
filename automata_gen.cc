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
