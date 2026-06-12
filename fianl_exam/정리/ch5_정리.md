# 자료구조 Ch5: Trees — 기말 정리본

> 전체 조망 + 변별력(100점 방지) 지엽 포인트 표시
> 🔥 = 시험에 잘 나오는 핵심 / ⚠️ = 100점 방지용 지엽/함정 포인트

---

## 0. 큰 그림 (왜 트리인가)

리스트·스택·큐는 **선형(linear)** 구조 — 데이터가 한 줄로 늘어선다.
트리는 **계층(hierarchical)** 구조 — 부모-자식 관계로 가지를 친다.

왜 필요한가? 정렬된 데이터에서 **검색을 빠르게** 하고 싶을 때(BST → O(log n)), 우선순위 관리(Heap), 집합 관리(Disjoint Set) 등 "한 줄로는 표현 안 되는 관계"를 다루기 위해서다.

Ch5의 흐름:
**일반 트리 용어 → 이진트리 성질 → 순회 → 스레드 이진트리 → 힙(우선순위 큐) → BST → 선택 트리 → 서로소 집합(union-find)**

---

## 1. 트리 용어 (Terminology)

### 정의
트리는 1개 이상의 노드로 된 유한 집합으로,
1. **root**라는 특별히 지정된 노드가 하나 있고
2. 나머지 노드들은 n ≥ 0 개의 **서로소(disjoint)** 부분집합 T₁, T₂, …, Tₙ으로 분할되며, 각각이 또 트리다 (= 루트의 subtree).

### 핵심 용어
| 용어 | 의미 |
|------|------|
| **degree of a node** | 그 노드의 subtree 개수 (자식 수) |
| **degree of a tree** | 트리 안 노드들의 degree 중 **최댓값** |
| **leaf (terminal)** | degree가 0인 노드 |
| **siblings** | 같은 부모를 가진 자식들 |
| **ancestors** | 루트에서 그 노드까지 경로상의 모든 노드 |
| **descendants** | 그 노드의 subtree에 있는 모든 노드 |
| **level** | 루트 = level 1, 나머지 = 부모 level + 1 |
| **height (depth)** | 트리 내 노드의 **최대 level** |

⚠️ **함정 1**: level은 **1부터** 시작 (이 PPT 기준). height = 최대 level.
⚠️ **함정 2**: degree of a tree는 평균이 아니라 **최댓값**.

---

## 2. 이진 트리 (Binary Tree)

### Tree vs. Binary Tree — ⚠️ 변별력 단골
| | 일반 Tree | Binary Tree |
|---|---|---|
| 빈 트리 | **없음** (1개 이상 노드 필수) | **있음** (empty binary tree 가능) |
| 자식 순서 | 순서 **없음** | 순서 **있음** (left/right 구분) |
| 자식 수 | 제한 없음 | 최대 2개 |

🔥 시험 포인트: "노드 수 0인 트리가 가능한가?" → 일반 트리 ✗, 이진 트리 ✓
🔥 "자식의 순서가 있는가?" → 이진 트리 ✓ (왼쪽/오른쪽이 다른 트리)

### Properties (Lemma)

**Lemma 5.2 [최대 노드 수]**
1. level i의 최대 노드 수 = **2^(i-1)**, i ≥ 1
2. depth k인 이진트리의 최대 노드 수 = **2^k − 1**, k ≥ 1

> 증명 감(귀납법): level i 최대 = level(i-1) 최대 × 2 = 2^(i-2) × 2 = 2^(i-1).
> depth k 전체 = Σ(i=1→k) 2^(i-1) = 2^k − 1 (등비급수).

**Lemma 5.3 [n₀ = n₂ + 1]** 🔥🔥 (가장 자주 나옴)
공집합 아닌 이진트리에서 leaf 수 n₀, degree 2인 노드 수 n₂일 때:
$$n_0 = n_2 + 1$$

> **증명 핵심 (이걸 물어볼 수 있음 ⚠️):**
> - 전체 노드 수: n = n₀ + n₁ + n₂
> - 전체 가지(branch) 수: B = n − 1 (루트 빼고 모든 노드가 부모로의 가지 1개)
> - 또한 B는 자식 관점: B = n₁ + 2·n₂ (degree1은 자식1개, degree2는 자식2개)
> - 두 식 연립: n₁ + 2n₂ = (n₀ + n₁ + n₂) − 1 → **n₀ = n₂ + 1**

