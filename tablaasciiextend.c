#include <stdio.h>

int main(){
	
	for(int i = 0; i < 256; i++){
		printf("%d = %c\n", i, i);
	}
	
	getchar();
	return 0;
}
