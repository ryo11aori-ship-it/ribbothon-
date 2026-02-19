#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_MEM 2500000
#define MAX_CODE 1000000
unsigned char mem[MAX_MEM];
long ptr = 0;
char code[MAX_CODE];
long jump_map[MAX_CODE];
long code_len = 0;
long dim_offsets[11];
void init_dims() {
long current_offset = 0;
dim_offsets[0] = 0;
for(int n=1; n<=10; n++) {
long cap = (long)pow(12-n, n);
current_offset += cap;
dim_offsets[n] = current_offset;
}
}
void build_jump_map() {
long stack[MAX_CODE];
long sp = 0;
for(long i=0; i<code_len; i++) {
char c = code[i];
if(c=='7' || c=='h' || c=='j') {
stack[sp++] = i;
} else if(c=='8' || c=='i' || c=='k') {
if(sp==0) { fprintf(stderr, "Loop error\n"); exit(1); }
long start = stack[--sp];
jump_map[start] = i;
jump_map[i] = start;
}
}
}
void execute() {
long pc = 0;
long turn_start_pc = 0;
int current_dim = 1;
int chars_in_dim = 0;
while(pc < code_len) {
char c = code[pc];
chars_in_dim++;
switch(c) {
case '0': break;
case '1': ptr++; break;
case '2': ptr--; break;
case '3': mem[ptr]++; break;
case '4': mem[ptr]--; break;
case '5': putchar(mem[ptr]); break;
case '6': mem[ptr] = getchar(); break;
case '7': if(!mem[ptr]) pc = jump_map[pc]; break;
case '8': if(mem[ptr]) pc = jump_map[pc]; break;
case '9': mem[ptr]+=3; break;
case 'a': mem[ptr]-=3; break;
case 'b': case 'c': break;
case 'd': case 'g': mem[ptr]--; break;
case 'e': case 'f': mem[ptr]++; break;
case 'h': if(!mem[ptr]){ pc = jump_map[pc]; } else { ptr--; } break;
case 'i': if(mem[ptr]){ pc = jump_map[pc]; } else { ptr--; } break;
case 'j': if(!mem[ptr]){ pc = jump_map[pc]; } else { ptr++; } break;
case 'k': if(mem[ptr]){ pc = jump_map[pc]; } else { ptr++; } break;
case 'x': 
turn_start_pc += 50; 
pc = turn_start_pc - 1; 
current_dim = 1; 
chars_in_dim = 0; 
break;
default: break;
}
if(c != 'x') {
if(chars_in_dim == 5) {
current_dim++;
chars_in_dim = 0;
}
}
pc++;
}
}
int main() {
init_dims();
int c;
while((c = getchar()) != EOF && code_len < MAX_CODE) {
if((c>='0' && c<='9') || (c>='a' && c<='k') || c=='x') {
code[code_len++] = (char)c;
}
}
build_jump_map();
execute();
return 0;
}
