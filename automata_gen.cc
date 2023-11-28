#include "automata_gen.h"


void print_automata(const std::vector<int>& t){
	for(int i=0; i<t.size(); ++i){
		std::cout << t[i];
		if(i%2==1){
			std::cout << std::endl;
		} else {
			std::cout << " ";
		}
	}
	std::cout << std::endl;
}