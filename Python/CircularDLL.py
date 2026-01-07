class Node:
    def __init__(self, data):
        self.data = data
        self.next = None
        self.prev = None

class CircularDLL:
    def __init__(self):
        self.head = None
        self.pos = None
        
    def move_fwd(self):
        if self.head:
            self.pos = self.pos.next
    
    def move_bwd(self):
        if self.head:
            self.pos = self.pos.prev
    
    def insert_head(self, data):
        new_node = Node(data)
        if self.head == None:
            self.pos = self.head = new_node
            # Circular Linked List이기 때문에
            # 노드가 하나라도 있으면 None이 금지됨
            self.head.next = self.head.prev = self.head
        else:
            old_head = self.head
            tail = old_head.prev
            new_node.next = old_head
            new_node.prev = tail
            tail.next = new_node
            old_head.prev = new_node
            self.head = new_node
            
    def insert_tail(self, data):
        new_node = Node(data)
        if self.head == None:  # insert head와 같음
            self.pos = self.head = new_node
            self.head.next = self.head.prev = self.head
        else:
            old_tail = self.head.prev
            old_tail.next = new_node
            new_node.next = self.head
            new_node.prev = old_tail
            self.head.prev = new_node
    
    def pop_head(self):
        # 객체 재정의에 앞서서 None Check 먼저 수행 
        if self.head == None:
            return
        # None Check 이후로 빼기
        old_head = self.head
        tail = old_head.prev
        # 노드가 하나라면
        if self.head == tail:
            self.pos = self.head = None
        else:   
            # pos는 터뜨리면 무조건 다음걸 가리키도록
            if self.pos == old_head:
                self.pos = old_head.next
            tail.next = old_head.next   # 동앗줄 끊기 1
            old_head.next.prev = tail   # 동앗줄 끊기 2
            self.head = old_head.next   # head 교체
            
        return old_head.data
    
    def pop_tail(self):
        if self.head is None:
            return
        
        old_tail = self.head.prev
        if self.head == self.head.next:
            self.pos = self.head = None
        else:
            if self.pos == old_tail:
                self.pos = self.head
            old_tail.prev.next = self.head
            self.head.prev = old_tail.prev
            
        return old_tail.data
            
    def search_bwd(self, data):
        if self.head is None:
            return False
        
        cpos = self.head.prev
        while True:
            if cpos.data == data:
                return True
            if cpos == self.head: 
                break
            cpos = cpos.prev
        return False
        
    def traverse_fwd(self):
        if self.head is None:
            print('Empty')
        else:
            cpos = self.head
            while True:
                print(cpos.data, end=' -> ')
                if cpos == self.head.prev:
                    print('Tail')
                    break
                cpos = cpos.next
            
    def print_pos_val(self):
        if self.pos is None:
            print('Empty')
        else:
            print(f"pos data is {self.pos.data}")
            



# ==========================================
# [Test Suite] 작성한 클래스 검증용 코드
# ==========================================

def run_test():
    print("🧪 Circular Doubly Linked List 테스트 시작\n")

    # 1. 초기화 및 삽입 테스트
    dll = CircularDLL()
    print("[Test 1] 삽입 (Insert Head/Tail)")
    dll.insert_head(10)  # [10]
    dll.insert_tail(20)  # [10, 20]
    dll.insert_head(5)   # [5, 10, 20]
    dll.insert_tail(30)  # [5, 10, 20, 30]
    
    # 결과 확인: 5 -> 10 -> 20 -> 30
    print("  Expect: 5 -> 10 -> 20 -> 30")
    print("  Result: ", end="")
    dll.traverse_fwd()
    
    # 원형 연결 확인 (Tail의 다음이 Head인지)
    if dll.head.prev.data == 30 and dll.head.prev.next == dll.head:
        print("  ✅ Circular Link Checked (Tail <-> Head 연결 정상)")
    else:
        print("  ❌ Circular Link Broken")
    print("-" * 30)

    # 2. 이동 및 현재 위치(pos) 테스트
    print("[Test 2] 이동 (Move Fwd/Bwd)")
    # 현재 pos는 insert 시 설정된 마지막 노드(30) 혹은 구현에 따라 다름.
    # 테스트를 위해 강제로 head로 설정 후 이동해봄
    dll.pos = dll.head # 5
    
    dll.move_fwd() # 10
    dll.move_fwd() # 20
    print(f"  Moved Fwd 2 times. Expect: 20, Actual: {dll.pos.data}")
    
    dll.move_bwd() # 10
    print(f"  Moved Bwd 1 time.  Expect: 10, Actual: {dll.pos.data}")
    print("-" * 30)

    # 3. 검색 테스트
    print("[Test 3] 검색 (Search Bwd)")
    found_20 = dll.search_bwd(20)
    found_99 = dll.search_bwd(99)
    
    print(f"  Search 20: {'✅ Found' if found_20 else '❌ Failed'}")
    print(f"  Search 99: {'✅ Not Found' if not found_99 else '❌ Wrongly Found'}")
    print("-" * 30)

    # 4. 삭제 테스트 (Pop Head/Tail)
    print("[Test 4] 삭제 (Pop)")
    
    val1 = dll.pop_head() # 5 삭제 -> [10, 20, 30]
    print(f"  Pop Head: {val1} (Expect 5)")
    
    val2 = dll.pop_tail() # 30 삭제 -> [10, 20]
    print(f"  Pop Tail: {val2} (Expect 30)")
    
    print("  Current List: ", end="")
    dll.traverse_fwd() # 10 -> 20
    print("-" * 30)

    # 5. 엣지 케이스: 모두 지우고 빈 리스트 만들기
    print("[Test 5] 엣지 케이스 (Empty List)")
    dll.pop_head() # 10 삭제 -> [20] (노드 1개 남음)
    print("  Pop Head... (1 node left)")
    
    last_val = dll.pop_tail() # 20 삭제 -> [] (Empty)
    print(f"  Pop Tail... Last value: {last_val}")
    
    if dll.head is None and dll.pos is None:
        print("  ✅ List is completely empty (Head/Pos is None)")
    else:
        print("  ❌ Memory Leak or Pointer Error")
        
    # 빈 리스트에서 삭제 시도
    empty_pop = dll.pop_head()
    if empty_pop is None:
        print("  ✅ Safe Pop from empty list checked")
    print("-" * 30)
    
    print("\n🎉 모든 테스트 완료!")

# 실행
if __name__ == "__main__":
    run_test()