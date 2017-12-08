//
//  main.c
//  multistructlist
//
//  Created by 津田準 on 2017/12/08.
//  Copyright © 2017 津田準. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLASS 10
#define MAX_NUMBER 40


struct STUDENT {
    struct STUDENT *clink;
    struct STUDENT *nlink;
    struct CLASS *class;
    struct NUMBER *number;
    char name[16];
};

struct CLASS {
    struct STUDENT *clink;
    int value;
} class[MAX_CLASS];

struct NUMBER {
    struct STUDENT *nlink;
    int value;
} number[MAX_NUMBER];

void error(char *s){
    fprintf(stderr, s);
    exit(1);
}

void initialize(){
    int i = 0;
    
    for(i = 0; i < MAX_CLASS; i++){
        class[i].clink = NULL;
        class[i].value = i;
    }
    for(i = 0; i < MAX_NUMBER; i++){
        number[i].nlink = NULL;
        number[i].value = i;
    }
}

void add(int x, char name[]){
    struct STUDENT *p;
    struct STUDENT *current;
    if( (p = malloc(sizeof(struct STUDENT))) == NULL)
        error("メモリが足りません\n");
    if(class[x].clink == NULL){
        class[x].clink = p;
        p -> class = &class[x];
        p -> number = &number[1];
        strcpy(p -> name, name);
    }else{
        current = class[x].clink;
        int i = 2;
        if(strcmp(name, current -> name) < 0){
            p -> clink = current;
            class[x].clink = p;
            p -> class = &class[x];
            p -> number = &number[1];
            strcpy(p -> name, name);
            while(current != NULL){
                current -> number = &number[i];
                current = current -> clink;
                i++;
            }
        }else{
            while( current -> clink != NULL ){
                if(strcmp(name, current -> clink -> name) < 0)
                    break;
                current = current -> clink;
                i++;
            }
            p -> clink = current -> clink;
            current -> clink = p;
            p -> class = &class[x];
            strcpy(p -> name, name);
            while( p != NULL){
                p -> number = &number[i];
                p = p -> clink;
                i++;
            }
            
        }
    }
}

void getNameList(int x){
    struct STUDENT *p;
    for(p = class[x].clink; p != NULL; p = p -> clink)
        printf("%d : %s\n", p -> number -> value, p -> name);
}



int main(int argc, const char * argv[]) {
    initialize();
    int flg = 1;
    while( flg ){
        int a = 0;
        int b = 0;
        char name[16];
        printf("名簿に生徒を追加 : 1\n");
        printf("生徒名簿を表示: 2\n");
        printf("終了: 3\n");
        scanf("%d", &a);
        switch(a){
            case 1:
                printf("クラス番号を入力\n");
                scanf("%d", &b);
                printf("名前を入力\n");
                scanf("%s", name);
                add(b, name);
                printf("生徒が名簿に追加されました\n");
                break;
            case 2:
                printf("クラスナンバーを入力してください\n");
                scanf("%d", &b);
                printf("%d組の名簿は以下の通りです\n", b);
                getNameList(b);
                break;
            case 3:
                flg = 0;
                break;
            default:
                flg = 1;
                break;
                
        }
    }
    return 0;
}
