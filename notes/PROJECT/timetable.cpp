
#include <bits/stdc++.h>
using namespace std;

// -------- DATA STRUCTURES --------
struct Course {
    string code;
    string faculty;
    int hours;
    bool isLab;
};

struct Assignment {
    string course;
    string faculty;
    string room;
};

class Timetable {
public:
    Assignment table[5][8];

    void init() {
        for(int i=0;i<5;i++)
            for(int j=0;j<8;j++)
                table[i][j] = {"","",""};
    }

    bool isFree(int d,int p){
        return table[d][p].course=="";
    }

    void assign(int d,int p,Assignment a){
        table[d][p]=a;
    }

    void unassign(int d,int p){
        table[d][p]={"","",""};
    }

    void print(){
        cout<<"\\nTIMETABLE\\n";
        for(int i=0;i<5;i++){
            for(int j=0;j<8;j++){
                if(table[i][j].course=="") cout<<"Free ";
                else cout<<table[i][j].course<<" ";
            }
            cout<<endl;
        }
    }
};

// -------- SAMPLE DATA --------
vector<Course> courses = {
    {"CS101","T1",3,false},
    {"CS102","T2",3,false},
    {"CS103","T3",2,true}
};

bool canPlaceLab(int d,int p,Timetable &tt){
    return p+1<8 && tt.isFree(d,p) && tt.isFree(d,p+1);
}

// -------- BACKTRACKING AI --------
bool solve(int idx, Timetable &tt){
    if(idx==courses.size()) return true;

    Course c = courses[idx];

    for(int d=0;d<5;d++){
        for(int p=0;p<8;p++){

            if(c.isLab){
                if(!canPlaceLab(d,p,tt)) continue;

                Assignment a={c.code,c.faculty,"LAB"};
                tt.assign(d,p,a);
                tt.assign(d,p+1,a);

                if(solve(idx+1,tt)) return true;

                tt.unassign(d,p);
                tt.unassign(d,p+1);
            }
            else{
                if(!tt.isFree(d,p)) continue;

                Assignment a={c.code,c.faculty,"R1"};
                tt.assign(d,p,a);

                if(solve(idx+1,tt)) return true;

                tt.unassign(d,p);
            }
        }
    }
    return false;
}

// -------- FITNESS (AI IMPROVEMENT) --------
int fitness(Timetable &tt){
    int score=100;

    for(int d=0;d<5;d++){
        for(int p=0;p<7;p++){
            if(tt.table[d][p].course=="" && tt.table[d][p+1].course!="")
                score-=2;
        }
    }
    return score;
}

int main(){
    Timetable tt;
    tt.init();

    if(solve(0,tt)){
        tt.print();
        cout<<"Fitness: "<<fitness(tt)<<endl;
    }
    else{
        cout<<"No solution\\n";
    }
}
