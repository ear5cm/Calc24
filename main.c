#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static char str[1024] = {0};

int calc24(int *a, int size) {
	//printf("RESULT:\n%s\n", str);
	int n = strlen(str);
	int i, j, k, l, h;
	if(size == 1 && a[0] == 24) {
		return 24;
	}
	for(i = 0; i < size; i++) {
		if(a[i] == 0) return 0;
	}
	for(i = 0; i < size; i++) {
		for(j = i + 1; j < size; j++) {
			for(k = 0; k < 4; k++) {
				l = 0;
				int b[4] = {0};
				switch(k) {
					case 0:
						b[l++] = a[i] + a[j];
						sprintf(str+n, "%d + %d\n", a[i], a[j]);
						break;
					case 1:
						if(a[i] > a[j]) {
							sprintf(str+n, "%d - %d\n", a[i], a[j]);
							b[l++] = a[i] - a[j];
						} else {
							sprintf(str+n, "%d - %d\n", a[j], a[i]);
							b[l++] = a[j] - a[i];
						}
						break;
					case 2:
						sprintf(str+n, "%d x %d\n", a[i], a[j]);
						b[l++] = a[i] * a[j];
						break;
					default:
						if(a[i] > a[j]) {
							if(a[i]%a[j] != 0) {
								b[l++] = 0;
							} else {
								sprintf(str+n, "%d / %d\n", a[i], a[j]);
								b[l++] = a[i] / a[j];
							}
						} else {
							if(a[j]%a[i] != 0) {
								b[l++] = 0;
							} else {
								b[l++] = a[j] / a[i];
								sprintf(str+n, "%d / %d\n", a[j], a[i]);
							}
						}
						break;

				}
				for(h = 0; h < size; h++) {
					if(h != i && h != j) {
						b[l++] = a[h];
					}
				}
				if(calc24(b, size-1) == 24)
				{
					n = strlen(str);
					return 24;
				}
			}
		}
	}
	return 0;
}

int calcAll() {
	int a[4];
	int i, j, m, n;
	int no = 0;
	int yes = 0;
	printf("No answer:\n");
	for(i=1; i<=10; i++) {
		for(j=i; j<=10; j++) {
			for(m=j; m<=10; m++) {
				for(n=m; n<=10; n++){
					a[0] = i;
					a[1] = j;
					a[2] = m;
					a[3] = n;
					memset(str, 0, 1024);
					if(24 != calc24(a, 4)) {
						no++;
						printf("%d %d %d %d\n", a[0], a[1], a[2], a[3]);
					}
				}
			}
		}
	}
	printf("Have answer:\n");
	for(i=1; i<=10; i++) {
		for(j=i; j<=10; j++) {
			for(m=j; m<=10; m++) {
				for(n=m; n<=10; n++){
					a[0] = i;
					a[1] = j;
					a[2] = m;
					a[3] = n;
					memset(str, 0, 1024);
					if(24 == calc24(a, 4)) {
						yes++;
						printf("%d %d %d %d\n", a[0], a[1], a[2], a[3]);
						printf("%s\n", str);
					}
				}
			}
		}
	}
	printf("Total: %d, No anwser: %d, Have anwser: %d\n", yes+no, no, yes);
	return 0;
}

/*************************************************************
usage:
1. ./a.out, show a quest, press any key show the answer
2. ./a.out all, show all we want to know
3. ./a.out num0 num1 num2 num3, all number must in 1-10
show the answer of given numbers.

 **************************************************************/
int main(int argc, const char** argv) {
	int a[4] = {0};
	int i;
	if(argc < 5) {
		if(argc > 1 && strncasecmp(argv[1],"all", 3) == 0) {
			calcAll();
			return 0;
		}
		srandom((unsigned long)argv);
		do{
			do {
				memset(str, 0, 1024);
				a[0] = random()%10+1;
				a[1] = random()%10+1;
				a[2] = random()%10+1;
				a[3] = random()%10+1;
			} while(24 != calc24(a, 4));

			printf("Q:\n%d %d %d %d\n", a[0], a[1], a[2], a[3]);
			printf("Enter key to get answer, q to quit:");

			char c = getchar();
			printf("A:\n%s\n", str);
			if(c == 'q' || c == 'Q') break;
		}while(1);

		return 0;
	}

	for(i = 0; i < 4; i++) {
		a[i] = atoi(argv[i+1]);
		if(a[i] < 1 || a[i] > 10) {
			printf("the numger must from 1 to 10\n");
			return 0;
		}
	}

	if(24 == calc24(a, 4)) {
		printf("The answer is:\n%s", str);
	} else {
		printf("Sorry, no answer.\n");
	}
}
