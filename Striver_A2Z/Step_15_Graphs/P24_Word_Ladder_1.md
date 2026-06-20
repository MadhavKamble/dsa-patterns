# Word Ladder I

> **LeetCode #127** · **Difficulty:** Hard · **Step 15 — Graphs · P24**

---

## Problem Understanding

**What is it asking?**
Given a `beginWord`, an `endWord`, and a `wordList`, find the **length of the shortest transformation sequence** from `beginWord` to `endWord`, where:
- Each step changes exactly **one letter**
- Every intermediate word must exist in `wordList`

Return `0` if no such sequence exists.

**Input:** `beginWord`, `endWord`, `wordList`
**Output:** Length of shortest transformation sequence (includes both begin and end word), or `0`

**Example:**
```
beginWord = "hit", endWord = "cog"
wordList  = ["hot","dot","dog","lot","log","cog"]

hit → hot → dot → dog → cog   (length = 5)
hit → hot → lot → log → cog   (length = 5)

Output: 5
```

**Key Observations:**
- This is BFS on an implicit graph: each word = node, edge exists if words differ by exactly one character
- BFS gives shortest path (minimum transformation steps)
- Try all 26 letter substitutions at each position — if result is in `wordList` → valid neighbor
- Erase words from set when visited — prevents revisiting (acts as `vis` array)
- `beginWord` may or may not be in `wordList` — erase it from set to avoid using it as intermediate

---

## Optimal Approach — BFS on Word Graph

### Key Observation

> Build the graph implicitly: from any word, generate all neighbors by changing one letter at a time and checking the word set. BFS on this implicit graph gives the shortest path = minimum steps.
>
> Using `unordered_set` for O(1) lookups. Erasing found words from the set marks them visited — avoids using a separate visited set and prevents cycles.

### Algorithm
1. Load `wordList` into `unordered_set`, erase `beginWord`
2. BFS with `queue<{word, steps}>`, start `{beginWord, 1}`
3. For each word dequeued: if equals `endWord` → return `steps`
4. For each position `i`, try all 26 letters:
   - If the new word is in the set → erase it, enqueue with `steps+1`
   - Restore `word[i]` after each position

### Dry Run

```
beginWord="hit", endWord="cog"
Set: {hot,dot,dog,lot,log,cog}

Queue: [{hit,1}]

Dequeue {hit,1}:
  i=0: ait,bit,...,hot✓ → erase hot, push {hot,2}; ...
  i=1: hat,hbt,...(none in set)
  i=2: hia,hib,...(none in set)

Dequeue {hot,2}:
  i=0: dot✓ → push {dot,3}, lot✓ → push {lot,3}
  ...

Dequeue {dot,3}:
  i=0: lot (already erased), ...
  i=2: dog✓ → push {dog,4}

Dequeue {lot,3}:
  i=2: log✓ → push {log,4}

Dequeue {dog,4}:
  i=0: cog✓ → push {cog,5}

Dequeue {cog,5}: == endWord → return 5 ✅
```

### Complexity
- **Time:** O(N × M × 26) — N words × M length × 26 letter substitutions
- **Space:** O(N × M) — queue + set storing all words

---

## Clean C++ Interview Code

```cpp
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        queue<pair<string,int>> q;
        q.push({beginWord,1});
        unordered_set<string> st(wordList.begin(),wordList.end());
        st.erase(beginWord);
        while(!q.empty()){
            string word=q.front().first;
            int steps=q.front().second;
            q.pop();
            if(word==endWord) return steps;
            for(int i=0;i<word.size();i++){
                char original=word[i];
                for(char ch='a';ch<='z';ch++){
                    word[i]=ch;
                    if(st.find(word)!=st.end()){
                        st.erase(word);
                        q.push({word,steps+1});
                    }
                }
                word[i]=original;
            }
        }
        return 0;
    }
};
```

### Variant — store steps in separate dist map (easier to extend)

```cpp
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> st(wordList.begin(),wordList.end());
        if(st.find(endWord)==st.end()) return 0;
        queue<string> q;
        q.push(beginWord);
        st.erase(beginWord);
        int steps=1;
        while(!q.empty()){
            int sz=q.size();
            steps++;
            for(int k=0;k<sz;k++){
                string word=q.front(); q.pop();
                for(int i=0;i<word.size();i++){
                    char original=word[i];
                    for(char ch='a';ch<='z';ch++){
                        word[i]=ch;
                        if(st.find(word)!=st.end()){
                            if(word==endWord) return steps;
                            st.erase(word);
                            q.push(word);
                        }
                    }
                    word[i]=original;
                }
            }
        }
        return 0;
    }
};
```

---

## Interview Explanation Script

> "This is BFS on an implicit word graph. Each word is a node; two words are neighbors if they differ by exactly one character. I find the shortest path from `beginWord` to `endWord` by BFS."

> "Instead of building the full graph (O(N²) edges), I generate neighbors on the fly: for each position, try all 26 letters and check if the result is in the word set — O(M×26) per word. I use the set itself as a visited marker by erasing words when they're added to the queue."

> "Restoring `word[i]=original` after trying all 26 characters for position `i` is critical — I'm mutating the string in-place to avoid creating copies."

---

## Recall Line *(10-Second Revision)*

> "Word Ladder: BFS, queue={word,steps}. Try all 26 chars at each position. Found in set → erase+enqueue. Return steps at endWord. O(N×M×26)."

---

## Short Revision Notes

- Erase `beginWord` from set — prevents going back to start as an intermediate
- Early `endWord` check: if `endWord` not in `wordList` → return 0 immediately
- Restore `word[i]=original` after each position's 26-letter scan
- Erase from set on enqueue (not dequeue) — prevents same word being enqueued multiple times
- BFS guarantees shortest path — don't use DFS for this
- `steps` starts at 1 (includes `beginWord` in the count)

---

## Pattern Recognition Trigger

**When I see:**
- "Minimum transformations between two states"
- "Each step changes one element, must be in valid set"
- "Shortest path in implicit graph"

**I should think of:** BFS with state = current configuration, neighbors = valid one-step changes

---

## Common Mistakes

❌ Not restoring `word[i]` after each position → mutates word permanently
❌ Not erasing `beginWord` from set → can loop back to start
❌ Erasing on dequeue instead of enqueue → same word enqueued multiple times
❌ DFS instead of BFS → doesn't give shortest path
❌ Not checking if `endWord` is in `wordList` → can never reach it

---

## What Interviewer Is Testing

- **Implicit graph BFS** — generating neighbors on the fly
- **Set as visited marker** — erasing instead of a separate `vis` set
- **In-place string mutation + restore** — efficiency trick
- **Why BFS and not DFS** for shortest path

---

## Related Problems

- [ ] LeetCode #126 — Word Ladder II (all shortest paths, harder)
- [ ] LeetCode #433 — Minimum Genetic Mutation (same pattern, 8-char strings, 4 letters)
- [ ] Striver Step 15 P22 — Shortest Path Undirected Unit Weight

---

## Pattern Category

`Graphs` · `BFS` · `Implicit Graph` · `Shortest Path` · `String`

---

## 30-Second Last-Minute Revision

> **Word Ladder:** BFS. Load wordList → unordered_set. Erase beginWord.
> Queue = {word, steps}. Dequeue → if endWord → return steps.
> For each position: try a-z → in set → erase + enqueue with steps+1. Restore word[i].
> **Time:** O(N×M×26) | **Space:** O(N×M)
> **Key:** erase = visited mark. Restore word[i] after each position.
