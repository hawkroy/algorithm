#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int m, n;
char pic[250][250];

void clearPic(void)
{
    int i, j;
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            pic[i][j] = 'O';
}

void drawPixel(int x, int y, char c)
{
    pic[x][y] = c;
}

void showPic(char* name)
{
    int i, j;

    printf("%s\n", name);
    for (j = 0; j < n; j++) {
        for (i = 0; i < m; i++)
            printf("%c", pic[i][j]);
        printf("\n");
    }
}

void fillRegionWorker(int x, int y, char c, char orig_c)
{
    if (x < 0 || x == m)
        return ;
    if (y < 0 || y == n)
        return ;
    if (pic[x][y] != orig_c)
        return ;
    pic[x][y] = c;

    fillRegionWorker(x+1, y, c, orig_c);
    fillRegionWorker(x-1, y, c, orig_c);
    fillRegionWorker(x, y+1, c, orig_c);
    fillRegionWorker(x, y-1, c, orig_c);
}

/*
 * this is the diffcult func, use DFS
 */
void fillRegion(int x, int y, char c)
{
    if (pic[x][y] == c)
        return ;
    fillRegionWorker(x, y, c, pic[x][y]);
}

int handleCmd(char* line)
{
    int quit = 0;
    char op = line[0];
    char name[40];
    int x, y, x1, y1, i, j;
    char color;

    switch (op) {
    case 'I':
        sscanf(line+1, "%d %d", &m, &n);
        clearPic();
        break;
    case 'C':
        clearPic();
        break;
    case 'L':
        sscanf(line+1, "%d %d %c", &x, &y, &color);
        drawPixel(x-1, y-1, color);
        break;
    case 'V':
        sscanf(line+1, "%d %d %d %c", &x, &y, &y1, &color);
        if (y > y1) {
            i = y;
            y = y1;
            y1 = i;
        }
        for (i = y-1; i <= y1-1; i++)
            drawPixel(x-1, i, color);
        break;
    case 'H':
        sscanf(line+1, "%d %d %d %c", &x, &x1, &y, &color);
        if (x > x1) {
            i = x;
            x = x1;
            x1 = i;
        }
        for (i = x-1; i <= x1-1; i++)
            drawPixel(i, y-1, color);
        break;
    case 'K':
        sscanf(line+1, "%d %d %d %d %c", &x, &y, &x1, &y1, &color);
        for (i = x-1; i <= x1-1; i++)
            for (j = y-1; j <= y1-1; j++)
                drawPixel(i, j, color);
        break;
    case 'F':
        sscanf(line+1, "%d %d %c", &x, &y, &color);
        fillRegion(x-1, y-1, color);
        break;
    case 'S':
        sscanf(line+1, "%s", name);
        showPic(name);
        break;
    case 'X':
        quit = 1;
        break;
    default:
        break;
    }

    return quit;
}

int main(int argc, char* argv[])
{
    char line[50];
    int quit = 0;

    while (fgets(line, sizeof(line), stdin) != NULL) {
        quit = handleCmd(line);

        if (quit)
            break;
    }

    return 0;
}
