#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h> 
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])  
// Alphabet size 
#define ALPHABET_SIZE (26)   
#define WORD 50
// Converts key current character into index 
// use only 'a' through 'z' and lower case 
#define CHAR_TO_INDEX(c) ((int)c - (int)'a') 
// trie node 
struct TrieNode 
{
    char edge;
    long unsigned int count;
    struct TrieNode *children[ALPHABET_SIZE]; 
    // isEndOfWord is true if the node represents 
    // end of a word 
    bool isEndOfWord; 
}TrieNode; 
// Returns new trie node (initialized to NULLs) 
struct TrieNode *getNode(char e) 
{ 
    struct TrieNode *pNode = NULL; 
    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode)); 
    if (pNode) 
    { 
        int i;  
        pNode->edge = e; 
        pNode->isEndOfWord = false;  
        for (i = 0; i < ALPHABET_SIZE; i++) 
            pNode->children[i] = NULL; 
    }  
    return pNode; 
}  
// If not present, inserts key into trie  
void insert(struct TrieNode *root, const char *key) 
{ 
    int level,length = strlen(key),index;
    struct TrieNode *pCrawl = root;  
    for (level = 0; level < length; level++) 
    { 
        index = CHAR_TO_INDEX(key[level]); 
        if (!pCrawl->children[index]) 
            pCrawl->children[index] = getNode(key[level]);  
        pCrawl = pCrawl->children[index]; 
    }   
    pCrawl->count+=1;
    pCrawl->isEndOfWord = true; 
} 
//gcc -Wall -fno-stack-protector trietxt.c -o trietxt
void forWord(struct TrieNode *root,char word[]){
    int len = strlen(word);
    if(root == NULL) return;
    for(int i = 0; i < ALPHABET_SIZE ; i++){
       if(root->children[i]!=NULL){
           word[len]=root->children[i]->edge;
           word[len+1]=0;    
           if(root->children[i]->isEndOfWord==true){
               printf("%s %ld\n",word,root->children[i]->count);
           }
           forWord(root->children[i],word);
       }
    }
}
void backWord(struct TrieNode *root,char word[]){
  int len = strlen(word);
    if(root == NULL) return;
    for(int i = ALPHABET_SIZE-1; i >= 0 ; i--){
       if(root->children[i]!=NULL){
           word[len]=root->children[i]->edge;
           word[len+1]=0;
           if(root->children[i]->isEndOfWord==true){
               printf("%s %ld\n",word,root->children[i]->count);
           }
           backWord(root->children[i],word);
       }
    }  
}
int getword(char *w, struct TrieNode *root){
    char c;
    int len = 0;
    while(len < WORD+1){ 
        if(scanf("%c",&c)!=1){
            return 0;
        }
        if(c == '\n'||c== '\t' || c == ' ' || c == EOF)
        {
            w[len]='\0';
            insert(root,w);
            return 1;
            
        }
        if ((c>='a'&&c<='z'))
        {
            w[len]=c;
            len++;
        }
        if ((c>='A'&&c<='Z'))
        {
            w[len]=c+32;
            len++;
        }
    }
    return 1;
}
void freetrie(struct TrieNode *root){
    if(root == NULL) return;
    for(int i = 0 ; i < ALPHABET_SIZE ; ++i){
        if(root->children[i]!=NULL) freetrie(root->children[i]);
    }
    free(root);
}
int main(int argspace, char ** args) 
{  
    struct TrieNode *root = getNode('!'); 
    int flag=1;
    while(flag==1){
        char w[WORD];
        flag = getword(w,root);
        memset(w,'\0',WORD);
        if(flag == 0) break;
    }
    if(argspace == 2){
        if(strlen(args[1])==1){
            if(args[1][0]=='r'){
                char wb[WORD];
                backWord(root,wb);  
            }
        }
    }
    else{
        char wb[WORD];
        forWord(root,wb);
    }
    freetrie(root);
    return 0; 
} 