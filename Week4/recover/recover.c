#include <stdio.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
	//check correct command-line args
	if (argc != 2) {
		fprintf(stderr, "Usage:./recover image\n");
		return 1;
	}  
    
    //return error if unable to open file
    FILE *file = fopen(argv[1], "r");
	if (file == NULL) {
		fprintf(stderr, "Could not open %s.\n", argv[1]);
		return 2;
	}

    //counter to keep track of iterations, number of jpeg image to be passed from sprintf, buffer which holds 512 bytes
    int n = 0;
    char jpegname[8]; 
    uint8_t buffer[512];
   
    //assign temporary file value
    FILE *holder = NULL; 
    //iterate over until program reaches the end of the file
    while (!feof(file)) {
        //check if matches start of jpeg file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] >= 0xe0 && buffer[3] <= 0xef)) {
            //close holder file if already present there
            if (holder != NULL) {
                fclose(holder);
            }
            //name files with three digits in format ###, with zeroes to pad empty values
            sprintf(jpegname, "%03d.jpg", n);
            //write image to holder file
            holder = fopen(jpegname, "w");
            //write new file with buffer added
            fwrite(buffer, sizeof(buffer), 1, holder);
            n++;
        } else if (n != 0) {
            //continue writing to holder file until next jpeg signature
            fwrite(buffer, sizeof(buffer), 1, holder);            
        }
        fread(buffer, sizeof(buffer), 1, file);
    }
    //close the file
    fclose(file);
    return 0;
}
