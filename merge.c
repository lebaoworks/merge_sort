#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxN 5000

int list[MaxN];        //Input List
int N;                 //Elements Count

int temp[MaxN];        //Save merge result

//Merge A and B into temp
void Merge(int A[], int n, int B[], int m)
{
    int i = 0, j = 0, p = 0;
    while (i < n || j < m)              //Haven't got all of those lists
    {
        if (i == n)                     //Got all of A
        {
            temp[p++] = B[j++];
            continue;
        }
        if (j == m)
        {
            temp[p++] = A[i++];         //Got all of B
            continue;
        }
        if (A[i] < B[j])                //Current element in A is smaller than current element in B
            temp[p++] = A[i++];
        else
            temp[p++] = B[j++];
    }
}

//Usage: Sort child lists lindex to child lists r_index
//Return: The number of elements in those child lists
int Sort(int l_index, int r_index)
{
    //Smallest case: 1 child list
    if (l_index == r_index)
        return 1;                               //return Number of elements
    int m_index = (l_index + r_index) >> 1;     //We will sort (l_index -> m_index) -> l_index
                                                //             (m_index+1 -> r_index) -> m_index
                                                                    
    int n = Sort(l_index, m_index);             //sort (l_index -> m_index)
    int m = Sort(m_index + 1, r_index);         //sort (m_index+1 -> r_index)

    Merge(&list[l_index], n, &list[m_index+1], m);      //Merge l_index and m_index
    memcpy(&list[l_index], temp, (n + m)*sizeof(int));  //Copy merged list from temp back to the list
    
    return n + m;
}
int main(int argc, char* argv[])
{
    //Check arguments
    if (argc < 2)
    {
        printf("Usage: Merge_Sort <ele_1> <ele_2> ... <ele_n>\n");
        return 1;
    }
    if (argc >4998)
    {
        printf("Exceed Maximum Size!!!\n");
        return 1;
    }

    //Get elements
    N = argc-1;
    for (int i=0; i<N; i++)
        list[i] = atoi(argv[i+1]);
    
    //Sort list
    Sort(0, N-1);
    return 0;
}

