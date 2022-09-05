#include<bits/stdc++.h>

using namespace std;

#define debug 0

typedef struct state
{
    char letter;
    int r;
    int p;
    int s;

}state;

typedef struct DFA
{
    state* DFAstates;
    int InputStartState;
}DFA;

char beatingState(char x)
{
    if(x == 'R') return 'P';
    if(x == 'P') return 'S';
    if(x == 'S') return 'R';
}

int next(state* input, state* output, int inputptr, int outputptr)
{
    char o = output[outputptr].letter;
    if(o == 'R') return input[inputptr].r;
    if(o == 'P') return input[inputptr].p;
    if(o == 'S') return input[inputptr].s;

    printf("this should not be printed intptr = %d and outptr = %d \n", inputptr, outputptr);
}

state* process(state *input , state* output, int inputstart, int* outputstart)
{
    map<int,int> m;
    m.clear();

    int outputptr = (*outputstart) + 1;
    if(debug) printf("starting with outputptr = %d\n",outputptr);
    int inputptr = inputstart;

    char c = input[inputptr].letter;
    output[outputptr].letter = beatingState(c);

    while(1)
    {
        char n = input[next(input,output,inputptr,outputptr)].letter;

        if(c == 'R')
        {
            output[outputptr].r = outputptr + 1;
            output[outputptr+1].letter = beatingState(n); 
        }
        if(c == 'S')
        {
            output[outputptr].s = outputptr + 1;
            output[outputptr+1].letter = beatingState(n); 
        }        
        if(c == 'P')
        {
            output[outputptr].p = outputptr + 1;
            output[outputptr+1].letter = beatingState(n); 
        }

        m.insert({inputptr,outputptr});

        if(m.find(next(input,output,inputptr,outputptr)) != m.end() )
        {
            if(c == 'R')
            {
                output[outputptr].r = m[next(input,output,inputptr,outputptr)];
                output[outputptr+1].letter = 0; 
            }
            if(c == 'S')
            {
                output[outputptr].s = m[next(input,output,inputptr,outputptr)];
                output[outputptr+1].letter = 0; 
            }        
            if(c == 'P')
            {
                output[outputptr].p = m[next(input,output,inputptr,outputptr)];
                output[outputptr+1].letter = 0; 
            }

            if(debug) printf("Im breaking here and output ptr is %d \n",outputptr);

            return output;
        }

        inputptr = next(input,output,inputptr,outputptr);
        c =  input[inputptr].letter;
        outputptr++;
        *outputstart = outputptr ;
    }

    return output;

}

int selectInitState(state* input, int n)
{
    int r = 0;
    int p = 0;
    int s = 0;

    for(int i = 1 ; i <= n; i++)
    {
        char c = input[i].letter;
        if(c == 'R') r++;
        if(c == 'S') s++;
        if(c == 'P') p++;
    }

    if(max(max(r,p),s) == r) return beatingState('R');
    if(max(max(r,p),s) == p) return beatingState('P');
    if(max(max(r,p),s) == s) return beatingState('S');

}

int main()
{
    int n;
    cin >> n;

    state input[n+1];
    state* output = (state*) malloc(1001 * sizeof(state));
    for(int i = 1 ; i <= n ; i++)
    {
        char c; int r,p,s;
        cin >> c;
        cin >> r >> p >> s;
        input[i].letter = c;
        input[i].r = r;
        input[i].p = p;
        input[i].s = s;
    }

    int totalnodes = 0;

    for(int startstateitr = 1; startstateitr <= n ;startstateitr++)
    {
        process(input, output, startstateitr, &totalnodes);
    }

    printf("%d\n",(3*n + 1));

    char initialState = selectInitState(input,n);
    output[0].letter = initialState;
    for(int j = 0; j <= (3*n) ; j++)
    {
        printf("%c %d %d %d \n",output[j].letter,output[j].p,output[j].r,output[j].s);
    }

}