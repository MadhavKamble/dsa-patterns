# Word Ladder II

> **LeetCode #126** · **Difficulty:** Hard · **Step 15 — Graphs · P25**

---

## Problem Understanding

**What is it asking?**
Given `beginWord`, `endWord`, and `wordList`, return **all shortest transformation sequences** from `beginWord` to `endWord`. Each step changes exactly one letter and every intermediate word must be in `wordList`.

**Input:** `beginWord`, `endWord`, `wordList`
**Output:** All shortest transformation sequences as `vector<vector<string>>`

**Example:**
```
beginWord = "hit", endWord = "cog"
wordList  = ["hot","dot","dog","lot","log","cog"]

Output: [["hit","hot","dot","dog","cog"],
         ["hit","hot","lot","log","cog"]]
```

**Key Observations (vs Word Ladder I):**
- Must find ALL shortest paths, not just length
- Queue stores **entire paths** (not just current word + step count)
- Words used at level `k` must NOT be erased until level `k+1` — multiple paths at same level may need the same word
- Only erase words from set when moving to the next BFS level
- Memory intensive: O(N × M × paths) for queue

---

## Key Difference from Word Ladder I

```
Word Ladder I:  queue<{word, steps}>       → find length
Word Ladder II: queue<vector<string>>      → find all paths

Erase timing:
  WL1: erase immediately on enqueue (prevents revisit)
  WL2: erase only when moving to next level (allows multiple same-level paths)
```

---

## Optimal Approach — BFS with Full Path Queue + Level-wise Erasure

### Key Observation

> Store the entire path in the queue. When we move to the next BFS level (path length increases), erase all words used in the previous level from the set. Within the same level, multiple paths can still use the same word — so we collect used words in `usedOnLevel` and only erase at the level boundary.
>
> All paths that reach `endWord` at the same minimum length are valid answers.

### Algorithm
1. Init set from wordList, queue with `{beginWord}`, `usedOnLevel={beginWord}`
2. BFS: dequeue path `vec`
3. If `vec.size() > level`: increment level, erase all `usedOnLevel` from set, clear `usedOnLevel`
4. Get `word = vec.back()`
5. If `word == endWord`: store `vec` in `ans` (only if same length as first answer)
6. Try all 26 chars at each position: if in set → push word to `usedOnLevel`, push extended path to queue

### Dry Run

```
beginWord="hit", endWord="cog"
Set: {hot,dot,dog,lot,log,cog}
usedOnLevel: [hit], level=0

Level 1 (vec.size()=1→2, erase {hit} from set):
  Process {hit}: neighbors → hot
  usedOnLevel=[hit,hot], queue=[{hit,hot}]

Level 2 (vec.size()=2→3, erase {hot} from set):
  Process {hit,hot}: neighbors → dot, lot
  usedOnLevel=[hot,dot,lot], queue=[{hit,hot,dot},{hit,hot,lot}]

Level 3 (erase {dot,lot}):
  Process {hit,hot,dot}: → dog
  Process {hit,hot,lot}: → log
  usedOnLevel=[dot,lot,dog,log], queue=[{hit,hot,dot,dog},{hit,hot,lot,log}]

Level 4 (erase {dog,log}):
  Process {hit,hot,dot,dog}: → cog
  Process {hit,hot,lot,log}: → cog
  usedOnLevel=[dog,log,cog]

Level 5 (erase {cog}):
  Process {hit,hot,dot,dog,cog}: word==endWord → ans=[[hit,hot,dot,dog,cog]]
  Process {hit,hot,lot,log,cog}: word==endWord, size matches → ans gets second path

ans = [["hit","hot","dot","dog","cog"],["hit","hot","lot","log","cog"]] ✅
```

### Complexity
- **Time:** O(N × M × 26 × L) — N words, M length, 26 chars, L = path length
- **Space:** O(N × M × paths) — queue holds all active paths

---

## Clean C++ Interview Code

```cpp
class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> st(wordList.begin(),wordList.end());
        queue<vector<string>> q;
        q.push({beginWord});
        vector<string> usedOnLevel;
        usedOnLevel.push_back(beginWord);
        int level=0;
        vector<vector<string>> ans;
        while(!q.empty()){
            vector<string> vec=q.front();
            q.pop();
            if(vec.size()>level){
                level++;
                for(auto it: usedOnLevel){
                    st.erase(it);
                }
                usedOnLevel.clear();
            }
            string word=vec.back();
            if(word==endWord){
                if(ans.size()==0){
                    ans.push_back(vec);
                }else if(ans[0].size()==vec.size()){
                    ans.push_back(vec);
                }
            }
            for(int i=0;i<word.size();i++){
                char original=word[i];
                for(char ch='a';ch<='z';ch++){
                    word[i]=ch;
                    if(st.count(word)>0){
                        vec.push_back(word);
                        q.push(vec);
                        usedOnLevel.push_back(word);
                        vec.pop_back();
                    }
                }
                word[i]=original;
            }
        }
        return ans;
    }
};
```

