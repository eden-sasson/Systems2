// Eden Sasson 6219808
// I affirm that I wrote this program myself without any help from any other people or sources from the internet.
// this code will allow flip, vertical flip, enlarging and scaling of a bmp file
#include <stdlib.h>
#include "bmplib.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>

/*
 * This method enlarges a 24-bit, uncompressed .bmp file
 * that has been read in using readFile()
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the original number of rows
 * cols     - the original number of columns
 *
 * scale    - the multiplier applied to EACH OF the rows and columns, e.g.
 *           if scale=2, then 2* rows and 2*cols
 *
 * new      - the new array containing the PIXELs, allocated within
 * newrows  - the new number of rows (scale*rows)
 * newcols  - the new number of cols (scale*cols)
 */
int enlarge(PIXEL* original, int rows, int cols, int scale,
	    PIXEL** new, int* newrows, int* newcols)
{
  /* THIS IS THE METHOD THAT YOU SHOULD WRITE */
  int row, col;
  if ((rows <= 0) || (cols <= 0)) return -1;
  if (scale <= 0) return -1;
  // setting the values
	* newrows = (scale*rows);
	* newcols = (scale*cols);
  
  * new = (PIXEL*)malloc((* newrows)*(* newcols)*sizeof(PIXEL));

  for(col = 0; col < *newcols; col++)
  {
    for(row = 0; row < *newrows; row++)
    {
      PIXEL* o = original + (row/scale) + (col/scale) * (cols - 1);
      PIXEL* n = (*new) + row + col * (*newcols - 1);
      *n = *o;	
    }	
  }
  return 0;
}

/*
 * This method rotates a 24-bit, uncompressed .bmp file that has been read
 * in using readFile(). The rotation is expressed in degrees and can be
 * positive, negative, or 0 -- but it must be a multiple of 90 degrees
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the number of rows
 * cols     - the number of columns
 * rotation - a positive or negative rotation,
 *
 * new      - the new array containing the PIXELs, allocated within
 * newrows  - the new number of rows
 * newcols  - the new number of cols
 */
int rotate(PIXEL* original, int rows, int cols, int rotation,
	   PIXEL** new, int* newrows, int* newcols)
{
  /* THIS IS THE METHOD THAT YOU SHOULD WRITE */
  int row, col;
  if ((rows <= 0) || (cols <= 0)) return -1;
 // setting the values
  if((rotation == 90) || (rotation == -270))
	{
		*newrows = cols;	
		*newcols = rows;
	}
  if((rotation == 180) || (rotation == -180))
	{
		*newrows = rows;
		*newcols = cols;
	}
  if((rotation == 270) || (rotation == -90))
	{
		*newrows = cols;	
		*newcols = rows;
	}
  * new = (PIXEL*)malloc((* newrows)*(* newcols)*sizeof(PIXEL));
  
  for(row = 0; row < rows; row++)
	{
    	for(col = 0; col < cols; col++)
		{
			PIXEL* o = original + row*cols + col;

			// checks value of rotation
			if ((rotation == 90) || (rotation == -270))
			{	
				// 90 and -270 is in the same position
				PIXEL* n = (*new) + (cols - col - 1) * rows + row;
				*n = *o;
			}
			// checks value of rotation
			else  if ((rotation == 180) || (rotation == -180))
			{  
				// 180 and -180 is in the same position
				PIXEL* n = (*new) + ((rows - row - 1) * cols) + (cols - col - 1);
				*n = *o;
			}
			// checks value of rotation
			else if ((rotation == 270) || (rotation == -90))
			{
				// 270 and -90 is in the same position
				PIXEL* n = (*new) + (col * rows) + (rows - row - 1);
				*n = *o;
			}
			// if not a multiple of 90
			else
			{
			printf("needs to be a multiple of 90\n");
			return 1;
			}

		}         
	}       
  return 0;
}

/*
 * This method Vertically flips a 24-bit, uncompressed bmp file
 * that has been read in using readFile().
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the number of rows
 * cols     - the number of columns
 *
 * new      - the new array containing the PIXELs, allocated within
 */

