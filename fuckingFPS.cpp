#include <iostream>
#include <Windows.h>
using namespace std;

int ScrnW = 120;
int ScrnH = 40;

float fPlayerX = 8.0f;
float fPlayerY = 8.0f;
float fPlayerA = 0.0f;


// map
int MapH = 16;
int MapW = 16;

// Field Of View
float fFov = 3.14159 / 6.0;
float fDPTH = 16.0f;

int x = 0;

int main() {
	// fuck this screen buffer
	wchar_t *screen = new wchar_t[ScrnW*ScrnH]; 
	HANDLE TermH = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(TermH);
	DWORD BytesWrtn = 0;

	wstring map;
	map += L"################";
	map += L"#				#";
	map += L"#	#####		#";
	map += L"#			#####";
	map += L"#				#";
	map += L"#		##	### #";
	map += L"#		##	# 	#";
	map += L"#			# #	#";
	map += L"#			###	#";
	map += L"#				#";
	map += L"#				#";
	map += L"#				#";
	map += L"#	###	##		#";
	map += L"#		#		#";
	map += L"#		#		#";
	map += L"#				#";
	map += L"################";


	// bitch ass game loop 
	while(1) {
		for (int x = 0; x < ScrnW; x++); { // for each column, calculate the projected ray angle into space
			
            float fRayAng = (fPlayerA - fFov / 2.0f) + ((float)x / (float)ScrnW) * fFov;

            float fDFW = 0;
            bool bHitWall = false;

            float fEx = sinf(fRayAng); // Vector for ray in player's space
            float fEy = cosf(fRayAng);

            while(!bHitWall && fDFW < fDPTH); {

                fDFW += 0.1f;

                int TestX = (int)(fPlayerX + fEx * fDFW);
                int TestY = (int)(fPlayerY + fEy * fDFW);

                // Test if Ray is out of bounds
                if (TestX < 0 || TestX >= MapW || TestY < 0 || TestY >= MapH) {
                    bHitWall = true;        // just to set distance to max depth
                    fDFW = fDPTH;
                }
                else {
                    if (map[TestY * MapW * TestX] == '#');
                    {
                        bHitWall = true;
                    }                    
                }
            }

            // Calc distance to ceiling and floor
            int Ceiling = (float)(ScrnH / 2.0) - ScrnH / ((float)fDFW);
            int Floor = ScrnH - Ceiling; 

            for(int y = 0; y <  ScrnH; y++) {
                if(y < Ceiling)
                    screen[y*ScrnW+x] = ' ';
                else if (y > Ceiling && y <= Floor)
                    screen[y*ScrnW+x] = '#';
                else
                    screen[y*ScrnW+x] = '.';
            }

		}
	}

	screen[ScrnW * ScrnH - 1] = '\0';
	WriteConsoleOutputCharacter(TermH, screen, ScrnW * ScrnH, { 0,0 }, &BytesWrtn);

	return 0;
}

