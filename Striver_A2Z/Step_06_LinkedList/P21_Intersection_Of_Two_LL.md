# 🔥 Intersection of Two Linked Lists

> **LeetCode #160** · **Difficulty:** Easy · **Step 6 — Linked List · P21**

---

## 🧠 Problem Understanding

**What is it asking?**
Two singly lists may merge and share a common tail. Return the **first common node** (by identity, not value), or `NULL` if they never intersect.

**Key Observation:**
Once two lists intersect, they share **every** node afterward (Y-shape, never X). The lengths before the junction may differ — so we must **align** the starting points.

**Simple Example:**
```
List1: 1 -> 3 -> 1 �‾
                    ↘
                     2 -> 4      ← intersection at node(2)
List2:          3 ↗
```

---

## 🎯 Interview Progression

### 🥉 Brute — Hash Set of List1 Nodes

> Put all of list1's nodes in a set; walk list2, first node found in the set is the intersection.

```cpp
node* intersectionBrute(node* head1,node* head2){
    unordered_set<node*> seen;
    while(head1){ seen.insert(head1); head1=head1->next; }
    while(head2){
        if(seen.count(head2)) return head2;
        head2=head2->next;
    }
    return NULL;
}
```

**Time:** O(N+M) · **Space:** O(N).

### 🥈 Better — Length Difference Alignment

> 💡 Compute `diff = len1 - len2`. Advance the longer list's pointer by `diff`, then walk both together; the first equal **node pointer** is the intersection.

```cpp
int getDifference(node* head1,node* head2){
    int len1=0,len2=0;
    while(head1!=NULL||head2!=NULL){
        if(head1!=NULL){ ++len1; head1=head1->next; }
        if(head2!=NULL){ ++len2; head2=head2->next; }
    }
    return len1-len2;
}

node* intersectionPresent(node* head1,node* head2){
    int diff=getDifference(head1,head2);
    if(diff<0)
        while(diff++!=0) head2=head2->next;
    else
        while(diff--!=0) head1=head1->next;
    while(head1!=NULL){
        if(head1==head2) return head1;
        head2=head2->next;
        head1=head1->next;
    }
    return head1;
}
```

**Time:** O(N+M) · **Space:** O(1).

### 🥇 Optimal — Two-Pointer Redirect (Cleanest)

> 💡 Two pointers walk their own list; on reaching the end, redirect to the **other** list's head. After at most `len1 + len2` steps both have walked the same total distance, so they meet at the intersection (or both hit `NULL` together → no intersection).

```cpp
node* intersectionPresent(node* head1,node* head2){
    node* d1=head1;
    node* d2=head2;
    while(d1!=d2){
        d1=d1==NULL?head2:d1->next;
        d2=d2==NULL?head1:d2->next;
    }
    return d1;
}
```

**Time:** O(N+M) · **Space:** O(1).

### Why the redirect works
Path of d1: `len1 (to end) + len2 (from other head to junction)`. Path of d2: `len2 + len1`. Both equal `len1 + len2`, so after that many steps they land on the **same node** — the junction. If no intersection, both become `NULL` at the same step and the loop exits with `d1 == NULL`. Elegant: no length computation, no branching on which list is longer.

### Dry Run (redirect)
Non-intersecting portions of length 3 and 1, shared tail length 2. d1 and d2 each traverse `3+2` and `1+2`, then cross over; they align and meet at the first shared node. ✅

---

## 🚀 Approach Comparison

| Approach | Time | Space | Note |
|----------|------|-------|------|
| Hash set | O(N+M) | O(N) | Simple, extra memory |
| Length diff | O(N+M) | O(1) | Two passes (len + walk) |
| **Two-pointer redirect** | O(N+M) | O(1) | Cleanest, no length math |

---

## 🧾 Recall Line *(10-Second Revision)*

> "Two pointers, on hitting NULL jump to the other head. They meet at intersection (or both NULL). Compare node identity, not value."

---

## 📝 Short Revision Notes

- Intersecting lists share **all** nodes after the junction (Y not X).
- Compare **node pointers** (`d1==d2`), never `->val`.
- Redirect trick equalizes path length `len1+len2` automatically.
- No intersection → both pointers become NULL simultaneously → loop exits.

---

## ⚠️ Common Mistakes

❌ Comparing values instead of node addresses (values can coincidentally match).
❌ In redirect, advancing to `->next` before the NULL check → skips the switch, misses meeting.
❌ Length-diff: applying the diff to the wrong (shorter) list.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "find where two lists merge", "common node / Y-intersection" → **two-pointer redirect** (or length alignment).

---

## 🏆 Pattern Category

`Linked List` · `Two Pointers`

---

## ⏱️ 30-Second Last-Minute Revision

> **Intersection = redirect trick.** `while(d1!=d2){ d1=d1?d1->next:head2; d2=d2?d2->next:head1; }` return d1. Both walk len1+len2 → meet at junction or NULL. O(N+M)/O(1).
