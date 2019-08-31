/**
*	FILE: p1.c 
*
*	DESCRIPTION: given a binary file
* 	organized as follows,
*
* 	binary-file
*-----------------------------------
*	...
*	<int> <--- size of record
*	<ASCII str[<=03]>
*	<ASCII str[<=50]>
*	<ASCII str[<=50]>
*	<ASCII str[<=30]>
*	<int>
*	...
*----------------------------------
*
*	The file has variable record 
*	and field size, using '#' as 
*	field delimiter. We wish to 
*	process such file, offering 
*	insertion, removal, hexdumping
*	and compression functionality 
*	printing all of its content in 
*	an organized fashion.
*
*	Restraints: Intensive data manipulations 
*	must be done in secondary memory, in other
*	words, directily on file stream.
*
*	AUTHOR: gfvante - 30 August 2019
*
*   NOTE ======================================== 
*   Error handling has not been implemented 
*   for clarity purposes. If you plan on using 
*   this code as part of a real application you 
*   you should treat the possible error scenarios! 
*   ==============================================
*
*/

int main(int argc, char *argv[])
{
	// opening file streams 
	FILE *f = fopen("input_file.bin", "w+b");

	/* process file once, storing offsets to
	   each record in a list (where the nodes have an
	   offset field, lag indicating if record in
	   question is marked or not and RRN:
	   
	   struct record {
	   	int rrn;
		int offset;
		char state;
		struct record *next;
	   }
	   
	   */









