#include <iostream>
#include "assert.h"
#include "map"
#include "vector"
#include "algorithm"
using namespace std;

struct Node{
    int data;
    Node* next;
    Node(int data) : data(data){};

};
class Vector{
private:
    int *arr = {nullptr};
    int capacity{};
    int size {0};
public:
    Vector(int size) : size(size){
        if(size < 0)
            size = 1;
        capacity = size + 10;
        arr = new int[capacity];
    }
    ~Vector(){
        delete[] arr;
        arr = nullptr;
    }
    int get_size(){
        return size;
    }
    int get(int idx){
        assert(idx >= 0 && idx < size);
        return arr[idx];
    }
    void set(int idx,int val){
        assert(idx >= 0 && idx < size);
        arr[idx] = val;
    }
    void print(){
        for(int i =0;i<size;i++){
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
//    void insert(int val,int idx){
//        int *temp = new int [size - idx + 1];
//        temp[0] = val;
//        for(int i = idx;i<size;i++){
//            temp[i - idx + 1] = arr[i];
//        }
//        this->push_back(-1);
//        // 0 1 2 3 4 5
//        for(int i = idx;i<size;i++){
//            arr[i] = temp[i - idx];
//        }
//    }

    void insert(int idx, int value) {
        assert(0 <= idx && idx < size);

        // we can't add any more
        if (size == capacity)
            expand_capacity();

        // Shift all the data to right first

        for(int p = size-1; p >= idx; --p)
            arr[p+1] = arr[p];

        arr[idx] = value;
        ++size;

        // Common mistake to iterate from begin to end
        // the whole array right array will be arr[idx]
        //for (int p = idx; p < size; ++p)
    }
    int pop(int idx){
        assert(0 <= idx && idx < size);
        int val = arr[idx];
        for(int i =idx;i<size-1;i++){
            arr[i] = arr[i+1];
        }
        size--;
        // 1 2 3 4 5
        return val;


    }
    int find(int value){
        for(int i =0;i<size;i++){
            if(arr[i] == value)
                return i;
        }
        return -1;
    }
    int find_transposition(int target){
        int pos = find(target);
        if(pos != -1){
            if(pos >= 1) {
                int temp = arr[pos - 1];
                arr[pos - 1] = arr[pos];
                arr[pos] = temp;
            }
            pos--;
        }
        return pos;
    }
    void expand_capacity(){
        capacity *= 2;
        //cout << "expanded\n";
        int *temp = new int [capacity];
        for(int i = 0;i<size;i++){
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
    }
    void push_back(int val){

        if(size == capacity){
            expand_capacity();
        }
        arr[size++] = val;

    }
    void right_rotate(int time){
        for(int j = 0;j<(time % size);j++) {
            int last = arr[size - 1];
            for (int i = size - 1; i > 0; i--) {
                arr[i] = arr[i - 1];
            }
            arr[0] = last;
        }
    }
    void left_rotate(int time) {
        for (int j = 0; j < (time % size); j++) {
            int first = arr[0];
            for (int i = 0; i < size - 1; i++) {
                arr[i] = arr[i + 1];
            }
            arr[size - 1] = first;
        }
    }
};
class LinkedList{
private:
    Node* tail{};
    int length =0;
public:
    Node* head{};

    ~LinkedList(){
        while (head){
            Node* curr = head->next;
            delete head;
            head = curr;
        }
    }
    Node* get_nth(int t){
        int c = 0;
        for(Node* i = head;i;i = i->next){
            if(t == ++c)
                return i;
        }
        return nullptr;
    }
    Node* get_nth_from_back(int t){
        // 1 2 3 4 5 6 len = 6
        // 6 5 4 3 2 1
        // length - nth + 1 = nth from back
        return get_nth(length - t + 1);
    }
    Node* find(int target){
        return find(head,target);
    }
    Node* find(Node* tempHead,int target){
        if(tempHead == nullptr)
            return nullptr;
        if(tempHead->data == target)
            return tempHead;

        return find(tempHead->next,target);
    }
    int search(int t){
        int c = 0;
        for(Node* i = head;i;i = i->next){
            if(t == i->data)
                return c;
            c++;
        }
        return -1;
    }
    void print(){
        Node* tempHead = head;
        for(Node *i = tempHead; i != nullptr;i = i->next){
            cout << i->data << " ";
        }
        cout << "\n";
    }
    void print1(){
        Node* tempHead = head;
        while (tempHead != nullptr){
            cout << tempHead->data << " ";
            tempHead = tempHead->next;
        }
        cout << "\n";
    }
    void print2(){
        print2(head);
    }
    void print2(Node* tempHead){
        if(tempHead == nullptr) {
            cout <<"\n";
            return;
        }
        cout << tempHead->data << " ";
        print2(tempHead->next);
    }
    void embed_after(Node* node,int val){
        Node* item = new Node(val);
        length++;
        node->next = item;
        item->next = node->next;
    }
    void insert_end(int val){
        length++;
        Node* t = new Node(val);
        if(head == nullptr && tail == nullptr) {
            head = tail = t;
            t->next = nullptr;
        }
        {
            tail->next = t;
            tail = t;
            tail->next = nullptr;
        }

    }
    void insert_end(Node *t){
        length++;
        if(head == nullptr && tail == nullptr) {
            head = tail = t;
            t->next = nullptr;
        }
        {
            tail->next = t;
            tail = t;
            tail->next = nullptr;
        }

    }
    void insert_sorted(int val){
        if(!length || val <= head->data)
            insert_front(val);
        else if(tail->data <= val)
            insert_end(val);
        else{
            for(Node *i = head, *prev = nullptr;i;prev = i,i=i->next){
                if(val <= i->data){
                    embed_after(prev,val);
                    break;
                }
            }
        }
    }
    void insert_front(int val){
        length++;
        Node* t = new Node(val);
        if(head == nullptr && tail == nullptr) {
            head = tail = t;
            t->next = nullptr;
        } else {
            t->next = head;
            head = t;
        }


    }
    int search_improved(int t){
        int idx =0;
        Node* prev = nullptr;
        for(Node* cur = head;cur;cur = cur->next,idx++){
            if(cur->data == t){
                if(!prev)
                    return idx;
                swap(cur->data,prev->data);
                return idx - 1;
            }
            prev = cur;
        }
        return -1;
    }
    bool is_same(LinkedList ls){
        if(ls.length == length){
            for(int i = 0;i<length;i++){
                if(get_nth(i+1)->data != ls.get_nth(i+1)->data)
                    return false;
            }
            return true;
        }
        else
            return false;
    }
    bool is_same2(LinkedList ls){
        int c = 1;
        // 1 2 3 4
        // 1 2 3 4 5 6
        for(Node* temp = head;temp;temp = temp->next,c++) {
                if(ls.get_nth(c) == nullptr || temp->data != ls.get_nth(c)->data) {
                    return false;
                }

        }
        return ls.get_nth(c) == nullptr;

    }
    void reverse(){
        Node* h = head;
        reverse(head, nullptr);
        tail = h;

    }
    void reverse(Node* curr,Node* prev){
        if(!curr) {
            head = prev;
            return;
        }
        reverse(curr->next,curr);
        curr->next = prev;
    }
    void swap_pairs(){
        Node* i = head;
        while (i){
            if(i->next == nullptr || i->next == tail)
                break;
            swap(i->data,i->next->data);
            i = i->next->next;
        }

    }
    void delete_node(Node *node){
        if(node == head){
            head=node->next;
        }
        length--;
        delete node;
    }
    void delete_and_replace_node(Node *node,Node *prev){

        if(node == head)
            delete_first();
        else if(node == tail)
            delete_last();
        else{

            prev->next = node->next;
            delete_node(node);
        }
    }
    void delete_next_node(Node* node){
        assert(node);
        Node* to_delete = node->next;
        bool is_tail = to_delete == tail;
        node->next = node->next->next;
        delete_node(to_delete);
        if(is_tail)
            tail = node;

    }
    void delete_even_position(){
        assert(length > 1);
        Node* prev = head;
        for(Node* i = head->next;;){
            Node* t = i;
            prev->next = i->next;
            tail = prev;
            prev = i->next;
            length--;
            if(i->next != nullptr) {
                i = i->next->next;
                delete t;
            }
            else {
                delete t;
                break;

            }


        }
    }
    void delete_with_key(int key){
        Node* prev = nullptr;
        for(Node* i = head;i;i = i->next){
            if(i == head && i-> data == key) {
                delete_front();
                return;
            }
            if(i == tail && i-> data == key) {
                delete_last();
                return;
            }
            if(i->data == key){
                length--;
                prev->next = i->next;
                delete i;
                return;
            }
            prev = i;

        }
    }
    void delete_with_key_last(int key){
        Node *prevT= nullptr,*prev = nullptr;
        Node *to_delete = nullptr;
        for(Node* i = head;i;i = i->next){

            if(i->data == key) {
                prev = prevT;
                to_delete = i;
            }

            prevT = i;
        }
        if(prev)
        delete_and_replace_node(to_delete,prev);

    }

    void delete_front(){
        assert(length !=0);
        if(length == 1)
            tail = nullptr;
        length--;
        Node* t = head;
        head = head->next;
        if(!head)
            tail = nullptr;
        delete t;
    }
    void delete_first(){
        if(head){
            length--;
            Node* temp = head;
            head = head->next;
            delete temp;
            if(!head)
                tail = nullptr;
        }
    }
    void delete_last(){
        if(length <= 1) {
            delete_first();
            return;
        }
        Node* prev = get_nth(length - 1);
        delete tail;
        length--;
        tail = prev;
        tail->next = nullptr;
    }
    void delete_nth(int n){
        assert(n > 0 && n <= length);
        if(n == 1){
            delete_first();
            return;
        }
        else if (n == length){
            delete_last();
            return;
        }
        else{
            Node* prev = get_nth(n-1);
            Node* nth = prev->next;
            prev->next = nth->next;
            delete nth;
            length--;
        }
    }
    void swap_head_and_tail(){
        Node* afterFirst = head->next;
        Node* before_last = get_nth(length-1);
        tail->next = afterFirst;
        before_last->next = head;
        swap(tail,head);
        tail->next = nullptr;
    }
    void left_rotate(int n){
        for(int i =0;i< n % length;i++){
        Node *t = head;
        head = head->next;
        tail->next = t;
        tail = t;
        tail->next = nullptr;
        }
    }
    void remove_duplicates(){
        map<int,int>mp;
        remove_duplicates(head, nullptr,mp);
    }
    void remove_duplicates(Node *i,Node *prev,map<int,int>&mp)
    {

        if(!i)
            return;
        mp[i->data]++;
        remove_duplicates(i->next,i,mp);
        if(mp[i->data] > 1){
            mp[i->data]--;
            delete_and_replace_node(i,prev);

        }

    }
    void move_to_back(int key){
        Node *prev = nullptr;
        int cnt = 0;
        for(Node *i = head;i;i=i->next){

            if(i != head && i->data == key){
                delete_and_replace_node(i,prev);
                cnt++;
                i = prev;
            }
            else if(i == head && i->data == key){
                delete_and_replace_node(i,prev);
                cnt++;
                i = head;
            }
            prev =i;
            if(!i)
                break;
        }
        while (cnt--){
            if(tail) {
                tail->next = new Node(key);
                tail = tail->next;
            } else{
                tail = head = new Node(key);
                tail->next = nullptr;
            }
        }
        tail->next = nullptr;
    }
    void arrange_odd(){
        Node *prev = head;
        Node *i = head->next;
        for(int cnt =0 ;cnt<length;cnt+=2){


            //Node cp = *i;
            if( i->next == nullptr)
                break;
            Node *t = i;
            i = i->next->next;
            insert_end(t->data);
            Node* tP = prev;
            prev = t->next;
            delete_and_replace_node(t,tP);

        }
    }
    int max(){
        return max(head);
    }
    int max(Node *i){
        if(!i)
            return -1e9;

        return std::max(max(i->next),i->data);
    }

    void debug(){
        if(length == 0) {
            assert(head == nullptr);
            assert(tail == nullptr);
        }
        else{
            assert(head != nullptr);
            assert(tail != nullptr);
            if(length == 1){
                assert(head == tail);
            }
            else{
                assert(head != tail);
            }
            assert(!tail->next);
        }
        int len = 0;
        for(Node* cur = head;cur;cur=cur->next,len++)
            assert(len <10000);
        assert(len == length);

    }

};
bool cmp(pair<int,Node*>a,pair<int,Node*>b){
    return a.first < b.first;
}
Node* sortList(Node* head){
    // Write your code here.
    vector<pair<int,Node*>>arr;
    for(Node *i = head;i;i=i->next){
        arr.push_back({i->data,i});
    }

    sort(arr.begin(),arr.end(),cmp);
    arr.push_back({-1,nullptr});

    for(int i =0;i<arr.size()-1;i++){
        arr[i].second->next = arr[i+1].second;
    }
    head = arr[0].second;
    return head;
}
class Stack{
private:
    int size{};
    int top{};
    int * array{};
public:
    bool isFull(){
        return top == size-1;
    }
    bool isEmpty(){
        return top == -1;
    }
    void display(){
        for(int i = top;i>=0;i--)
            cout << array[i] << " ";
        cout << "\n";
    }
    void display_char(){
        for(int i = top;i>=0;i--)
            cout << (char)array[i];
        cout << " ";
    }
    Stack(int size):size(size),top(-1){
        array = new int [size];
    }
    void push(int x){
        assert(!isFull());
        array[++top] = x;
    }
    int pop(){
        assert(!isEmpty());
        return array[top--];
    }
    int peek(){
        assert(!isEmpty());
        return array[top];
    }
    void insert_at(int idx,int val){
        if(idx == top + 2) {
            top++;
            return;
        }
        insert_at(idx+1,array[idx]);
        array[idx] = val;
    }
    void insert_at_bottom(int val){
        insert_at(0,val);
    }
    void reverse_from(int i){
        if(i == top+1)
            return;
        insert_at(i,array[top--]);
        reverse_from(i+1);
    }
    void reverse_stack(){
        reverse_from(0);
    }
};
vector<string> take_all_input(){
    vector<string>txt;
    string word;
    while (cin>>word){
        if(word == "EOF")
            break;
        txt.push_back(word);
    }
    return txt;

}
string reverse_string(string to_reverse){
    string reversed;
    reversed.resize(to_reverse.size());
    Stack *st = new Stack(to_reverse.size());
    for(int i =0;i<to_reverse.size();i++){
        st->push((int)to_reverse[i]);
    }
    int cnt = 0;
    while (!st->isEmpty()) {
        reversed[cnt++] = st->peek();
        st->pop();
    }
    return reversed;

}
vector<string> reverse_txt(vector<string> txt){
    vector<string>reversed(txt.size());
    for(int i = 0;i<txt.size();i++){
        reversed[i] = reverse_string(txt[i]);
    }
    return reversed;
}
bool valid_parentheses(string equation){
    map<char,char>mp;
    Stack *st = new Stack(equation.size()+1);
    mp[')'] = '(';
    mp['}'] = '{';
    mp[']'] = '[';
    for(int i =0;i<equation.size();i++){
        if(!mp[equation[i]]){
            st->push(equation[i]);
        }
        else{
            if(!st->isEmpty() && st->peek() == mp[equation[i]]){
                st->pop();
            }
            else{
                return false;
            }
        }
    }
    return st->isEmpty();
}
int score_of_parentheses(string equation){
    Stack *st = new Stack(equation.size()+1);
    int score = 0;
    equation.push_back('(');
    for(int i =0;i<equation.size();i++){


    }
    return score;
}
// I solved the rest of the not so orignal problems (Leet code problems) before so im not going to do it again
string removeDuplicates(string &s) {
    Stack *st = new Stack(s.size()+1);
    for(int i =0;i<s.size();i++){
        if(!st->isEmpty() && st->peek() == s[i]){
            st->pop();
        }
        else{
            st->push(s[i]);
        }
    }

    string ans;
    while (!st->isEmpty()){
        ans.push_back(st->peek());
        st->pop();
    }
    return s = reverse_string(ans);

}
class Equation{
public:
int execute_operation(int a,int b,char op){
    int t = a;
    switch (op) {
        case '*':
            return a * b;
        case '/':
            return a / b;
        case '+':
            return a + b;
        case '-':
            return  a - b;
        case '^':
            for(int i =1;i<b;i++)
                a *= t;
            return a;
        default:
            return 0;
    }
}
int operation_priority(char op){
    if(op == '^')
        return 1;
    else if(op == '*' || op == '/')
        return 2;
    else if(op == '+' || op == '-')
        return 3;
}
bool is_operation(char c){
    return c == '*' || c == '/' || c == '+' || c == '-' || c == '^';
}
string infix_to_postfix(string infix,int idx = 0){
    Stack *op = new Stack(infix.size()+1);
    string postfix;
    for(int i =idx;i<infix.size();i++){
        if(is_operation(infix[i])){
            while (!op->isEmpty() && operation_priority(op->peek()) < operation_priority(infix[i])){
                    postfix += op->pop();
            }
            op->push(infix[i]);
        }
        else if(infix[i] == '(' || infix[i] == ')'){
            while (infix[i] == ')' && !op->isEmpty()){
                postfix += op->pop();
            }
            postfix += infix_to_postfix(infix,i+1);
            break;
        }else
        {
            postfix += infix[i];
        }
    }
    // 2 + (3*3)
    // 29+
    // (2+3)*4
    while (!op->isEmpty()){
        postfix += op->pop();
    }
    return postfix;
}
string infix_to_prefix(string infix){
    return reverse_string(infix_to_postfix(reverse_string(infix)));
}
string postfix_to_infix(string postfix){
    string infix;
    Stack *op = new Stack(postfix.size()+1);
    for(int i =0;i<postfix.size();i++){
        if(isdigit(postfix[i])){
            op->push(postfix[i]);
        }
        else
        {
            infix += op->pop();
            infix += postfix[i];
        }
    }
    while (!op->isEmpty()){
        infix += op->pop();
    }
    /*
     * 1+2*(3*4)
      1234**+
     * */
    return reverse_string(infix);
}
string simplify(string infix){
    return postfix_to_infix(infix_to_postfix(infix));
}
int solve_postfix(string equation){
    // only works for number <= 9
    Stack *st = new Stack(equation.size() + 4);
    // A+B/C*D-E/(F+G) == ABC/D*+EFG+/-
    for(int i = 0;i<equation.size();i++){
//        cout << "For i = " << i << "the stack is ";
//        st->display();
        if(is_operation(equation[i])){
            int b = st->pop();
            st->push(execute_operation(st->pop(),b,equation[i]));
        }
        else{
            st->push(equation[i] - '0');
        }
    }
    return st->peek();
}
int solve_equation(string equation){
    return solve_postfix(infix_to_postfix(equation,0));
}
};

int main() {
    string equation;cin>>equation;
    Equation *s = new Equation();
    while (equation != "0") {
        cout << s->infix_to_postfix(equation) << "\n";
        cout << s->solve_equation(equation) << "\n";
        cin >> equation;
    }
    // A+B/C*D-E/(F+G)
    return 0;
}
