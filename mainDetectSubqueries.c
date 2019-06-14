/** This works! */
/** Permanent link: http://rextester.com/HGM93937 */
/** Permanent link: http://rextester.com/MIYW80272 */
/** Permanent link: http://rextester.com/XAUMUK24748 */
/**************************************************************************************************************************************/
/** Microsoft (R) C/C++ Optimizing Compiler Version 19.00.23506 for x86 */
/** Detect and extract subqueries from SQL */
/** Detect and extract subqueries from SQL 3rd go */
/** Code by Twareintor */

#include  <stdio.h>
#include <windows.h>

const char* szTest[] = {
    "select * from Assets where ClsId in (\r\n\tselect Class from Archives where DateArchived>=DateValue(Year(Now())-4, 1, 1) and ArID<>n",
    "ull and NameArchived not like '%))' or LCase(Comments) in (  \t   select 'interrupted' union select 'cleared' union select 'resol",
    "ved' union select 'solved') or LCase(SpecialRemark) like '%long_term%' or LCase(SpecialRemark) like '%long term%'    )) and Left",
    "(Kennzeichen, 10) in (    select distinct left(Kennzeichen, 10) from Verbraucher    \n) sort by ClsId asc, Assignment asc;       ",
//  "00000000000000001111111111111111222222222222222233333333333333334444444444444444555555555555555566666666666666667777777777777777",
//  "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef",
       
};

const char* szRuler[] = {
    "00000000000000001111111111111111222222222222222233333333333333334444444444444444555555555555555566666666666666667777777777777777",
    "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef",
    
};
char szDebug[6][0x80];

int GetSubqueries(char* szsSubqueries, const char* szQuery, size_t nQuerySize);

char* Tolower(char* p){for ( ; *p; ++p) *p = tolower(*p);}

char* ToUPPER(char* p){for ( ; *p; ++p) *p = toupper(*p);}

char* ToCapital(char* p){*p = toupper(*p);}

int IsKeyword(char* szTestString, const char* szKeyword, size_t keywordSize);

int main(void)
{
    char* szQuery = (char*)GlobalAlloc(GPTR, 0x80*0x04+0x01); /** reserve place for the nullchar */
    int i;

    for(i = 0; i<0x04; i++) memcpy(szQuery+i*0x80, szTest[i], 0x80);
    /** printf("%s\n", szQuery); */
    /** the test of getting subqueries here */
    char* szSubqueries = (char*)GlobalAlloc(GPTR, 0x80*0x04+0x01); /** the same size as the query... */
    
    GetSubqueries(szSubqueries, szQuery, 0x80*0x04);
    int j = 0;
    char* p = szSubqueries;
    while(*p)
    {
        printf("\"%s\"\n", p);
        while(*(++p)); ++p;
        
    }
    
    printf("%s\n", szDebug[0]);
    printf("%s\n", szDebug[1]);
    
    GlobalFree(szSubqueries);
    GlobalFree(szQuery);
    printf("Hello, world!\n");
    return 0;
}


int GetSubqueries(char* szsSubqueries, const char* szQuery, size_t nQuerySize)
{
    /** TO DO: Revision and optimization; */
    /** it does what its name says and will be part of a query editing and formatting utility project */
    char* p = szQuery;
    const char* szKeywords[] = {"select", "$$$$$$$$$"}; /** second is a dummy string as reserve */
    int nPar = 0; /** counts parantheses: increases with '(' decreases with ')'; when 0, end of block */
    char* begin, *end;
    int posInSubq = 0; /** current position where to write in the output string */
    int nOdd = 0; /** text qualifiers: the parantheses between qualifiers are ignored */
    int i = 0;
    while(*p)
    {
        if('('==*p)
        {
            nPar++; /** increases with every open one, then ignore the blanks, tabs, returns and linefeeds */
            ++p;
            /** printf("%s, %d\n%s", *szKeywords, sizeof(*szKeywords), p); */
            if(IsKeyword(p, szKeywords[0], sizeof(szKeywords[0])-2))  /** */  
            {
                begin = p;
                while(nPar) /** as long as the final counter-paranthesis not found... */
                {
                    if('\''==*p) nOdd = !nOdd;
                    sprintf(szDebug[0], "%d", nOdd);
                    nPar+=(('('==*p)-(')'==*p))*(!nOdd);
                    if(0==*p) break;
                    ++p;
                    sprintf(szDebug[1], "%d", nPar);
                }
                end = p;
                size_t nchars = end-1-begin;
                memcpy(szsSubqueries + posInSubq, begin, nchars);
                posInSubq+=nchars;
                szsSubqueries[posInSubq++] = '\0';
            }
        }
        else if(')'==*p)
        {
            nPar--; /** decreases with every closed one */
        }
        if(0==*p) break;
        ++p;
        ++i;
    }
    printf("\n");
    return 0;
}

int IsKeyword(char const* szTestString, const char* szKeyword, size_t keywordSize)
{
    char* p = szTestString;
    while(' '==*p||'\t'==*p||'\r'==*p||'\n'==*p) ++p;
    return !memcmp(szKeyword, p, keywordSize); /** sizeof(*szKeyword)-2) */
}

/**************************************************************************************************************************************/

/** Output must be =  


"select Class from Archives where DateArchived>=DateValue(Year(Now())-4, 1, 1) and ArchID<>null and NameArchived not like '(%)' or LCase(SpecialRemark) in (select 'interrupted' union select 'cleared' union select 'resolved' union select 'solved') or LCase(SpecialRemark) like '%long_term%' or LCase(SpecialRemark) like '%long term%'"
"select distinct left(Kennzeichen, 10) from Verbraucher10"
0
0
Hello, world!



*/
