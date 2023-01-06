# Single-Cycle-MIPS-CPU
design a single-cycle MIPS CPU in C++. Single-cycle CPU program needs to be able to execute the following 10 instructions LW, SW, ADD, SUB, AND, OR, SLT, NOR, BEQ, J.

## Code Breakdown

### Fetch( )
The fetch function gets the line of code in the .txt file that PC points to. For example, if PC is 4 it goes to 4 / 4 = 1. Thus the first line of our .txt file. Next_PC is also in this Fetch function to be able to get branch_target and jump_target. Thus, the Fetch function reads the file using ifstream and reads the proper line using getline according to the value of PC. Once this line is read it is the return value for the fetch function.

### Decode( )
This line value is then given to the Decode function as a string. The decode function relies heavily on our assignment Homework 3 to be able to properly read the binary code. All function in assignment three that read the binary code are in the file Decoder.h. Our Decode function follows the same structure as our assignment three and decodes the binary code. In this function we use the variables rdValue, rsValue, and rtValue to get the values of the binary code. We then convert those values to decimal values and assign them to their corresponding variables opCodeDecimal, rsDecimal, rtDecimal, rdDecimal, shamtDecimal, funcDecimal, and immDecimal. According to what kind of type the binary code is I, J or R we get the proper values. Once we know what kind of variable this is we can get our alu variable.

### Exceute( )
From the Decode function with get our alu_op variable. We then use this variable to decide what kind of action we will take. If the function is an R-type we get the proper alu code and thus perform the action as needed. For example, if we get the code 0010 we will add or if we get the code 0000 we will perform a binary and. If the line of binary code is not an R-type we set alu_op to zero and set alu-zero to 1 for our code to understand we are not performing an action. If we do have an R-type we get ready to perform our action for the Writeback function. If this is an R- type we then decide if it as a J-type or I -type. Is this excecute function we also solve our branch_target in case we have to jump to another line in our file.

### Mem( )
If our instruction is not an R-type we then assume it is an I-type. We have to I-type instruction in our program. Load word and Store word. For both of these actions we call the Memory function. This function has access to the variable d_mem. Depending on what action is called LW or SW we call the Mem function and perform the appropriate action. The memory function is the only function that has access to memory and thus only these two actions can change memory.

### Writeback( )
Our Writeback function will take the action of the execute function if we have a R-type or a LW action. If we have a SW we don’t have to write back as we handled all that action in the Mem function. Our total_clock_cycles variable thus takes all the cycles we have taken and prints them out. We also increment PC and thus move onto our next action.

### ControlUnit( )
Our control unit is used in our for our program to know what kind of binary code we are using for example if we do not have an R-type then our control unit is activated because apu_zero is activated. We then use ALU control to run the proper function.

### registerFile[ ]
Array representing an array of size 32 to represent all the registers in a MIPS one cycle CPU.

### d_mem[ ]
An array representing an array of size 32 to represent all the slots for memory in a single cycle CPU.

### registerName[ ]
Used in order to use the names assigned to all the registers in a MIPS CPU for example $t1

## Binary Input
10001110000010110000000000000100 \
00000001001010100110100000100010 \
00000001101010111000100000101010 \
00010010001000000000000000000011 \
00000001101010110110100000100000 \
00000010001011010110100000100101 \
10101110000011010000000000000000 \
10101110000011010000000000000000


## Results
![Results](/results.png?raw=true "Results")
