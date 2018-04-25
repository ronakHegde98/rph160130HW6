/*
 * CDK matrix that will display the contents of a binary file
 * File:   mainFile.cc
 * Author: Ronak Hegde
 * Email: rph160130@utdallas.edu
 */

#include <iostream>
#include "cdk.h"
#include "program6.h"
#include <fstream>
#include <iomanip>


//global varibales 
#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;


int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix
  

// C0 and R0 are placeholders
  const char 		*rowTitles[] = {"R0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"C0", "a", "b", "c", "C4", "C5"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH,BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED, vMIXED, vMIXED}; 
  
  char buffer[100];
  
 //create a variable for a BinaryFileRecord and BinaryFileHeader that will allow us to store contents
 //that we read from the binary file 
 BinaryFileRecord *myRecord = new BinaryFileRecord();
 BinaryFileHeader *myHeader = new BinaryFileHeader();

 ifstream binInfile ("cs3377.bin", ios::in | ios::binary);

 binInfile.read((char*)myHeader,sizeof(BinaryFileHeader));

//error out if the bin file was not found
if(!binInfile)
{
 	cout << "There was an error opening the binary file\n";
	exit(0);
}
	
  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);


  //these three series of statements will allow us to print to the header file
  sprintf(buffer,"Magic: 0x%X", myHeader->magicNumber);
  setCDKMatrixCell(myMatrix, 1, 1,buffer);
  drawCDKMatrix(myMatrix, true);    /* required  */  
	
  sprintf(buffer, "Version: %u", myHeader->versionNumber);
  setCDKMatrixCell(myMatrix, 1,2, buffer);
  drawCDKMatrix(myMatrix, true);

  sprintf(buffer, "NumRecords: %lu", myHeader->numRecords);
  setCDKMatrixCell(myMatrix,1,3,buffer);
  drawCDKMatrix(myMatrix, true);
 
 unsigned long long int  numberOfRecords = myHeader->numRecords;
 
//for loop that will print and loop through the records and 
 for(int i = 2; i <int(numberOfRecords)+2; i++)
 {
 	binInfile.read((char*)myRecord, sizeof(BinaryFileRecord));
 	sprintf(buffer, "strlen: %u",myRecord->strLength);
	setCDKMatrixCell(myMatrix,i,1, buffer);
	drawCDKMatrix(myMatrix, true);

	
	sprintf(buffer, "%s", myRecord->stringBuffer);
	setCDKMatrixCell(myMatrix, i, 2, buffer);
	drawCDKMatrix(myMatrix, true);
 }


 //so we can see results, pause until a key is pressed
 unsigned char x;
 cin >> x;

  // Cleanup screen
  endCDK();
}
