#include<iostream>
#include <cstdio>
using namespace std;
#include<math.h>
#include <cstring>
#include <cstdlib>
#define UNASSIGNED 0
#define N 9
typedef unsigned char BYTE;

#define MAX 25

int takeInput(int sudoku[N][N])
{
    int size = 0;
   
    size=9;
    std::string sudoku_question;
    std::getline (std::cin,sudoku_question);
    //int grid[N][N];
    int i = 0;
    int x = 0;
    int y = 0;
    
    char key[] = "123456789b";
    char * pch;
    pch = strpbrk ( (char*)sudoku_question.c_str(), key);
    
    while (pch != NULL)
    {
      if (y == 9) { x++; y=0; }
      if (*pch == 'b')
      {
        //printf ("[0 , %d , %d] ", x, y);
        sudoku[x][y++] = 0;
      }
      else
      {
        //printf ("[%d, %d, %d] " , ((*pch) - '0'), x, y);
        sudoku[x][y++] = ((*pch) - '0');
      }
      pch = strpbrk (pch+1,key);
    }
    
        return size;
}

//Function to display solved Sudoku Board
void displaySolution(int sudoku[N][N], int size)
{
    printf("((");
    for(int i=0;i<size;i++)
    {   
        for(int j=0;j<size; j++)
        {
            if (i == 8 && j == 8)
                printf("%d))", sudoku[i][j]);
            else if ( ((j+1)%3) == 0)
            {
                if (j == 8)
                    printf("%d)),((", sudoku[i][j]);
                else
                    printf("%d),(", sudoku[i][j]);
            }
            else
                printf("%d,", sudoku[i][j]);
            
        }
    }
    cout<<"\n";
}

bool isFull(int sudoku[N][N], int size)
{
    int i,j;    
    for(i=0;i<size;i++)
        for(j=0;j<size;j++)
            if(!sudoku[i][j])
                return false;
    return true;
}

int findPossibleValues(int sudoku[N][N], int size, int a[], int r, int c)
{
    int n=0;
    int i,j;
    int s=(int)(sqrt(size));
    int b[N+1]={0};

    //Note no.s appeared in current row
    for(i=0; i<size; i++)
        b[sudoku[r][i]]=1;

    //Note no.s appeared in current column
    for(i=0; i<size; i++)
        b[sudoku[i][c]]=1;

    //Note no.s appeared in current block
    r=(r/s)*s, c=(c/s)*s;
    for(i=r; i<r+s; i++)
        for(j=c; j<c+s;j++)
            b[sudoku[i][j]]=1;

    //Fill array a[] with no.s unappeared in current row, column and block
    for(i=1;i<=size; i++)
        if(!b[i])
            a[n++]=i;

    return n;
}


void SolveSudoku(int sudoku[N][N], int size, int &solution_num, bool &solved_flag, bool &enough)
{
    int i,j, a[N+1]={0}, n=0;

    if(enough) //true if user does not want more solutions
        return;

    if(isFull(sudoku, size))    //true if now sudoku board is solved completely
    {
        solved_flag = 1;
    //cout<<"\n\nSolution no. "<<(solution_num++)<<endl;
        displaySolution(sudoku, size);
   
        // Maximum possible answers = 5472730538
        for(int x=1;x<=5472730538;x++)
        return;
    }

    //Find first vacant place/position
    int break_flag = 0;
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
            if(!sudoku[i][j])
            {
                break_flag = 1;
                break;
            }
        if(break_flag)
            break;
    }

    //check possibilities at that vacant place
    n = findPossibleValues(sudoku, size, a, i, j);
    for(int l=0;l<n;l++)
    {
        //put value at vacant place
        sudoku[i][j]=a[l];
        //now solve the updated board
        SolveSudoku(sudoku, size, solution_num, solved_flag, enough);
    }
    sudoku[i][j]=0;
}

int main()
{
    //Input
    int sudoku[N][N] = {0}, size;
    size = takeInput(sudoku);

    int solution_num = 1;
    bool solved_flag = 0;
    bool enough = false;
    SolveSudoku(sudoku, size, solution_num, solved_flag, enough);
    if(!solved_flag)
       cout<<"Board has no solutions."<<endl;
    return 0;
}
