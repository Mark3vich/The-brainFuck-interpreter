#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void read_cmd_list(FILE *cmdlist) {
    char c;
    int i = 0;
    while (!feof(cmdlist)) {
        if (i == 200) {
            printf("\n");
            i = 0;
        }
        fscanf(cmdlist, "%c", &c);
        if (!feof(cmdlist)) {
            printf("%c", c);
            i++;
        }
    }
    printf("\n");
    rewind(cmdlist);
}

void process(FILE *cmdlist, char cpu[]) {
    char cmd_char;
    do {
        fscanf(cmdlist, "%c", &cmd_char);
        switch (cmd_char) {
            case '>':
                cpu++;
                break;
            case '<':
                cpu--;
                break;
            case '+':
                (*cpu)++;
                break;
            case '-':
                (*cpu)--;
                break;
            case '.':
                if (!feof(cmdlist))
                    putchar(*cpu);
                break;
            case ',':
                *cpu = getchar();
                break;
            case '[': {
                int n = 1;
                if ((*cpu) == 0)
                    while (n != 0) {
                        fscanf(cmdlist, "%c", &cmd_char);
                        if (cmd_char == ']')
                            n--;
                        else if (cmd_char == '[')
                            n++;
                    }
            }
                break;
            case ']': {
                int n = 1;
                if ((*cpu) != 0)
                    while (n != 0) {
                        fseek(cmdlist, -2, SEEK_CUR);
                        fscanf(cmdlist, "%c", &cmd_char);
                        if (cmd_char == ']')
                            n++;
                        else if (cmd_char == '[')
                            n--;
                    }
            }
                break;
        }
    } while (!feof(cmdlist));
    printf("\n");
}

int main() {
    SetConsoleOutputCP(CP_UTF8 );

    char cpu[30000] = {0};
    FILE *cmdlist = fopen("cmds.txt", "r");
    printf("Код файла: \n");
    read_cmd_list(cmdlist);
    process(cmdlist, cpu);
    system("pause");
}

// Hello World
// ++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.
// Считывает символы и выводит на экран  
// ,[.,]
// Из 2 в 8 
// ,>,>,>,>,>,[>+<------------------------------------------------[->+<]+<[------------------------------------------------[->>++<<]+<[------------------------------------------------[->>>++++<<<]+[<]]]>[>]<[<]<[<]+[>]>[>]<-[[<]<[<]>+[>]>[>]<-]<-<[-<[-<[<]]]>[>]<]<[+++++++++++++++++++++++++++++++++++++++++++++++<]>[.>].
