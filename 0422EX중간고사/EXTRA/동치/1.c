// 동치 클래스 (Equivalence Class) - 교수님 알고리즘 기반
// 입력: 동치 쌍 <i, j>
// 출력: 동치 클래스별로 묶어서 출력 (i=0부터 순서대로)
//
// 핵심 아이디어:
// 1단계: 쌍 입력 → seq 배열에 양방향 저장 (insert_front 방식)
// 2단계: i=0부터 스캔, out[i]=TRUE면 클래스 출력
//        → 노드 자체를 스택으로 재활용하는 방식!

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 12
#define FALSE 0
#define TRUE 1

// 구조체 선언
typedef struct node *nodePointer;
typedef struct node {
    int data;
    nodePointer link;
} Node;

// 전역 변수
short int out[MAX_SIZE];   // out[i]=TRUE: 아직 출력 안 됨
nodePointer seq[MAX_SIZE]; // seq[i]: i와 동치인 원소들의 연결리스트

int main() {

    int i, j, n = MAX_SIZE;
    nodePointer x, y, top;

    // 초기화
    for (i = 0; i < n; i++) {
        out[i] = TRUE;
        seq[i] = NULL;
    }

    // ===== Phase 1: 쌍 입력 → 양방향으로 seq에 저장 =====
    // <i,j> 입력시 j를 seq[i]에, i를 seq[j]에 추가 (insert_front)
    int pairs[][2] = {
        {0,4}, {3,1}, {6,10}, {8,9}, {7,4},
        {6,8}, {3,5}, {2,11}, {11,0}
    };
    int num_pairs = 9;

    for (int k = 0; k < num_pairs; k++) {
        i = pairs[k][0];
        j = pairs[k][1];

        // j를 seq[i]에 추가
        x = (nodePointer)malloc(sizeof(Node));
        x->data = j;
        x->link = seq[i];
        seq[i] = x;

        // i를 seq[j]에 추가 (양방향!)
        x = (nodePointer)malloc(sizeof(Node));
        x->data = i;
        x->link = seq[j];
        seq[j] = x;
    }
    int count = 0;
    // ===== Phase 2: 동치 클래스 출력 =====
    // i=0부터 순서대로 스캔 → 순서가 중요!
    for (i = 0; i < n; i++) {
        if (out[i]) {  // 아직 출력 안 된 원소 발견
            printf("class %d: %d",count, i);
            out[i] = FALSE;
            count++;
            x = seq[i];   // x: 현재 탐색 중인 리스트
            top = NULL;   // top: 스택 (노드 자체를 재활용)

            for (;;) {
                // 현재 리스트 x를 끝까지 탐색
                while (x) {
                    j = x->data;
                    if (out[j]) {           // 아직 출력 안 된 원소면
                        printf(" %d", j);
                        out[j] = FALSE;
                        // 현재 노드 x를 스택에 push하고 다음으로 이동
                        y = x->link;        // 다음 노드 저장
                        x->link = top;      // x를 스택에 연결
                        top = x;            // top 갱신
                        x = y;              // 다음 노드로 이동
                    }
                    else x = x->link;       // 이미 출력됐으면 그냥 넘어감
                }

                // 현재 리스트 소진 → 스택에서 pop
                if (!top) break;            // 스택 비었으면 종료
                x = seq[top->data];         // pop된 원소의 seq 리스트로 이동
                top = top->link;            // top 갱신
            }
            printf("\n");
        }
    }

    return 0;
}