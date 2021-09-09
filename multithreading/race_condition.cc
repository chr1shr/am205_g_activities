#include <cstdio>
#include <cstring>

#include "omp.h"

int main(int argc,char **argv) {

    // Print a syntax message if a command-line argument isn't provided
    if(argc!=2) {
        fputs("Syntax: ./race_condition <keyword>\n\n"
              "<type> can be: 'wrong' for the incorrect default\n"
              "               'atomic' for the atomic keyword\n"
              "               'critical' for the critical keyword\n"
              "               'reduction' for the reduction keyword\n",stderr);
        return 1;
    }
    
    // Read the omp keyword
    int keyword;
    if(strcmp(argv[1],"wrong")==0) keyword=0;
    else if(strcmp(argv[1],"atomic")==0) keyword=1;
    else if(strcmp(argv[1],"critical")==0) keyword=2;
    else if(strcmp(argv[1],"reduction")==0) keyword=3;
    else {
        fputs("Unknown omp keyword\n",stderr);
        return 1;
    }

    // Compute 1*1+...+1024*1024
    unsigned int c=0;
    switch(keyword) {
        // Incorrect default, will have race condition if run in parallel
        case 0: 
#pragma omp parallel for
                for(unsigned int i=0;i<1024;i++) {
                    c=i*i+c;
                }       
                break;
        
        // Atomic keyword
        case 1:
#pragma omp parallel for shared(c)
                for(unsigned int i=0;i<1024;i++) {
                    int d=i*i;
#pragma omp atomic
                    c+=d;
                }       
                break;
        
        // Critical keyword
        case 2:
#pragma omp parallel for
                for(unsigned int i=0;i<1024;i++) {
                    int d=i*i;
#pragma omp critical
                    {
                    // You can more code here
                    c+=d;                    
                    }
                }       
                break;

        // Reduction keyword
        case 3: 
#pragma omp parallel for reduction(+:c)
                for(unsigned int i=0;i<1024;i++) {
                    c=i*i+c;
                }       
                break;
    }
    printf("Sum=%u\n",c);
}