/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* __lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q,
                                     bool *find_p, bool *find_q) {
    struct TreeNode *retval = NULL;
    bool r_p = false, r_q = false, l_p = false, l_q = false;
    
    if (!root)
        return NULL;
    else if (root == q)
        *find_q = true;
    else if (root == p)
        *find_p = true;
    
    // descendant of itself
    retval = __lowestCommonAncestor(root->left, p, q, &l_p, &l_q);
    *find_q |= l_q;
    *find_p |= l_p;
    if (l_p && l_q) {
        return retval;
    } else if ((root == p || root == q) &&
               (l_p || l_q)) {
        return root;
    }

    
    // descendant of itself
    retval = __lowestCommonAncestor(root->right, p, q, &r_p, &r_q);
    *find_q |= r_q;
    *find_p |= r_p;
    if (r_p && r_q) {
        return retval;
    } else if ((root == p || root == q) &&
               (r_p || r_q)) {
        return root;
    }
    
    if ((l_p || l_q) && (r_p || r_q))
        return root;
    
    return NULL;
}

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    bool find_p = false, find_q = false;
    
    return __lowestCommonAncestor(root, p, q, &find_p, &find_p);
}
