#include <iostream>
#include <fstream>

using namespace std;



void writeBMP(unsigned char *img, int h, int w)
{
	FILE *f;
	int filesize = 54 + 3*w*h;  //w is your image width, h is image height, both int
	unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
	unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
	unsigned char bmppad[3] = {0,0,0};

	bmpfileheader[ 2] = (unsigned char)(filesize    );
	bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
	bmpfileheader[ 4] = (unsigned char)(filesize>>16);
	bmpfileheader[ 5] = (unsigned char)(filesize>>24);

	bmpinfoheader[ 4] = (unsigned char)(       w    );
	bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
	bmpinfoheader[ 6] = (unsigned char)(       w>>16);
	bmpinfoheader[ 7] = (unsigned char)(       w>>24);
	bmpinfoheader[ 8] = (unsigned char)(       h    );
	bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
	bmpinfoheader[10] = (unsigned char)(       h>>16);
	bmpinfoheader[11] = (unsigned char)(       h>>24);

	f = fopen("img.bmp","wb");
	fwrite(bmpfileheader,1,14,f);
	fwrite(bmpinfoheader,1,40,f);
	for(int i=0; i<h; i++)
	{
		fwrite(img+(w*(h-i-1)*3),3,w,f);
		fwrite(bmppad,1,(4-(w*3)%4)%4,f);
	}

	free(img);
	fclose(f);	
}


int main(int argc, char *argv[]) 
{
	int count = 0;
	//dec;are image for rgb Values
		unsigned char * img = NULL;
		img = (unsigned char *)malloc(3*1250*1250);
		memset(img,0,3*1250*1250);
		
		
		unsigned short buffer[1250][1250];
		unsigned short temp_data = 0;
		for (int i =0;i < 1250; i++)
		{
			for (int j =0 ;j < 1250;j++)
			{
				buffer[i][j] = temp_data;
			}
			temp_data += 65535/1250;
		}
		
		//Get RGB Color of every pixle ??? // Maybe we don't wan't the RGB Component? so Just the "alpha"
		for(int i =0; i < 1250; i++)
		{
			for(int j =0; j < 1250; j++)
			{
				unsigned int red   = (buffer[i][j] & 0x00ff0000) >> 16;
				img[count] = red; count++;
				unsigned int green = (buffer[i][j] & 0x0000ff00) >> 8;
				img[count] = green; count++;
				unsigned int blue  = (buffer[i][j] & 0x00ff00ff);
				img[count] = blue; count++;
				
				cout << red << " " <<green <<" " <<blue <<" " <<endl;
			}
		}
		
		
		//std::cout << sizeof(img);
		writeBMP(img,1250,1250);

}

