# 자료구조 기말 정리 — Ch8. Hashing (해싱)

> 🔥 = 시험 단골 / ⚠️ = 100점 방지용 지엽·함정 포인트
> 📌 = PPT에 텍스트로 없고 내가 트레이싱·추론한 부분 (직접 검산 권장)

---

## 0. 큰 그림 — 왜 해싱인가?

**핵심 한 줄:** BST는 "비교해서 찾기" → 좋아야 O(log n). 해싱은 "계산해서 바로 위치 알기" → 평균 **O(1)**.

비유: 도서관에서 책 찾기.
- **BST/탐색** = 서가를 따라 "이거보다 큰가 작은가" 비교하며 내려감.
- **해싱** = "이 책 ISBN을 함수에 넣으니 3번 책장 5칸" 하고 **주소를 계산**해서 바로 감.

그래서 해싱의 본질은 두 가지 결정으로 갈린다:
1. **어떤 함수로 주소를 계산할까?** → 해시 함수 (division / mid-square / folding)
2. **계산했더니 그 자리가 이미 차 있으면?** → 충돌·오버플로 처리 (linear probing / quadratic / chaining)

그리고 테이블이 꽉 차오를 때 통째로 다시 만들기 아까우니까 점진적으로 늘리는 게:
3. **Dynamic Hashing (동적 해싱)** ← 🔥 우리 교수님 이론 단골

전체 흐름:
```
key  --[hash function]-->  bucket 주소  --[꽉 찼으면 overflow 처리]-->  최종 저장 위치
                                              테이블 포화 시 --> dynamic hashing으로 확장
```

---

## 1. 용어·기본 구조

| 용어 | 의미 |
|---|---|
| **bucket** | 해시 테이블의 한 칸 (ht[0]…ht[b-1]), 총 **b**개 |
| **slot** | 한 bucket 안에 record 저장 공간, bucket당 **s**개 |
| **hash function h(x)** | key x → 0 ~ b-1 사이 정수(주소)로 매핑 |
| **synonym** | h(k1)=h(k2)인 서로 다른 두 key (같은 주소로 감) |
| **collision (충돌)** | 새 pair 넣을 bucket이 이미 비어있지 않음 |
| **overflow (오버플로)** | 꽉 찬(full) bucket에 새 identifier를 넣으려 함 |

⚠️ **collision vs overflow 함정:** 둘은 다르다. 그런데 **slot이 1개(s=1)면 collision과 overflow가 동시에 발생**한다. (slot이 여러 개면 충돌해도 빈 slot 있으면 overflow는 아직 아님)

**밀도 공식** 🔥
- **key density** = n / T  (n=테이블 내 identifier 수, T=가능한 전체 key 수)
- **loading factor(loading density)** = **α = n / (s·b)**

⚠️ loading factor 분모는 **s·b** (전체 slot 수). b만 쓰면 틀림.
예제(PPT p9): b=26, s=2, n=10 → α = 10/(26·2) = 10/52 ≈ 0.19

**시간복잡도:** overflow 없다고 가정하면 = (해시함수 계산) + (bucket 내 탐색) = **n과 무관 → O(1)**.

---

## 2. 해시 함수 3종

### ① Division (나눗셈) — 실무 최다 사용 🔥
- **h(k) = k % D**, bucket 범위 0 ~ D-1
- **D 선택이 결정적:**
  - D가 2로 나눠지면 홀/짝 key가 홀/짝 bucket으로 편향
  - D가 작은 소인수(2,3,5,7…)를 가지면 분포 편향
  - → **충분히 큰 소수(prime)** 권장

⚠️ **PPT p14 예제 (트레이싱 단골):** key = 3,6,9,12,15,18,21,24

| key | 3 | 6 | 9 | 12 | 15 | 18 | 21 | 24 |
|---|---|---|---|---|---|---|---|---|
| **% 6** | 3 | 0 | 3 | 0 | 3 | 0 | 3 | 0 |
| **% 7** | 3 | 6 | 2 | 5 | 1 | 4 | 0 | 3 |

→ D=6(=2·3, 작은 소인수)이면 **0,3만** 나오는 끔찍한 편향. D=7(소수)이면 골고루. **소수가 왜 좋은지를 이 표로 묻기 딱 좋음.**

### ② Mid-Square (중간 제곱)
- key를 **제곱**한 뒤, 결과의 **가운데 비트들**을 뽑아 주소로 사용
- r비트를 쓰면 테이블 크기 = **2^r**
- 예: 10100 제곱 → ...(가운데 5비트 추출)... → 주소

### ③ Folding (접기)
- key를 같은 길이 여러 조각으로 나눠 **더함**
- **Shift folding:** 그냥 다 더함
  - k=12320324111220 → (123, 203, 241, 112, 20) → 합 = **699**
- **Folding at the boundaries (경계 접기):** **번갈아 한 조각씩 뒤집어서(reverse)** 더함
  - x2, x4를 reverse: 123 + 302 + 241 + 211 + 20 = **897**

