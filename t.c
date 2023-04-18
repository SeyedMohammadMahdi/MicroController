#include "stdio.h"
#include "stdlib.h"
#include "string.h" 


int compare(char *str1, char *str2);
int main()
{
  printf("%d", compare("hello world", "world hello"));
  return 0;
}

int compare(char *str1, char *str2) {
    int str1_length = strlen(str1);
    int str2_length = strlen(str2);
    char *words1[200];
    char *words2[200];
    char *word;
    int i, j, count1 = 0, count2 = 0, similar1 = 0;
    float similar_words = 0;
    // Split string1 into words
    word = strtok(str1, " \n");
    while (word != NULL && count1 < 200) {
        words1[count1++] = word;
        word = strtok(NULL, " \n");
    }

    // Split string2 into words
    word = strtok(str2, " \n");
    while (word != NULL && count2 < 200) {
        words2[count2++] = word;
        word = strtok(NULL, " \n");
    }
    
    long int index_1 = 0;
    long int index_2 = 0;
    // Compare the words in both strings
    for (i = 0; i < count1; i++) {
        index_2 = 0;
        for (j = 0; j < count2; j++) {
            if (strcmp(words1[i], words2[j]) == 0) {
                similar_words += 1.0 - abs(index_2 - index_1) / ((str1_length + str2_length) / 2.0);
                printf("for word : %s index1 is : %ld\n", words1[i], index_1);
                printf("index2 is : %ld\n", index_2);
                break;
            }
            index_2 += strlen(words2[j]);
        }
        index_1 += strlen(words1[i]);
    }
    // for (i = 0; i < count1; i++){
    // 	if(strstr(str2, words1[i]) != NULL){
    // 		similar1++;
    // 	}
    // }
    // hello new world
    // world counter hi hello

    // Calculate similarity percentage
    if (count1 == 0 || count2 == 0) {
        return 0;
    } else {
        float similarity = (similar_words * 100.0) / ((count1 + count2) / 2.0);
        similarity += 0.51;
        return (int)similarity;
    }
}
