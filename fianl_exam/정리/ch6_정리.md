## 0. 큰 그림 (왜 그래프인가)

트리는 "계층"(부모-자식, 사이클 없음)만 표현한다. 하지만 현실엔 **임의의 관계**가 많다 — 도시 간 도로, 친구 관계, 통신망. 이건 한 노드가 여러 노드와 자유롭게 연결되고, 사이클도 생긴다. 이걸 다루는 게 **그래프**.

> 역사적 출발점: **쾨니히스베르크 7개 다리** 문제. "각 다리를 딱 한 번씩 건너 출발점으로 돌아올 수 있나?" → 오일러가 땅=정점, 다리=간선으로 추상화. **모든 정점의 차수(degree)가 짝수여야** 가능(Eulerian walk). 그래프 이론의 시초.

Ch6 흐름:
**그래프 ADT/용어 → 표현(인접 행렬/리스트) → 순회(DFS/BFS) → 연결성/신장트리 → 최소비용 신장트리(Kruskal/Prim)**

---

## 1. 그래프 용어 (Terminology)

### 정의
**G = (V, E)** — V는 정점(vertex/node) 집합, E는 간선(edge) 집합. 각 간선은 서로 다른 두 정점을 연결.

### 방향 vs. 무방향
|            Undirected (무방향)     | Directed / Digraph (방향) |
| 간선 표기 | (u,v) = (v,u) **같음** | (u,v) ≠ (v,u) **다름** (방향 있음) |
| 인접 표현 | u, v는 서로 **adjacent** | u is **adjacent to** v / v is **adjacent from** u |

⚠️ **incident**: 간선 (u,v)는 정점 u와 v에 **incident on** 하다 (간선↔정점 관계).
⚠️ adjacent(정점↔정점) vs incident(간선↔정점) 용어 구분.

### 간선 수 — 🔥 (complete graph 공식 단골)
| | 최대 간선 수 (complete graph) |
|---|---|
| **무방향** | **n(n-1)/2** |
| **방향**   | **n(n-1)** |

> 이유: 정점 쌍은 n(n-1)개. 무방향은 (u,v)=(v,u)니까 2로 나눔. 방향은 안 나눔.
⚠️ self-loop / self-edge (u,u)는 보통 **단순 그래프에서 제외**. self-edge 있으면 graphlike structure, 같은 간선 여러 개면 multigraph.

### 차수 (Degree) — 🔥 빈칸/계산 단골
- **degree(v)** = v에 incident한 간선 수
- 🔥 **모든 정점 차수의 합 = 2e** (e = 간선 수). 한 간선이 양끝 정점에 1씩 기여하니까.
- 방향 그래프:
  - **in-degree(v)** = v로 들어오는 간선 수
  - **out-degree(v)** = v에서 나가는 간선 수
중요 무방향일 때 (1,2)라는 간선이 있다치면 1의 degree는 2가 아닌 1이다.
---
Complete Undirected Graph
모든 정점이 서로 연결되어있음 

## 2. 그래프 표현 (Representation) 🔥🔥

### 인접 행렬 (Adjacency Matrix)
공간복잡도: O(n²)
n×n 0/1 행렬. A(i,j) = 1 ⟺ (i,j)가 간선.
- 🔥 대각선(diagonal)은 전부 0 (self-loop 없으니).
- 🔥 **무방향 그래프의 인접 행렬은 대칭(symmetric)**: A(i,j) = A(j,i). 방향 그래프는 대칭 아닐 수 있음.
- 🔥 **rowsum(i) = 정점 i의 degree** (무방향). 방향이면 rowsum = out-degree, **colsum = in-degree** ⚠️
- 공간: **n² bits**. 무방향이면 위/아래 삼각만 저장 → (n-1)n/2 bits.
- degree나 인접 정점 찾기: **O(n)** 시간.

### 인접 리스트 (Adjacency List)
정점 i마다 "i에서 갈 수 있는 정점들"의 리스트. 배열 n개 + 각각 체인.
- 🔥 체인 노드 총 개수: 무방향 = **2e**, 방향(digraph) = **e**.
  (무방향은 간선 하나가 양쪽 리스트에 두 번 등장)