⚠️ shift(699) vs boundary(897) 결과 다름. **어느 게 boundary 방식이고 값이 뭔지** 묻는 단답 가능.

---

## 3. 오버플로 처리

크게 두 갈래:
- **Open addressing (개방 주소법):** 꽉 차면 **테이블 안의 다른 빈 bucket**을 찾아감 (linear / quadratic / rehashing / random probing). s 고정.
- **Chaining (체이닝):** bucket마다 **synonym 연결 리스트** 유지. **s 유연**.

### 3-1. Linear Probing (선형 조사) 🔥
- 탐색 순서: **ht[(h(k)+i) % b]**, i=0,1,2,…
- 빈 자리(NULL) 나올 때까지 한 칸씩 증가. 끝까지 가면 circular하게 0으로.
- search 종료 3조건: (a) key 발견 (b) NULL 만남(없음) (c) 시작점 복귀(테이블 full, 없음)

⚠️ **단점 = clustering (군집화) / 단답 빈칸 후보.**
PPT p21 빈칸: "identifier들은 **cluster(군집/덩어리)**를 형성하게 됨 → search time을 증가시킨다."
이유: synonym 아닌 key들도 한 덩어리로 뭉쳐서, 한 번 뭉치면 점점 더 길어지는 악순환.

📌 PPT p21 "atol" 트레이싱 (h=첫 글자, atol→'a'→0번부터): 0~9가 acos,atoi,char,define,exp,ceil,cos,float,atol,floor… 식으로 이미 차 있어서 한참 밀려감. → cluster 때문에 탐색 비용 폭증을 보여주는 예.

### 3-2. Quadratic Probing (이차 조사) — 실습 과제로 구현함
- 탐색 순서: **f(x)**, **(f(x) + i²) % b**, **(f(x) − i²) % b** (1 ≤ i ≤ (b−1)/2)
- 선형의 **1차 군집(primary clustering) 완화**가 목적 (+i², −i² 양방향으로 튐)
- ⚠️ **b = 4j+3 형태의 소수**일 때 **모든 bucket이 조사됨**(보장). ← 단답 단골 숫자 조건. "4j+3"

### 3-3. Rehashing / Random probing (간단히)
- **Rehashing:** 해시 함수를 여러 개 f₁,f₂,…를 차례로 적용해 군집 줄임
- **Random probing:** (f(x)+s(i))%b, s(i)는 1~(b-1) 사이 난수

### 3-4. Chaining (체이닝) 🔥
- bucket마다 synonym **연결 리스트**. 각 리스트는 그 bucket의 모든 synonym 포함.
- 예(PPT p24): [0]→acos→atoi→atol, [2]→char→ceil→cos→ctime, [5]→float→floor …
- **평균 비교 횟수 = 1 + α/2** ⚠️ (α = identifier 수 / head node 수)
- **최악 비교 횟수 = O(n)** (다 한 리스트로 몰린 경우)

⚠️ **probing의 α는 n/(sb)** 인데 **chaining의 α는 ids/head nodes(=ids/b)** 로 정의가 다름. 공식 1+α/2 의 α를 헷갈리면 함정.

---

## 4. Dynamic Hashing (동적 해싱) 🔥🔥 — 이론 최다 출제

### 왜?
loading density가 임계치를 넘으면 테이블을 키워야 함. 그런데 **b → 2b+1로 D 바꿔서 전부 재해싱(rebuild)은 비쌈**. → **dynamic hashing으로 rebuild 시간 감소**(필요한 부분만 쪼갬).

### 핵심 구조 2가지
1. **trie(트라이) 기반:** identifier의 **비트 시퀀스를 따라가며** 페이지 찾는 이진 트리
2. **directory 기반:** 포인터 배열(directory)로 페이지 가리킴 ← 실제로 쓰는 형태

### 비트 사용 규칙 ⚠️ (가장 잘 틀리는 곳)
- PPT는 **LSB(최하위 비트)에서 MSB 순으로** 비트를 선택해 분기한다.
- **first level 분기 = least significant bit**, second level = 두 번째 하위 비트…
- 예(PPT 두 low-order bits): 각 identifier의 **하위 2비트**가 페이지 주소(00,01,10,11).

### directory depth (디렉터리 깊이) 🔥
- **h(k)의 비트 몇 개를 인덱스로 쓰느냐** = directory depth
- **h(k, d) → directory 크기 = 2^d**
  - h(k,2) → directory 크기 2² = 4
  - h(k,5) → directory 크기 2⁵ = 32

### overflow splitting 동작 (PPT p35 핵심)
페이지 overflow 발생 시:
- **overflow 난 페이지만 재조정** (depth 1 늘려 둘로 split)
- **나머지 페이지들은 directory만 2배**로 늘고, 새 인덱스(앞에 1 붙은 것)는 **기존 페이지를 그대로 가리킴**(공유)
- 예(p35 depth 2→3): 01에서 overflow → 001/101로 쪼갬. 00,10,11은 000/010/011이 되고 100,110,111은 각각 000,010,011과 **같은 페이지**를 가리킴.

