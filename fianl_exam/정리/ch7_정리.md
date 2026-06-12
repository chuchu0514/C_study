# 자료구조 Ch7: Sorting — 기말 정리본

> 전체 조망 + 변별력(100점 방지) 지엽 포인트 표시
> 🔥 = 시험 단골 / ⚠️ = 100점 방지용 지엽/함정 포인트

---

## 0. 큰 그림 (왜, 그리고 어떻게 고를까)

정렬은 그 자체가 목적이라기보다, **검색을 빠르게** 하려는 전처리다. 정렬 안 된 리스트는 순차탐색 O(n)뿐이지만, 정렬돼 있으면 **이진탐색 O(log n)**이 된다. 그래서 정렬이 자료구조의 핵심 주제.

핵심 질문은 "어떤 정렬을 언제 쓰나"이고, 그 답은 세 축으로 갈린다: **시간복잡도 / 안정성(stable) / 추가 메모리**.

🔥🔥 **이 챕터의 절반은 아래 비교표다. 이것만 완벽하면 이론 점수 대부분 확보.**

| 정렬 | 평균 | 최악 | 안정성 | 추가공간 | 특징 |
|------|------|------|--------|----------|------|
| **Insertion** | O(n²) | O(n²) | **stable** ✅ | O(1) | 작은 n·거의 정렬된 데이터에 최고 |
| **Quick** | **O(n log n)** | **O(n²)** ⚠️ | **unstable** ❌ | O(log n) | 평균 최고, 최악 주의 |
| **Merge** | O(n log n) | **O(n log n)** ✅ | **stable** ✅ | **O(n)** ⚠️ | 최악이 가장 좋음, 공간 많이 씀 |
| **Heap** | O(n log n) | O(n log n) | **unstable** ❌ | **O(1)** ✅ | 최악 보장 + 공간 적음 |
| **Radix** | O(d(n+r)) | O(d(n+r)) | **stable** ✅ | O(n+r) | 비교 없이 정렬 |

> ⚠️🔥 **안정성 암기 트릭**: **Insertion / Merge / Radix = stable**, **Quick / Heap = unstable**. (이거 빈칸·O/X 단골)
> ⚠️ Merge의 약점은 공간 O(n), Quick의 약점은 최악 O(n²), Heap은 둘 다 좋지만 unstable.

---

## 1. 용어 (Terminology)

- **record / field / key**: 레코드는 한 객체 정보(필드들의 묶음), key는 식별·정렬 기준 필드.
- **Sorting problem**: K_s(1) ≤ K_s(2) ≤ … 가 되도록 레코드를 재배치하는 순열 s 찾기.
- **Ordering relation < 은 transitive**: x<y, y<z ⟹ x<z.

### Stable Sorting 🔥🔥 — 가장 중요한 정의
입력에서 i<j이고 **Kᵢ = Kⱼ**(키가 같음)이면, 정렬 후에도 **Rᵢ가 Rⱼ보다 앞**에 오는 정렬 = stable.
> 즉 "같은 key끼리는 원래 순서를 유지". 같은 키 레코드가 있으면 정렬 결과가 유일하지 않은데, stable이면 유일하게 결정됨.
> 예) 입력 6, 7, 3, 2₁, 2₂, 8 → stable: 2₁, 2₂, 3, 6, 7, 8 / unstable: 2₂, 2₁, … (2의 순서가 뒤집힘)

⚠️ 함정: "정렬 결과의 숫자 나열은 같아도" 같은 키의 **원래 순서 보존 여부**로 stable/unstable이 갈린다.

---

## 2. Insertion Sort (삽입 정렬) 🔥

### 아이디어
"a[1]은 정렬됨. a[2]부터 차례로, 앞의 정렬된 부분에 **알맞은 자리에 끼워넣기**." 손으로 카드 정렬하듯.

```c
void insertionSort(element a[], int n) {
    for (j = 2; j <= n; j++) {
        element temp = a[j];
        insert(temp, a, j-1);   // a[1..j-1] 중 자리 찾아 삽입
    }
}
void insert(element e, element a[], int i) {
    a[0] = e;                   // ⚠️ 보초(sentinel): 경계검사 생략용
    while (e.key < a[i].key) {
        a[i+1] = a[i];          // 한 칸씩 뒤로 밀기
        i--;
    }
    a[i+1] = e;
}
```
⚠️ **a[0] = e (sentinel)**: while문에서 i가 0까지 가도 멈추게 하는 보초값. 빈칸 포인트.
⚠️ 조건이 **`e.key < a[i].key`** (strict <). 같으면(`<=`) 멈춰서 뒤에 둠 → 이게 **stable**의 이유.

