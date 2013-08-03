#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<iomanip>
using namespace std;
//Standard Chartered test problem--solved

string rule[100];
double val[100];
int len;

void scanRule(string s){
     istringstream f(s);
     string scut;
     int cnt = 0;
     while( getline(f,scut,' ')){
            if(cnt == 1){
                   rule[len] = scut;
            }else if(cnt == 3){
                  val[len] = atof(scut.c_str());  
                  //printf("z %f\n", val[len]); 
            }
            //cout<<scut<<endl;
            cnt++;
     } 
     len++;
}

double getRule(string r){
     for(int i=0; i<len; i++){
             if(rule[i] == r){
                        return val[i];
             }
     }
     return -1;
}

double getMeter(string r, double v){
       if(r == "feet"){
            r = "foot";
       }
       double rv = getRule(r);
       if( rv != -1){
           return rv*v;
       }
       string rms;
       int rlen = r.length();
       if(r[rlen-1] == 's'){
           rms = r.substr(0,rlen-1);
           rv = getRule(rms);
           if(rv != -1)      return rv*v;
       }
       if(r[rlen-1] == 's' && r[rlen-2] == 'e'){
           rms = r.substr(0,rlen-2);
           rv =  getRule(rms);
           if(rv != -1)      return rv*v;
       }
       //cout<<"not found"<<endl; 
       return 0;
}

double calculate(string s){
       istringstream f(s);
       string scut;
       double pmeter = 0.0, next;
       int flag = 0;//1:+  2: -
       while( getline(f, scut, ' ')){
              if(scut == "+"){
                      flag = 1;                      
              }else if (scut == "-"){
                    flag = 2;
              }else{
                    next = atof(scut.c_str()); 
                    getline(f, scut, ' ');
                    next = getMeter(scut, next);
                    if(flag == 0){
                        pmeter = next;    
                    }else if(flag == 1){
                          pmeter = pmeter + next;      
                    }else if(flag == 2){
                          pmeter = pmeter - next;
                    }
              }
       }
       return pmeter;
}

int main(){
    ifstream input("input.txt");
    ofstream output;
    output.open("output.txt",ios::trunc);
    output<<"zhenzhang@tju.edu.cn"<<endl;
    string s;
    int i,flag=0;
    double rs;
    len = 0;
    
    while( getline(input,s)){
           if(s.length()==0 || s.empty()){
                flag = 1; 
                continue;          
           }else if(flag == 0){
                 scanRule(s);
                 //cout<<s.c_str()<<endl;
           }else if(flag == 1){
                 rs = calculate(s);
                 output<<endl<<setiosflags(ios::fixed)<<setprecision(2)<<rs<<" m";
                 //printf("%.2f\n", rs); 
           }
    }
    
    output.close();
    system("pause");
    return 0;    
}