### h(k) 계산 예 (PPT 표, 정렬 주의)
- h(A0,1)=0, h(A1,3)=001=1, h(B1,4)=1001=9, h(C1,6)=110001=49
- ⚠️ **h(k, r)의 r은 "쓰는 비트 수"**. 표기상 큰 수(49 등)는 그 비트열을 십진수로 본 것.

### directory 문제점 → 왜 directory를 도입했나
trie 직접 방식의 두 문제:
1. 페이지 접근 시간이 **identifier 구별에 필요한 비트 수에 의존**
2. identifier 분포가 **치우치면(skewed) 트리도 치우침**
→ 이를 해결하려고 **directory(평평한 포인터 배열) 도입**.

---

## 5. 📌 p39 연습문제 트레이싱 (PPT에 답 없음 — 내가 검산한 것, 직접 재확인 권장)

조건: page capacity = 2, 위→아래 순 삽입, directory 방식(하위 비트부터).

삽입 ID와 이진수(하위비트가 분기 기준):
a0=100000, b1=101001, c2=110010, c0=110000, a3=110011, c1=110001, b7=101111, a4=100100, b5=101101, d1=111001

📌 **내가 표준 extendible hashing으로 트레이싱한 결과 (global depth 4):**

| directory 질문 | 가리키는 최종 페이지의 ID |
|---|---|
| **0000** | a0, c0 |
| **0111** | a3, b7 |
| **1001** | b1, d1 |
| **1100** | a4 |

⚠️ **주의:** 이건 표준 확장 해싱 알고리즘으로 돌린 결과라, 교수님 PPT의 split 시 directory 갱신 세부 규칙과 미세하게 다를 수 있음. **반드시 PPT p33~38 그림 규칙대로 손으로 한 번 더 트레이싱해서 대조**할 것. 특히 split 후 어느 비트로 두 페이지를 가르는지(하위 d번째 비트)가 PPT 관례와 맞는지 확인 필요.

---

## 6. 시험 직전 체크리스트

### 🔥 자주 나오는 것
- **loading factor α = n/(s·b)** — 분모 s·b
- **division: D는 큰 소수** + p14 표(% 6 vs % 7 편향)
- **folding** shift(다 더함) vs boundary(번갈아 reverse) — 값 계산
- **linear probing 단점 = clustering** (빈칸 단골)
- **chaining 평균 = 1 + α/2**, 최악 = O(n)
- **quadratic: b=4j+3 소수 → 모든 bucket 조사**
- **dynamic hashing: directory depth d → 크기 2^d**, overflow splitting 동작

### ⚠️ 100점 방지용 (지엽·함정)
- collision ≠ overflow, **단 s=1이면 동시 발생**
- chaining의 α(=ids/head nodes) vs probing의 α(=n/sb) 정의 다름
- mid-square: r비트 → 테이블 크기 2^r
- dynamic hashing 비트 선택은 **LSB→MSB** 순 (반대로 쓰면 페이지 다 틀림)
- directory 도입 이유 = trie의 ①비트수 의존 ②skew 문제 해결

---

## 7. 변별력 예측

중간고사에서 isp/icp(circular queue full count, avail list malloc 횟수)처럼 **세부 규칙 하나로 변별하는 한 문제**가 늘 있었던 패턴을 ch8에 대입하면:

**ch8의 그 "한 문제"는 거의 확실히 Dynamic Hashing의 overflow splitting 트레이싱**일 가능성이 높다. 구체적으로:
- 특정 ID를 삽입했을 때 **directory depth가 몇이 되는지**, 또는
- 특정 directory 인덱스(예: 1001)가 **최종적으로 어느 페이지를 가리키는지 / 그 페이지의 ID는 무엇인지** (= p39 연습문제 형태 그대로)

이게 변별 문제인 이유: **비트를 LSB부터 읽는 규칙**, **overflow 난 페이지만 쪼개고 나머지는 공유**한다는 규칙, **directory 2배 확장 타이밍** — 이 세 규칙 중 하나라도 헷갈리면 답이 통째로 틀린다. 계산 자체는 쉬운데 **규칙을 정확히 아느냐**로 갈리므로 변별에 최적.

📌 교수님 "PPT 예제 반대로" 경향 + 단답식 출제 고려하면:
- PPT는 c5, c1, D1, D2 삽입 예를 보여줬으니 → **시험은 다른 ID 세트(예: p39의 a0,b1,c2,…)로 directory 인덱스가 가리키는 페이지/ID를 단답으로** 물을 가능성. → **p39 트레이싱을 손으로 완벽히 익혀두는 게 이 단원 핵심 대비.**
