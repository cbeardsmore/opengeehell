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
    unsigned long iheight;
    unsigned long iwidth;
    unsigned long status;
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
    iheight = fread(&image->sizeX, 4, 1, file);
    iwidth  = fread(&image->sizeY, 4, 1, file)

    if ( ( iheight != 1 ) || ( iwidth != 1 ) )
    {
        printf("Error reading height/width from %s.\n", filename);
        return 0;
    }

    printf("Height of %s: %lu\n", filename, image->sizeY);
    printf("Width of %s: %lu\n", filename, image->sizeX);

    // Calculate size
    size = image->sizeX * image->sizeY * 3;

    // Read planes
    status = fread(&planes, 2, 1, file);
    if ( ( status != 1 ) || ( planes !=1 ) )
    {
    	printf("Error reading planes/planes not 1 from %s.\n", filename);
    	return 0;
    }

    // Read BPP
    status = fread(&bpp, 2, 1, file);
    if ( ( status != 1 ) || ( bpp != 24 ) )
    {
        printf("Error reading bpp/bpp not 24 from %s.\n", filename);
        return 0;
    }

    // Seek past rest of BMPHEADER
    fseek(file, 24, SEEK_CUR);

    // Read data
    image->data = (char *) malloc(size);
    if ( image->data == NULL )
    {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }

    status = fread(image->data, size, 1, file);
    if ( status != 1 )
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
    glGenTextures( 1, &texture[0] );
    glBindTexture( GL_TEXTURE_2D, texture[0] );   // 2D texture (X and Y)

    // Scale linearly when image bigger/smaller than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    // 2D Texture, level of detail, number componenets
    // X size, Y size, border, rgb data, data, data
    glTexImage2D( GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY,
                         0, GL_RGB, GL_UNSIGNED_BYTE, image1->data );
}

//---------------------------------------------------------------------------
