// 더블 링크드 리스트 (Doubly Linked List) 예제
// llink = 왼쪽(이전) 노드, rlink = 오른쪽(다음) 노드
// header node 사용: 데이터 없는 더미 노드, 항상 존재

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 구조체 선언
typedef struct node *nodePointer;
typedef struct node {
    nodePointer llink;  // 이전 노드 포인터
    int data;           // 데이터
    nodePointer rlink;  // 다음 노드 포인터
} Node;

// 함수 선언
nodePointer create_header();    // header 노드 생성
void dinsert(nodePointer node, int data);  // node 오른쪽에 삽입
void ddelete(nodePointer header, nodePointer deleted);  // 노드 삭제
void print_list(nodePointer header);  // 출력


int main() {

    // header 노드 생성 (빈 리스트)
    nodePointer header = create_header();
    printf("=== 더블 링크드 리스트 예제 ===\n\n");

    // 삽입: header 오른쪽에 순서대로 10, 20, 30 삽입
    dinsert(header, 10);
    dinsert(header->llink, 20);   // 10 오른쪽에 20 삽입
    dinsert(header->llink, 30);  // 20 오른쪽에 30 삽입

    printf("삽입 후: ");
    print_list(header);  // 10 20 30

    // 삭제: 20 삭제
    nodePointer target = header->rlink->rlink;  // 20을 가리키는 노드
    printf("20 삭제 후: ");
    ddelete(header, target);
    print_list(header);  // 10 30

    // 성질 확인: ptr = ptr->llink->rlink = ptr->rlink->llink
    nodePointer ptr = header->rlink;  // 10 노드
    printf("ptr->data = %d\n", ptr->data);
    printf("ptr->llink->rlink->data = %d\n", ptr->llink->rlink->data);  // 같아야 함
    printf("ptr->rlink->llink->data = %d\n", ptr->rlink->llink->data);  // 같아야 함

    // 메모리 해제
    nodePointer cur = header->rlink;
    while (cur != header) {
        nodePointer tmp = cur->rlink;
        free(cur);
        cur = tmp;
    }
    free(header);

    return 0;
}

// header 노드 생성
// 빈 리스트: header->llink = header->rlink = header (자기 자신)
nodePointer create_header() {
    nodePointer header = (nodePointer)malloc(sizeof(Node));
    header->llink = header;
    header->rlink = header;
    header->data = -1;  // header는 데이터 없음
    return header;
}

// node 오른쪽에 newnode 삽입
// 순서 중요! node->rlink = newnode 가 반드시 마지막!
void dinsert(nodePointer node, int data) {
    nodePointer newnode = (nodePointer)malloc(sizeof(Node));
    newnode->data = data;

    newnode->llink = node;              // newnode ← node
    newnode->rlink = node->rlink;       // newnode → node의 오른쪽 node가 제일 끝노드라면 head가 되겠지 
    node->rlink->llink = newnode;       // node 오른쪽의 llink = newnode
    node->rlink = newnode;              // node → newnode (반드시 마지막!)
}

// deleted 노드 삭제
// header 노드는 삭제 불가!
// 싱글 링크드리스트와 달리 prev 포인터 불필요 (llink로 이전 노드 바로 접근)
void ddelete(nodePointer header, nodePointer deleted) {
    if (deleted == header) {
        printf("header 노드는 삭제 불가!\n");
        return;
    }
    deleted->llink->rlink = deleted->rlink;  // 이전 노드 → 다음 노드
    deleted->rlink->llink = deleted->llink;  // 다음 노드 → 이전 노드
    free(deleted);
}

// 리스트 출력 (header는 출력 안 함)
void print_list(nodePointer header) {
    nodePointer cur = header->rlink;
    while (cur != header) {
        printf("%d ", cur->data);
        cur = cur->rlink;
    }
    printf("\n");
}