### 특징
- **stable** ✅, O(n²), 추가공간 O(1).
- 🔥 **거의 정렬된(partially ordered) 데이터**에 매우 빠름. **작은 n (n ≤ 20)**에 최적.
- ⚠️ 다른 정렬들이 작은 segment에서 insertion sort로 전환하는 이유(quick/merge가 n≤15에서 더 느림).

---

## 3. Quick Sort (퀵 정렬) 🔥🔥

### 아이디어 (분할 정복)
**pivot** 하나 잡고, "pivot보다 작은 건 왼쪽, 큰 건 오른쪽"으로 분할(partition) → 양쪽 재귀.

```c
void quickSort(element a[], int left, int right) {
    if (left < right) {
        int i = left, j = right + 1;
        int pivot = a[left].key;          // ⚠️ pivot = 맨 왼쪽
        do {
            do i++; while (a[i].key < pivot);   // 왼→오, pivot보다 크거나 같은 것 찾기
            do j--; while (a[j].key > pivot);   // 오→왼, pivot보다 작거나 같은 것 찾기
            if (i < j) SWAP(a[i], a[j], temp);
        } while (i < j);
        SWAP(a[left], a[j], temp);        // pivot을 제자리 j로
        quickSort(a, left, j-1);          // 왼쪽 부분
        quickSort(a, j+1, right);         // 오른쪽 부분
    }
}
```
- ⚠️ i = 작은 쪽(왼쪽) 인덱스, j = 큰 쪽(오른쪽) 인덱스. 교차하면 멈추고 pivot을 j에 놓음.
- ⚠️ **left >= right 면 즉시 리턴** (종료 조건).

### 복잡도 🔥
- **평균/최적**: 절반씩 잘 나뉘면 T(n) ≤ cn + 2T(n/2) → **O(n log n)**.
- **최악**: O(n²) ⚠️ — 이미 정렬된 데이터에서 pivot이 한쪽 끝이면 분할이 1:n-1로 됨.
- **unstable** ❌, 추가공간 O(log n)(재귀 스택).
- 🔥 **평균 성능 최고(best average)**지만 최악 O(n²)가 약점.

### ⚠️ 변별력 포인트
- "pivot을 **맨 오른쪽(rightmost)**으로 바꾸고 **non-decreasing**으로 정렬하려면 코드를 어떻게 고치나?" → PPT에 명시된 응용 질문. i/j 초기값과 비교 방향을 대칭으로 수정.
- 성능 개선: segment 크기 ≤ 15면 재귀 멈추고 insertion sort.

---

## 4. 정렬의 하한 (Lower Bound) — Decision Tree 🔥 이론 단골

### "비교 기반 정렬은 O(n log n)보다 빠를 수 없다"
- **Decision tree**: 정렬 과정을 트리로 — 정점=key 비교, 분기=비교 결과.
- n개 정렬의 가능한 결과(순열) = **n!** 가지 → decision tree의 **leaf 수 ≥ n!**.
- decision tree는 binary tree → height k면 최대 leaf 수 = **2^(k-1)**.
- 따라서 **2^(k-1) ≥ n!** ⟹ k-1 ≥ log₂(n!) ⟹ **k ≥ log₂(n!) + 1**.
- log₂(n!) = Σ log₂(i) ≥ … ≥ (n/2)log(n/2) = **Ω(n log n)**.

🔥 결론: 비교 기반 정렬의 **최악 비교 횟수 하한 = Ω(n log n)**. 그래서 merge/heap이 이론상 최선.
⚠️ Radix sort는 **비교를 안 하므로** 이 하한에 안 걸림(그래서 O(d(n+r)) 가능).

---

## 5. Merge Sort (병합 정렬) 🔥🔥

### 두 정렬 리스트 병합 (핵심 연산)
두 정렬된 리스트 A, B를 하나로 → 양쪽 맨 앞 비교해서 작은 걸 C로. 한쪽 비면 나머지 붙임.
```c
if (initList[i].key <= initList[j].key)   // ⚠️ <= 가 stable의 핵심
    mergedList[k++] = initList[i++];
else
    mergedList[k++] = initList[j++];
```
- 시간 **O(n+m)**, 한 원소 이동 O(1).
- 🔥 **`<=`** 라서 같은 키일 때 **앞 리스트(i)** 원소를 먼저 → **stable** ✅.

