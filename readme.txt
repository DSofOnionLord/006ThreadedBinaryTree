
1) 입력 데이터를 읽어 threaded binary tree를 구성하시오. 입력 데이터는 다음과 같은 형식을 갖는다.

%cat input.txt
n				// total # of nodes, where n = 10
3   8  12   5   17   23	// store in the order of a complete binary tree
78  0  5    7   0    29	// 0 means an empty node
+   17   55			// 노드 17 inorder 순으로 오른쪽에 노드 55를 삽입
-   78			// 노드 78을 삭제


①  C 언어의 배열이나 동적 메모리 할당을 사용하여 우선 binary tree를 구성하시오.


②  위의 ①에서 구성한 binary tree를 사용하여 threaded binary tree를 구성하시오.


③  위의 ②에서 구성한 threaded binary tree에서 특정 값을 갖는 노드의 오른쪽(inorder)에 하나의 노드를 삽입하는 프로그램을 작성하시오.


④  위의 ③에서 구성한 threaded binary tree에서 특정 값을 갖는 노드의 오른쪽(inorder)에 하나의 노드를 삭제하는 프로그램을 작성하시오.


⑤  위의 ④에서 구성한 threaded binary tree를 복사하는 프로그램을 작성하시오.