### Full vs. Complete — ⚠️ 헷갈림 1순위
| | Full Binary Tree | Complete Binary Tree |
|---|---|---|
| 정의 | depth k에서 노드 수가 **정확히 2^k − 1** (꽉 참) | n개 노드가 depth k인 full tree의 **1~n번 위치에 대응** |
| 모양 | 모든 레벨이 완전히 채워짐 | 마지막 레벨만 **왼쪽부터** 채워질 수 있음 |
| 관계 | full이면 항상 complete | complete가 full은 아닐 수 있음 |

🔥 핵심: **Full ⊂ Complete** (full은 complete의 특수 케이스).
⚠️ 함정: "마지막 레벨이 오른쪽부터 차 있으면?" → complete **아님** (반드시 왼쪽부터).

---

## 3. 이진 트리 표현 (Representation)

### 배열 표현 — Lemma 5.4 🔥 (인덱스 계산 단골)
complete binary tree를 배열에 1번부터 순차 저장하면, 노드 i에 대해:
- **parent(i)** = ⌊i/2⌋ (i ≠ 1일 때)
- **left_child(i)** = 2i (단, 2i ≤ n)
- **right_child(i)** = 2i + 1 (단, 2i+1 ≤ n)

⚠️ **함정**: 인덱스 **1부터 시작** (0번 인덱스 안 씀). 0부터 시작하면 공식이 달라진다.
⚠️ skewed tree(편향)를 배열로 하면 **공간 낭비 심함** (2^k−1 칸 필요한데 k개만 씀).

depth = ⌊log₂ n⌋ + 1

### 링크 표현
```c
typedef struct node *treePointer;
typedef struct node {
    int data;
    treePointer leftChild, rightChild;
} node;
```
⚠️ link 분석: 노드 n개 → 총 link 2n개, 그 중 **사용되는 link n−1개**, **NULL link는 n+1개**.
(이 "n+1개 null link"가 스레드 이진트리의 출발점)

---

## 4. 순회 (Traversals) 🔥🔥

뿌리(V)를 언제 방문하느냐로 구분 (L=왼쪽, R=오른쪽):
| 순회 | 순서 | 약자 |
|------|------|------|
| **Inorder** | L → V → R | LVR |
| **Preorder** | V → L → R | VLR |
| **Postorder** | L → R → V | LRV |
| **Level order** | 레벨 순(BFS), 큐 사용 | — |

🔥 inorder는 **BST에서 정렬된 순서**로 출력됨 (중요!).
⚠️ level order는 재귀 아니라 **큐(queue)**로 구현.

PPT 예제 트리 결과 (외워두면 검산용):
- inorder: **H D I B E A F C G**
- preorder: A B D H I E C F G
- postorder: H I D E B F G C A

### Iterative Inorder (스택 사용) ⚠️ 변별력
재귀 대신 **명시적 스택**으로 inorder 구현:
```
1. 현재 노드부터 왼쪽 끝까지 내려가며 전부 push
2. pop → 방문(출력)
3. 그 노드의 오른쪽 자식으로 이동, 1번 반복
4. 스택 비고 현재 노드도 NULL이면 종료
```

---

## 5. 스레드 이진 트리 (Threaded Binary Tree) ⚠️🔥 fill-in-the-blank 단골

### 왜?
이진트리 link 2n개 중 **n+1개가 NULL로 낭비**됨. 이 NULL을 순회에 쓰자!

### 규칙
- `ptr->leftChild`가 NULL이면 → **inorder predecessor**를 가리키게 (왼쪽 thread)
- `ptr->rightChild`가 NULL이면 → **inorder successor**를 가리키게 (오른쪽 thread)

### 노드 구조 (⚠️ thread 플래그 필수)
```c
typedef struct threadedTree *threadedPointer;
typedef struct threadedTree {
    short int leftThread;    // TRUE면 leftChild가 thread
    threadedPointer leftChild;
    char data;
    threadedPointer rightChild;
    short int rightThread;   // TRUE면 rightChild가 thread
} threadedTree;
```
⚠️ **leftThread/rightThread**: TRUE = thread(순회용 포인터), FALSE = 진짜 자식 link.

### insucc (inorder successor 찾기) — ⚠️ 알고리즘 빈칸 단골
```c
threadedPointer insucc(threadedPointer tree) {
    threadedPointer temp = tree->rightChild;
    if (!tree->rightThread)            // 오른쪽이 thread가 아니면(=진짜 자식 있으면)
        while (!temp->leftThread)      // 그 오른쪽 서브트리의 가장 왼쪽으로
            temp = temp->leftChild;
    return temp;
}
```
> 빈칸 포인트: `!tree->rightThread`, `!temp->leftThread`, `temp = temp->leftChild`
> predecessor를 찾으려면? → right↔left, succ↔pred 전부 대칭으로 바꾸면 됨.

