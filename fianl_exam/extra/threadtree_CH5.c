#include <stdio.h>
#include <stdlib.h>

/* ── 노드 구조체 (PDF p.51) ──
 * leftThread=1  → leftChild가 inorder predecessor를 가리키는 thread
 * leftThread=0  → leftChild가 진짜 왼쪽 자식
 * rightThread=1 → rightChild가 inorder successor를 가리키는 thread
 * rightThread=0 → rightChild가 진짜 오른쪽 자식
 */
typedef struct threadedTree *threadedPointer;
typedef struct threadedTree {
    short int leftThread;//0이면 진짜 자식 
    threadedPointer leftChild;
    char data;
    threadedPointer rightChild;
    short int rightThread;
} threadedTree;

threadedPointer head; /* 더미 head 노드 */

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//초중요 진짜 자식이 있을때 즉 s가 0일때 false일때는 child는 진짜 자식을 가리킴 그게 아닐땐 child는 다음 순서를 가리킴(프로그래머가 미리 inorder방향으로 세팅해놓음 중요)
//이것만 기억하자 실제자식이 없으면 이미 다 해놨다
/* ── inorder successor 찾기 (PDF p.54) ──
 * Case1: rightThread=1  → rightChild가 바로 successor //자식없음 
 * Case2: rightThread=0  → 오른쪽 subtree에서 leftThread 만날 때까지 왼쪽으로 //진짜 오른쪽 자식 있음 그러니까 다음 방향을 찾기위해서 석세서이용
 */
threadedPointer insucc(threadedPointer tree) {
    threadedPointer temp = tree->rightChild;
    if (!tree->rightThread)//오른쪽 실제자식이 없다면 
        while (!temp->leftThread)//왼쪽자식이 
            temp = temp->leftChild;
    return temp;
}

//inorder predecessor찾기
threadedPointer presucc(threadedPointer tree){
    threadedPointer temp = tree->leftChild;
    if(!tree->leftThread)
        while(!temp->rightThread)
            temp = temp->rightChild;
    return temp;
}

/* ── threaded inorder traversal (PDF p.56) ──
 * head에서 시작, insucc 반복 호출, head로 돌아오면 종료
 */
void tinorder(threadedPointer tree) {
    threadedPointer temp = tree;
    for (;;) {
        temp = insucc(temp);
        if (temp == tree) break;
        printf("%c ", temp->data);
    }
    printf("\n");
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
int main() {
    /*
     * PDF p.51 트리 구성
     *        A
     *       / \
     *      B   C
     *     / \ / \
     *    D  E F  G
     *   / \
     *  H   I
     *
     * inorder: H D I B E A F C G
     */

    /* head: leftChild=A(진짜), rightChild=head(자기자신), rightThread=0으로 설정
     * rightThread=0이어야 insucc(head)가 왼쪽 subtree 타고 내려가서 H(첫 노드)를 찾음 */
    head = malloc(sizeof(threadedTree));
    head->data        = '*';
    head->leftThread  = 0;      /* 진짜 왼쪽 자식 → A(root) */
    head->rightThread = 0;      /* 0으로 설정해야 traversal 시작 가능 */
    head->rightChild  = head;   /* 오른쪽은 자기 자신 (순환 종료용) */

    threadedPointer A=malloc(sizeof(threadedTree)); A->data='A';
    threadedPointer B=malloc(sizeof(threadedTree)); B->data='B';
    threadedPointer C=malloc(sizeof(threadedTree)); C->data='C';
    threadedPointer D=malloc(sizeof(threadedTree)); D->data='D';
    threadedPointer E=malloc(sizeof(threadedTree)); E->data='E';
    threadedPointer F=malloc(sizeof(threadedTree)); F->data='F';
    threadedPointer G=malloc(sizeof(threadedTree)); G->data='G';
    threadedPointer H=malloc(sizeof(threadedTree)); H->data='H';
    threadedPointer I=malloc(sizeof(threadedTree)); I->data='I';

    /* head → A */
    head->leftChild = A;

    /* 내부 노드: 진짜 자식 (Thread=0) */
    A->leftChild=B; A->leftThread=0; A->rightChild=C; A->rightThread=0;
    B->leftChild=D; B->leftThread=0; B->rightChild=E; B->rightThread=0;
    C->leftChild=F; C->leftThread=0; C->rightChild=G; C->rightThread=0;
    D->leftChild=H; D->leftThread=0; D->rightChild=I; D->rightThread=0;

    /* Thread 연결 (inorder: H D I B E A F C G 기준)
     * 각 노드의 NULL이었던 포인터 → successor/predecessor로 */
    H->leftChild=head; H->leftThread=1;  /* H의 predecessor 없음 → head */
    H->rightChild=D;   H->rightThread=1; /* H의 successor = D */

    I->leftChild=D;    I->leftThread=1;  /* I의 predecessor = D */
    I->rightChild=B;   I->rightThread=1; /* I의 successor = B */

    E->leftChild=B;    E->leftThread=1;  /* E의 predecessor = B */
    E->rightChild=A;   E->rightThread=1; /* E의 successor = A */

    F->leftChild=A;    F->leftThread=1;  /* F의 predecessor = A */
    F->rightChild=C;   F->rightThread=1; /* F의 successor = C */

    G->leftChild=C;    G->leftThread=1;  /* G의 predecessor = C */
    G->rightChild=head;G->rightThread=1; /* G의 successor 없음 → head */

    printf("Threaded Inorder Traversal: ");
    tinorder(head);
    /* 기대값: H D I B E A F C G */

    return 0;
}