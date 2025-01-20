
/*
    Simulator driver
*/

#include <stdio.h>
#include <strings.h>

typedef int Coord;

void write_to_file();
void load();
void display();

main(argc,argv)

    int		argc;
    char	**argv;

    {
	FILE	        *in,*out;
	int 		example,examples;
	char		pat[16][24],ch;

	if (argc < 2)
	    {
		printf("\nInsufficient arguments\n");
		exit(-1);
	    }


	in = fopen(argv[1],"r");
	out = fopen(argv[2],"w");

	if (in == NULL)
	    {
	        printf("Input file does not exist");
		exit(-1);
	    }

/*	examples = atoi(argv[2]);*/

/*	for (example = 0; example <= atoi(argv[2]); example++) */
	while (getc(in) != EOF)
	    {
              	load(in,pat);    /* load training pattern for class */
/*		printf("\nExample: %d\n",example); */
/*		display(pat); */
		write_to_file(out,pat);
	/*	ch = getchar();*/
/*		if (ch == EOF) write_to_file(out,pat); */
	    }

	printf("\nCompleted\n");
	fclose(in);
	fclose(out);
    }









/*
    Routine to load data into the initial (iteration 0) state of the network
*/

void
load(fptr,pat)

    FILE	*fptr;
    char        pat[16][24];

    {
	Coord	x,y;
	int	ch,skip;

	for (skip = 0; skip < 3; skip++)
	    do
		ch = getc(fptr); 
	    while(ch != '\n');

	for (y = 0; y < 24; y++)
	    {
	        for (x = 0; x < 16; x++)
		    {
			ch = getc(fptr);
			getc(fptr);
		    	switch (ch) {
				case '0' : pat[x][y] = '*';
					   break;
				case '1' : pat[x][y] = ' ';
					   break;
				default  : printf("Load: unexpected char: %d\n",ch);
					   exit(-1); }
		    }
/*	        ch = getc(fptr); /* skip EOL */
	    }
    }
	




/*
    Routine to write data to a file
*/

void
write_to_file(fptr,pat)

    FILE        *fptr;
    char        pat[16][24];

    {
        Coord   x,y;

        for (y = 0; y < 24; y++)
            {
                for (x = 0; x < 16; x++)
                    switch (pat[x][y]) {
                        case ' ' : fputc('0',fptr);
                                   break;
                        case '*' : fputc('1',fptr);
                                   break;
                        default  : printf("Write: unexpected char: %d\n",pat[x][y]);
                                   break; /*exit(-1);*/ }
		fputc('\n',fptr);
            }
    }






/*
    Display the current network state
*/

void
display(pat)

    char	pat[16][24];

    {
	Coord	x,y;

	for (y = 0; y < 24; y++)
	    {
	        for (x = 0; x < 16; x++)
		    switch(pat[x][y]) {
		        case ' ': putc(' ',stdout);
				  break;
			case '*': putc('*',stdout);
				  break;
			default : printf("\nImpossible character in array");
				  break; }
		printf("\n");
	    }
    }
