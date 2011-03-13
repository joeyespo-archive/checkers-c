//**************************************
//     
// Name: Bitmap Loading Class
// Description:Loads and saves bitmaps o
//     f all color depths, and edits individual
//     pixels of 24-bit bitmaps.
// By: Wesley Hopper
//
//This code is copyrighted and has// limited warranties.Please see http://
//     www.Planet-Source-Code.com/xq/ASP/txtCod
//     eId.1215/lngWId.3/qx/vb/scripts/ShowCode
//     .htm//for details.//**************************************
//     
//Bitmap File Loading/Saving/Editing Cla
//     ss [bmp.h]
/*****Bitmap BMP;BMP.Load(filename, NORMAL or FLIP);orBitmap BMP(filename, NORMAL or FLIP);*****/

//#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#define NORMAL	1
#define FLIP	2
#define BM_NOTBMP		3
#define BM_OPENERR		4
#define BM_CREATEERR	5
#define BM_ALLOCERR		6
#define BM_READERR		7
#define BM_WRITEERR		8

class Bitmap
{
	public:
    		Bitmap();    		Bitmap(const char*, int);    		~Bitmap();    		int			Load(const char*, int);    		int			SetPixelColor(int, int, COLORREF);    		COLORREF		GetPixelColor(int, int);    		int			Save(const char*);    				    		int DataSize, Width, Height, BPP, Colors, ScanLineSize;    		BITMAPFILEHEADER BMPHeader;		//bmpmap file info    		BITMAPINFOHEADER BMPInfoHeader; //info including the palette    		BITMAPINFO		 *BMPInfo;		//pointer to the BITMAPINFO structure    		BYTE *Buffer;		//pointer to bitmap data    		PALETTEENTRY Palette[256]; //palette storage}; Bitmap::Bitmap()
    {    	Buffer=NULL;    	BMPInfo=NULL;}Bitmap::Bitmap(const char *Filename, int BufferFormat)

    {    	Buffer=NULL;    	BMPInfo=NULL;    	Load(Filename, BufferFormat);}Bitmap::~Bitmap()

    {    	if(Buffer) free(Buffer);    	if(BMPInfo) free(BMPInfo);}/*******************************************************Bitmap::Load	Paramaters: 	Filename - Name of the bitmap to open	BufferFormat - How to load the bitmap data into memory		(NORMAL - Normal bottom up format)		(FLIP - Flip the data to a top to bottom format)	Return:	0 on success, Bitmap Error Code on error*******************************************************/int Bitmap::Load(const char *Filename, int BufferFormat)

    {    	FILE *bmp;    	//open file    	if(!(bmp=fopen(Filename, "rb")))    		return BM_OPENERR;    	//check file type    	WORD BMPtag;    	fread(&BMPtag, 1, sizeof(WORD), bmp);    	if(BMPtag!=0x4D42)

        	{        		fclose(bmp);        		return BM_NOTBMP;}        	        	rewind(bmp);        	        	//read BITMAPFILEHEADER & BITMAPINFOHEADER        	fread(&BMPHeader, 1, sizeof(BITMAPFILEHEADER), bmp);         	fread(&BMPInfoHeader, 1, sizeof(BITMAPINFOHEADER), bmp);        	        	//init bmp info        	DataSize=BMPInfoHeader.biSizeImage;        	Width=BMPInfoHeader.biWidth;        	Height=BMPInfoHeader.biHeight;        	BPP=BMPInfoHeader.biBitCount;        	Colors=pow(2,BPP);        	ScanLineSize=DataSize/Height;        	        	//allocate buffer for BITMAPINFO*        	if(BMPInfo) free(BMPInfo);        	BMPInfo=(BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER)+sizeof(PALETTEENTRY)*Colors);         	BMPInfo->bmiHeader=BMPInfoHeader;        			        	//load palette if needed        	if(BPP<16)

            	{            		//read palette from file            		fread(&Palette, Colors, sizeof(PALETTEENTRY), bmp);            		memcpy(&BMPInfo->bmiColors, &Palette, sizeof(Palette));}            	            	//allocate memory            	if(Buffer) free(Buffer);            	if(!(Buffer=(BYTE*)malloc(DataSize)))

                {                		fclose(bmp);                		return BM_ALLOCERR;}                	//read data                	memset(Buffer, 0, BMPInfoHeader.biSizeImage);                	if(BufferFormat==1) //normal                		if(!fread(Buffer, 1, BMPInfoHeader.biSizeImage, bmp))

                    		{                    			fclose(bmp);                    			return BM_READERR;}                    	                    	if(BufferFormat==2) //flip                    	for(int line=BMPInfoHeader.biHeight-1; line>=0; line--)                    		fread(Buffer+line*(BMPInfoHeader.biSizeImage/BMPInfoHeader.biHeight), 1, BMPInfoHeader.biSizeImage/BMPInfoHeader.biHeight, bmp);                    	                    	fclose(bmp);                    	return 0;                }                /*************************************                Bitmap::Save                	Paramaters:                	filename - Name to save the bitmap                Return:                	0 on success, Error value on error                *************************************/                int Bitmap::Save(const char* filename)

                    {                    	//Write file                    	FILE *bmp;                    	if(!(bmp=fopen(filename, "wb"))) return BM_CREATEERR;                    	fwrite(&BMPHeader, 1, sizeof(BITMAPFILEHEADER), bmp);                    	fwrite(&BMPInfoHeader, 1, sizeof(BITMAPINFOHEADER), bmp);                    	                    	if(BPP<16) if(!fwrite(Palette, 1, sizeof(Palette), bmp)) return BM_WRITEERR;                    	if(!fwrite(Buffer, 1, DataSize, bmp)) return BM_WRITEERR;                    	                    	fclose(bmp);                    	return 0;                }                //The following functions are for 24-bit
                //     color only
                /*********************************************************                Bitmap::SetPixelColor                	Paramaters:                	x - X index of pixel                	y - Y index of pixel (from top left origin)                	cr - COLORREF of the color to change the pixel to                		*COLORREF is a WinAPI type                	Return:                	1 on success, 0 if the pixel is out of range of                 	the bitmap dimensions.                **********************************************************/                inline int Bitmap::SetPixelColor(int x, int y, COLORREF cr)

                    {                    	if(x>=Width || x<0 || y>=Height || y<0) return 0;                    	int pixel=(Height-1-y)*ScanLineSize+x*3;                    	Buffer[pixel]=(BYTE)(cr>>16);                    	Buffer[pixel+1]=(BYTE)(cr>>8);                    	Buffer[pixel+2]=(BYTE)cr;                    	                    	return 1;                }                /*********************************************************                Bitmap::GetPixelColor                	Paramaters:                	x - X index of pixel                	y - Y index of pixel (from top left origin)                	Return:                	COLORREF of the pixel color                **********************************************************/                inline COLORREF Bitmap::GetPixelColor(int x, int y)

                    {                    	if(x>=Width || x<0 || y>=Height || y<0) return 0;                    	                    	int pixel=(Height-1-y)*ScanLineSize+x*3;                    	int B=Buffer[pixel], G=Buffer[pixel+1], R=Buffer[pixel+2];                    	return RGB(R,G,B);                }