- ⚠️ **Inverse adjacency list**(역인접 리스트): "i로 들어오는 정점들"을 저장. 각 체인의 노드 수 = 해당 정점의 **in-degree**.
  (일반 인접 리스트의 체인 노드 수 = out-degree)

Inverse Adjacency List
일반 list: i → 어디로 가는지 (out)
Inverse list: i ← 어디서 오는지 (in)
각 chain의 노드 수 = 해당 vertex의 in-degree
일반 list 각 chain의 노드 수 = out-degree

Adjacency Lists 
예시 
aList[1] → 2 → 4
aList[2] → 1 → 5
aList[3] → 5
aList[4] → 5 → 1
aList[5] → 2 → 4 → 3

### 가중치 그래프 = Network
간선에 가중치(cost) 있는 그래프 = **network**.
- cost adjacency matrix: C(i,j) = 간선 (i,j)의 비용.
- 인접 리스트면 각 원소가 (인접 정점, 가중치) 쌍.

행렬: C[i][j] = 가중치(원랜 1임)  → Cost Adjacency Matrix
리스트: 각 노드를 (vertex, weight) 쌍으로 저장

### 행렬 vs 리스트 선택 ⚠️
| | 인접 행렬 | 인접 리스트 |
|---|---|---|
| 공간 | O(n²) — **dense graph 유리** | O(n+e) — **sparse graph 유리** |
| 간선 존재 확인 | O(1) | O(degree) |
| 모든 인접정점 순회 | O(n) | O(degree) |

---

## 3. 순회: DFS / BFS 🔥🔥🔥 (이론·실습 둘 다 단골)

### DFS (깊이 우선) — 스택/재귀
"갈 수 있는 데까지 깊게 파고들었다가 막히면 되돌아온다(backtrack)."
```c
struct node {
    int vertex;        // 연결된 vertex 번호
    struct node *link; // 다음 노드 포인터
};

nodePointer graph[MAX];  // 각 vertex의 리스트 시작점
graph[0] ──→ NULL
graph[1] ──→ [2] → [4] → NULL
graph[2] ──→ [1] → [5] → NULL
graph[3] ──→ [5] → NULL
graph[4] ──→ [5] → [1] → NULL
graph[5] ──→ [2] → [4] → [3] → NULL

void dfs(int v) {
    nodePointer w;
    visited[v] = TRUE;
    printf("%5d", v);
    for (w = graph[v]; w; w = w->link)
        if (!visited[w->vertex])
            dfs(w->vertex);   // 재귀!
}
```

### BFS (너비 우선) — 큐(FIFO)
"가까운 것부터 레벨 단위로 넓게 퍼진다."
```c
void bfs(int v) {
    nodePointer w;
    front = rear = NULL;
    printf("%5d", v);
    visited[v] = TRUE;
    addq(v);
    while (front) {
        v = deleteq();
        for (w = graph[v]; w; w = w->link)
            if (!visited[w->vertex]) {
                printf("%5d", w->vertex);
                addq(w->vertex);
                visited[w->vertex] = TRUE;
            }
    }
}

```
DFS로 트리 탐색할 때:

현재 노드 출력 → 왼쪽 → 오른쪽   : Preorder   ← DFS랑 제일 비슷
왼쪽 → 현재 노드 출력 → 오른쪽   : Inorder
왼쪽 → 오른쪽 → 현재 노드 출력   : Postorder

### ⚠️🔥 DFS vs BFS 핵심 비교 (가장 자주 틀리는 곳)
| | DFS | BFS |
|---|---|---|
| 자료구조 | **스택**(재귀) | **큐**(FIFO) |
| visited 표시 시점 | 방문(pop/호출) 시 | **큐에 넣을 때(enqueue)** |
| printf 위치 | 함수 진입 직후 | 큐에 넣기 직전 |
| 결과 | 깊게 | 레벨 순 |

