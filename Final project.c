#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOP 1
#define BOT 2

struct node
{
    char plate [15] ;/*string type variable*/
    struct node *link ;
} *front[5], *rear[5] ;/*declare front and rear object*/

char plate[15], temp[15] ;
int i ;

void adddq ( struct node**, struct node**, int, char* ) ;/*declare  add queue function*/
char* deldq ( struct node**, struct node**, int ) ;/*declare delete function*/
void push ( struct node**, char* ) ;/*declare push function*/
char* pop ( struct node** ) ;/*declare pop function*/
void qdisplay ( struct node * ) ;/*declare display function*/

void main( )
{
    char ad ;
    int s, lane = -1, min, lc ;
    printf("\n***Welcome to our project***\n");
    printf("\nGiving below the number of lane\n");

   while ( 1 )
    {
        for ( i = 0 ; i < 5 ; i++ )
        {
            printf( "lane %d: ", i ) ;/*print the number of lane*/
            qdisplay ( front[i] ) ;/*display the front number*/
        }
       printf("\nwhat do you want???\n");
        printf( "\n1.Park car\n2.Departure\n3.Quit\n(  choice 1 press A/ choice 2 press D/choice 3 press Q ): " ) ;/*print the choice options*/
        printf("\nEnter your choice:");
        ad = getch( ) ;/* read character function*/

        if ( toupper ( ad ) == 'Q' )
            exit ( 1 ) ;

        printf ( "\nEnter license plate num:" ) ;
        gets ( plate ) ;/* read string function*/
        ad = toupper ( ad ) ;

        if ( ad == 'A' )  /* arrival of car*/

        {
            lane = -1 ;  /* assume no lane is available*/

            min = 10 ;
            for ( i = 0 ; i < 5 ; i++ )
            {
                s = count ( front[i] ) ;/*count the number of front*/
                if ( s < min )
                {
                    min = s ;
                    lane = i ;
                }
            }

            if ( lane == -1 )/* when lane is equal to -1*/
                printf ( "\nNo room available" ) ;
            else
            {
                adddq ( &front[ lane ], &rear[ lane ], BOT, plate ) ;/*add queue function*/
                printf ( "\npark car at lane %d slot %d\n", lane, s ) ;
            }
        }
        else
        {
            if ( ad == 'D' )  /* departure of car */

            {
                for ( i = 0 ; i < 5 ; ++i )
                {
                    s = search ( front[i], plate ) ;
                    if ( s != -1 )
                    {
                        lane = i ;
                        break ;
                    }
                }
                if ( i == 5 )
                    printf ( "\nno such car!!\n" ) ;
                else
                {
                    printf ( "\ncar found at lane %d slot %d\n", lane, s ) ;
                    deldq ( &front[ lane ], &rear[ lane ], s ) ;/*delete queue */
                }
            }
            else if ( ad == 'Q' )
                    exit ( 1 ) ;
        }
    }
}

/*adds a new element at the end of queue */
void adddq ( struct node **f, struct node **r, int tb, char *p )
{
    struct node *q ;
    /* create new node */

    q = ( struct node * ) malloc ( sizeof ( struct node ) ) ;
    strcpy ( q -> plate, p ) ;/*string compare to p to q->plate*/
    q -> link = NULL ;

    /* if the queue is empty */
if ( *f == NULL )
        *f = q ;
    else
    {
        if ( tb == BOT )
            ( *r ) -> link = q ;
        else
        {
            q -> link = *f ;
            *f = q ;
            return ;
        }
    }
    *r = q ;
}

char* deldq ( struct node **f, struct node **r, int n )
{
    struct node *q, *top = NULL ;
    /* if queue is empty */
if ( *f == NULL )
        printf ( "queue is empty" ) ;
    else
    {
        if ( n == 0 )
        {
            strcpy ( temp, ( *f ) -> plate ) ;/* string copy function to copy string f->data to temp*/
            q = *f ;
            *f = ( *f ) -> link ;
            free ( q ) ;/*free the value of q*/
            return temp ;
        }
/* locate node */
        for ( i = 0 ; i < n ; i++ )
        {
            /* drive out cars */
            push ( &top, ( *f ) -> plate ) ;
         /* delete the node */
            q = *f ;
            *f = q -> link ;
            free ( q ) ;
        }
       /* delete the nth node */
         q = *f ;
        *f = q -> link ;
        free ( q ) ;
        for ( i = 0 ; i < n ; i++ )
        {
            strcpy ( temp, pop ( &top ) ) ;

            /* add the node */
        adddq ( f, r, TOP, temp ) ;
        }
    }
}

int count ( struct node *q )
{
    int c = 0 ;

    /* traverse the entire linked list */
while ( q!= NULL )
    {
        q = q -> link ;
        c++ ;
    }
    return c ;
}

int search ( struct node *q, char *p )
{
    int s = -1, c = 0 ;

    while ( q != NULL )
    {
        if ( strcmp ( p, q -> plate ) == 0 )/*compare string function to compare string p->plate to p*/
        {
            s = c ;
            break ;
        }
        else
        {
            q = q -> link ;
            c++ ;
        }
    }
    return ( s ) ;
}

/* adds a new element to the top of stack */
void push ( struct node **s, char* item )
{
    struct node *q ;
    q = ( struct node* ) malloc ( sizeof ( struct node ) ) ;/*dynamically allocation memory*/
    strcpy ( q -> plate, item ) ;/*copy string item to t->plate*/
    q -> link = *s ;
    *s = q ;
}

/* removes an element from top of stack */
char* pop ( struct node **s )
{
    struct node *q ;

    /* if stack is empty */
if ( *s == NULL )
    {
        return NULL ;
    }
    else
    {
        q = *s ;
        strcpy ( temp, q -> plate ) ;
        *s = q -> link ;
        free ( q ) ;/*free the value of q.*/
        return ( temp ) ;/*return temp*/
    }
}

void qdisplay ( struct node *q )
{
    while( q != NULL )/*when q is not equal to NULL.*/
    {
        printf ( "%s\t", q -> plate ) ;
        q = q -> link ;
    }
    printf ( "\n" ) ;
}

