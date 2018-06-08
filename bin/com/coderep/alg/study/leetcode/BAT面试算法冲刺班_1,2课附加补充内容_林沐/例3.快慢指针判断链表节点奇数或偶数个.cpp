#include <stdio.h>

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

int check_nodes(ListNode *head) {
	ListNode *fast = head;
	ListNode *slow = head;
	while(fast){
		slow = slow->next;
		fast = fast->next;
		if (!fast){
			return 1;
   		}
	    fast = fast->next;
   }
   return 0;
}

int main(){
	ListNode a(1);
	ListNode b(2);
	ListNode c(3);	
	a.next = &b;
	b.next = &c;	
	ListNode d(1);
	ListNode e(2);
	ListNode f(3);
	ListNode g(4);	
	d.next = &e;
	e.next = &f;
	f.next = &g;
	printf("a list %d\n", check_nodes(&a));
	printf("d list %d\n", check_nodes(&d));
	return 0;
}

