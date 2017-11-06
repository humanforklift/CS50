/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
	// ensure proper usage
	if (argc != 4)
	{
		printf("Usage:resize n infile outfile\n");
		return 1;
	}

	// remember filenames & factor to resize by
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];
		
    //check n is within acceptable range
    if (n  < 1 || n > 100) {
        fprintf(stderr, "n, the resize factor, must satisfy 0 < n <= 100.\n");
        return 2;
    }

	// open input file 
	FILE* inptr = fopen(infile, "r");
	if (inptr == NULL)
	{
		printf("Could not open %s.\n", infile);
		return 3;
	}

	// open output file
	FILE* outptr = fopen(outfile, "w");
	if (outptr == NULL)
	{
		fclose(inptr);
		fprintf(stderr, "Could not create %s.\n", outfile);
		return 4;
	}

	// read infile's BITMAPFILEHEADER
	BITMAPFILEHEADER bf;
	fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

	// read infile's BITMAPINFOHEADER
	BITMAPINFOHEADER bi;
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

	// ensure infile is (likely) a 24-bit uncompressed BMP 4.0
	if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
					bi.biBitCount != 24 || bi.biCompression != 0)
	{
		fclose(outptr);
		fclose(inptr);
		fprintf(stderr, "Unsupported file format.\n");
		return 5;
	}

	// create bitmap headers for changed image
	BITMAPFILEHEADER change_bf = bf;
	BITMAPINFOHEADER change_bi = bi;	
		
	//calculate new width and height
	change_bi.biWidth *= n;
	change_bi.biHeight *= n;

	// determine padding for scanlines
	int original_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
	int change_padding =  (4 - (change_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

	// Calculate file and image size
	change_bi.biSizeImage = ((sizeof(RGBTRIPLE) * change_bi.biWidth) + change_padding) * abs(change_bi.biHeight);
	change_bf.bfSize = change_bi.biSizeImage + (sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER));
	
	// write outfile's BITMAPFILEHEADER
	fwrite(&change_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

	// write outfile's BITMAPINFOHEADER
	fwrite(&change_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

	// iterate over infile's scanlines
	for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
	{
		// write each line 'x' amount of times
		for(int x = 0; x < n; x++)
		{
			// iterate over pixels in scanline
			for (int j = 0; j < bi.biWidth; j++)
			{
				// temporary storage
				RGBTRIPLE triple;

				// read RGB triple from infile
				fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

				// write RGB triple to outfile
				for(int y = 0; y < n; y++) 
				{
					fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
				}
			}

			// skip over padding in infile
			fseek(inptr, original_padding, SEEK_CUR);

			// then add it to outfile
			for (int k = 0; k < change_padding; k++)
			{
				fputc(0x00, outptr);
			}
		
			fseek(inptr, -(bi.biWidth * 3 + original_padding ), SEEK_CUR);
		}
		fseek(inptr, bi.biWidth * 3 + original_padding, SEEK_CUR);
	}

	// close infile
	fclose(inptr);

	// close outfile
	fclose(outptr);

	// success
	return 0;
}
