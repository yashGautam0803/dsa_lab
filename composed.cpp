//banker
#include<bits/stdc++.h>
using namespace std;
class BA
{
    private:
        int n, m;
        vector<int> total;
        vector<int> available;
        vector<int> safesequence;
        vector<vector<int>> maxneed;
        vector<vector<int>> allocation;
        vector<vector<int>> need;
    public:
        void input();
        bool isSafe();
        void calculateneed();
        void calculateavailable();
        void display();
};
void BA::input()
{
    cout<<"Enter number of processes: ";
    cin>>n;
    cout<<"Enter total number resources: ";
    cin>>m;
    total.resize(m);
    available.resize(m);
    maxneed.resize(n, vector<int>(m));
    allocation.resize(n, vector<int>(m));
    need.resize(n, vector<int>(m));
    cout<<"Enter total resources of each type: ";
    for(auto &x: total)
        cin>>x;
    cout<<"Enter allocation matrix: \n";
    for(int i=0;i<n;i++)
    {
        cout<<"P"<<i+1<<": ";
        for(int j=0;j<m;j++)
            cin>>allocation[i][j];
    }
    cout<<"Enter max matrix: \n";
    for(int i=0;i<n;i++)
    {
        cout<<"P"<<i+1<<": ";
        for(int j=0;j<m;j++)
            cin>>maxneed[i][j];
    }
}
void BA::calculateneed()
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
            need[i][j]=maxneed[i][j]-allocation[i][j];
    }
}
void BA::calculateavailable()
{
    for(int j=0;j<m;j++)
    {
        int allocated=0;
        for(int i=0;i<m;i++)
            allocated+=allocation[i][j];
        available[j]=total[j]-allocated;
    }
}
bool BA::isSafe()
{
    vector<int> work=available;
    vector<bool> finish(n, 0);
    int count=0;
    safesequence.clear();
    while(count<n)
    {
        bool found=false;
        for(int i=0;i<n;i++)
        {
            if(!finish[i])
            {
                bool canallocate=true;
                for(int j=0;j<m;j++)
                {
                    if(need[i][j]>work[j])
                    {
                        canallocate=false;
                        break;
                    }
                }
                if(canallocate)
                {
                    for(int j=0;j<m;j++)
                        work[j]+=allocation[i][j];
                    finish[i]=true;
                    found=true;
                    safesequence.push_back(i);
                    count++;
                }
            }
        }
        if(!found)
        {
            cout<<"\nSystem is in unsafe state\n";
            return false;
        }    
    }
    cout<<"System is in safe state\nSafe sequence: ";
    for(int i=0;i<n;i++)
    {
        cout<<"P"<<safesequence[i]<<" ";
        if(i!=n-1)
            cout<<"->";
    }
    return true;
}
void BA::display()
{
    cout<<"\nCalculated Need Matrix:\n";
    for(int i=0;i<n;i++)
    {
        cout<<"P"<<i+1<<": ";
        for(int j=0;j<m;j++)
            cout<<need[i][j]<<" ";
        cout<<endl;
    }
    cout<<"\nCalculated Available Resources:\n";
    for(int j=0;j<m;j++)
        cout<<"R"<<j<<": "<<available[j]<<"\t";
    cout<<endl;
}
int main()
{
    BA banker;
    banker.input();
    banker.calculateneed();
    banker.calculateavailable();
    banker.isSafe();
    banker.display();
    return 0;
}
//DMA
#include<bits/stdc++.h>
using namespace std;
void display(const vector<int> &alloc, const vector<int> &proc, const vector<int> &blocks){
    cout<<"\nProcess\tSize\tBlock Allocated\n";
    for(size_t i=0;i<proc.size();i++)
    {
        if(alloc[i]!=-1)
            cout<<"P"<<i+1<<"\t"<<proc[i]<<"\tblock "<<alloc[i]+1<<endl;
        else
            cout<<"P"<<i+1<<"\t"<<proc[i]<<"\tNot Allocatedc\n";
    }
    cout<<"\nTotal Free space available: "<<accumulate(blocks.begin(), blocks.end(), 0)<<endl;
}
pair<vector<int>, vector<int>> FF(vector<int> blocks, const vector<int> &proc)
{
    vector<int> alloc(proc.size(), -1);
    for(size_t i=0;i<proc.size();i++)
    {
        for(size_t j=0;j<blocks.size();j++)
        {
            if(blocks[j]>=proc[i])
            {
                alloc[i]=j;
                blocks[j]-=proc[i];
                break;
            }
        }
    }
    return {alloc, blocks};
}
pair<vector<int>, vector<int>> BF(vector<int> blocks, const vector<int> &proc)
{
    vector<int> alloc(proc.size(), -1);
    for(size_t i=0;i<proc.size();i++)
    {
        int best=-1;
        for(size_t j=0;j<blocks.size();j++)
        {
            if(blocks[j]>=proc[i] && (best==-1 || blocks[j]<blocks[best])){
                best=j;
            }
        }
        if(best!=-1)
        {
            alloc[i]=best;
            blocks[best]-=proc[i];
        }
    }
    return {alloc, blocks};
}
pair<vector<int>, vector<int>> WF(vector<int> blocks, const vector<int> &proc)
{
    vector<int> alloc(proc.size(), -1);
    for(size_t i=0;i<proc.size();i++)
    {
        int worst=-1;
        for(size_t j=0;j<blocks.size();j++)
        {
            if(blocks[j]>=proc[i] && (worst==-1 || blocks[j]>blocks[worst])){
                worst=j;
            }
        }
        if(worst!=-1)
        {
            alloc[i]=worst;
            blocks[worst]-=proc[i];
        }
    }
    return {alloc, blocks};
}
vector<int> compact(const vector<int> &blocks)
{
    int totalfree=accumulate(blocks.begin(), blocks.end(), 0);
    return {totalfree};
}
int main()
{
    int nblocks, nproc;
    cout<<"Enter number of memory blocks: ";
    cin>>nblocks;
    vector<int> blocks(nblocks);
    for(int i=0;i<nblocks;i++)
    {
        cout<<"Enter size of block"<<i+1<<": ";
        cin>>blocks[i];
    }
    cout<<"Enter number of processes: ";
    cin>>nproc;
    vector<int> proc(nproc);
    for(int i=0;i<nproc;i++)
    {
        cout<<"Enter size of process"<<i+1<<": ";
        cin>>proc[i];
    }
    cout<<"\nChoose Allocation Strategy\n";
    cout<<"\n1.First Fit\n2.Best Fit\n3.Worst Fit\nWrong choice: ";
    int choice;
    cin>>choice;
    vector<int> alloc, remain;
    string method;
    switch(choice)
    {
        case 1: tie(alloc, remain)=FF(blocks, proc); method="First Fit"; break;
        case 2: tie(alloc, remain)=BF(blocks, proc); method="Best Fit"; break;
        case 3: tie(alloc, remain)=WF(blocks, proc); method="Worst Fit"; break;
        default: cout<<"Wrong choice"; return 0;
    }
    cout<<"\n---"<<method<<" result---\n";
    display(alloc, proc, remain);
    vector<int> waiting;
    for(size_t i=0;i<proc.size();i++)
    {
        if(alloc[i]==-1)
            waiting.push_back(proc[i]);
    }
    cout<<"\nDo you want to perform compaction? (yes/no): ";
    string response;
    cin>>response;
    for(auto &c: response) c=tolower(c);
    if(response=="yes"){
        vector<int> newblocks=compact(remain);
        if(!waiting.empty())
        {
            auto[newalloc, _]=FF(newblocks, waiting);
            for(size_t i=0;i<waiting.size();i++)
            {
                if(newalloc[i]!=-1)
                    cout<<"\nprocess of size "<<waiting[i]<<" allocated after compaction\n";
                else  
                    cout<<"\nprocess of size "<<waiting[i]<<" still waiting\n";
            }
        }
        else{
            cout<<"\nNo waiting process";
            cout<<"\nTotal free space available "<<accumulate(remain.begin(), remain.end(),0);
        }
    }
    return 0;
}
//MLQ
#include<bits/stdc++.h>
using namespace std;
struct process{
    string name;
    int at, bt, priority, ft=0, wt=0, tat=0, rt=0;
};
int main()
{
    int n, quantum;
    cout<<"ENter number of processes: ";
    cin>>n;
    cout<<"Enter time quantum for higher priority processes: ";
    cin>>quantum;
    vector<process> p(n);
    for(int i=0;i<n;i++)
    {
        p[i].name="P"+to_string(i+1);
        cout<<"Enter priority, arrival and burst time for "<<p[i].name<<": ";
        cin>>p[i].priority>>p[i].at>>p[i].bt;
        p[i].rt=p[i].bt;
    }
    sort(p.begin(), p.end(), [](auto &a, auto &b){
        return (a.at==b.at) ? a.priority<b.priority : a.at<b.at;
    });
    int time=0, completed=0;
    int NA=0;
    vector<string> GANTT;
    queue<int> q1, q2;
    while(completed<n)
    {
        while(NA<n && p[NA].at<=time)
        {(p[NA].priority==1 ? q1 : q2).push(NA); NA++;}
        if(!q1.empty())
        {
            int i=q1.front(); q1.pop();
            int exec=min(quantum, p[i].rt);
            GANTT.push_back(p[i].name);
            time+=exec;
            p[i].rt-=exec;
            while(NA<n && p[NA].at<=time)
            {(p[NA].priority==1 ? q1 : q2).push(NA); NA++;}
            if(p[i].rt==0)
            {
                p[i].ft==time;
                completed++;
            }else q1.push(i);
        }
        else if(!q2.empty())
        {
            int i=q2.front(); q2.pop();
            GANTT.push_back(p[i].name);
            time+=p[i].rt;
            p[i].ft=time;
            p[i].rt=0;
            completed++;
            while(NA<n && p[NA].at<=time)
            {(p[NA].priority==1 ? q1 : q2).push(NA); NA++;}
        }
        else{
            GANTT.push_back("IDLE");
            time++;
        }
    }
    double totaltat=0, totalwt=0;
    for(auto &x: p)
    {
        x.tat=x.ft-x.at;
        x.wt=x.tat-x.bt;
        totalwt+=x.tat;
        totaltat+=x.wt;
    }
    cout<<"\nGANTT chart:\n";
    for(auto &x: GANTT)
        cout<<x<<" ";
    cout<<"\nProcess\tAT\tBT\tPriority\tTAT\tWT\n";
    for(auto &x: p)
        cout<<x.name<<"\t"<<x.at<<"\t"<<x.bt<<"\t"<<x.priority<<"\t"<<x.tat<<"\t"<<x.wt<<"\n";
    cout<<"\nAverage waiting time: "<<totalwt/n;
    cout<<"\nAverage turnaround time: "<<totaltat/n;
    return 0;    
}
//ClOOK
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n, head, dir;
    cin>>n;
    vector<int> rq(n);
    for(int&i:rq) cin>>i;
    cin>>head>>dir; // dir = 1 → right, 0 → left

    rq.push_back(head);
    sort(rq.begin(), rq.end());
    int pos = find(rq.begin(), rq.end(), head) - rq.begin(), seek = 0;
    vector<int> seq;

    if(dir){ // move right first
        for(int i=pos; i<rq.size()-1; i++){
            seek += rq[i+1] - rq[i];
            seq.push_back(rq[i+1]);
        }
        // jump to first request on left side
        seek += rq.back() - rq.front();
        for(int i=0; i<pos; i++){
            seek += rq[i+1] - rq[i];
            seq.push_back(rq[i+1]);
        }
    } else { // move left first
        for(int i=pos; i>0; i--){
            seek += rq[i] - rq[i-1];
            seq.push_back(rq[i-1]);
        }
        // jump to last request on right side
        seek += rq.back() - rq.front();
        for(int i=rq.size()-2; i>=pos; i--){
            seek += rq[i+1] - rq[i];
            seq.push_back(rq[i]);
        }
    }

    cout<<"Sequence: "<<head;
    for(int x:seq) cout<<" -> "<<x;
    cout<<"\nTotal Seek Time: "<<seek;
    cout<<"\nAverage Seek Time: "<<(float)seek/n;
}
//CSCAN
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n, head, dir;
    cin>>n;
    vector<int> rq(n);
    for(int&i:rq) cin>>i;
    cin>>head>>dir; // dir = 1 → right, 0 → left
    int disk_size = 199; // max cylinder (change if needed)
    
    rq.push_back(head);
    sort(rq.begin(), rq.end());
    int pos = find(rq.begin(), rq.end(), head) - rq.begin(), seek = 0;
    vector<int> seq;

    if(dir){ // right first
        for(int i=pos; i<rq.size()-1; i++){
            seek += rq[i+1] - rq[i];
            seq.push_back(rq[i+1]);
        }
        seek += (disk_size - rq.back()); // go till end
        seq.push_back(disk_size);
        seek += disk_size; // jump from end to start
        seq.push_back(0);
        for(int i=0; i<pos; i++){
            seek += rq[i+1] - rq[i];
            seq.push_back(rq[i+1]);
        }
    } else { // left first
        for(int i=pos; i>0; i--){
            seek += rq[i] - rq[i-1];
            seq.push_back(rq[i-1]);
        }
        seek += rq.front(); // go till start
        seq.push_back(0);
        seek += disk_size; // jump from start to end
        seq.push_back(disk_size);
        for(int i=rq.size()-2; i>=pos; i--){
            seek += rq[i+1] - rq[i];
            seq.push_back(rq[i]);
        }
    }

    cout<<"Sequence: "<<head;
    for(int x:seq) cout<<" -> "<<x;
    cout<<"\nTotal Seek Time: "<<seek;
    cout<<"\nAverage Seek Time: "<<(float)seek/n;
}
//FCFS
#include<bits/stdc++.h>
using namespace std;
int main() {
    int n, head;
    cout<<"Enter number of requests: ";
    cin>>n;
    vector<int> rq(n);
    cout<<"Enter requests: ";
    for(int i=0;i<n;i++) cin>>rq[i];
    cout<<"Enter initial head position: ";
    cin>>head;

    int seek=0, cur=head;
    cout<<"\nSequence: "<<cur;
    for(int i=0;i<n;i++) {
        seek += abs(rq[i]-cur);
        cur = rq[i];
        cout<<" -> "<<cur;
    }
    cout<<"\nTotal Seek Time: "<<seek;
    cout<<"\nAverage Seek Time: "<<(float)seek/n;
    return 0;
}
//FIFO
#include<bits/stdc++.h>
using namespace std;
int main()
{
    string input;
    int frames;
    cout<<"Enter reference string (space separated): ";
    getline(cin, input);
    cout<<"Enter frames size: ";
    cin>>frames;
    stringstream ss(input);
    vector<int> pages;
    int page;
    while(ss>>page) pages.push_back(page);
    queue<int> fifo;
    vector<int> framelist;
    int hits=0, faults=0;
    for(int page: pages)
    {
        bool hit=(find(framelist.begin(), framelist.end(), page)!=framelist.end());
        if(hit) hits++;
        else{
            faults++;
            if((int)framelist.size()==frames)
            {
                int remove=fifo.front();
                fifo.pop();
                framelist.erase(find(framelist.begin(), framelist.end(), remove));
            }
            fifo.push(page);
            framelist.push_back(page);
        }
        cout<<"Page "<<page<<": ";
        for(int x: framelist) cout<<x<<" ";
        cout<<(hit?"(Hit)":"(Fault)")<<endl;
    }
    cout<<"\nTotal Page Faults: "<<faults<<endl;
    cout<<"Total Page Hits: "<<hits<<endl;
    cout<<"Page fault rate: "<<faults<<"/"<<pages.size()<<"="<<(double)faults/pages.size()<<endl;
    return 0;
}
//LRU
#include<bits/stdc++.h>
using namespace std;
int main()
{
    string input;
    int frames;
    cout<<"Enter the ppage reference string(space separated): ";
    getline(cin, input);
    cout<<"Enter the number of frames: ";
    cin>>frames;
    stringstream ss(input);
    vector<int> pages;
    int page;
    int hits=0, faults=0;
    while(ss>>page) pages.push_back(page);
    vector<int> framelist;
    for(int page: pages)
    {
        auto it=find(framelist.begin(), framelist.end(), page);
        bool hit=(it!=framelist.end());
        if(hit)
        {
            hits++;
            framelist.erase(it);
            framelist.push_back(page);
        }
        else{
            faults++;
            if((int)framelist.size()==frames)
                framelist.erase(framelist.begin());
            framelist.push_back(page);
        }
        cout<<"Page "<<page<<": ";
        for(int x: framelist) cout<<x<<" ";
        cout<<(hit?"(hit)":"(fault)")<<endl;
    }
    cout<<"\nTotal page faults: "<<faults<<endl;
    cout<<"Total page hits: "<<hits<<endl;
    cout<<"Page fault rate: "<<faults<<"/"<<pages.size()<<"="<<(double)faults/pages.size()<<endl;
    return 0;
}
//OPTIMAL
#include<bits/stdc++.h>
using namespace std;
int main()
{
    string input;
    int frames;
    cout<<"Reference string: "; getline(cin, input);
    cout<<"Frame size: "; cin>>frames;
    stringstream ss(input);
    int page;
    vector<int> pages;
    while(ss>>page) pages.push_back(page);
    int hits=0, faults=0;
    vector<int> framelist;
    for(int i=0;i<pages.size();i++)
    {
        auto it=find(framelist.begin(), framelist.end(), pages[i]);
        if(it!=framelist.end()) hits++;
        else{
            faults++;
            if(framelist.size()<frames) framelist.push_back(pages[i]);
            else{
                int idx=0, far=-1;
                for(int j=0;j<frames;j++)
                {
                    int k=find(pages.begin()+i+1, pages.end(), framelist[j])-pages.begin();
                    if(k==pages.size()){ idx=j; break;}
                    if(k>far) {far=k; idx=j;}
                }
                framelist[idx]=pages[i];
            }
        }
        cout<<"Page "<<pages[i]<<": ";
        for(int a: framelist) cout<<a<<" ";
        cout<<(it!=framelist.end() ? "(HIT)" : "(FAULT)")<<endl;
    }
    cout<<"\nFaults: "<<faults<<"Hits: "<<hits<<"Rate: "<<(double)faults/pages.size();
    return 0;
}
//RR
#include<bits/stdc++.h>
using namespace std;
struct process{
    string name;
    int at, bt, rt, ct, wt, tat;
};
int main()
{
    int n;
    cout<<"Enter number of processes: ";
    cin>>n;
    vector<process> p(n);
    for(int i=0;i<n;i++)
    {
        p[i].name="P"+to_string(i+1);
        cout<<"Enter at and bt for "<<p[i].name<<": ";
        cin>>p[i].at>>p[i].bt;
        p[i].rt=p[i].bt;
        p[i].ct=p[i].wt=p[i].tat=0;
    }
    int time=0, completed=0;
    vector<int> visited(n, 0);
    queue<int> q;
    vector<string> order;
    double totalwt=0, totaltat=0;
    int quantum;
    cout<<"Enter time quantum: ";
    cin>>quantum;
    sort(p.begin(), p.end(), [](process a, process b)
    {
        return a.at<b.at;
    });
    q.push(0);
    visited[0]=1;
    while(!q.empty())
    {
        int idx=q.front();
        q.pop();
        if(time<p[idx].at)
            time=p[idx].at;
        int exec=min(p[idx].rt, quantum);
        p[idx].rt-=exec;;
        time+=exec;
        order.push_back(p[idx].name);
        for(int i=0;i<n;i++)
        {
            if(!visited[i] && p[i].at<=time && p[i].rt>0)
            {
                q.push(i);
                visited[i]=1;
            }    
        }
        if(p[idx].rt>0)
            q.push(idx);
        else{
            p[idx].ct=time;
            p[idx].tat=p[idx].ct - p[idx].at;
            p[idx].wt=p[idx].tat - p[idx].bt;   
            totalwt+=p[idx].wt;
            totaltat+=p[idx].tat;
            completed++;
        }
    }
    cout<<"\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for(auto &proc: p)
    {
        cout<<proc.name<<"\t"<<proc.at<<"\t"<<proc.bt<<"\t"<<proc.ct<<"\t"<<proc.tat<<"\t"<<proc.wt<<"\n";
    }
    cout<<"\nAverage TAT: "<<totaltat/n;   
    cout<<"\nAverage WT: "<<totalwt/n;
    cout<<"\nExecution Order: ";
    for(auto &name: order)
    {
        cout<<name<<" ";
    }
    return 0;
}
//SCAN
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n, head, dir;
    cin>>n;
    vector<int> rq(n);
    for(int&i:rq)cin>>i;
    cin>>head>>dir; // dir = 1 → right, 0 → left
    int disk_size=199; // max cylinder (change if needed)
    
    rq.push_back(head);
    sort(rq.begin(),rq.end());
    int pos=find(rq.begin(),rq.end(),head)-rq.begin(),seek=0;
    vector<int> seq;
    
    if(dir){ // right first
        for(int i=pos;i<rq.size()-1;i++){
            seek+=rq[i+1]-rq[i];
            seq.push_back(rq[i+1]);
        }
        seek+=disk_size - rq.back(); // go till end
        seq.push_back(disk_size);
        for(int i=pos-1;i>=0;i--){
            seek+= (i==pos-1? disk_size - rq[i+1] : rq[i+1]-rq[i]);
            seq.push_back(rq[i]);
        }
    }else{ // left first
        for(int i=pos;i>0;i--){
            seek+=rq[i]-rq[i-1];
            seq.push_back(rq[i-1]);
        }
        seek+=rq.front(); // go till 0
        seq.push_back(0);
        for(int i=pos+1;i<rq.size();i++){
            seek+= (i==pos+1? rq[i-1] : rq[i]-rq[i-1]);
            seq.push_back(rq[i]);
        }
    }
    
    cout<<"Sequence: "<<head;
    for(int x:seq)cout<<" -> "<<x;
    cout<<"\nTotal Seek Time: "<<seek<<"\nAverage Seek Time: "<<(float)seek/n;
}
//SJF
#include<bits/stdc++.h>
using namespace std;
struct process{
    string name;
    int at, bt, ct, tat, wt;
};
int main()
{
    int n;
    cout<<"Enter number of processes: ";
    cin>>n;
    vector<process> p(n);
    for(int i=0;i<n;i++)
    {
        p[i].name="P"+to_string(i+1);
        cout<<"Enter arrival time and burst time for "<<p[i].name<<": ";
        cin>>p[i].at>>p[i].bt;
    }
    int time =0, completed=0;
    vector<process> order;
    while(completed<n)
    {
        int idx=-1, minburst=1e9;
        for(int i=0;i<n;i++)
        {
            if(p[i].at<=time && p[i].ct==0)
            {
                if(p[i].bt<minburst)
                {
                    minburst=p[i].bt;
                    idx=i;
                }
            }
        }
        if(idx==-1)
        {
            time++;
            continue;
        }
        time+=p[idx].bt;
        p[idx].ct=time;
        p[idx].tat=p[idx].ct - p[idx].at;
        p[idx].wt=p[idx].tat - p[idx].bt;
        order.push_back(p[idx]);
        completed++;
    }
    double totalwt=0, totaltat=0;
    cout<<"\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for(auto &proc: order)
    {
        cout<<proc.name<<"\t"<<proc.at<<"\t"<<proc.bt<<"\t"<<proc.ct<<"\t"<<proc.tat<<"\t"<<proc.wt<<"\n";
        totalwt+=proc.wt;
        totaltat+=proc.tat;
    }
    cout<<"\nAverage TAT: "<<totaltat/n;
    cout<<"\nAverage WT: "<<totalwt/n;
    cout<<"\nExecution Order: ";
    for(auto &proc: order)
    {
        cout<<proc.name<<" ";
    }
    return 0;
}
//SRTF
#include<bits/stdc++.h>
using namespace std;
struct process{
    string name;
    int at, bt, rt, ct, tat, wt;
};
int main()
{
    int n;
    cout<<"Enter number of processes: ";
    cin>>n;
    vector<process> p(n);
    for(int i=0;i<n;i++)
    {
        p[i].name="p"+to_string(i+1);
        cout<<"Enter arrival time and busrt time for: "<<p[i].name<<": ";
        cin>>p[i].at>>p[i].bt;
        p[i].rt=p[i].bt;
        p[i].ct=p[i].wt=p[i].tat=0;
    }
    int time=0, completed=0;
    vector<string> order;
    double totalwt=0, totaltat=0;
    while(completed<n)
    {
        int idx=-1, minremain=1e9;
        for(int i=0;i<n;i++)
        {
            if(p[i].at<=time && p[i].rt>0)
            {
                if(p[i].rt<minremain)
                {
                    minremain=p[i].rt;
                    idx=i;
                }
            }
        }
        if(idx==-1)
        {
            time++;
            continue;
        }
        p[idx].rt--;
        time++;
        order.push_back(p[idx].name);
        if(p[idx].rt==0)
        {
            p[idx].ct=time;
            p[idx].tat=p[idx].ct - p[idx].at;
            p[idx].wt=p[idx].tat - p[idx].bt;
            totalwt+=p[idx].wt;
            totaltat+=p[idx].tat;
            completed++;
        }
    }
    cout<<"\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for(auto &proc: p)
    {
        cout<<proc.name<<"\t"<<proc.at<<"\t"<<proc.bt<<"\t"<<proc.ct<<"\t"<<proc.tat<<"\t"<<proc.wt<<"\n";
    }
    cout<<"\nAverage TAT: "<<totaltat/n;
    cout<<"\nAverage WT: "<<totalwt/n;
    cout<<"\nExecution Order: ";
    for(auto &name: order)
    {
        cout<<name<<" ";
    }
    return 0;
}
//SSTF
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n, head; cin>>n;
    vector<int> rq(n); for(int&i:rq) cin>>i;
    cin>>head;
    vector<int> done(n,0);
    int seek=0, cnt=0;
    cout<<"Sequence: "<<head;
    while(cnt<n){
        int idx=-1, mn=1e9;
        for(int i=0;i<n;i++)
            if(!done[i] && abs(rq[i]-head)<mn)
                mn=abs(rq[i]-head), idx=i;
        seek+=mn; head=rq[idx]; done[idx]=1; cnt++;
        cout<<" -> "<<head;
    }
    cout<<"\nTotal Seek Time: "<<seek<<"\nAverage Seek Time: "<<(float)seek/n;
}