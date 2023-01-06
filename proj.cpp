#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Decoder.h"

using namespace std;

//global variables
int rdValue = 0;
int rsValue = 0;
int rtValue = 0;

int registerFile[32] = {0,0,0,0,0,0,0,0,0,32,5,0,0,0,0,0,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int d_mem[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,16,0,0};

string registerName[32] = {"$zero", "$at", "v0", "v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};


int opcodeDecimal;
int rsDecimal;
int rtDecimal;
int rdDecimal;
int shamtDecimal;
int funcDecimal;

int immDecimal;

int alu_result;

int total_clock_cycles = 0;

int pcCounter = 0;


string Fetch() {

	//used to input a file
	//input is the name given to the file
	//("name of file") text in this is the actual name of the file
	ifstream input("sample_part1.txt");

	//value of current line to read
	string line;

	//gets line using pcCounter
	for (int i = 0; i < (pcCounter / 4 + 1); i++) {
        getline(input, line);
	}

   static int next_pc = pcCounter + 4;

	//increment pcCounter
	pcCounter = pcCounter + 4;

	return line;

}

int Decode(string instruc) {
	//checking opcode

	string opcode = instruc.substr(0, 6);

	//if opcode is 0 then we have R-type
   if(opcode == "000000") {

		string rs = instruc.substr(6, 5);
    	string rt = instruc.substr(11, 5);
    	string rd = instruc.substr(16, 5);
    	string shamt = instruc.substr(21, 5);
		string func = instruc.substr(26, 6);

      opcodeDecimal = binaryDecimal(opcode);

      rsDecimal = binaryDecimal(rs);
      rtDecimal = binaryDecimal(rt);
      rdDecimal = binaryDecimal(rd);
      shamtDecimal = binaryDecimal(shamt);
		funcDecimal = binaryDecimal(func);


      //Commented out to get desired output
		//cout << "Instruction Type: R" << endl;
		//cout << "Operations: " << findOperator(funcDecimal) << endl;
		//cout << "Rs: " << rsDecimal << endl;
		//cout << "Rt: " << rtDecimal << endl;
		//cout << "Rd: " << rdDecimal << endl;
		//cout << "Shamt: " << shamtDecimal << endl;
		//cout << "Funct: " << funcDecimal << endl;

   rsValue = registerFile[rsDecimal];
   rtValue = registerFile[rtDecimal];

   if (findOperator(funcDecimal) == "sub") {
      return 0110;
   }

   else if (findOperator(funcDecimal) == "add") {
      return 0010;
   }

   else if (findOperator(funcDecimal) == "and") {
      return 0000;
   }

   else if (findOperator(funcDecimal) == "or") {
      return 0001;
   }

   else if (findOperator(funcDecimal) == "nor") {
      return 1100;
   }

   else if (findOperator(funcDecimal) == "slt") {
      return 0111;
   }

}

else {

   string rs = instruc.substr(6, 5);
   string rt = instruc.substr(11, 5);
   string imm = instruc.substr(16, 16);

   opcodeDecimal = binaryDecimal(opcode);
   rsDecimal = binaryDecimal(rs);
   rtDecimal = binaryDecimal(rt);
   immDecimal  = binaryDecimal(imm);

   rsValue = registerFile[rsDecimal];
   rtValue = registerFile[rtDecimal];

   //cout << "Instruction Type: I" << endl;
	//cout << "Operations: " << iOrJTypeInstruc(opcodeDecimal) << endl;
	//cout << "Rs: " << rsDecimal << endl;
	//cout << "Rt: " << rtDecimal << endl;
	//cout << "Imm: " << immDecimal << endl;


   return 0;
   
}

return 1;

}

void Mem(int code) {
   if (code == 35) {
      registerFile[rtDecimal] = d_mem[ (registerFile[rsDecimal] + immDecimal) / 4];
      
      //cout << "Register " << rtDecimal << " is modified to " << registerFile[rtDecimal] << endl;
   }

   else if(code == 43) {
      //cout << "SW ACTION" << endl;
      //cout << " what dm will change " << ((registerFile[rsDecimal] + immDecimal) / 4) << endl;
      d_mem[ ((registerFile[rsDecimal] + immDecimal) / 4) ] = registerFile[rtDecimal];

   }

   else {
       cout << "MEMORY ERROR" << endl;
   }
}

void Execute(int alu_op) {

   // sub
   if (alu_op == 0110) {
      alu_result = registerFile[rsDecimal] - registerFile[rtDecimal];

   }

   //add 

   if (alu_op == 0010) {
      alu_result = registerFile[rsDecimal] + registerFile[rtDecimal];

   }

   //AND

   if (alu_op == 0000) {

      alu_result = registerFile[rsDecimal] & registerFile[rtDecimal];

   }

   //OR

   if (alu_op == 0001) {
      alu_result = registerFile[rsDecimal] | registerFile[rtDecimal];

   }
   
   //SLT
   
   if (alu_op == 0111) {
      if (registerFile[rsDecimal] < registerFile[rtDecimal]) {
         alu_result = 1;
      }

      else {
         alu_result =  0;
      }

   }

   //NOR
   
   if (alu_op == 1100) {
      alu_result = ~(registerFile[rsDecimal] | registerFile[rtDecimal]);


   }

   // If not R-type we let alu_op = 0 in order to handle other types
   //We use this as a control
   //Might change

    if (alu_op == 0) {

       // Call to change memory LW
       if(opcodeDecimal == 35) {
          Mem(35);
       }
      
      //call to change memory SW
       else if (opcodeDecimal == 43) {
          Mem(43);
       }



      //call to do BEQ Jump
       else if(opcodeDecimal == 4) {
          //cout << "BEQ Action" << endl;

          if (registerFile[rsDecimal] == registerFile[rtDecimal]) {
             //cout << "we jump" << endl;

            //if we branch here we get where we branch too
            int branch_target = pcCounter + immDecimal * 4;
            pcCounter = branch_target;

          }
       }


      //call for J Jump
      else if(opcodeDecimal == 2) {
         cout << "J Action" << endl;
         cout << "we jump" << endl;

         //if we branch here we get where we branch too
         int jump_target = pcCounter + immDecimal * 4;
         pcCounter = jump_target;

          
       }


      
   }

}

void Writeback () {
   total_clock_cycles++;

   if(opcodeDecimal == 0) {
      registerFile[rdDecimal] = alu_result;
      cout << "total_clock_cycles " << total_clock_cycles << " :"<< endl;
      cout  << registerName[rdDecimal] << " is modified to " << hex << "Ox" << registerFile[rdDecimal] << endl;
      cout << "pc is modified to " << "0x"<< hex << pcCounter << endl << endl;
   }

   else {

      if (opcodeDecimal == 4) {
         cout << "total_clock_cycles " << total_clock_cycles << " :"<< endl;
        // cout << registerName[rtDecimal] << " is modified to " << hex << "0x" << registerFile[rtDecimal] << endl;
         cout << "pc is modified to " << "0x"<< hex << pcCounter << endl << endl;;

      }

      else if (opcodeDecimal == 43) {
         cout << "total_clock_cycles " << total_clock_cycles << " :"<< endl;
         cout << "memory Ox" << (registerFile[rsDecimal] + immDecimal) << " is modified to Ox"<< registerFile[rtDecimal] << endl;
         cout << "pc is modified to " << "0x"<< hex << pcCounter << endl << endl;;

      }
      
      else {

      cout << "total_clock_cycles " << total_clock_cycles << " :"<< endl;
      cout << registerName[rtDecimal] << " is modified to " << hex << "0x" << registerFile[rtDecimal] << endl;
      cout << "pc is modified to " << "0x"<< hex << pcCounter << endl << endl;
      }


   }

}

void ControlUnit(int code) {
   if (alu_result == 0) {
      bool alu_zero = 1;
   }
   bool check1 = 0;
   bool check2 = 1;
   bool check3 = 0;
   bool check4 = 0;
   bool check5 = 1;

}

void print() {
   cout << "Register: " << endl;

   for (int i = 0; i < 32; i++) {
       cout << i << ":     " << registerFile[i] << "         MEMORY " << i << ": "<< d_mem[i] << endl;
   }

}



// END OF DECODE






int main(int argc, const char * argv[]) {

	Execute(Decode(Fetch()));
   Writeback();
   //print();


   Execute(Decode(Fetch()));
   Writeback();
  // print();


   Execute(Decode(Fetch()));
   Writeback();
  // print();

   Execute(Decode(Fetch()));
   Writeback();
   //print();

   Execute(Decode(Fetch()));
   Writeback();
  // print();


}