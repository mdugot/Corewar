# Corewar  

A programming game in which battle programs compete for control of a virtual computer.  
See https://en.wikipedia.org/wiki/Core_War.  

This project is composed of two parts.  

An assembler that assembles the battle programs.  
It converts a file .s writed in Redcode to a binary file .cor.  
> ./asm file.s  

And the virtual computer where the battle programs are loaded end executed.  
It allows several options :  
-s : silent mode.  
-v : visual mode with ncurse.  
-dump NUMBER : end the battle after NUMBER cycles and print the memory.  
-n NUMBER WARRIOR.cor : give to the warrior an id equal to NUMBER.  
> ./corewar [-s] [-v] [-dump nbr_cycles] [[-n number] champion1.cor] ...  
