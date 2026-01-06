class Node:
    def __init__(self, data):
        self.data = data
        self.prev = None
        self.next = None

class DoublyCircularLinkedList:
    def __init__(self):
        self.head = None
        self.current = None

    def insert_at_head(self, data):
        new_node = Node(data)
        if not self.head:
            new_node.next = new_node.prev = new_node
            self.head = self.current = new_node
        else:
            tail = self.head.prev
            new_node.next = self.head
            new_node.prev = tail
            tail.next = self.head.prev = new_node
            self.head = new_node

    def insert_at_tail(self, data):
        new_node = Node(data)
        if not self.head:
            new_node.next = new_node.prev = new_node
            self.head = self.current = new_node
        else:
            tail = self.head.prev
            new_node.prev = tail
            new_node.next = self.head
            tail.next = self.head.prev = new_node


    def delete_from_head(self):
        if not self.head:
            return
        if self.head.next == self.head:
            self.head = self.current = None
            return
        tail = self.head.prev
        if self.current == self.head:
            self.current = self.head.next
        self.head = self.head.next
        self.head.prev = tail
        tail.next = self.head

    def delete_from_tail(self):
        if not self.head:
            return
        if self.head.next == self.head:
            self.head = self.current = None
            return
        tail = self.head.prev
        new_tail = tail.prev
        if self.current == tail:
            self.current = self.head
        new_tail.next = self.head
        self.head.prev = new_tail

    def move_next(self):
        if self.current:
            self.current = self.current.next

    def move_prev(self):
        if self.current:
            self.current = self.current.prev

    def print_current(self):
        if self.current:
            print("Current:", self.current.data)
        else:
            print("Current: None")

    def traverse_forward(self):
        if not self.head:
            print("Empty")
            return
        current = self.head
        while True:
            print(current.data, end=" -> ")
            current = current.next
            if current == self.head:
                break
        print("(head)")

    def traverse_backward(self):
        if not self.head:
            print("Empty")
            return
        current = self.head.prev
        while True:
            print(current.data, end=" <- ")
            current = current.prev
            if current == self.head.prev:
                break
        print("(tail)")


dll = DoublyCircularLinkedList()

dll.insert_at_tail(34)
dll.insert_at_tail(53)
dll.insert_at_tail(21)
dll.insert_at_tail(53)
dll.insert_at_tail(42)

dll.insert_at_head(64)
dll.delete_from_tail()

dll.traverse_forward()
# 64 -> 34 -> 53 -> 21 -> 53 -> (head)

dll.current = dll.head
dll.print_current() # 64

for i in range(8):
    dll.move_next()

dll.print_current() # 21