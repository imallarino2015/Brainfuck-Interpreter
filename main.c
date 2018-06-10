#include<stdio.h>

int isValid(const char vc[],const char c){
    for(int a=0;vc[a];a++)
        if(c==vc[a])
            return 1;
    return 0;
}

unsigned findLoopBeg(char str[],unsigned index,char beg,char end){
    int bVal=0;
    do{
        if(str[index]==beg)
            bVal--;
        if(str[index]==end)
            bVal++;
        if(bVal==0)
            break;
        index--;
    }while(bVal!=0);
    return index;
}

int main(int argv,char** argc){
    ///TODO: Allow multiple different ways to use program (terminal + file)
    ///Initailize program

    //printf("%x\n",&ptr);

    const char VAL_CHAR[]={'+','-',',','.','[',']','<','>'};
    const enum OP{INC=0,DEC,INPUT,CHAR_OUT,LOOP_BEG,LOOP_END,PREV_ADDR,NEXT_ADDR};
    char memory[256];
    for(unsigned a=0;memory[a];a++)
        memory[a]=0;
    unsigned char ptr=0;
    ///Load file in to memory in entirety
    ///TODO: add the whole file to memory, remove whitespace

    const unsigned BUFFER_SIZE=1024;
    char buffer[BUFFER_SIZE];

    FILE* file=fopen("example.bf","r");

    fscanf(file,"%s",buffer);
    ///fscanf(file,"%s",buffer);
    ///fgets(buffer,BUFFER_SIZE,file);

    ///Check all characters valid

    unsigned size=0;
    for(;buffer[size];size++)
        if(!isValid(VAL_CHAR,buffer[size])){
            printf("The valid characters are: ");
            for(int b=0;VAL_CHAR[b];b++)
                printf("%c ",VAL_CHAR[b]);
            printf("\nPlease check your input.");
            return 1;
        }

    ///Check matching brackets

    int bCount=0;
    for(int a=0;buffer[a];a++){
        if(buffer[a]==VAL_CHAR[LOOP_BEG])
            bCount++;
        if(buffer[a]==VAL_CHAR[LOOP_END])
            bCount--;
        if(bCount<0)
            break;
    }
    if(bCount!=0){
        printf("Mismatching brackets.\n");
        printf("Please check your input.");
        return 2;
    }

    ///Sequentially iterate through characters
    ///Check for loop characters
    ///Attach characters to functions/actions

    for(int a=0;buffer[a];a++){
        if(buffer[a]==VAL_CHAR[INC]){   //increment the selected value
            memory[ptr]++;
        }
        if(buffer[a]==VAL_CHAR[DEC]){   //decrement the selected value
            memory[ptr]--;
        }
        if(buffer[a]==VAL_CHAR[INPUT]){ //ask the user for input
            printf("\n");
            memory[ptr]=getchar();
            getchar();
        }
        if(buffer[a]==VAL_CHAR[CHAR_OUT]){  //print the selected value on the screen
            printf("%c",memory[ptr]);
        }
        if(buffer[a]==VAL_CHAR[LOOP_END]){  //return to the index of the matching bracket
            if(memory[ptr]!=0){
                a=findLoopBeg(buffer,a,VAL_CHAR[LOOP_BEG],VAL_CHAR[LOOP_END]);
            }
        }
        if(buffer[a]==VAL_CHAR[PREV_ADDR]){ //increment the address of the pointer
            ptr--;
        }
        if(buffer[a]==VAL_CHAR[NEXT_ADDR]){ //decrement the address of the pointer
            ptr++;
        }
    }

    ///Finalize program (execution successful)

    fclose(file);
    return 0;
}