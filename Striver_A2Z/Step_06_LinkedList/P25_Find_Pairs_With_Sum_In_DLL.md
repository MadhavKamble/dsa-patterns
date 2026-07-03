# 🔥 Find Pairs with a Given Sum in a Sorted DLL

> **Concept Problem** · **Difficulty:** Medium · **Step 6 — Linked List · P25**

---

## 🧠 Problem Understanding

**What is it asking?**
Given a **sorted** doubly linked list and a target `sum`, return all pairs `(a, b)` with `a + b == sum` (a from the left, b from the right).

**Key Observation:**
Because it's sorted and doubly linked, we can use the classic **two-pointer** trick from both ends — `left` at head, `right` at tail. Move `left` forward (bigger) or `right` backward (smaller) based on the current sum. The `back` pointer is what lets `right` walk **backward** in O(1).

**Simple Example:**
```
List:  1 ⇄ 2 ⇄ 3 ⇄ 4 ⇄ 5 ⇄ 6,  sum = 7
Pairs: (1,6) (2,5) (3,4)
```

---

## 🎯 Interview Progression

### 🥉 Brute — All Pairs

> Nested loop over every `(i, j)` with i before j. O(N²) time, O(1) space. Ignores the sorted property.

### 🥇 Optimal — Two Pointers from Both Ends

> 💡 `left=head`, `right=tail`. If `left+right == sum` → record, move both inward. If `< sum` → `left` forward. If `> sum` → `right` backward. Stop when the pointers meet or cross.

```cpp
vector<pair<int,int>> findPairs(Node* head,int sum){
    vector<pair<int,int>> ans;
    if(head==NULL) return ans;
    Node* left=head;
    Node* right=head;
    while(right->next!=NULL) right=right->next;
    while(left!=right&&right->next!=left){
        int cur=left->data+right->data;
        if(cur==sum){
            ans.push_back({left->data,right->data});
            left=left->next;
            right=right->back;
        }else if(cur<sum){
            left=left->next;
        }else{
            right=right->back;
        }
    }
    return ans;
}
```

**Time:** O(N) (after O(N) to reach the tail) · **Space:** O(1) (excluding the output).

### Why the stop condition is `left != right && right->next != left`
- `left != right` → pointers haven't landed on the **same** node (odd-position crossing).
- `right->next != left` → they haven't **crossed past** each other (even-position crossing). Without this second guard, after `left` and `right` swap sides you'd start double-counting / reading invalid pairs.
- Sorted order guarantees: raising `left` only increases the sum, lowering `right` only decreases it — so no valid pair is ever skipped.

### Dry Run
`1 2 3 4 5 6`, sum=7:

| left | right | cur | action |
|------|-------|-----|--------|
| 1 | 6 | 7 | record (1,6); left→2, right→5 |
| 2 | 5 | 7 | record (2,5); left→3, right→4 |
| 3 | 4 | 7 | record (3,4); left→4, right→3 |
| 4 | 3 | — | `right->next==left` → stop |

**Pairs:** (1,6)(2,5)(3,4) ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "Sorted DLL → two pointers left=head/right=tail. sum==target record+move both; <target left++; >target right--. Stop when meet/cross. O(N)."

---

## 📝 Short Revision Notes

- Needs **sorted** list; `back` pointer enables O(1) backward moves.
- Stop guard: `left != right && right->next != left` (covers odd & even crossing).
- Same idea as two-sum on a sorted array, but on a list.
- Brute O(N²) ignores sortedness — mention then optimize.

---

## ⚠️ Common Mistakes

❌ Using only `left != right` → over-runs on even-length lists (pointers cross).
❌ Forgetting to move **both** pointers after recording a match → infinite loop / duplicates.
❌ Applying two-pointer on an **unsorted** DLL (must sort first, or use a hash set).

---

## 🧠 Pattern Recognition Trigger

**When I see:** "pairs with sum in a sorted (doubly) list", "two-sum on a list" → **two pointers from both ends** using `back`.

---

## 🏆 Pattern Category

`Linked List` · `Doubly Linked List` · `Two Pointers`

---

## ⏱️ 30-Second Last-Minute Revision

> **Pairs with sum (sorted DLL):** left=head, right=tail. ==sum → record + move both; <sum → left++; >sum → right--. Stop `left!=right && right->next!=left`. O(N).
