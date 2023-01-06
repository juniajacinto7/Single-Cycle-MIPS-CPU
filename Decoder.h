#ifndef DECODER_h
#define DECODER_h

#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <math.h>

using namespace std;

//Made by Julio Lopez
// function converting a binary number to decimal
int binarytoDec(long binaryValue) {

   /* local variable declaration */
   long decimalValue = 0;
   long powerOf2 = 1; // 2^0 = 1 then 2^1 = 2 then 2^2 = 4 .... must iterate every loop

   while (binaryValue != 0) {
      long remainder = binaryValue % 10; // get the first number of binary and then second number and so on
      decimalValue = (remainder * powerOf2) + decimalValue;
      powerOf2 = powerOf2 * 2; // we multiply by two in order to raise to the next power 
      binaryValue = binaryValue / 10; // removes the last most value and reasigns new value to binaryValue
   }
 
   return decimalValue; 
}

//CODE by Junia Jacinto
//binary to decimal for j type
int binaryDecimal (string target) {

   double mult = pow(2, (target.length()-1));
   int finalVal = 0;

   for(int i = 0; i < target.length(); i++) {
      char tempChar = target[i];

      if( tempChar == '1'   ) {
         finalVal = finalVal + mult;
         mult = mult /2;
      }

      else {
          mult = mult /2;
      }
   }

   return finalVal;

}

//Made by Julio Lopez
//Made to find the operator of R-type
string findOperator(int decimalValue) {

   switch(decimalValue) {
      case 32 :
         return "add";
         break;
      case 33 :
         return "adu";
         break;
      case 36 :
         return "and";
         break;
      case 8 :
         return "jr";
         break;
      case 39 :
         return "nor";
         break;
      case 37 :
         return "or";
         break;
      case 42 :
         return "slt";
         break;
      case 43 :
         return "sltu";
         break;
      case 0 :
         return "sll";
         break;
      case 2 :
         return "srl";
         break;
      case 34 :
         return "sub";
         break;
      case 35 :
         return "subu";
         break;
      default :
        return "error";
   }
}

//CODE by Junia Jacinto
//Used to get operation for I type and J type
string iOrJTypeInstruc(int opCode) {

   string instrucType;

   if(opCode == 8) {
      instrucType = "addi";
   }
   else if (opCode == 9) {
      instrucType = "addiu";

   }

   else if (opCode == 12) {
      instrucType = "andi";
   }

   else if (opCode == 4) {
       instrucType = "beq";

   }

   else if (opCode == 5) {
      instrucType = "bne";

   }

   else if (opCode == 36) {
      instrucType = "lbu";

   }

   else if (opCode == 37) {
      instrucType = "lhu";
   }

   else if (opCode == 48) {
      instrucType = "ll";
   }

   else if (opCode == 15) {
      instrucType = "lui";
   }

   else if (opCode == 13) {
      instrucType = "ori";
   }

   else if (opCode == 10) {
      instrucType = "slti";
   }

   else if (opCode == 11) {
      instrucType = "sltiu";
   }

   else if (opCode == 40) {
      instrucType = "sb";
   }

   else if (opCode == 56) {
      instrucType = "sc";
   }

   else if (opCode == 41) {
      instrucType = "sh";
   }

   else if (opCode == 43) {
      instrucType = "sw";
   }

    else if (opCode == 35) {
      instrucType = "lw";
   }

   // J-type

   else if (opCode == 2) {
      instrucType = "j";
   }

   else if (opCode == 3) {
      instrucType = "jal";
   }

   else {
      instrucType = "error: Not a proper opcode for i or j type. Review input.";
   }

   return instrucType;
}






#endif