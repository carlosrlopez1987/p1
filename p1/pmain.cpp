#include <windows.h>
#include <stdio.h>

void main(){

	HANDLE hFile;
	HANDLE hAppend;
	DWORD  dwBytesRead, dwBytesWritten, dwPos;
	BYTE   buff[4096];

  // Open the existing file.

	hFile = CreateFile(TEXT("C:\\developer\\ms visual studio\\one.txt"), // open One.txt
			GENERIC_READ,             // open for reading
            0,                        // do not share
            NULL,                     // no security
            OPEN_EXISTING,            // existing file only
            FILE_ATTRIBUTE_NORMAL,    // normal file
            NULL);                    // no attr. template

	if (hFile == INVALID_HANDLE_VALUE){
		printf("Could not open One.txt."); 
		return;
	}

  // Open the existing file, or if the file does not exist,
  // create a new file.

	hAppend = CreateFile(TEXT("C:\\developer\\ms visual studio\\two.txt"), // open Two.txt
			FILE_APPEND_DATA,         // open for writing
			FILE_SHARE_READ,          // allow multiple readers
			NULL,                     // no security
			OPEN_ALWAYS,              // open or create
			FILE_ATTRIBUTE_NORMAL,    // normal file
			NULL						// no attr. template
	);

	if ( hAppend == INVALID_HANDLE_VALUE){
		printf("Could not open Two.txt."); 
		return;
	}

  // Append the first file to the end of the second file.
  // Lock the second file to prevent another process from
  // accessing it while writing to it. Unlock the
  // file when writing is complete.

	while (ReadFile(hFile, buff, sizeof(buff), &dwBytesRead, NULL) && dwBytesRead > 0){
		dwPos = SetFilePointer( hAppend, 0, NULL, FILE_END );
		LockFile( hAppend, dwPos, 0, dwBytesRead, 0 );
		WriteFile( hAppend, buff, dwBytesRead, &dwBytesWritten, NULL );
		UnlockFile( hAppend, dwPos, 0, dwBytesRead, 0 );
	}

  // Close both files.

	CloseHandle(hFile);
	CloseHandle(hAppend);
}
