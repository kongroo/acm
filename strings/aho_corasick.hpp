#ifndef DS_STRING_AHO_CORASICK
#define DS_STRING_AHO_CORASICK

#include <array>
#include <queue>
#include <string>
#include <vector>

struct AhoCorasick {
    struct Node {
        //std::vector<int> V;
        std::array<Node*, 26> ch;
        Node* fail = NULL;
    };
    Node* root;
    AhoCorasick(const std::vector<std::string>& S) {
        root = new Node();
        //int idx = 0;
        auto addString = [&](const std::string & s) {
            Node* pos = root;
            for (size_t i = 0; i < s.size(); i++) {
                if (!pos->ch[s[i] - 'a']) pos->ch[s[i] - 'a'] = new Node();
                pos = pos->ch[s[i] - 'a'];
                // if (i + 1 == s.size()) pos->V.push_back(idx++);
            }
        };
        for (auto&& s : S) addString(s);
        std::queue<Node*> Q;
        Q.push(root);
        while (!Q.empty()) {
            Node* cur = Q.front();
            Q.pop();
            for (char c = 'a'; c <= 'z'; c++) {
                if (!cur->ch[c - 'a']) continue;
                Node* nxt = cur->ch[c - 'a'];
                Node* pos = cur->fail;
                while (pos && !pos->ch[c - 'a']) pos = pos->fail;
                nxt->fail = pos ? pos->ch[c - 'a'] : root;
                Q.push(nxt);
            }
        }
    }
    int solve(const std::string& s) {
        Node* pos = root;
        //set<int> S;
        for (auto c : s) {
            while (pos && !pos->ch[c - 'a']) pos = pos->fail;
            pos = pos ? pos->ch[c - 'a'] : root;
            Node* tmp = pos;
            while (tmp != root) {
                /*
                if (tmp->vis) break;
                for (auto v : tmp->V) S.insert(v);
                tmp->vis = true;
                tmp = tmp->fail;
                */
            }
        }
        return 0;
        // return S.size();
    }
};

#endif /* ifndef DS_STRING_AHO_CORASICK */