### 스택/재귀 없는 전체 inorder
`insucc`을 **반복 호출**하면 스택 없이 inorder 순회 완성. (head node에서 시작)

---

## 6. 우선순위 큐 & 힙 (Priority Queue & Heap) 🔥🔥

### 우선순위 큐
일반 큐 = FIFO. 우선순위 큐 = **우선순위 높은 게 먼저** 나감 (OS 작업 스케줄링 등).
보통 **힙**으로 구현.

### Max/Min 정의 — ⚠️ 헷갈림 주의
| | Max Tree / Max Heap | Min Tree / Min Heap |
|---|---|---|
| Max/Min **Tree** | 각 노드 ≥ 자식들 | 각 노드 ≤ 자식들 |
| Max/Min **Heap** | max tree **이면서 complete binary tree** | min tree **이면서 complete binary tree** |

🔥 Heap = "Max/Min tree" + "**Complete** binary tree" 둘 다 만족. → 배열 구현 가능.
🔥🔥 **교수님 패턴(메모)**: PPT가 min-heap 예제면 시험은 **max-heap**으로 낸다 (반대로 출제!).

### Insert — O(log₂ n)
새 원소를 **맨 끝(새 leaf)**에 넣고 → 부모와 비교하며 위로 올림(up-heap). 루트까지 path만 비교.
```
i = ++(*n);                    // 배열 크기 1 증가, 끝 위치
while (i != 1 && item > heap[i/2]) {  // max heap 기준
    heap[i] = heap[i/2];       // 부모를 끌어내림
    i /= 2;
}
heap[i] = item;
```
> 예) 21 삽입, n=5→6: 21 > heap[3]이면 heap[6]=heap[3], i=3 → 21>heap[1]이면 heap[3]=heap[1], i=1 → heap[1]=21.

### Delete — O(log₂ n)
**루트(최댓값/최솟값)를 제거** → 마지막 원소를 루트로 올림 → 자식과 비교하며 내림(down-heap, heapify).

⚠️ 함정: 힙에서 삭제는 항상 **루트만** (max heap이면 최댓값). 임의 위치 삭제 아님.
⚠️ 삽입은 끝→위로, 삭제는 끝원소를 루트에 놓고→아래로. 방향 헷갈리지 말 것.

depth = ⌈log₂(n+1)⌉ 이므로 두 연산 모두 O(log n).

---

## 7. 이진 탐색 트리 (BST) 🔥🔥

### 정의
모든 노드에 대해: **왼쪽 서브트리 < 노드 < 오른쪽 서브트리** (중복 없음).
🔥 inorder 순회하면 **오름차순 정렬** 출력.

### 연산
- **search(root, key)**: key < 노드면 왼쪽, key > 노드면 오른쪽. O(h).
- **insert**: search처럼 내려가서 NULL 자리에 삽입.
- **delete**: 3경우
  - leaf → 그냥 삭제
  - 자식 1개 → 자식이 자리 대체
  - 자식 2개 → **왼쪽 서브트리의 최댓값** 또는 **오른쪽 서브트리의 최솟값**으로 대체

### Height — ⚠️🔥 변별력 단골
| 경우 | height |
|------|--------|
| 평균 | **O(log₂ n)** |
| 최악 (정렬된 순서로 삽입) | **O(n)** — skewed tree! |

⚠️🔥 **함정 (메모리에 기록된 변별력 패턴과 동일)**: key를 1,2,3,…,n **순서대로** insert하면 → 오른쪽으로만 뻗은 **skewed tree** → height = n → search O(n). 정렬된 입력이 BST엔 최악.

→ 그래서 **균형 트리(Balanced)**: AVL, 2-3 tree, red-black tree. 최악에도 height O(log n) 보장.
모든 연산이 O(h)로 bound됨.

---

## 8. 선택 트리 (Selection Trees) ⚠️ (덜 다룸 / 지엽 가능성)

### 문제
k개의 정렬된 run(시퀀스)을 하나로 merge할 때, 매번 최솟값을 직접 비교하면 k−1번 비교 필요 → 비효율.

### Winner Tree
- 각 노드가 두 자식 중 **작은 값(승자)**을 가지는 complete binary tree.
- **루트 = 전체 최솟값**.
- 한 record 출력 후 재구축: 해당 leaf에서 루트까지 path만 갱신 → **O(log₂ k)**.

### 복잡도
- 초기 setup: O(k)
- tree level: log₂k + 1
- 재구축: O(log₂ k)
- n개 record 전체 merge: **O(n log₂ k)** 🔥

