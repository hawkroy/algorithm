/*===========================================
 *  Compile:
 *    Debug:  gcc 1011.c -g -D _DEBUG -o 1011
 *    Non-Debug:  gcc 1011.c -o 1011
 *
 *  Desc: HDU 1011 Problem  - StarShip, tree DP
 *
 *  Complex:  O (room * trooper^2)
 * ==========================================
 */

#include <stdio.h>
#include <string.h>

#define MAX_ROOM          101
#define MAX_TROOPER       101
#define BUGS_PER_TROOPER  20

// room structure
typedef struct {
  int brain;    // possibility of brain
  int bugs;     // protected bugs
  int cnt;      // room link number
  int link[MAX_ROOM]; // link info
} tROOM;

int room_cnt;
int trooper_cnt;

tROOM rooms[MAX_ROOM];  // rooms info
int visit[MAX_ROOM];
int len[MAX_ROOM];
int temp[MAX_ROOM];
int brain[MAX_ROOM][MAX_TROOPER]; // the optimize array, B{room, troopers}

//-------------- queue structure begin ---------------------
int queue[MAX_ROOM];
int front;
int rear;

int empty_queue(void) {
#ifdef _DEBUG
  int i;
  printf("in empty_queue, queue is: ");
  for (i = front; i < rear; i++) {
    printf("%d ", queue[i]);
  }
  printf("\n");
#endif
  return (front==rear);
}

void enter_queue(int elm) {

#ifdef _DEBUG
  printf("enter queue: %d\n", elm);
#endif

  queue[rear++] = elm;
  return ;
}

int deenter_queue(void) {
  int elm;
  elm = queue[front++];

#ifdef _DEBUG
  printf("de-enter queue: %d\n", elm);
#endif

  return elm;
}
//-------------- queue structure end ---------------------

void init(void) {
  memset(rooms, 0, sizeof(tROOM)*MAX_ROOM);
  memset(brain, 0, sizeof(int)*MAX_ROOM*MAX_TROOPER);
  memset(queue, 0, sizeof(int)*MAX_ROOM);
  memset(visit, 0, sizeof(int)*MAX_ROOM);
  memset(len, 0, sizeof(int)*MAX_ROOM);
  front = 0;
  rear = 0;
  return ;
}

void handle_input(void) {
  int i, j;
  int src, dst;

  for (i = 1; i <= room_cnt; i++) {
    scanf("%d %d\n", &rooms[i].bugs, &rooms[i].brain);
  }

  for (i = 1; i <= room_cnt-1; i++) {
    scanf("%d %d\n", &src, &dst);

    rooms[src].link[rooms[src].cnt] = dst;
    rooms[src].cnt++;
    
    rooms[dst].link[rooms[dst].cnt] = src;
    rooms[dst].cnt++;
  }
  // holder flag
  rooms[1].link[rooms[1].cnt] = 0;
  rooms[1].cnt++;
  
  for (i = 1; i <= room_cnt; i++) {
    len[i] = rooms[i].cnt;
  }

#ifdef _DEBUG
  for (i = 1; i <= room_cnt; i++) {
    printf("bugs = %d, brain = %d, cnt = %d\n", rooms[i].bugs, rooms[i].brain, rooms[i].cnt);
    printf("link[] = ");
    for (j = 0; j < rooms[i].cnt; j++) {
      printf("%d ", rooms[i].link[j]);
    }
    printf("\n");
  }
#endif

  return ;
}

void handle(void) {
  int i, j, t, start;
  int cur, father;

#ifdef _DEBUG
  int k;
#endif

  if (trooper_cnt == 0) {
    brain[0][trooper_cnt] = 0;
    return;
  }
  
  for (i = 1; i <= room_cnt; i++) {
    if (rooms[i].cnt == 1) {
      enter_queue(i);
    }
  }

  while (!empty_queue()) {
    cur = deenter_queue();
    visit[cur] = 1;

#ifdef _DEBUG
    printf("current room is: %d\n", cur);
#endif
    
    if  ((rooms[cur].bugs % BUGS_PER_TROOPER) == 0) {
      start = rooms[cur].bugs / BUGS_PER_TROOPER;
    }
    else {
      start = rooms[cur].bugs / BUGS_PER_TROOPER + 1;
    }

    // here, brain[][] indicates for exceed trooper for the cur room
    for (i = trooper_cnt-start; i >= 0; i--) {  // must descend, \
                                             not accumulate result \
                                             !!!i=trooper_cnt-start, overflow
      brain[cur][i+start] = brain[cur][i]+rooms[cur].brain;
    }

    // here, brain[][] indicates for the trooper for the cur room
    for (i = 0; i <= start-1; i++) {
      brain[cur][i] = 0;
    }

#ifdef _DEBUG
    printf("brain in cur room #%d: ", cur);
    for (k = 0; k <= trooper_cnt; k++) {
      printf("%d ", brain[cur][k]);
    }
    printf("\n");
#endif
    
    for (t = 0; t < rooms[cur].cnt; t++) {
      father = rooms[cur].link[t];
      
      if (visit[father]) {
        continue;
      }

#ifdef _DEBUG
      printf("the %d's father is : %d\n", cur, father);
#endif

      // calc this room for the upper room's brain effect
      // here, brain[cur][] for the trooper of room
      // brain[father][] for the exceed trooper of room
      // the temp array must, reduce accumulate effect of brain[][]
      brain[cur][0] = 0;
      brain[father][0] = 0;
      for (i = 0; i <= trooper_cnt; i++) {
        if (brain[cur][i] < brain[father][i]) {
          temp[i] = brain[father][i];
        }
        else {
          temp[i] = brain[cur][i];
        }
      }
      for (i = trooper_cnt; i >= 0; i--) {
        for (j = i ; j >= 0; j--) {
          // why i and j can't reach 0?
          // it will double the brain[father][i] in case one room has 0 bugs
          if (temp[i] < (brain[cur][j]+brain[father][i-j])) {
            temp[i] = brain[cur][j]+brain[father][i-j];
          }
        }
      }
      for (i = 0; i <= trooper_cnt; i++) {
        brain[father][i] = temp[i];
      }

#ifdef _DEBUG
      printf("brain in father room #%d: ", father);
      for (k = 0; k <= trooper_cnt; k++) {
        printf("%d ", brain[father][k]);
      }
      printf("\n");
#endif

      len[father]--;
      // father's child calc over, prepare for father
      if (len[father] == 1) {
        enter_queue(father);
      }
    }
  }

  return ;
}

void print_output(void) {
  printf("%d\n", brain[0][trooper_cnt]);
  return ;
}

int main(int argc, char * argv[]) {
#ifdef _DEBUG
  int turn = 0;
#endif

  while (scanf("%d %d", &room_cnt, &trooper_cnt) != EOF) {
    if (room_cnt == -1 && trooper_cnt == -1) {
      break;
    }
#ifdef _DEBUG
    printf("turn %d\n", turn++);
#endif
    init();
    handle_input();
    handle();
    print_output();
  }

  return 0;
}
