/***
 * This is a literal translation of the Acey Ducey game
 * this includes warts (and some bugs), as included in the original
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// to be more 1:1 with the basic source, let's simulate BAS RND
double RND() {
    int random = (rand() % 1000);
    return ((double)random / 1000);
}

int main(int argc, char *argv[]) {
    srand(time(NULL)); // we have to seed random in C

    printf("%40s%s\n", "", "ACEY DUCEY CARD GAME");
    printf("%26s%s\n\n\n", "", "CREATIVE COMPUTING  MORRISTOWN, NEW JERSEY");

    printf("ACEY-DUCEY IS PLAYED IN THE FOLLOWING MANNER \n");
    printf("THE DEALER (COMPUTER) DEALS TWO CARDS FACE UP\n");
    printf("YOU HAVE AN OPTION TO BET OR NOT BET DEPENDING\n");
    printf("ON WHETHER OR NOT YOU FEEL THE CARD WILL HAVE\n");
    printf("A VALUE BETWEEN THE FIRST TWO.\n");
    printf("IF YOU DO NOT WANT TO BET, INPUT A 0\n");

    int n=100;
    int m=0;
    int a, b, c, q;
    char retry[4];
    line_110: q=100;

    line_120: printf("YOU NOW HAVE %i DOLLARS.\n\n", q);
    goto line_260;

    line_210: q=q+m;
    goto line_120;

    line_240: q=q-m;
    goto line_120;

    line_260: printf("HERE ARE YOUR NEXT TWO CARDS: \n");
    line_270: a=(int)((14*RND())+2);
    if(a<2) goto line_270;
    if(a>14) goto line_270;
    line_300: b=(int)((14*RND())+2);
    if(b<2) goto line_300;
    if(b>14) goto line_300;

    if(a<11) goto line_400;
    if(a==11) goto line_420;
    if(a==12) goto line_440;
    if(a==13) goto line_460;
    if(a==14) goto line_480;
    line_400: printf("%i\n", a);
    goto line_500;
    line_420: printf("JACK\n");
    goto line_500;
    line_440: printf("QUEEN\n");
    goto line_500;
    line_460: printf("KING\n");
    goto line_500;
    line_480: printf("ACE\n");

    line_500: if(b<11) goto line_550;
    if(b==11) goto line_570;
    if(b==12) goto line_590;
    if(b==13) goto line_610;
    if(b==14) goto line_630;
    line_550: printf("%i\n", b);
    goto line_640;
    line_570: printf("JACK\n");
    goto line_640;
    line_590: printf("QUEEN\n");
    goto line_640;
    line_610: printf("KING\n");
    goto line_640;
    line_630: printf("ACE\n");

    line_640: printf("\n\n");
    printf("WHAT IS YOUR BET ");
    scanf("%i", &m);

    if(m!=0) goto line_680;
    printf("CHICKEN!!\n\n");
    goto line_260;

    line_680: if(m<=q) goto line_730;
    printf("SORRY, MY FRIEND, BUT YOU BET TOO MUCH.\n");
    printf("YOU HAVE ONLY %i DOLLARS TO BET.\n", q);
    goto line_640;

    line_730: c=(int)((14*RND())+2);
    if(c<2) goto line_730;
    if(c>14) goto line_730;
    if(c<11) goto line_810;
    if(c==11) goto line_830;
    if(c==12) goto line_850;
    if(c==13) goto line_870;
    if(c==14) goto line_890;
    line_810: printf("%i\n", c);
    goto line_900;
    line_830: printf("JACK\n");
    goto line_900;
    line_850: printf("QUEEN\n");
    goto line_900;
    line_870: printf("KING\n");
    goto line_900;
    line_890: printf("ACE\n");

    line_900: printf("\n");
    if(c>a) goto line_930;
    goto line_970;
    line_930: if(c>=b) goto line_970;
    printf("YOU WIN!!\n");
    goto line_210;
    line_970: printf("SORRY, YOU LOSE\n");
    if(m<q) goto line_240;

    printf("\n\n");
    printf("SORRY, FRIEND, BUT YOU BLEW YOUR WAD.\n");

    printf("\n\n");
    printf("TRY AGAIN (YES OR NO)\n");
    scanf("%s", retry);
    if(strcmp("YES", retry) == 0) goto line_110;
    printf("O.K., HOPE YOU HAD FUN!\n");

    return 0;
}