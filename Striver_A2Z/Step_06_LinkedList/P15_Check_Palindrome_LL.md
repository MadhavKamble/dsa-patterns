# 🔥 Check if a Linked List is a Palindrome

> **LeetCode #234** · **Difficulty:** Easy/Medium · **Step 6 — Linked List · P15**

---

## 🧠 Problem Understanding

**What is it asking?**
Return `true` if the list reads the same forwards and backwards.

**Key Observation:**
Find the middle (slow/fast), **reverse the second half**, then compare it node-by-node with the first half. Optionally restore the second half afterward. O(1) extra space.

**Simple Example:**
```
1 -> 5 -> 2 -> 5 -> 1     → palindrome (true)
1 -> 2 -> 3 -> 4          → not palindrome (false)
```

---

## 🎯 Interview Progression

### 🥉 Brute — Copy to Array / Stack

> Push all values into a vector, then two-pointer check (or compare with its reverse).

```cpp
bool isPalindromeBrute(Node* head){
    vector<int> v;
    Node* temp=head;
    while(temp!=NULL){
        v.push_back(temp->data);
        temp=temp->next;
    }
    int i=0,j=v.size()-1;
    while(i<j){
        if(v[i]!=v[j]) return false;
        i++;
        j--;
    }
    return true;
}
```

**Time:** O(N) · **Space:** O(N).

### 🥇 Optimal — Middle + Reverse Second Half

> 💡 slow/fast to reach the middle, reverse from `slow->next`, compare both halves, then reverse the second half back to leave the list intact.

```cpp
Node* reverseLinkedList(Node* head){
    if(head==NULL||head->next==NULL) return head;
    Node* newHead=reverseLinkedList(head->next);
    Node* front=head->next;
    front->next=head;
    head->next=NULL;
    return newHead;
}

bool isPalindrome(Node* head){
    if(head==NULL||head->next==NULL) return true;
    Node* slow=head;
    Node* fast=head;
    while(fast->next!=NULL&&fast->next->next!=NULL){
        slow=slow->next;
        fast=fast->next->next;
    }
    Node* newHead=reverseLinkedList(slow->next);
    Node* first=head;
    Node* second=newHead;
    while(second!=NULL){
        if(first->data!=second->data){
            reverseLinkedList(newHead);
            return false;
        }
        first=first->next;
        second=second->next;
    }
    reverseLinkedList(newHead);
    return true;
}
```

**Time:** O(N) · **Space:** O(1) (ignoring the reversal recursion stack).

### Why the middle-finding uses `fast->next && fast->next->next`
This variant stops slow at the **end of the first half** so `slow->next` cleanly starts the second half (works for both odd and even lengths). We only compare while `second != NULL`, so an odd-length middle element is naturally skipped — it doesn't need a mirror.

### Dry Run
`1 -> 5 -> 2 -> 5 -> 1`:
- Middle: slow stops at node(2). Reverse `slow->next` = `5 -> 1` → `1 -> 5`.
- Compare first `1 -> 5 -> 2...` vs second `1 -> 5`: 1==1 ✅, 5==5 ✅, second hits NULL → **palindrome** ✅.

---

## 🧾 Recall Line *(10-Second Revision)*

> "Middle via slow/fast, reverse second half, compare both halves, reverse back. O(N)/O(1)."

---

## 📝 Short Revision Notes

- Middle-finder here: `while(fast->next && fast->next->next)` → slow at end of first half.
- Compare loop guarded by `second != NULL` → odd middle auto-skipped.
- **Restore** the second half (reverse back) to be polite / non-destructive.
- Brute (array + two pointers) is the easy fallback if O(N) space is fine.

---

## ⚠️ Common Mistakes

❌ Reversing from `slow` instead of `slow->next` → mishandles the middle.
❌ Not restoring the list (interview may require it intact).
❌ Comparing beyond `second` length → strays into the first half.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "is the list a palindrome", "compare list with its reverse in O(1) space" → **middle + reverse half + compare**.

---

## 🏆 Pattern Category

`Linked List` · `Two Pointers` · `Reversal`

---

## ⏱️ 30-Second Last-Minute Revision

> **Palindrome LL:** slow/fast to middle → reverse 2nd half → compare halves → reverse back. O(N)/O(1). Brute = dump to array + two-pointer.
