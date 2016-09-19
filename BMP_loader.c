/***************************************************************************
*  FILE: BMP_loader.c
*  AUTHOR: Connor Beardsmore - 15504319
*  UNIT: CG200 Assignment S2 - 2016
*  PURPOSE: Quick bitmap loader, for 23-bit bitmaps with 1 plane only
*  LAST MOD: 19/09/16
*  REQUIRES: NONE
*  REFERENCE: http://www.dcs.ed.ac.uk/~mxr/gfx/2d/BMP.txt
***************************************************************************/

// FUNCTION: imageLoad()
// IMPORT: image (Image*), filename (char*)
// EXPORT: error (int)
// PURPOSE: Load image and read data into image

int imageLoad(char *filename, Image *image)
{
    FILE *file;
    unsigned long size;                 // image size (bytes)
    unsigned long i;                    // standard counter
    unsigned short int planes;          // image planes (1)
    unsigned short int bpp;             // bits per pixel (24)
    char temp;                          // temporary color storage

    // Open file
    file = fopen(filename, "rb"
    if ( file ==NULL )
    {
        printf("File Not Found : %s\n",filename);
        return 0;
    }

    // Seek through BMPHEADER to width and height
    fseek(file, 18, SEEK_CUR);

    // Read width
    if ((i = fread(&image->sizeX, 4, 1, file)) != 1)
    {
    	printf("Error reading width from %s.\n", filename);
    	return 0;
    }
    printf("Width of %s: %lu\n", filename, image->sizeX);

    // Read height
    if ((i = fread(&image->sizeY, 4, 1, file)) != 1)
    {
    	printf("Error reading height from %s.\n", filename);
    	return 0;
    }
    printf("Height of %s: %lu\n", filename, image->sizeY);

    // Calculate size
    size = image->sizeX * image->sizeY * 3;

    // Read planes
    if ((fread(&planes, 2, 1, file)) != 1)
    {
	printf("Error reading planes from %s.\n", filename);
	return 0;
    }
    if (planes != 1)
    {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }

    // Read BPP
    if ((i = fread(&bpp, 2, 1, file)) != 1)
    {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }

    // Seek past rest of BMPHEADER
    fseek(file, 24, SEEK_CUR);

    // Read data
    image->data = (char *) malloc(size);
    if (image->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }

    if ((i = fread(image->data, size, 1, file)) != 1)
    {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }

    // Reverse all the colours
    for ( i=0; i<size; i+=3 )
    {
    	temp = image->data[i];
    	image->data[i] = image->data[i+2];
    	image->data[i+2] = temp;
    }

    return 1;
}

//---------------------------------------------------------------------------
// FUNCTION: loadGLTextures()
// IMPORT: image (Image*), filename (char*)
// EXPORT: error (int)
// PURPOSE: Loads Bitmaps and convert to textures

// Load Bitmaps And Convert To Textures
void loadGLTextures()
{
    // Load Texture
    Image *image;

    // Allocate space for texture
    image = (Image *)malloc(sizeof(Image));
    if (image == NULL)
    {
        printf("Error allocating space for image");
        exit(0);
    }

    if (!ImageLoad("Data/lesson6/NeHe.bmp", image))
    {
    	exit(1);
    }

    // Create Texture
    glGenTextures(1, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);   // 2D texture (X and Y)

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture

    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image,
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);
}

//---------------------------------------------------------------------------
