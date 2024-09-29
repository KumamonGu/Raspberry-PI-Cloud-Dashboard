#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 102400
#define NUM_THREADS 20

int n1,n2;
char *s1,*s2;
FILE *fp;
int countArray[NUM_THREADS]={0};


int readf(FILE *fp)
{
	if((fp=fopen("emoji.txt", "r"))==NULL){
		printf("ERROR: can't open string.txt!\n");
		return 0;
	}
	s1=(char *)malloc(sizeof(char)*MAX);
	if(s1==NULL){
		printf("ERROR: Out of memory!\n");
		return -1;
	}
	s2=(char *)malloc(sizeof(char)*MAX);
	if(s1==NULL){
		printf("ERROR: Out of memory\n");
		return -1;
	}
	/*read s1 s2 from the file*/
	s1=fgets(s1, MAX, fp);
	s2=fgets(s2, MAX, fp);
	n1=strlen(s1);  /*length of s1*/
	n2=strlen(s2)-1; /*length of s2*/

	if(s1==NULL || s2==NULL || n1<n2)  /*when error exit*/
		return -1;
	return 0;
}


int num_substring(int t)
{
    int start, end;
    int count = 0;
    
    // 计算当前线程负责的起始位置和结束位置
    int chunk_size = n1 / NUM_THREADS;
    start = t * chunk_size;
    
    // 最后一个线程需要处理到字符串的末尾
    if (t == NUM_THREADS - 1) {
        end = n1;
    } else {
        end = (t + 1) * chunk_size + n2 - 1; // 确保检查跨界子串
        if (end > n1) {
            end = n1; // 保证不超过s1的长度
        }
    }

    // 遍历当前线程负责的部分并计算子串出现的次数
    for (int i = start; i <= end - n2; i++) {
        if (strncmp(&s1[i], s2, n2) == 0) {
            count++;
        }
    }
    
    // 将结果存入全局数组
    countArray[t] = count;
    
    return count;
}




void *calSubStringThread(void *threadid){
    long tid;
    tid = (long)threadid;
    int num = num_substring(tid);
    printf("This is thread %ld, num of substring %s is %d\n", tid, s2, num);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int t, rc;
    int totalNum = 0;

	readf(fp);

	for(t=0; t<NUM_THREADS; t++){
        rc = pthread_create(&threads[t], NULL, calSubStringThread, (void *) (size_t)t);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    for(t=0; t<NUM_THREADS; t++){
        pthread_join(threads[t], NULL);
    }

 	printf("The number of substrings is: %d\n", totalNum);
	return 1;
}