⚠️ **함정**: BFS는 큐에 **넣는 순간** visited=TRUE로 찍는다(중복 삽입 방지). DFS는 들어가서 찍음. 트레이싱할 때 이거 헷갈리면 순서 다 틀어짐.

🔥 **교재 281p dfs(0) 결과** (검산용): **0 1 3 7 4 5 2 6**
> 인접 리스트 순서대로: 0→1→(1의)3→(3의)7→(7의)4→5→(5의)2→(2의)6
🔥 같은 그래프 BFS(0)이면 레벨 순: 0 1 2 3 4 5 6 7

### ⚠️ 트레이싱 주의: 인접 리스트 순서가 결과를 결정
같은 그래프라도 인접 리스트에 정점이 적힌 **순서**에 따라 DFS/BFS 방문 순서가 달라진다. 시험에선 주어진 리스트(또는 인접 행렬 → 작은 번호부터) 순서를 **그대로** 따라야 함.

### 시간 복잡도 🔥
| | 인접 행렬 | 인접 리스트 |
|---|---|---|
| DFS | O(n²) | O(n + e) | vertex마다 n개 열 다 확인, vertex n개 + edge e개만 확인
| BFS | O(n²) | O(n + e) |

> 둘 다 복잡도 같음. 1개 connected component면 O(n²) / O(n+e).
> BFS: 각 정점은 큐에 정확히 한 번 들어갔다 나옴.

---

## 4. 경로·연결성 용어 🔥
트리는 그래프의 특수한 형태
트리는 싸이클이 없고 연결성이 반드시 존재 so edge수가 n-1개인것 그리고 루트도 존재함 

