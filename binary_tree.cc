#include<stack>
#include<queue>
#include<vector>
#include<iostream>
#include<algorithm>
#include<map>
#include<unordered_map>


using namespace std;

int post_idx;
int pre_idx;
unordered_map<int, int> in_map;

typedef struct Node{
    Node *left;
    Node *right;
    int value;
    Node() : left(NULL), right(NULL), value(-1) {}
    Node(int v) : left(NULL), right(NULL), value(v) {}
} Node;


int GetMaxDepth(Node* root);

void InitBinaryTree(Node *one) {
    if (!one) {
        return;
    }
    Node* two = new Node(2);
    Node* three = new Node(3);
    Node* four = new Node(4);
    Node* five = new Node(5);
    Node* six = new Node(6);
    Node* seven = new Node(7);
    Node* eight = new Node(8);
    Node* night = new Node(9);
    Node* ten = new Node(10);
    one->left = two;
    one->right = three;
    two->left = four;
    four->right = six;
    three->left = five;
    five->left = seven;
    five->right = eight;
    eight->left = night;
    night->right = ten;
    //cout<< one->right->value << endl;
    //cout<< five->left->value << endl;
    
}
vector<int> PreOrder(Node* root) {
    stack<Node*> s;
    vector<int> res;
    Node* cur = NULL;
    if (root) s.emplace(root);
    while (!s.empty()) {
        cur = s.top();
        res.emplace_back(cur->value);
        s.pop();
        if (cur->right) s.emplace(cur->right);
        if (cur->left) s.emplace(cur->left);
    }
    //cout<< res.size() << endl;
    return res;
}

vector<int> InOrder(Node* root) {
    stack<Node*> s;
    vector<int> res;
    Node* cur = root;
    while (cur || !s.empty()) {
        while (cur) {
            s.emplace(cur);
            cur = cur->left;
        }
        cur = s.top();
        res.emplace_back(cur->value);
        s.pop();
        cur = cur->right;
    }
    return res;
}        

vector<int> InOrder1(Node* root) {
    stack<Node*> s;
    vector<int> res;
    Node* cur = root;
    while (cur || !s.empty()) {
        if (cur) {
            s.emplace(cur);
            cur = cur->left;
        } else {
            cur = s.top();
            res.emplace_back(cur->value);
            s.pop();
            cur = cur->right;
            
        }
    }
    return res;
}        
vector<int> PostOrder(Node* root) {
    vector<int> res;
    stack<Node*> s;
    Node* cur = NULL;
    s.emplace(root);
    while (!s.empty()) {
        cur = s.top();
        s.pop();
        res.emplace_back(cur->value);
        if (cur->left) s.emplace(cur->left);
        if (cur->right) s.emplace(cur->right);
    }
    reverse(res.begin(), res.end());
    return res;   
}        

vector<int> PostOrder1(Node* root) {
    vector<int> res;
    stack<Node*> s;
    Node* cur = root;
    Node* prev = NULL;
    while (cur || !s.empty()) {
        while (cur) {
            s.emplace(cur);
            cur = cur->left;
        }
        cur = s.top();
        s.pop();
        if (cur->right == NULL || cur->right == prev) {
            res.emplace_back(cur->value);
            prev = cur;
            cur = NULL;
        } else {
            s.emplace(cur);
            cur = cur->right;
        }
    }
    return res;   
}

