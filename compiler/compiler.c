#include <assert.h>
#include "compiler.h"

int E();
void STMT();
void IF();
void BLOCK();
void DOWHILE();

int tempIdx = 0, labelIdx = 0;

#define nextTemp() (tempIdx++)
#define nextLabel() (labelIdx++)
#define emit printf

int isNext(char *set) {
  char eset[SMAX], etoken[SMAX];
  sprintf(eset, " %s ", set);
  sprintf(etoken, " %s ", tokens[tokenIdx]);
  return (tokenIdx < tokenTop && strstr(eset, etoken) != NULL);
}

int isEnd() {
  return tokenIdx >= tokenTop;
}

char *next() {
  // printf("token[%d]=%s\n", tokenIdx, tokens[tokenIdx]);
  return tokens[tokenIdx++];
}

char *skip(char *set) {
  if (isNext(set)) {
    return next();
  } else {
    printf("skip(%s) got %s fail!\n", set, next());
    assert(0);
  }
}

// F = (E) | Number | Id
int F() {
  int f;
  if (isNext("(")) { // '(' E ')'
    next(); // (
    f = E();
    next(); // )
  } else { // Number | Id
    f = nextTemp();
    char *item = next();
    emit("t%d = %s\n", f, item);
  }
  return f;
}

// E = F (op E)*
int E() {
  int i1 = F();
  while(isNext("+ - * / & | ! < > =")){
    char *op = next();
    if(isNext("+ - * / & | ! < > =")){
      char *a = next();
      int i2 = E();
      int i = nextTemp();
      emit("t%d = t%d %s%s t%d\n", i, i1, op, a, i2);
      i1 = i;
    }
    else{
      int i2 = E();
      int i = nextTemp();
      emit("t%d = t%d %s t%d\n", i, i1, op, i2);
      i1 = i;
    }
  }
  return i1;
}

// ASSIGN = id '=' E;
void ASSIGN() {
  char *id = next();
  skip("=");
  int e = E();
  skip(";");
  emit("%s = t%d\n", id, e);
}

void DOWHILE(){
  int doBegin = nextLabel();
  int doEnd = nextLabel();
  emit("(L%d)\n", doBegin);
  skip("do");
  STMT();
  skip("while");
  skip("(");
  int e = E();
  emit("if not T%d goto L%d\n", e, doEnd);
  skip(")");
  skip(";");
  emit("goto L%d\n", doBegin);
  emit("(L%d)\n", doEnd);
}

// STMT = WHILE | BLOCK | ASSIGN
void STMT() {
  if (isNext("do"))
    return DOWHILE();
  else if (isNext("{"))
    BLOCK();
  else
    ASSIGN();
}

// STMTS = STMT*
void STMTS() {
  while (!isEnd() && !isNext("}")) {
    STMT();
  }
}

// BLOCK = { STMTS }
void BLOCK() {
  skip("{");
  STMTS();
  skip("}");
}

// PROG = STMTS
void PROG() {
  STMTS();
}

void parse() {
  printf("============ parse =============\n");
  tokenIdx = 0;
  PROG();
}