| 용어 | 정의 |
|------|------|
| **subgraph** G' | V(G') ⊆ V(G), E(G') ⊆ E(G) | 원래 그래프의 V, E 일부로 만든 그래프
| **path** (경로) | u → i₁ → … → v, 각 연속쌍이 간선 |u에서 v까지 이어지는 vertex 시퀀스
| **simple path** | 처음·끝 빼고 모든 정점이 **서로 다른** 경로 | 처음·끝 제외하고 중복 vertex 없는 path
| **cycle** (사이클) | **처음=끝**인 simple path |
| **connected** (무방향) | 모든 정점 쌍 사이에 경로 존재 |
Connected Graph: 모든 vertex 쌍 사이에 path가 존재(undirected) Connected graph → component 1개
| **connected component** | **maximal** connected subgraph (더 못 키우는 연결 덩어리) |

🔥🔥 **Tree(그래프 관점)**: **사이클 없는 연결 그래프**. 정점 n개면 간선 정확히 **n-1개**.
⚠️ "connected component는 maximal" — 더 이상 정점·간선을 추가하면서 연결성을 유지할 수 없는 최대 덩어리. connected graph는 component가 정확히 1개.

### connected component 찾기 (DFS 활용)
```c
void connected(void) {
    for (i = 0; i < n; i++)
        if (!visited[i]) { dfs(i); printf("\n"); }
}
```
⚠️ for문이 도는 횟수 중 실제 dfs가 호출된 횟수 = **연결 요소 개수**.

---

## 5. 신장 트리 (Spanning Tree) 🔥

Spanning Tree (신장 트리): "그래프에서 cycle만 걷어내서 트리로 만든 것"
DFS/BFS 탐색은 모든 vertex 방문이 목적이고,
그 과정에서 사용한 edge들만 모으면 Spanning Tree가 부산물로 나오는 것!

### 정의
원래 그래프의 **모든 정점을 포함**하면서, 그래프의 간선만으로 만든 **트리**(사이클 없음).
- 정점 n개 → 신장 트리는 정점 n개, 간선 **n-1개**. 🔥

① 시작 vertex가 달라지면 → 완전히 다른 spanning tree
② 같은 시작점이어도 인접 리스트 순서가 달라지면 → 다른 spanning tree

### DFS/BFS spanning tree
- **DFS spanning tree**: DFS 중 "처음 방문하는 정점에 닿을 때 사용한 간선"들의 집합.  //유일하지 않음!
- **BFS spanning tree**: BFS 중 같은 방식. //유일하지 않음!

같은 그래프도 탐색 방법에 따라 모양이 달라짐!
⚠️ 둘은 일반적으로 **모양이 다르다** (DFS는 깊고 길쭉, BFS는 얕고 넓음). 같은 그래프·같은 시작점이라도.

---

## 6. 최소 비용 신장 트리 (MST) 🔥🔥🔥 — 이론 단골 "Kruskal/Prim 구분 + 결과"

### 정의
신장 트리 중 **간선 가중치 합이 최소**인 것. 두 대표 알고리즘: Kruskal, Prim. (둘 다 그리디)  prim kru 결과동일 !!

이게 왜 나왔냐
Spanning Tree는 여러 개 만들 수 있어.
근데 edge에 가중치(비용) 가 있을 때 → 비용이 가장 적은 Spanning Tree를 원함!
Tree cost = 선택된 edge 가중치의 합

### Kruskal — **간선(edge) 기반** 🔥 싼 edge부터 하나씩 추가 //cycle을이루지않는edge를선택 Sparse (edge 적음)일때 유리 
```
T = {};
간선들을 cost 오름차순(nondecreasing)으로 정렬
while (T가 n-1개 미만 && E 안 비었음) {
    가장 싼 간선 (v,w) 선택, E에서 제거
    if ((v,w)가 T에 사이클 안 만들면)  add (v,w) to T;
    else  discard;
}
if (T가 n-1개 미만)  "No spanning tree"

1단계: 모든 edge를 가중치 오름차순 정렬
2단계: 가장 작은 edge부터 선택
cycle 생기면 → 스킵
cycle 안 생기면 → 추가
3단계: edge가 n-1개 될 때까지 반복


```
🔥 **핵심**: 전체 간선을 **싼 것부터** 보면서, **사이클만 안 생기면** 추가. 정점 무관, 숲(forest)이 점점 합쳐짐.

⚠️🔥 **사이클 검사 = union-find**:
- 간선으로 연결된 정점들을 하나의 **집합(set)**으로 관리.
- 새 간선 (v,w) 추가 시, **v와 w가 이미 같은 set**이면 → 사이클! → 버림.
- 다른 set이면 → 추가하고 두 set을 **union**.

> 예 (PPT): {0,5}{2,3}{1}{6}{4} → 간선 14(1-6) 추가 → {0,5}{2,3}{1,6}{4} → 간선 16(2-1) 추가 → {0,5}{1,6,2,3}{4} … (set이 점점 합쳐짐)


### Prim — **정점(vertex) 기반** 🔥
```
TV = {0};  T = {};   // 임의의 시작 정점 가능
while (T가 n-1개 미만) {
    let (u,v) = u∈TV, v∉TV 인 간선 중 최소 비용
    if (없으면) break;
    add v to TV;  add (u,v) to T;   // ⚠️ 빈칸 단골
}
```

Prim     vertex 기반 — 트리를 키워나가며 확장 Dense (edge 많음>>vertex) 일때 유리  왜? vertex기반이니까 ! edge가 vertex보다 많을 때 유리하겠지? 
한붓그리기가 아니다! 어느 정점에서 시작해도 트리모양은 달라져도 max cost는 같다 
let (u, v) be a least cost edge such that
    u ∈ TV   ← TV 안의 vertex
    v ∉ TV   ← TV 밖의 vertex  ← 이게 핵심!
TV안의 정점에서 시작해서 TV밖의 정점 이랑 연결 제일싼거 고르기 그 중 

TV 정점순서 Ex) {0,5,4,3,2,1,6}
T = 선택한 edge 모음{(0,5), (5,4), (4,3), (3,2), (2,1), (1,6)}  ← n-1=6개!

🔥 **핵심**: **하나의 트리**에서 시작해, "트리에 닿아있는 간선 중 가장 싼 것"으로 트리를 **한 정점씩** 키워나감. 항상 연결 상태 유지.

