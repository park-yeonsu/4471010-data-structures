#include <stdio.h>
#include <stdlib.h>

#define kMaxStackSize 1000000

struct Stack {
  int data[kMaxStackSize];
  int top;
};

void InitStack(struct Stack* stack) {
  stack->top = -1;
}

void Push(struct Stack* stack, int x) {
  stack->data[++stack->top] = x;
}

int Pop(struct Stack* stack) {
  if (stack->top == -1) {
    return -1;
  }
  return stack->data[stack->top--];
}

int Size(struct Stack* stack) {
  return stack->top + 1;
}

int IsEmpty(struct Stack* stack) {
  return stack->top == -1 ? 1 : 0;
}

int Top(struct Stack* stack) {
  if (stack->top == -1) {
    return -1;
  }
  return stack->data[stack->top];
}

int main() {
  int n;
  scanf("%d", &n);

  struct Stack stack;
  InitStack(&stack);

  for (int i = 0; i < n; i++) {
    int command;
    scanf("%d", &command);

    switch (command) {
      case 1: {
        int x;
        scanf("%d", &x);
        Push(&stack, x);
        break;
      }
      case 2: {
        printf("%d\n", Pop(&stack));
        break;
      }
      case 3: {
        printf("%d\n", Size(&stack));
        break;
      }
      case 4: {
        printf("%d\n", IsEmpty(&stack));
        break;
      }
      case 5: {
        printf("%d\n", Top(&stack));
        break;
      }
    }
  }

  return 0;
}