⚠️ leaf 수 = k(run 수), non-leaf(inner) 수 = 2^(h-1) − 1 (height h일 때).
⚠️ Loser tree도 있음: 각 노드가 진 쪽(loser)을 저장 → 재구축 시 비교 횟수 절감.

---

## 9. 서로소 집합 / Union-Find 🔥

### 개념
원소 0~n-1을 겹치지 않는 집합들로 관리. 트리로 표현 (root = 집합 이름).
- **Find(i)**: i가 속한 집합(루트) 찾기
- **Union(i,j)**: 두 집합 합치기
- 표현: `parent[]` 배열. root는 parent를 **음수**로 저장 (음수 절댓값 = 노드 수).

### simpleUnion / simpleFind
```c
void simpleUnion(int i, int j) { parent[i] = j; }   // i의 부모를 j로
int simpleFind(int i) { while (parent[i] >= 0) i = parent[i]; return i; }
```
⚠️ 문제점: 한쪽으로만 붙이면 **degenerate(편향) tree** → Find가 O(n).

### Weighted Union (가중치 규칙) 🔥 — ⚠️ 변별력
```
count(i) = 트리 i의 노드 수
if count(i) < count(j) then j를 부모로  (작은 트리를 큰 트리 밑에)
else i를 부모로                         (같으면 i가 부모)
```
🔥 **노드 수가 많은 트리가 부모**가 됨. (같으면 i)
🔥 **Lemma**: weightedUnion으로 만든 n노드 트리의 height ≤ **⌊log₂ n⌋ + 1**.

> 구현: root의 parent는 음수, 절댓값이 노드 수.
> 예) weightedUnion(0,8): parent[0]=-4, parent[4]=-3 상태에서, 노드 수 비교해서 적은 쪽을 많은 쪽 밑에.

### Collapsing Find 🔥🔥 — ⚠️ 이론 시험 타깃 (메모 기록)
규칙: **j가 i에서 root까지 path 상의 노드면, j를 직접 root의 자식으로 만든다** (경로 압축).

```c
int collapsingFind(int i) {
    int root, trail, lead;
    for (root = i; parent[root] >= 0; root = parent[root]);  // 1) root 찾기
    for (trail = i; trail != root; trail = lead) {           // 2) path 압축
        lead = parent[trail];
        parent[trail] = root;
    }
    return root;
}
```
> 예) collapsingFind(12): root=8 찾은 뒤, 12, 7, 5를 전부 parent=8로 변경.
> 효과: 다음 Find부터 거의 O(1)에 가까워짐 (amortized).

⚠️ 빈칸 포인트: `parent[root] >= 0` (root 판별), `trail != root` (루프 종료), `parent[trail] = root` (압축).

---

## 10. 시험 직전 체크리스트

### 🔥 자주 나오는 것
- [ ] n₀ = n₂ + 1 공식 **+ 증명**(branch 두 번 세기)
- [ ] 배열 인덱스 공식 (parent ⌊i/2⌋, child 2i / 2i+1, **1부터 시작**)
- [ ] 세 가지 순회 결과 직접 트레이싱 (특히 inorder = BST 정렬)
- [ ] Heap insert/delete 한 단계씩 (⚠️ PPT가 min이면 시험은 max!)
- [ ] BST 삽입/삭제/height (정렬 입력 → skewed → O(n))
- [ ] Kruskal/union-find 맥락의 weightedUnion 규칙
- [ ] Collapsing Find (이론 타깃)

### ⚠️ 100점 방지용 지엽 포인트 (이번에 노려볼 것)
- [ ] **Full vs Complete** 정확한 정의 차이 (마지막 레벨 왼쪽부터!)
- [ ] **Tree vs Binary Tree** 차이 (빈 트리 가능 여부 / 자식 순서)
- [ ] Threaded BT의 **leftThread/rightThread 플래그** 의미 + insucc 빈칸
- [ ] NULL link 개수 = **n+1** (스레드 동기)
- [ ] Selection tree 복잡도 O(n log₂ k), winner/loser 구분
- [ ] weightedUnion height **≤ ⌊log₂ n⌋ + 1** 부등식
- [ ] degree of a tree = **최댓값** (평균 아님), level **1부터**

> 중간고사 때 스택 안/밖 우선순위(isp/icp) 같은 "정의·세부 규칙" 한 문제로 변별했듯,
> ch5에서도 **정의의 미묘한 차이**(full/complete, tree/binary, thread 플래그)나
> **부등식/공식의 경계조건**이 그 한 문제가 될 가능성이 높음.
