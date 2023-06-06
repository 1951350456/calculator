#include<bits/stdc++.h>
using namespace std;
double cal(double m,double n,char op){
    switch (op) {
        case '+':
            return m+n;
        case '-':
            return m-n;
        case '*':
            return m*n;
        default:
            return m/n;
    }
}
void Calculator() {
    map<char, double> w = {{'+', 1},{'-', 1},{'*',2},{'/',2},{'(',3},{')',3}};
    stack<char> Operator;
    stack<double> num;
    string exp;
    getline(cin,exp);
    int cnt = 0;
    for(int i=0;i<exp.length();i++) {
        if(isdigit((exp[i]))) {
            if(i==0) {
                double p = exp[i]-'0';
                cnt++;
                while(isdigit(exp[i+1])){
                    i++;
                    p = p*10+exp[i]-'0';
                    cnt++;
                }
                num.push(p);
            }
            else if(isdigit((exp[i-1]))){
                double p = num.top();
                p *= 10;
                num.pop();
                double d = p+exp[i]-'0';
                num.push(d);
            }
            else
                num.push(exp[i] - '0');
        }
        else{
            if(i==cnt)
            Operator.push(exp[i]);
            else{
                if(w[Operator.top()]<w[exp[i]])
                    Operator.push(exp[i]);
                else{
                    if(Operator.top()=='(')
                        Operator.push(exp[i]);
                    else if(Operator.top()==')'){
                        Operator.pop();
                        while(Operator.top()!='('){
                            double m = num.top();
                            num.pop();
                            double n = num.top();
                            num.pop();
                            char op = Operator.top();
                            Operator.pop();
                            m = cal(n,m,op);
                            num.push(m);
                        }
                        Operator.pop();
                        i--;
                    }
                    else{
                        double m = num.top();
                        num.pop();
                        double n = num.top();
                        num.pop();
                        char op = Operator.top();
                        Operator.pop();
                        m = cal(n,m,op);
                        num.push(m);
                        Operator.push(exp[i]);
                    }
                }
            }
        }
    }
    if(Operator.top()==')') {
        Operator.pop();
        while (Operator.top() != '(') {
            double m = num.top();
            num.pop();
            double n = num.top();
            num.pop();
            char op = Operator.top();
            Operator.pop();
            m = cal(n, m, op);
            num.push(m);
        }
        Operator.pop();
    }
    while(!Operator.empty()){
        double m = num.top();
        num.pop();
        double n = num.top();
        num.pop();
        char op = Operator.top();
        Operator.pop();
        m = cal(n,m,op);
        num.push(m);
    }
    cout<<num.top();
}
int main(){
    Calculator();
}