vector<int> LayerOrder(Node* root) {
    queue<Node*> q;
    vector<int> res;
    Node* cur;
    if (!root) 
        return res;
    q.emplace(root);
    while (!q.empty()) {
        cur = q.front();
        res.emplace_back(cur->value);
        q.pop();
        if (cur->left) q.emplace(cur->left);
        if (cur->right) q.emplace(cur->right);
    }
    return res;
}
/*
vector<int> LayerOrderFull(Node* root) {
    queue<Node*> q;
    vector<int> res;
    int node = 0;
    int num = 1;
    Node* cur;
    if (!root) 
        return res;
    int depth = GetMaxDepth(root);
    q.emplace(root);
    while (!q.empty() && num <= depth) {
        while (num) {
            cur = q.front();
            res.empalce_back(cur->value);
            q.pop();
            if (cur->right) {
                q.emplace(cur->left);
            } else {
                q.emplace(NULL);
            }
            if (cur->right) {
                q.emplace(cur->right);
            } else {
                q.emplace(NULL);
            }
        }
    }
    return res;
}
*/
vector<vector<int>> LayerOrder1(Node* root) {
    queue<Node*> q;
    vector<vector<int>> res;
    int node = 0;
    Node* cur;
    if (!root) 
        return res;
    q.emplace(root);
    int num = 1;
    while (!q.empty()) {
        vector<int> level;
        while (num) {
            cur = q.front();
            level.emplace_back(cur->value);
            q.pop();
            if (cur->left) {
                q.emplace(cur->left);
                node++;
            }
            if (cur->right) {
                q.emplace(cur->right);
                node++;
            }
            num--;
        }
        res.emplace_back(level);
        num = node;
        node = 0;
    }
    return res;
}

//void split(string input, map<int, int>& res) {
void split(string input, queue<string>& res) {
    string ele;
    char ss = ',';
    int pos = 1;
    for (auto c : input) {
        if (c == ss) {
            //if (ele != "NULL") {
                //res[pos] = atoi(ele.c_str());
            //    res.emplace(ele);
            //}
            res.emplace(ele);
            ele.clear();
            pos++;
        } else {
            ele += c;
        }         
    }
    if (!ele.empty()) {
        res.emplace(ele);
    }
    return ;
}
/*
Node* unserialize(string info) {
    map<int, int> res;
    map<int, Node*> tmp;
    map<int, int>::iterator it;
    split(info, res);
    Node* root = new Node(res[1]);
    tmp[1] = root;
    for (auto a : res) {
        int idx = a.first;
        int val = a.second;
        cout << a.first << " " << a.second << endl;
        Node* node = tmp[a.first];
        it = res.find(idx*2);
        if (it != res.end()) {
            Node* left = new Node(it->second);
            cout << it->first << " " << it->second << endl;
            node->left = left;
            tmp[it->first] = left;   
        }
        it = res.find(idx*2 + 1);
        if (it != res.end()) {
            Node* right = new Node(it->second);
            cout << it->first << " " << it->second << endl;
            node->right = right;
            tmp[it->first] = right;   
        }
    }
    return root;
}

string serialize(Node* root) {
    string res;
    if (!root) 
        return res;
    int depth = GetMaxDepth(root);
    queue<Node*> q;
    int node = 0;
    int num = 1;
    int level = 1;
    Node* cur;
    Node* tmp = NULL;
    q.emplace(root);
    res += to_string(root->value);
    res += ',';
    while (!q.empty()) {
        while(num--) {
            cur = q.front();
            q.pop();
            if (cur == NULL && level < depth) {
                res += "NULL,NULL,";
                node += 2;
                q.emplace(tmp);
                q.emplace(tmp);
            } else if (cur != NULL) {
                if (level < depth) {
                    if (!cur->left) {
                        res += "NULL,";
                        q.emplace(tmp);
                    } else {
                        res += to_string(cur->left->value);
                        res += ",";
                        q.emplace(cur->left);
                    }
                    if (!cur->right) {
                        res += "NULL,";
                        q.emplace(tmp);
                    } else {
                        res += to_string(cur->right->value);
                        res += ",";
                        q.emplace(cur->right);
                    }
                    node +=2;
                }
            }
        }
        level++;
        num = node;
        node = 0;
        cout << q.size() << endl;
    }
    return res;
}
*/

string serialize(Node* root) {
    if (root == NULL) {
        return "#";
    }
    return to_string(root->value) + ',' + serialize(root->left) + ',' + serialize(root->right);
}


Node* helper(queue<string>& res) {
    string v = res.front();
    res.pop();
    if (v == "#") {
        return NULL;
    }
    Node* root = new Node(atoi(v.c_str()));
    root->left = helper(res);
    root->right = helper(res);
    return root;
}