int verticalflip (PIXEL *original, PIXEL **new, int rows, int cols)
{
  /* THIS IS THE METHOD THAT YOU SHOULD WRITE */
  int row, col;

  if ((rows <= 0) || (cols <= 0)) return -1;

  *new = (PIXEL *) malloc (rows*cols*sizeof(PIXEL));

  for (row=0; row < rows; row++)
  {
    for (col=0; col < cols; col++) 
    {
      PIXEL* o = original + row*cols + col;
	  PIXEL* n = (*new) + ((rows - row - 1) * cols) + (cols - col - 1);
      *n = *o;
    }
  }  
  return 0;
}

/*
 * This method horizontally flips a 24-bit, uncompressed bmp file
 * that has been read in using readFile().
 *
 * THIS IS GIVEN TO YOU SOLELY TO LOOK AT AS AN EXAMPLE
 * TRY TO UNDERSTAND HOW IT WORKS
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the number of rows
 * cols     - the number of columns
 *
 * new      - the new array containing the PIXELs, allocated within
 */
int flip (PIXEL *original, PIXEL **new, int rows, int cols)
{
  int row, col;

  if ((rows <= 0) || (cols <= 0)) return -1;

  *new = (PIXEL*)malloc(rows*cols*sizeof(PIXEL));

  for (row=0; row < rows; row++)
    for (col=0; col < cols; col++) {
      PIXEL* o = original + row*cols + col;
      PIXEL* n = (*new) + row*cols + (cols-1-col);
      *n = *o;
    }

  return 0;
}

int main(int argc, char *argv[])
{
  int r, c;
  PIXEL *b, *nb;

  readFile("example.bmp", &r, &c, &b);
  flip(b, &nb, r, c);
  writeFile("result.bmp", r, c, nb);
	// set 
	int ch;
	extern int optind;
	extern char *optarg;

  int sflag=0, rflag=0, vflag = 0, fflag=0, oflag = 0;
	int rnum = 0, snum =0;
	// files
  char *ifile;
  char *ofile;
  
	// usage statment
	static char usage[] = "Usage: %s bmptool [-f | -r degrees |-s scale| -v ] [-o output_file] [input_file]";
	
	// cases
	while((ch = getopt(argc, argv,"fr:s:vo:")) != -1)
	{
		switch(ch)
    	{
		
			case 's':
			sflag = 1;
			snum = atoi(optarg);
			break;
		
			case 'r': 
			rflag = 1;
			rnum = atoi(optarg);
			break;
		
			case 'v':
			vflag = 1;
			break;
		
			case 'f':
			fflag = 1;
			break;
		
			case 'o':
			oflag = 1;
			ofile = optarg;
			break;
		
			case '?':
			printf("%s", usage);
			return 1;
			break;
  		
		}
	}
	// input file
	if(argv[optind]!=NULL)
	{
		ifile=argv[optind];
	}
	else
	{
		ifile = NULL;
		readFile(ifile, &r, &c, &b);
	}
  // first scale, then rotate, vertical and regular flip

	if (sflag == 1)
	{
		// can only scale by 2 or 3
		if((snum == 2) || (snum == 3))
    	{    
      		enlarge(b, r, c, snum, &b, &r, &c);
    	}
    	else
    	{
			// if scaled by anything other than 2 or 3
			printf("can only scale 2 or 3 times\n");
			return 1;
		}	 
  	}
	// flags
	if (rflag == 1)
	{
    	rotate(b, r, c, rnum, &b, &r, &c);
  	}
	if (vflag == 1)
	{
   		verticalflip(b, &b, r, c);
		flip(b, &b, r, c);
	}
	if (fflag == 1)
	{
    
    	flip(b, &b, r, c);
      
	}
	// output file
	if(oflag == 1)
	{
		writeFile(ofile, r, c, b);
	}
	else
	{
		ofile=NULL;
		// if no output file name
		writeFile(ofile, r, c, b);
	} 
  
	// free and end program
	free(b);
	free(nb);
	return 0;
}