### Iterative Merge Sort (반복형)
정렬된 segment 크기 s를 **1 → 2 → 4 → 8 …** 두 배씩 키우며 merge pass 반복.
- ⚠️ **merge pass 수 = ⌈log₂ n⌉**, 각 pass O(n) → **총 O(n log n)**.
- ⚠️ segment 크기 s로 짝짓다가 남는 경우(case 분기): `i+2s-1 ≤ n`(완전한 두 쌍), `i+s-1 < n ≤ i+2s-1`(반쪽), 남으면 그대로.

### Recursive Merge Sort (재귀형)
리스트를 반으로 쪼개 각각 재귀 정렬 후 merge. 보통 **link[] 배열(연결 리스트)**로 구현해 실제 데이터 이동 없이 링크만 조정.
- Downward pass(쪼개기) O(n) 전체 + Upward pass(병합) 각 레벨 O(n) × O(log n) 레벨 = **O(n log n)**.

### 특징
- **stable** ✅, 최악도 **O(n log n)** ✅ (최악이 가장 좋은 정렬).
- ⚠️ 단점: **추가공간 O(n)** 필요. (heap sort와의 핵심 차이)
- n ≤ 15에서는 insertion sort가 더 빠름 → small instance는 insertion으로.

### ⚠️ Natural Merge Sort (지엽)
입력에 **이미 정렬된 구간(natural run)**을 초기 segment로 활용 → pass 수 감소.
- 경계는 a[i] > a[i+1]인 지점. "데이터가 부분 정렬됐는지 확인"하는 기능 필요.

---

## 6. Heap Sort (힙 정렬) 🔥🔥 — 실습 Q3 후보

### 아이디어
ch5의 max heap 이용. **(1) max heap 구성 → (2) 루트(최댓값)를 맨 뒤로 빼고 힙 크기 줄여 재조정** 반복.

⚠️🔥 **오름차순 정렬 → max heap 사용!** (헷갈림 1순위)
> 루트(최댓값)를 배열 맨 뒤로 보내고 힙에서 제외 → 뒤에서부터 큰 값이 쌓임 → 결과는 오름차순.
> (내림차순 정렬하려면 min heap. **메모리 패턴: PPT가 min 예제면 시험은 max로 출제**)

### 두 단계
```c
// 1. heap construction: 마지막 leaf의 parent부터 거꾸로 adjust
for (i = n/2; i >= 1; i--)   adjust(a, i, n);     // 전체 O(n)

// 2. n-1번 반복: 루트와 마지막 교환 → 힙 크기 줄여 재조정
for (i = n-1; i >= 1; i--) {
    SWAP(a[1], a[i+1], temp);   // 루트(최대)를 끝으로
    adjust(a, 1, i);            // 남은 [1..i] 다시 heap화
}
```

### adjust(a, i, n) — down-heap (핵심) 🔥
i를 루트로 보고 아래로 내려가며 자리 잡기:
```c
void adjust(element a[], int root, int n) {
    int child = 2 * root;            // 왼쪽 자식
    element temp = a[root];
    int rootkey = a[root].key;
    while (child <= n) {
        if (child < n && a[child].key < a[child+1].key)
            child++;                 // ⚠️ 두 자식 중 큰 쪽 선택
        if (rootkey > a[child].key)  // 부모가 더 크면 자리 확정
            break;
        else {
            a[child/2] = a[child];   // 큰 자식을 부모로 끌어올림
            child *= 2;
        }
    }
    a[child/2] = temp;
}
```
- ⚠️ **heap construction은 O(n)** (직관과 달리 O(n log n) 아님!), adjust 한 번은 **O(log n)**.
- 전체 heap sort = **O(n log n)**.

### 특징
- **unstable** ❌, O(n log n) 보장, 추가공간 **O(1)** ✅ (in-place — merge 대비 장점).

---

## 7. Radix Sort (기수 정렬) 🔥🔥 — 실습 Q3 후보, 이론 "pass 결과" 단골