Node* unserialize(string input) {
    queue<string> res;
    split(input, res);
    return helper(res);    
}
int GetMaxDepth(Node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + max(GetMaxDepth(root->left), GetMaxDepth(root->right));
} 

int GetMinDepth(Node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + min(GetMinDepth(root->left), GetMinDepth(root->right));
}
 
bool IsBalance(Node* root) {
    int max = GetMaxDepth(root);
    int min = GetMinDepth(root);
    return (abs(max - min) > 1) ? false : true;
}

int MaxBranch(Node* root) {
    if (root == NULL) {
        return 0;
    }
    int left = GetMaxDepth(root->left) + 1;
    int right = GetMaxDepth(root->right) + 1;
    int ret = left + right + 2;
    return ret;
}

int MaxBranch1(Node* root, int& ans) {
    if (root == NULL) {
        return 0;
    }
    int left = MaxBranch1(root->left, ans) + 1;
    int right = MaxBranch1(root->right, ans) + 1;
    int ret = max(left, right);
    ans = max(ans, left + right + 2);
    return ret;
}
int LeafCount(Node* root) {
    if (root == NULL){
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    return LeafCount(root->right) + LeafCount(root->left);
}

int GetMaxWeight(Node* root) {
    if (root == NULL) {
        return 0;
    }
    return root->value + max(GetMaxWeight(root->left), GetMaxWeight(root->right));
} 

int GetMinDistance(Node* root) {
    if (root == NULL) {
        return 0;
    }
    int left = GetMinDistance(root->left);
    int right = GetMinDistance(root->right);
    if (left * right == 0) {
        return left + right + 1;
    } else {
        return min(left, right) + 1;
    }
}

int GetLevel(Node* root) {
    queue<Node*> q;
    if (root == NULL) return 0;
    q.emplace(root);
    int cur = 1;
    int level = 0;
    int node = 0;
    Node* tmp = NULL;
    while (!q.empty()) {
        while (cur) {
            tmp = q.front();
            q.pop();
            if (tmp->left) {
                q.emplace(tmp->left);
                node++;
            }
            if (tmp->right) {
                q.emplace(tmp->right);
                node++;
            }
            cur--;    
        }
        cur = node;
        node = 0;
        level++;
    }
    return level;
}

int GetNode(Node* root) {
    if (root == NULL) return 0;
    return GetNode(root->left) + GetNode(root->right) + 1;
}

int GetLevelNode(Node* root, int k) {
    if (root == NULL) return 0;
    if (k == 1) return 1;
    return GetLevelNode(root->left, k-1) + GetLevelNode(root->right, k-1);
}
// in pre
Node* MakeTreePreAndIn(vector<int>& s, vector<int>& t, int s1, int s2, int t1, int t2) {
    if (t2 < t1 || s2 < s1) {
        return NULL;
    }
    int value = t[t1];
    Node* root = new Node(value);
    if (t1 == t2 || s1 == s2) {
        return root;
    }
    int idx = in_map[value];
    // len = idx - s1
    //cout << s1 << s2 << t1 << t2 << idx << endl;
    root->left  = MakeTreePreAndIn(s, t, s1, idx - 1, t1 + 1, t1 + 1 + idx - s1 - 1);
    root->right = MakeTreePreAndIn(s, t, idx + 1, s2, t1 + 1 + (idx - s1), t2);
    return root;
}

Node* findRoot(vector<int>& s, vector<int>& t, int s1, int s2, int t1, int t2) {
    if (t2 < t1) {
        return NULL;
    }
    int value = t[t2];
    Node* root = new Node(value);
    if (t1 == t2) {
        return root;
    }
    int idx = in_map[value];
    root->left  = findRoot(s, t, s1, idx - 1, t1, t1 + (idx - s1 - 1));
    root->right = findRoot(s, t, idx + 1, s2, t1 + (idx - s1), t2 - 1 );

    return root;
}

Node* findRoot(vector<int>& inorder, vector<int>& postorder, int start, int end) {
    if (start > end) {
        return NULL;
    }
    int value = postorder[post_idx];
    Node* root = new Node(value);
    int idx = in_map[value];
    post_idx--;
    root->right = findRoot(inorder, postorder, idx+1, end);
    root->left = findRoot(inorder, postorder, start, idx-1);
    return root;
}   

Node* MakeTreePreAndIn(vector<int>& inorder, vector<int>& preorder, int start, int end) {
	if (start > end) {
        return NULL;
    }
    int val = preorder[pre_idx];
    Node* root = new Node(val);
    int idx = in_map[val];
    pre_idx++;
    root->left = MakeTreePreAndIn(inorder, preorder, start, idx - 1);
    root->right = MakeTreePreAndIn(inorder, preorder, idx+1, end);
    return root;
}

Node* Construct(vector<int>& inorder, vector<int>& postorder) {
	pre_idx = 0;
    post_idx = postorder.size() - 1;
    int idx = 0;
    for (auto& val : inorder) {
        in_map[val] = idx++;
    }
    //return findRoot(inorder, postorder, 0, inorder.size() - 1, 0, postorder.size() - 1);
    //return MakeTreePreAndIn(inorder, postorder, 0, inorder.size() - 1, 0, postorder.size() - 1);
    //return findRoot(inorder, postorder, 0, post_idx);
    return MakeTreePreAndIn(inorder, postorder, 0, post_idx);
}

int main() {
    Node* root = new Node(1);
    vector<int> res;    
    InitBinaryTree(root);
    //res = PreOrder(root);
    //cout<< "PreOrder: ";
    //res = InOrder(root);
    //cout<< "InOrder: ";
    //res = PostOrder(root);
    //cout<< "PostOrder: ";
    //for (auto& e:res) {
    //    cout<< e << " ";
    //}
    //cout<< endl;
    
    //res = PostOrder1(root);
    //cout<< "PostOrder: ";
    //for (auto& e:res) {
    //    cout<< e << " ";
    //}
    //cout<< endl;
    
    res = LayerOrder(root);
    cout<< "LayerOrder: ";
    for (auto& e:res) {
        cout<< e << " ";
    }
    cout<< endl;

    int depth = GetMaxDepth(root);
    cout<< "depth : " << depth << endl;
    
    depth = GetMinDepth(root);
    cout<< "depth : " << depth << endl;
 
    bool is_balance = IsBalance(root);
    cout<< "is_balance : " << is_balance << endl;
        
    int weight = GetMaxWeight(root);
    cout<< "weight : " << weight << endl;
 
       
    int level = GetLevel(root);
    cout<< "level : " << level << endl;
    
    int distance = GetMinDistance(root);
    cout<< "distance : " << distance << endl;
    
    int ret = LeafCount(root);
    cout<< "leaf node count : " << ret << endl;
 	   
    ret = MaxBranch(root);
    cout<< "max branch : " << ret << endl;
    int ans = 0;
    ret = MaxBranch1(root, ans);
    cout<< "max branch : " << ans << endl;
    
    ret = GetLevelNode(root, 4);
    cout<< "level 4 node num : " << ret << endl;
 
    vector<int> in   = {4,6,2,1,7,5,8,3};
    vector<int> post = {6,4,2,7,8,5,3,1};
 	vector<int> pre  = {1,2,4,6,3,5,7,8};   
    //Node* t = Construct(in, post);
    Node* t = Construct(in, pre);
    res = LayerOrder(t);
    cout<< "LayerOrder: ";
    for (auto& e:res) {
        cout<< e << " ";
    }
    cout<< endl;

	string s = serialize(root);
	cout << s <<endl; 
 
    Node* tmp = unserialize(s);
    res = LayerOrder(tmp);
    cout<< "LayerOrder: ";
    for (auto& e:res) {
        cout<< e << " ";
    }
    cout << endl;
    int node_num = GetNode(tmp);
    cout << "node_num " << node_num << endl;
    
    return 0;
}
