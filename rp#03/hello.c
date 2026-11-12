#include <stdio.h>
#include <string.h>

const char *secret = "Rev_journey";

int check(char *input){
	return strcmp(input, secret) == 0;
}

int main(int argc, char **argv){
	if(argc != 2){
		printf("Usage: $s <password>\n", argv[0]);
		return 1;
	}
	if(check(argv[1])){
		printf("Correct| You found the secret.\n");
	}else{
		printf("Wrong!\n");
	}
	return 0;
}


