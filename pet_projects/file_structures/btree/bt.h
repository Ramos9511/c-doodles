/* bt.h...
	header file for btree programs 
*/

#define MAXKEYS 4 /*não devria ser 3?, se é ordem 4, maxkey = 4 - 1?*/
#define MINKEYS MAXKEYS / 2
#define NIL (-1)
#define NOKEY '@'
#define NO 0
#define YES 1
#define STRUCT_SIZE 50

typedef struct { /*btree structure - page*/
  short keycount; /* number of keys in page	*/
  char key[MAXKEYS]; /* the actual keys		*/
  //char key[MAXKEYS][4]; /*string key - codigo da seguradora*/
  short child[MAXKEYS + 1]; /* ptrs to rrns of descendants  */
} BTPAGE;

#define PAGESIZE sizeof(BTPAGE)

/*arquivo seguradora*/
typedef struct input_record {
	int codigo;
	char nome[50];
	char seguradora[50];
	char tipo_seg[30];
}IRecord;

extern short root; /* rrn of root page */
extern int btfd; /* file descriptor of btree file */
extern int infd; /* file descriptor of input file */

void btclose();
int btopen();
int btread(short rrn, BTPAGE* page_ptr);
int btwrite(short rrn, BTPAGE* page_ptr);
short create_root(char key[], int offset, short left, short right);
short create_tree();
short getpage();
short getroot();
int insert(short rrn, char key, short* promo_r_child, char* promo_key);
void ins_in_page(char key[], int offset, short r_child, BTPAGE* p_page);
void pageinit(BTPAGE* p_page);
void putroot(short root);
int search_node(char key[], BTPAGE* p_page, short* pos);
void split(char key[], int offset, short r_child, BTPAGE* p_oldpage, char* promo_key, int *promo_offset, short* promo_r_child, BTPAGE* p_newpage);
