/*
//  main.c
//  Morse
//
//  Created by Amin Amjadi on 11/1/15.
//  Copyright © 2015 AIT. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct mtree
{
    char c;
    struct mtree *dit;
    struct mtree *dah;
}mt;

mt *insert(mt *r,char *code,char c)  /*insert function for tree*/
{
    if(r==NULL){
        r = (mt*) malloc(sizeof(mt));
        r->c = c;
        r->dit = r->dah = NULL;
        return r;
    }
    else if(code[0]=='.') r->dit=insert(r->dit,code+1,c);
    else if(code[0]=='-')r->dah=insert(r->dah,code+1,c); /* code[0]==‘_’  */
    else if(code[0]=='\0'){r->c=c; }
    return r;
};


void free_tree(mt *r) /*free function for tree*/
{
    if (r!=NULL) {
        free_tree(r->dit);
        free_tree(r->dah);
        free(r);
    }
    else return;
}
void decode(mt *r,char *code){
    char *ch;
    
    if (code[0]=='.') {
        decode(r->dit, code+1);
    }
    else if (code[0]=='-') {
        decode(r->dah, code+1);
    }
    else {
        ch=&r->c; /*ch gets the charater which we looking for and then we print it*/
        if (ch) {
            printf("%c",r->c);
        }
        else printf("'not found'"); /*if there is no ch then print not found for our decode funtion*/
    }
    
}

void encode(char code[26][10],char c)
{
    
    if(isupper(c)){
        printf("%s ",code[c-'A']); /*print the morse words(after each letter there is space)*/
    }
    else { /*after each space(new word) goes to the new line*/
        printf("\n");
    }
    
}


int main()
{
    mt *tree=NULL;
    char morse[27][10]={
        ".-", /*morse code of letter A*/
        "-...", /*morse code of letter B*/
        "-.-." , /*morse code of letter C*/
        "-.." , /*morse code of letter D*/
        "." , /*morse code of letter E*/
        "..-." , /*morse code of letter F*/
        "--." , /*morse code of letter G*/
        "...." , /*morse code of letter H*/
        ".." , /*morse code of letter I*/
        ".---" , /*morse code of letter J*/
        "-.-" , /*morse code of letter K*/
        ".-.." , /*morse code of letter L*/
        "--" , /*morse code of letter M*/
        "-." , /*morse code of letter N*/
        "---" , /*morse code of letter O*/
        ".--." , /*morse code of letter P*/
        "--.-" , /*morse code of letter Q*/
        ".-." , /*morse code of letter R*/
        "..." , /*morse code of letter S*/
        "-" , /*morse code of letter T*/
        "..-" , /*morse code of letter U*/
        "...-" , /*morse code of letter V*/
        ".--" ,  /*morse code of letter W*/
        "-..-" ,  /*morse code of letter X*/
        "-.--" , /*morse code of letter Y*/
        "--.." ,/*morse code of letter Z*/
        " "
    };

    /*insert all the elements to the tree*/
    tree=insert(tree, morse[26], '\n');
    tree=insert(tree, morse[4], 'E');
    tree=insert(tree, morse[8], 'I');
    tree=insert(tree, morse[18], 'S');
    tree=insert(tree, morse[7], 'H');
    tree=insert(tree, morse[21], 'V');
    tree=insert(tree, morse[20], 'U');
    tree=insert(tree, morse[5], 'F');
    tree=insert(tree, morse[0], 'A');
    tree=insert(tree, morse[17], 'R');
    tree=insert(tree, morse[11], 'L');
    tree=insert(tree, morse[22], 'W');
    tree=insert(tree, morse[15], 'P');
    tree=insert(tree, morse[9], 'J');
    tree=insert(tree, morse[19], 'T');
    tree=insert(tree, morse[13], 'N');
    tree=insert(tree, morse[3], 'D');
    tree=insert(tree, morse[1], 'B');
    tree=insert(tree, morse[23], 'X');
    tree=insert(tree, morse[10], 'K');
    tree=insert(tree, morse[2], 'C');
    tree=insert(tree, morse[24], 'Y');
    tree=insert(tree, morse[12], 'M');
    tree=insert(tree, morse[6], 'G');
    tree=insert(tree, morse[25], 'Z');
    tree=insert(tree, morse[16], 'Q');
    tree=insert(tree, morse[14], 'O');
    
    char a = '\0' ,b[256][10] ,c;     /* a:character we use for encoding
                                         b:character we use for decoding which is limited to just 256 letters
                                         c:character we use for continuing at the end
                                       */
    int i,j,k,z;
    c='y';
    while (c=='y' || c=='Y') {
        
        
        printf("for encode please enter 1,for decode 2:");
        scanf("%d",&i);
        while (getchar()!='\n') {
            
        } /*we put this to debug the scannig problem for next scanning*/
        if (i==1) {
            printf("please type the sentence which you want to convert to the morse:(in capital letters)\n");
            while (a!='\n') { /*we initialize 'a' as a='\0' before and we scan entry from user untill the new line*/
                scanf("%c",&a);
                encode(morse, a);
            }
            a = '\0'; /*we set 'a' to \0 again to wont have any problem after user wants to continue with another text*/
        }
        else if (i==2){
            printf("\nplease enter the morse which you want to decode:\n");
            j=0;
            k=0;
            scanf("%c", &b[k][j]);
            while (b[k][j]!='\n'){
                while (b[k][j]!=' ' && b[k][j]!='\n') {
                    ++j;
                    scanf("%c", &b[k][j]);
                }
                ++k; /*after each space go to the new 'k' to decode which means new word*/
                j=0;
                scanf("%c", &b[k][j]);
            }
            --k; /*because at last we count 'k' 1 time more before ending the loop*/
            z=k;
            for (k=0; k<=z; ++k) {
                if (b[k]) {
                    decode(tree, b[k]);
                }
            }
        }
        printf("\nDo you wish to continue?[y/n]");
        scanf("%s",&c); /*we scan entry from user if that is 'Y' or 'y' we go back again*/
        
    }
    free_tree(tree); /*free the tree at the end*/
    
    return 0;
}