⚠️ **빈칸 단골**: `add v to TV;` 와 `add (u,v) to T;` 두 줄. (방문 정점 집합 TV와 트리 간선 집합 T 둘 다 갱신)
⚠️ Prim은 **임의의 정점**에서 시작 가능 (결과 MST는 같지만 간선 추가 순서가 다름).

### ⚠️🔥🔥 Kruskal vs Prim — 가장 중요한 변별 포인트
| | **Kruskal** | **Prim** |
|---|---|---|
| 기준 | **간선(edge)** 기반 | **정점(vertex)** 기반 |
| 진행 방식 | 싼 간선부터 골라 숲을 합침 | 한 트리를 한 정점씩 확장 |
| 중간 상태 | 여러 조각(forest) 가능 | 항상 **하나의 연결 트리** |
| 사이클 방지 | **union-find** | v∉TV 조건으로 자동 |
| 유리한 경우 | **sparse graph**(간선 적음) | **dense graph**(간선 많음) |

🔥 시험: "각 단계에서 추가되는 간선 순서를 쓰라"가 단골. **Kruskal은 전체에서 최소 간선**, **Prim은 트리에 닿은 것 중 최소 간선** — 이 차이로 중간 순서가 달라진다(최종 MST 비용은 같음).

> **메모리 패턴 주의**: 너는 메모리상 Prim을 final용으로 아직 안 봤었음. 위 Prim 부분(빈칸 두 줄 + 정점 기반 + 임의 시작) 꼭 챙기기.

### PPT 예제 그래프 (정점 0~6, 검산용)
간선 가중치: 0-5=10, 0-1=28, 1-6=14, 1-2=16, 2-3=12, 3-4=22, 4-5=25, 4-6=24, 3-6=18
- **Kruskal 추가 순서**(싼 것부터, 사이클 제외): 10(0-5) → 12(2-3) → 14(1-6) → 16(1-2) → 22(3-4) → 25(4-5)
- **Prim**(0 시작): 10(0-5) → 25(5-4) → 22(4-3) → 12(3-2) → 16(2-1) → 14(1-6)
- 총 비용 = 10+12+14+16+22+25 = **99** (둘 다 같음) 🔥

---

## 7. 시험 직전 체크리스트

### 🔥 자주 나오는 것
- [ ] complete graph 간선 수: 무방향 **n(n-1)/2**, 방향 **n(n-1)**
- [ ] 차수 합 = 2e / 인접 행렬 rowsum=out-degree, colsum=in-degree
- [ ] 인접 리스트 노드 수: 무방향 2e, 방향 e
- [ ] **DFS/BFS 방문 순서 직접 트레이싱** (실습 Q1 단골!)
- [ ] DFS=스택/재귀, BFS=큐 / 복잡도 O(n²) vs O(n+e)
- [ ] spanning tree 정점 n개 → 간선 n-1개
- [ ] **Kruskal vs Prim 구분 + 각 단계 간선 추가 순서**
- [ ] Kruskal의 union-find 사이클 검사

### ⚠️ 100점 방지용 지엽 포인트 (이번에 노려볼 것)
- [ ] **adjacent vs incident** 용어 정확히
- [ ] 방향그래프: adjacent **to** vs adjacent **from** 방향
- [ ] **inverse adjacency list** = in-degree (일반은 out-degree)
- [ ] BFS에서 visited 찍는 시점 = **큐에 넣을 때** (방문 때 아님!)
- [ ] connected component = **maximal** subgraph
- [ ] Prim 코드 빈칸: `add v to TV; add (u,v) to T;`
- [ ] Kruskal=sparse 유리, Prim=dense 유리
- [ ] DFS/BFS spanning tree는 같은 그래프라도 **모양이 다름**
- [ ] Euler walk 조건: 모든 정점 degree **짝수** (쾨니히스베르크)

> 중간고사 isp/icp처럼 "정의·세부 규칙" 한 문제로 변별하는 패턴 기준,
> ch6에선 **adjacent/incident 용어**, **BFS의 visited 시점**, **inverse adjacency list = in-degree**,
> 혹은 **Kruskal/Prim의 기준 차이(간선 vs 정점)** 가 그 한 문제가 될 가능성이 높음.
