/*
 * maxblanks.c
 *
 * Copyright 2015 U0128754 <U0128754@U0128754-TPL-A>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>

#define BUF_SZ 1024

char* nextLine() {
    char *line, buffer[BUF_SZ];
    int lineSz = 1;

    line = malloc(1);

    if(line == NULL) {
        perror("fail to allocate buffer for a line.");
        exit(1);
    }

    line[0] = '\0';

    while(fgets(buffer, BUF_SZ, stdin)) {
        lineSz += strlen(buffer);

        line = realloc(line, lineSz);

        if(line == NULL) {
            perror("fail to re-allocate buffer for a line.");
            exit(1);
        }

        strcat(line, buffer);

        if(lineSz > 1 && line[lineSz-2] == '\n') {
            // line[lineSz-2] = '\0';
            break;
        }
    }

    return lineSz == 1 ? NULL : line;
}

int max (int i, int j) {

    return i > j ? i : j;
}

int min (int i , int j) {
    return i < j ? i:j;
}

int countMaxBlanks(char *str) {
    if (str == NULL) return 0;

    int cnt = 0;
    int len = strlen(str);

    char *p = str;
    char c = 0;
    int nc = 0;

    for( c = *p; c!=0; c = *p) {
        //   printf("check from %dth char\n",p-str);
        nc++;
        if(isspace(c)) {

            if(isspace(*(p - cnt/2))  || isspace(*(p + cnt/2))) {
                {

                    char *h, *t ;

                    for(h=p;  h != str && isspace(*(h-1)); h--) {
                        nc++;
                    }

                    for(t=p;  *t!=0 && isspace(*t); t++) {
                        nc++;
                    }
                    cnt = max (cnt, t - h);
                    //  printf("max blank seq %d\n", cnt);
                }
            }
        }
        p = p+cnt+1 < str+len ? p+cnt+1 : str+len;
    }

    //    printf("total chcked %d chars\n", nc);
    return cnt;
}

int slowCount( char *str) {
    if (str == NULL) return 0;

    char *a = str;
    char c;

    int cnt , n;
    cnt = n = 0;

    while( (c=*a)!=0 ) {
        if(isspace(c)) {
            for(n = 0; isspace(*a); a++)
            {
                n++;
            }
            cnt = max(cnt, n);
        } else {
            for(a +=1; *a!=0 && !isspace(*a); a++) {};
        }
    }
    return cnt;
}

int main(int argc, char **argv) {
    char *line = NULL;
    while( (line =  nextLine()) != NULL) {
        printf("%d\n",countMaxBlanks(line));
        free(line);
    }

    return (0);
}

