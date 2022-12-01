## 알고리즘 및 실습  

### Bubble Sort
+ #### 버블정렬 : O(n)  
***
### Insertion Sort
+ #### 삽입정렬 : O(n)
***
### Selection Sort
+ #### 선택정렬 : O(n)   
***
### Heap
+ #### 1개 삽입마다 힙을 만들어 버린다.
***
### BuildHeap & rBuildHeap
+ #### 상향식 힙생성 : 일단 데이터를 다 이진트리에 저장하고, 힙으로 만들어 버린다.
***
### InPlaceHeapSort
+ #### 제자리 힙정렬 : 힙으로 정렬된 배열을 크기순으로 정렬한다.
+ #### 마지막 노드에 작은것 부터 넣어주며 정렬 : O(log(n))
***
### MergeSort
+ #### 합병정렬 : 분할해서 정렬 후 다시 합치기 : O(log(n))
***
### QuickSort
+ #### 퀵정렬 : 기준(Pivot)을 정해서 기준을 중심으로 크기별로 좌우로 나눠주며 정렬 : 
***
### FindElement
+ #### 사전탐색 알고리즘 : 이미 정렬된 데이터를 O(log(n))으로 찾기
***
### Binary Search Tree (with External Node)
+ #### 이진탐색트리 특징
+ #### 1. 왼쪽 서브트리에는 해당 노드의 키보다 작은 키를 가진 노드로 이루어짐
+ #### 2. 오른쪽 서브트르에는 해당 노드의 키보다 큰 키를 가진 노드로 이루어짐
+ #### 3. 좌우 서브 트리도 모두 이진탐색트리
***
### Binary Search Tree (without External Node)
***
### AVL Tree
***
### Hash Table (separate chaining)
+ #### 분리 연쇄법 : 연결리스트 사용 & 충동X
***
### Hash Table (open addressing)
+ #### 개방 주소법 : 충돌 항목을 테이블의 다른 셀에 저장
+ #### 1. 선형조사법 (linear probing) : A[(h(k) + f(i)) % M] , f(i) = i, i = 0,1,2...
+ #### 2. 2차조사법 (quadratic probing) : A[(h(k) + f(i)) % M] , f(i) = i^2, i = 0,1,2...
+ #### 3. 이중해싱 (double hashing) : A[(h(k) + f(i)) % M] , f(i) = i*h'(k), i = 0,1,2... , h'(k)는 M과 서로소
***
### Graph (Edge list)
+ #### 간선리스트 구조
***
### Graph (Adjacency list)
+ #### 인접리스트 구조
***
### Graph (Adjacency Matrix)
+ #### 인접행렬 구조
***
### Graph DFS
+ #### 깊이 우선 탐색 (Depth-First-Search)
***
### Graph rDFS
+ #### 재귀적 깊이 우선 탐색
***
### Graph BFS
+ #### 너비 우선 탐색 (Breadth-Fisrt-Search)
***
### Floyd-Warshall
+ #### 폴로이드-워셜 알고리즘
+ #### 그래프에서 가능한 모든 노드 쌍에 대한 최단거리
