#include<iostream>
#include<fstream>
#include<conio.h>
#include<vector>
#include<map>
#include<windows.h>
#include<ctime>
using namespace std;
HANDLE hdl=GetStdHandle(STD_OUTPUT_HANDLE);
class word_bank{
    private:
        map<string,string> dict;
        vector<pair<string,string>> new_entries;
    public:
        void load(){
            string word,meaning;
            ifstream infile;
            infile.open("dict.txt");
            while(infile>>word>>meaning){
                dict.insert(make_pair(word,meaning));
            }
            infile.close();
        }
        pair<string,string> search(string target){
            auto it=dict.find(target);
            if(it!=dict.end()) return *it;
            return {"",""};
        }
        int test(){
            int size=dict.size();
            if(size==0){
                return -1;
            }
            cout<<"规则:"<<endl;
            cout<<"测试采用积分制,"<<endl;
            cout<<"答对一道题得10分,"<<endl;
            cout<<"不会/答错既不得分也不扣分,"<<endl;
            cout<<"测试中一共有3次提示机会,使用时将显示单词的长度及随机一位字母,"<<endl;
            cout<<"若累计不会/答错3道题则测试终止."<<endl;
            cout<<"\n";
            system("pause");
            system("cls");
            int rec=0,tip=3,life=3,turn=1;
            while(life>0){
                int q=rand()%size;
                auto it=dict.begin();
                for(int i=0;i<q;i++) it++;
                string question=it->second,answer=it->first;
                bool tip_is_used=false;
                cout<<"温馨提示:"<<endl;
                cout<<"a.如需提前结束测试请输入0"<<endl;
                cout<<"b.如果此题不会想pass请输入1"<<endl;
                cout<<"c.如需使用提示请输入2"<<endl<<endl;
                cout<<"目前积分为 "<<rec<<" 分"<<endl;
                cout<<"还剩下 "<<tip<<" 次提示机会"<<endl;
                cout<<"再pass/答错 "<<life<<" 道题则测试终止"<<endl<<endl;
                cout<<"现在是第 "<<turn<<" 题"<<endl;
                cout<<"输入下方中文释义对应的单词:"<<endl<<endl;
                SetConsoleTextAttribute(hdl,FOREGROUND_RED+FOREGROUND_GREEN|FOREGROUND_INTENSITY);
                cout<<question<<endl;
                cout<<"\n";
                SetConsoleTextAttribute(hdl,FOREGROUND_BLUE+FOREGROUND_GREEN+FOREGROUND_RED|FOREGROUND_INTENSITY);
                flag:
                string input;
                cin>>input;
                cout<<"\n";
                if(input=="0"){
                    system("cls");
                    return rec;
                }else if(input=="1"){
                    life-=1;
                    SetConsoleTextAttribute(hdl,FOREGROUND_RED|FOREGROUND_INTENSITY);
                    cout<<"正确答案是: "<<answer<<endl;
                }else if(input=="2"){
                    if(!tip_is_used){
                        if(tip>0){
                            tip-=1;
                            tip_is_used=true;
                            int len=answer.length();
                            string clue(len,'*');
                            int c=rand()%len;
                            clue[c]=answer[c];
                            cout<<"提示: "<<clue<<endl;
                        }else{
                            cout<<"提示机会已耗尽,无法再使用提示"<<endl;
                        }
                    }
                    goto flag;
                }else if(input==answer){
                    SetConsoleTextAttribute(hdl,FOREGROUND_GREEN|FOREGROUND_INTENSITY);
                    cout<<"√ 回答正确 +10分"<<endl;
                    rec+=10;
                }else{
                    life-=1;
                    SetConsoleTextAttribute(hdl,FOREGROUND_RED|FOREGROUND_INTENSITY);
                    cout<<"× 回答错误"<<endl;
                    cout<<"正确答案是: "<<answer<<endl;
                    string input_meaning=search(input).second;
                    if(input_meaning!=""){
                        cout<<"而你输入的 "<<input<<" 的中文释义为: "<<input_meaning<<endl;
                    }
                }
                SetConsoleTextAttribute(hdl,FOREGROUND_BLUE+FOREGROUND_GREEN+FOREGROUND_RED|FOREGROUND_INTENSITY);
                turn+=1;
                system("pause");
                system("cls");
            }
            return rec;
        }
        void insert(pair<string,string> new_entry){
            dict.insert(new_entry);
            new_entries.push_back(new_entry);
        }
        void print(){
            for(map<string,string>::iterator it=dict.begin();it!=dict.end();it++){
                cout<<it->first<<" "<<it->second<<endl;
            }
        }
        void upload(){
            if(new_entries.empty()) return;
            ofstream outfile;
            outfile.open("dict.txt",ios::app);
            outfile<<"\n";
            for(vector<pair<string,string> >::iterator it=new_entries.begin();it!=new_entries.end();it++){
                outfile<<it->first<<" "<<it->second<<endl;
            }
        }
}wb;
int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    srand((unsigned int)time(0));
    wb.load();
    while(true){
        cout<<"*************************"<<endl;
        cout<<"** 键入 1 检索指定单词 **"<<endl;
        cout<<"** 键入 2 进行单词测验 **"<<endl;
        cout<<"** 键入 3 以添加新单词 **"<<endl;
        cout<<"** 键入 4 显示全部单词 **"<<endl;
        cout<<"** 键入 0 以保存并退出 **"<<endl;
        cout<<"*************************"<<endl; 
        char gch=getch();
        string t="";
        int test_result;
        pair<string,string> temp_entry;
        switch(gch){
            case '1':
                cout<<"输入你要查询的单词:"<<endl;
                cin>>t;
                temp_entry=wb.search(t);
                if(temp_entry.first==""){
                    cout<<"不存在该单词"<<endl;
                    cout<<"是否添加? (键入空格键-是 / 键入其它键-否)"<<endl;
                    gch=getch();
                    if(gch==' '){
                        temp_entry.first=t;
                        cout<<"输入其中文释义:"<<endl;
                        cin>>temp_entry.second;
                        wb.insert(temp_entry);
                    } 
                }else{
                    SetConsoleTextAttribute(hdl,FOREGROUND_RED+FOREGROUND_GREEN|FOREGROUND_INTENSITY);
                    cout<<temp_entry.first<<" "<<temp_entry.second<<endl;
                    SetConsoleTextAttribute(hdl,FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_BLUE|FOREGROUND_INTENSITY);
                }
                break;
            case '2':
                test_result=wb.test();
                if(test_result==-1) cout<<"词库为空,无法测验,请先添加单词"<<endl;
                else cout<<"恭喜你,这次测试达到了 "<<test_result<<" 的高分,再接再厉!"<<endl;
                break;
            case '3':
                cout<<"输入单词:"<<endl;
                cin>>t;
                temp_entry=wb.search(t);
                if(temp_entry.first==""){
                    cout<<"输入该单词的中文释义:"<<endl;
                    cin>>temp_entry.second;
                    wb.insert(temp_entry);
                }else{
                    cout<<"已存在该单词:"<<endl;
                    SetConsoleTextAttribute(hdl,FOREGROUND_RED+FOREGROUND_GREEN|FOREGROUND_INTENSITY);
                    cout<<temp_entry.first<<" "<<temp_entry.second<<endl;
                    SetConsoleTextAttribute(hdl,FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_BLUE|FOREGROUND_INTENSITY);
                }
                break;
            case '4':
                wb.print();
                break;
            case '0':
                wb.upload();
                return 0;
            default:
                cout<<"无效指令,请重试"<<endl;
        }
        system("pause");
        system("cls");
    }
    return 0;
}