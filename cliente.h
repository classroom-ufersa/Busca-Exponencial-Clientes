typedef struct cliente Cliente;

int Numero_clientes(FILE * arquivo, int numero_clientes);

void add_clientes(int numero_clientes,Cliente *cliente);

int preencher_clientes(FILE * arquivo,Cliente * cliente);