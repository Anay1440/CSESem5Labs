struct token {
    char name[100];
	char type[20];
    int row, col;
};
typedef struct token Token;

struct node {
    Token token;
    struct node * next;
};
typedef struct node Node;

struct symbol {
    char name[100];
    char type[100];
    char dataType[100];
    int size, numberOfArgs;
};
typedef struct symbol Symbol;

struct symbolNode {
    Symbol symbol;
    struct symbolNode * next;
};
typedef struct symbolNode SymbolNode;

int checkType(char *);
int check(char *);
void getType(char *, int);
void insertNode(Node *, char *, int, int, int);
void insertSymbolNode(SymbolNode *, char *, char *, const char *, int, int);
int symbolExists(SymbolNode *, char *);
Node * getNextToken();
int execLA(char *);