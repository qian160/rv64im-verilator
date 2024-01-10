#include<iostream>
#include<stdio.h>
#include<assert.h>
#include<fstream>

using namespace std;

// g++ -std=c++17 load.cpp -o load 
/*
	a possible set of steps:
		1. riscv gcc -c -> .o
		2. ld(put all the needed objs together)
		3. objcopy
	input = binary file(.bin), output = 4 txt files(which can later be used by verilog's readmemh)
*/

int main(int argc, char **argv)
{
	if(argc < 2){
		cout << "need an argument!\n";
		return 0;
	}

	string img_file(argv[1]);

	FILE * in = fopen(img_file.c_str(), "rb");
	assert(in);	

	FILE * output[4] {
		fopen("./img0", "w"),
		fopen("./img1", "w"),
		fopen("./img2", "w"),
		fopen("./img3", "w"),
	};

	for(auto &p: output){
		assert(p);
	}

	uint8_t cnt = 0;
	uint8_t buffer;
	while(1){
		if(fread(&buffer, sizeof(uint8_t), 1, in) <= 0) break;
		fprintf(output[cnt], "%08x\n", buffer);
		cnt = (cnt + 1) & 0b11;
	}

	for(int i = 0; i < 4; i ++)
		fclose(output[i]);
	fclose(in);
}
