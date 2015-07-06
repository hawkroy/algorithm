#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int reg[10];
int mem[1000];

int execute(int pc)
{
    char data[3];

    data[0] = mem[pc]/100+'0';
    data[1] = (mem[pc]%100)/10+'0';
    data[2] = mem[pc]%10+'0';

    pc++;
    switch (data[0]-'0') {
    case 1:
        pc = -1;
        break;
    case 2:
        reg[data[1]-'0'] = data[2]-'0';
        reg[data[1]-'0'] %= 1000;
        break;
    case 3:
        reg[data[1]-'0'] += data[2]-'0';
        reg[data[1]-'0'] %= 1000;
        break;
    case 4:
        reg[data[1]-'0'] *= data[2]-'0';
        reg[data[1]-'0'] %= 1000;
        break;
    case 5:
        reg[data[1]-'0'] = reg[data[2]-'0'];
        reg[data[1]-'0'] %= 1000;
        break;
    case 6:
        reg[data[1]-'0'] += reg[data[2]-'0'];
        reg[data[1]-'0'] %= 1000;
        break;
    case 7:
        reg[data[1]-'0'] *= reg[data[2]-'0'];
        reg[data[1]-'0'] %= 1000;
        break;
    case 8:
        reg[data[1]-'0'] = mem[reg[data[2]-'0']];
        reg[data[1]-'0'] %= 1000;
        break;
    case 9:
        mem[reg[data[2]-'0']] = reg[data[1]-'0'];
        mem[reg[data[2]-'0']] %= 1000;
        break;
    case 0:
        if (reg[data[2]-'0'] != 0)
            pc = reg[data[1]-'0'];
        break;
    }

    return pc;
}

int main(int argc, char* argv[])
{
    int cases;
    int insts;
    int data;
    int pc;
    int i;
    char line[10];

    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d", &cases);
    fgets(line, sizeof(line), stdin);

    while (cases-- > 0) {
        memset(reg, 0, sizeof(reg));
        memset(mem, 0, sizeof(mem));
        insts = 0;
        pc = 0;
        i = 0;

        while (fgets(line, sizeof(line), stdin) != NULL) {
            if (line[0] == '\n' || line[0] == '\r')
                break;

            sscanf(line, "%d", &data);
            mem[i++] = data;
        }

        do {
            pc = execute(pc);
            insts++;
        } while (pc != -1);

        printf("%d\n", insts);

        if (cases != 0)
            printf("\n");
    }

    return 0;
}
