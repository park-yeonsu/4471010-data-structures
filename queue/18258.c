#include <stdio.h>
#include <stdlib.h>

#define kMaxQueueSize 2000000

struct Queue {
  int data[kMaxQueueSize];
  int front;
  int back;
  int size;
};

void InitQueue(struct Queue* queue) {
  queue->front = 0;
  queue->back = 0;
  queue->size = 0;
}

void Push(struct Queue* queue, int x) {
  queue->data[queue->back++] = x;
  queue->size++;
}

int Pop(struct Queue* queue) {
  if (queue->size == 0) {
    return -1;
  }
  queue->size--;
  return queue->data[queue->front++];
}

int Size(const struct Queue* queue) {
  return queue->size;
}

int IsEmpty(const struct Queue* queue) {
  return queue->size == 0 ? 1 : 0;
}

int Front(const struct Queue* queue) {
  if (queue->size == 0) {
    return -1;
  }
  return queue->data[queue->front];
}

int Back(const struct Queue* queue) {
  if (queue->size == 0) {
    return -1;
  }
  return queue->data[queue->back - 1];
}

int main() {
  int n;
  scanf("%d", &n);

  struct Queue queue;
  InitQueue(&queue);

  char command[6];
  for (int i = 0; i < n; i++) {
    scanf("%s", command);

    if (command[0] == 'p' && command[1] == 'u') {
      int x;
      scanf("%d", &x);
      Push(&queue, x);
    } else if (command[0] == 'p') {
      printf("%d\n", Pop(&queue));
    } else if (command[0] == 's') {
      printf("%d\n", Size(&queue));
    } else if (command[0] == 'e') {
      printf("%d\n", IsEmpty(&queue));
    } else if (command[0] == 'f') {
      printf("%d\n", Front(&queue));
    } else if (command[0] == 'b') {
      printf("%d\n", Back(&queue));
    }
  }

  return 0;
}