---

## Why Level-wise Erasure Matters

```
Example: two paths use "dot" at the same level
  Path A: hit → hot → dot → dog → cog
  Path B: hit → hot → dot → log → cog  (if dot→log existed)

If we erase "dot" immediately when Path A uses it:
  → Path B can never use dot → miss valid path

Level-wise erasure: keep "dot" in set for the entire level,
erase only when moving to next level → both paths found ✅

But we DO erase previous-level words — "hot" must not be
used at level 3+ to prevent longer-than-minimum paths.
```

---

## Interview Explanation Script

> "Word Ladder II stores entire paths in the queue instead of just word+step. The tricky part is erasure timing: in Word Ladder I, we erase words immediately on enqueue. Here, we erase only when moving to the next BFS level — multiple paths at the same level may need the same intermediate word."

> "I use `usedOnLevel` to collect all words added during the current level. When the path length grows (we've entered a new level), I erase the previous level's words from the set and clear `usedOnLevel`. This ensures no path can grow longer than the shortest path."

> "All paths that reach `endWord` with the same length as the first answer are collected."

---

## Recall Line *(10-Second Revision)*

> "WL2: queue stores full paths. usedOnLevel erased at level boundary (not immediately). All same-length paths to endWord collected."

---

## Short Revision Notes

- Queue holds `vector<string>` (full path) — much heavier than WL1
- `level` tracks current path length; `vec.size() > level` detects level change
- `usedOnLevel`: collect words added this level → erase from set at next level start
- `vec.pop_back()` after `q.push(vec)` — restores `vec` for next iteration (in-place path building)
- Answer condition: `ans.size()==0` OR `ans[0].size()==vec.size()` — only collect shortest paths
- `st.count(word)>0` same as `st.find(word)!=st.end()` — use whichever feels cleaner

---

## Pattern Recognition Trigger

**When I see:**
- "Find ALL shortest paths"
- "All minimum-length transformation sequences"
- "Enumerate all shortest routes"

**I should think of:** BFS with full path in queue + level-wise visited erasure

---

## Common Mistakes

❌ Erasing words immediately (like WL1) → misses paths that use same word at same level
❌ Never erasing words → paths longer than minimum get added to answer
❌ Not restoring `vec` with `vec.pop_back()` after pushing to queue
❌ Including paths longer than first answer (`ans[0].size() != vec.size()`)
❌ Using DFS — won't guarantee shortest paths without extra complexity

---

## What Interviewer Is Testing

- **Level-wise erasure insight** — the core trick vs Word Ladder I
- **Full path storage** in queue + `vec.pop_back()` restore pattern
- **Answer collection logic** — only paths matching minimum length
- Knowing why this is significantly harder than WL1

---

## Word Ladder I vs II Summary

| | Word Ladder I | Word Ladder II |
|--|--------------|----------------|
| Goal | Minimum length | All minimum-length paths |
| Queue stores | `{word, steps}` | `vector<string>` (full path) |
| Erase timing | Immediately on enqueue | At level boundary |
| `usedOnLevel` | Not needed | Required |
| Complexity | O(N×M×26) | O(N×M×26×L×paths) |
| Memory | O(N×M) | O(N×M×paths) |

---

## Related Problems

- [ ] LeetCode #127 — Word Ladder I (same BFS, just return length)
- [ ] LeetCode #433 — Minimum Genetic Mutation
- [ ] Striver Step 15 P24 — Word Ladder I

---

## Pattern Category

`Graphs` · `BFS` · `Implicit Graph` · `Shortest Path` · `All Paths` · `String`

---

## 30-Second Last-Minute Revision

> **Word Ladder II:** Queue = full paths. `usedOnLevel` = words added this level.
> Level change (`vec.size()>level`): erase usedOnLevel from set, clear it.
> `word==endWord` → push to ans if size matches first answer.
> Neighbors: try a-z, in set → push word to usedOnLevel, push extended path, pop_back.
> **Key:** erase at level boundary, NOT immediately.