### 아이디어 (비교 안 함!)
key를 **자릿수(digit)**로 분해해서, 각 자리별로 **bin(버킷)**에 분배·수집 반복.
- **r**: 각 digit가 가질 수 있는 값의 개수(=bin 수). r=10이면 10진수, r=2면 2진수.
- **d**: 자릿수 개수.
- bin은 **linked queue**(연결 큐)로 관리.

### MSD vs LSD ⚠️🔥
| | MSD (Most Significant Digit) | LSD (Least Significant Digit) |
|---|---|---|
| 시작 자리 | **높은 자리(왼쪽)**부터 | **낮은 자리(오른쪽=1의 자리)**부터 |
| 방식 | 분배 후 각 pile을 다시 재귀 정렬 | 한 자리씩 전체를 stable하게 반복 |
| overhead | **큼** ⚠️ | 작음 (구현 간단) |

🔥 **LSD 핵심**: 낮은 자리부터 정렬하되 **반드시 stable**하게. 그래야 높은 자리 정렬 시 낮은 자리 순서가 보존됨.
> 트럼프 예: face(값) 먼저 정렬 → suits(무늬)로 정렬. 같은 무늬 안에서 2→3→…→Ace 순서 유지(stable이라).

### LSD 동작 (10개 수, [0,999], r=10, d=3 → 3회 반복) 🔥
1. **1의 자리**로 bin 분배 → 순서대로 수집
2. **10의 자리**로 분배 → 수집
3. **100의 자리**로 분배 → 수집 → 완료

⚠️ 구현 디테일 (빈칸 가능):
- `a[]`는 그대로 두고 **`link[]`로 다음 원소 위치를 추적** (실제 데이터 안 옮김).
- **front[i] / rear[i]**: digit가 i인 원소 리스트의 **시작/끝 인덱스**.
  - 예) f[3] = digit 3인 첫 원소 index, e[3] = 마지막 원소 index.

### 복잡도
- **O(d(n + r))**. d, r이 작으면 거의 O(n) — 비교 정렬 하한을 안 받음.
- **stable** ✅.

### ⚠️ 변별력 응용 (PPT "생각해 봅시다")
- **non-increasing(내림차순)** 정렬하려면? → bin 수집 순서를 반대로.
- 트럼프처럼 **자리마다 radix가 다른 경우**(face는 13, suits는 4) → 각 자리 bin 수를 다르게.

---

## 8. 시험 직전 체크리스트

### 🔥 자주 나오는 것
- [ ] **5개 정렬 복잡도+안정성 표** 완벽 암기 (이론 절반)
- [ ] stable 정의 + 어느 게 stable인가 (Ins/Merge/Radix ✅, Quick/Heap ❌)
- [ ] Quick: pivot 분할 한 단계 트레이싱, 평균 O(nlogn)/최악 O(n²)
- [ ] Merge: merge pass 수 = ⌈log₂n⌉, 공간 O(n)
- [ ] **Heap sort: 오름차순=max heap**, adjust 동작, construction O(n)
- [ ] **Radix sort: 각 pass 후 결과** (LSD, 1의자리→10의자리→…)
- [ ] decision tree 하한 Ω(n log n) 논증

### ⚠️ 100점 방지용 지엽 포인트 (이번에 노려볼 것)
- [ ] insertion의 **sentinel a[0]=e**, 비교가 `<`(stable 이유)
- [ ] merge의 `<=`가 stable을 만든다는 점
- [ ] heap **construction이 O(n)** (O(n log n) 아님 — 함정)
- [ ] radix의 **front[]/rear[]/link[]** 역할 (데이터 안 옮기고 링크만)
- [ ] **MSD vs LSD** 차이 + MSD overhead 큼
- [ ] decision tree: leaf ≥ n!, height ≥ log₂(n!)+1
- [ ] Natural merge sort: 경계 a[i]>a[i+1]
- [ ] Quick 최악 = **이미 정렬된 입력** (pivot이 끝값일 때)

> 중간고사 isp/icp처럼 세부 규칙 한 문제로 변별하는 패턴 기준,
> ch7에선 **안정성 O/X**, **heap construction O(n) 함정**, **radix의 link[]/front[]/rear[] 메커니즘**,
> **stable을 만드는 비교 연산자(`<` vs `<=`)** 같은 게 그 한 문제가 될 가능성이 높음.
> 실습 Q3는 radix 또는 heap sort 단골이니, 두 코드 손으로 짤 수 있게 연습 권장.
