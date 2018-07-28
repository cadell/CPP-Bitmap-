#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

std::vector<std::string> string_buffer;

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
		string_buffer.push_back(reinterpret_cast<char *>(img+(w*(h-i-1)*3)));
		fwrite(bmppad,1,(4-(w*3)%4)%4,f);
		string_buffer.push_back(reinterpret_cast<char *>(bmppad));
	}

	free(img);
	fclose(f);	
}


int main(int argc, char *argv[]) 
{
	int count = 0;
	//dec;are image for rgb buffer[0][i]ues
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
		//Invert endianness before getting the "RGB" buffer[0][i]s
		for (unsigned short *ptr = (unsigned short*)buffer + 1250*1250; ptr>(unsigned short*)buffer; ) 
		{
			const unsigned short val = *(--ptr);
			*ptr = (unsigned short)((val>>8) | ((val<<8)));

		}		
		//Get RGB Color of every pixle ??? // Since we are building a grayScale image the RGB values need to be the same? no need to avg?
		for(int i =0; i < 1250; i++)
		{
			for(int j =0; j < 1250; j++)
			{			
				img[count] = buffer[i][j]; count++;
				img[count] = buffer[i][j]; count++;
				img[count] = buffer[i][j]; count++;
				//img[count] = buffer[i][j]; count++;
				//cout << red << " " <<green <<" " <<blue <<" " <<endl;
			}
		}
		

		
		
		///Draw on the image
		int temp = 0;
		bool print_once = true;
		for(int i =0; i < 1250; i++)
		{
			auto red = (buffer[0][i] & 0xF800) >> 11; 
			auto red_8bit = red << 3;
			img[temp] = 255; temp++;
			auto green = (buffer[0][i] & 0x07E0) >> 5;
			auto green_8bit = green << 2;
			img[temp] = 0; temp++;
			auto blue = (buffer[0][i] & 0x001F);
			auto blue_8bit = blue << 3;
			img[temp] = 255; temp++;
//			
			red = (buffer[1][i] & 0xF800) >> 11; 
			red_8bit = red << 3;
//			cout << red_8bit <<" red"<<endl;
			img[temp] = 255; temp++;
			green = (buffer[1][i] & 0x07E0) >> 5;
			green_8bit = green << 2;
//			cout << green_8bit <<" green"<<endl;
			img[temp] = 0; temp++;
			blue = (buffer[1][i] & 0x001F);
			blue_8bit = blue << 3;
//			cout << blue_8bit <<" blue" <<endl;
			img[temp] = 255; temp++;
//							
		}
		
		//std::cout << sizeof(img);
		writeBMP(img,1250,1250);
		
		std::string image_data;
		//Return the buffer in a string
		for(auto const& elements : string_buffer)
		{
			image_data += elements;
		}
		

}

