#include<iostream>
#include<vector>
#include<cassert>
#include<chrono>
#include<set>

using namespace std;


void print_automaton(const vector<int>& t){
	for(int i=0; i<t.size(); ++i){
		cout << t[i];
		if(i%2==1){
			cout << endl;
		} else {
			cout << " ";
		}
	}
	cout << endl;
}

class AutomataGenerator{
private:
	vector<int> t; //transition vector, size: 1*2k
	int k; //number of states
	vector<int> increaseIndices;
	bool notEnded = true;
	
public:
	AutomataGenerator(int input_k){
		k = input_k;
		t.resize(2*k, 0);
		increaseIndices.resize(k+1);
		for(int i=0; i<k; ++i){
			increaseIndices[i] = i-1;
		}
		increaseIndices[k] = 2*k;
		defaultFill();
	}
	
	const vector<int>& getT() const{
		return t;
	}
	
	void printT(){
		print_automaton(t);
	}
	
	bool getNext(){
		int i = k-1;
		bool again = true;
		while(again and i>=0){
			bool success = updateFillBetween(i);
			if(!success){
				--i;
				again = true;
			} else {
				again = false;
			}
		}
		if(again){
			bool success = updateIncreaseIndices();
			if(not success){
				notEnded = false;
			}
			defaultFill();
		}
		return notEnded;
	}
	
private:
	void defaultFill(){
		for(int i=0; i<2*k; ++i){
			t[i] = 0;
		}
		for(int i=1; i<k; ++i){
			t[increaseIndices[i]]=i;
		}
	}
	
	void printIncreaseIndices(){
		cout << "Increase indices: " << endl;
		for(int i=0; i<k+1; ++i){
			cout << increaseIndices[i] << " ";
		}
		cout << endl << endl;
	}
	
	bool updateIncreaseIndices(){
		int i = k-1;
		bool again = true;
		bool noError = true;
		while(again){
		//cout << "aa " << increaseIndices[i]+1 << " " << 2*i-1 << endl;
			if(i==0){
				again = false;
				noError = false;
			} else if(increaseIndices[i]+1>2*i-1){
				again = true;
				--i;
			} else {
				again = false;
				increaseIndices[i]++;
				i++;
				while(i<k){
					increaseIndices[i] = increaseIndices[i-1]+1;
					i++;
				}
			}
		}
		
		return noError;
	}
	
	bool updateFillBetween(int max){
		int start = increaseIndices[max];
		int end = increaseIndices[max+1];
		int index = end - 1;
		while(index>start && t[index]==max){
			t[index] = 0;
			--index;
		}
		if(index > start){
			++t[index];
			return true;
		} else {
			return false;
		}
	}

};

int runAutomaton(int n, const vector<int> &t, string input, bool do_print=false){
	if(do_print) cout << "Run automaton: " << endl;
	if(do_print) print_automaton(t);
	int state = 0;
	for(int i=0; i<input.size(); ++i){
		int character = int(input[i]) - int('0');
		int newState = t[state * 2 +character];
		if(do_print)
			cout << "q" << state << ", " << character
				 << " -> q" << newState << endl;
		state = newState;
	}
	if(do_print)
		cout << "Running finished, final state: "
			 << state << endl << endl;
	return state;
}

class WordSequenceGenerator{
private:
	int n; //length of words
	int l; //number of words
	vector<string> words;
	string startWord;

	string getNextWord(string w){
		int i = w.size() - 1;
		while(i>=0 and w[i]=='1'){
			w[i] = '0';
			--i;
		}
		if(i>=0){
			w[i]= '1';
		}
		return w;
	}

	bool updateWord(string& w){
		int i = w.size() - 1;
		while(i>=0 and w[i]=='1'){
			w[i] = '0';
			--i;
		}
		if(i>=0){
			w[i]= '1';
			return true;
		} else {
			return false;
		}
	}
	
	bool isUnique(const vector<string>& words){
	    std::set<string> setOfWords(words.begin(), words.end());
    	return setOfWords.size() == words.size();
    }

public:
	WordSequenceGenerator(int input_n, int input_l):
		n(input_n),
		startWord(n, '0')
	{
		l = input_l;
		words.resize(l, startWord);
		for(int i=1; i<l; ++i){
			words[i] = getNextWord(words[i-1]);
		}
	}
	
	const vector<string>& getWords() const{
		return words;
	}
	
	bool updateWordSequence(){
		bool success;
		success = false;
		int i = words.size()-1;
		while(i>=0 and not success){
			success = incrementWord(i);
			--i;
		}
		if(not success){
			return false;
		} else {
			return true;
		}
	}

	bool incrementWord(int i){
		if(i<0 or l<=i){
			throw "Invalid input";
		}
		bool success = updateWord(words[i]);
		if(i==0){
			cout << words[i] << endl;
		}
		if(words[i] == startWord) return false;
		for(int j=i+1; j<l; ++j){
			words[j] = getNextWord(words[j-1]);
			if(words[j] == startWord){
				return false;
			}
		}
		return true;
	}
};


class Tester{
private:
	int n;
	int l;
	int max_needed_states;
	bool do_print;
	int start_k;
	int end_k;
	
public:
	Tester(int input_n, int input_l, int input_start_k=2, int input_end_k=99999, bool input_do_print=false) {
		n = input_n;
		l = input_l;
		max_needed_states = 1;
		do_print = input_do_print;
		start_k = input_start_k;
		end_k = input_end_k;
	}
	
	int run(){
		auto begin = std::chrono::high_resolution_clock::now();
		
		WordSequenceGenerator wsg(n, l);
		const vector<string>& words{wsg.getWords()};
		do{
			//cout << w1 << endl;
			//cout << "Second word: " << w2 << endl;
			
			int state_number = separate_words(words);
			
			//cout << "Separated with " << k << " states." << endl << endl;
			//print_automaton(separating_automaton);
			//runAutomaton(n, separating_automaton, input1, true);
			//runAutomaton(n, separating_automaton, input2, true);
			if(max_needed_states<state_number){
				max_needed_states = state_number;
			}
			
		} while(wsg.updateWordSequence());
		
		auto end = std::chrono::high_resolution_clock::now();
    	auto elapsed = std::chrono
    		::duration_cast<std::chrono::nanoseconds>(end - begin);
    	printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
		
		return max_needed_states;
	}
	
	int separate_words(const vector<string> words){
		int k=start_k;
		bool separation_done = false;
		do{
			++k;
			AutomataGenerator ag(k);
			const vector<int>& t {ag.getT()};
			do{
				vector<int> final_states(words.size());
				for(int i=0; i<words.size(); ++i){
					final_states[i] = runAutomaton(n, t, words[i]);
				}		
				std::set<int> set_of_final_states
					(final_states.begin(), final_states.end());
				if(set_of_final_states.size()
					==final_states.size())
				{
					separation_done = true;
					break;
				}
			} while(ag.getNext());
		} while(!separation_done and k<end_k);
		if(separation_done){
			return k;
		} else{
			return 99999;
		}
	}

};

int main(){
	int n;
	cout << "Size of words(n): ";
	cin >> n;
	
	int l;
	cout << "Number of words(l): ";
	cin >> l;
	
	int start_k = 1;
	
	Tester tester(n, l, start_k, 9999, false);
	int max_needed_states = tester.run();
	cout << "max needed states: " << max_needed_states << endl;

/*
	WordSequenceGenerator wsg(n, l);
	const vector<string>& words{wsg.getWords()};
	do{
		for(int i=0; i<words.size(); ++i){
			cout << words[i] << "  ";
		}
		cout << endl;
	} while(wsg.updateWordSequence());
*/
}
