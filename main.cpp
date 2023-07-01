#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<pair<char,int>> set_repetition_of_letters(vector<char> txt);
vector<char> delete_index(vector<char> txt,int index); //utility
void sort_list(vector<pair<char,int>>& list);
void swap(vector<pair<char,int>>& list,int i,int j); //utility
vector <pair<char,string>> huffman(vector<pair<char,int>> &list);
void delete_pair(vector<pair<char,int>> & list,int index);  //utility
void delete_pair(vector<pair<char,char>> & list,int index);  //utility
vector<char> make_new_txt(vector<char> txt,vector <pair<char,string>> char_code);

int main()
{
    char temp;
    vector<char> txt;
    vector<pair<char,int>> list;
    vector <pair<char,string>> char_code; // code of each charector
    vector<char> result;
    ifstream file;
    ofstream huffman_code_file;
    ofstream out_put_file;
    string filename;
    int count=0;
    string check;

    cin>>filename;
    //example: E:/f_txt.txt

    //read from file
    file.open(filename,ios::in);
    if(!file)
    {
        exit(EXIT_FAILURE);
    }
    while(file>>temp)
    {
        txt.push_back(temp);
    }
    file.close();

    //set the repetion of each charector & sort
    list =set_repetition_of_letters(txt);
    sort_list(list);

    //find the code of each charector by huffman
    char_code =huffman(list);

    //write result in Huffman_codes file
    huffman_code_file.open("E:/Huffman_codes.txt",ios::out);
    count=0;
    if(!huffman_code_file)
    {
        exit(EXIT_FAILURE);
    }
    while(count!=char_code.size())
    {
        huffman_code_file<<char_code[count].first<<" "<<char_code[count].second<<"\n";
        count++;
    }
    huffman_code_file.close();

    //set output file
    result= make_new_txt(txt,char_code);
    count=0;
    out_put_file.open("E:/output.txt",ios::out);
    if(!out_put_file)
    {
        exit(EXIT_FAILURE);
    }
    while(count!=result.size())
    {
        out_put_file<<result[count];
        count++;
    }
    out_put_file.close();



    //FOR CHECK ONE STRING
    cout<<"if you want to incode the sentence; now enter it:"<<"\n";
    txt.resize(0);
    cin>>check;
    for(int i=0;i<check.size();i++)
    {
        txt.push_back(check[i]);
    }
    //set the repetion of each charector & sort
    list =set_repetition_of_letters(txt);
    sort_list(list);

    //find the code of each charector by huffman
    char_code =huffman(list);

    result= make_new_txt(txt,char_code);
    count=0;
    while(count!=result.size())
    {
        cout<<result[count];
        count++;
    }

    return 0;
}

vector<pair<char,int>> set_repetition_of_letters(vector<char> txt){
    vector<pair<char,int>> result;
    pair<char,int> temp;
    result.resize(0);
    int count=0;
    while (txt.size()!=0) {
        temp.first=txt[0];
        count=1;
        for(int i=1;i<txt.size();i++)
        {
            if(txt[0]==txt[i])
            {
               count++;
               txt=delete_index(txt,i);
               i--;
            }
        }
        txt=delete_index(txt,0);
        temp.second=count;
        result.push_back(temp);
    }

    return result;
}

vector<char> delete_index(vector<char> txt,int index){
    vector<char> result;

    result.resize(txt.size()-1);
    if(index>0)
    {

        for(int i=0;i<index;i++)
        {
            result[i]=txt[i];
        }
    }

    for(int i=index;i<txt.size()-1;i++)
    {
        result[i]=txt[i+1];
    }

    return result;
}

void sort_list(vector<pair<char,int>>& list){

    for(int i=0;i<list.size();i++)
    {
        for(int j=i+1;j<list.size();j++)
        {
            if(list[i].second>list[j].second)
            {
                swap(list,i,j);
            }

        }

    }
}

void swap(vector<pair<char,int>>& list,int i,int j){

    pair<char,int> temp;
    temp=list[i];
    list[i]=list[j];
    list[j]=temp;

}

vector <pair<char,string>> huffman(vector<pair<char,int>> &list){

    vector <pair<char,string>> char_code; //code of each charector
    vector<pair<char,char>> lw_list; //left & write list
    int sum=0;

    while(list.size()>1)
    {
        //make a sub tree of two list pairs
        pair<char,char> temp;
        sum=list[0].second+list[1].second;
        temp.first=list[0].first;
        delete_pair(list,0); //delet left
        temp.second=list[0].first;//keep write
        list[0].second=sum;
        lw_list.push_back(temp);
        sort_list(list);
    }

    //add two last charectors
    char_code.resize(0);
    char_code.resize(2);

    char_code[0].first=lw_list[lw_list.size()-1].second;
    char_code[0].second.push_back('1');

    char_code[1].first=lw_list[lw_list.size()-1].first;
    char_code[1].second.push_back('0');

    delete_pair(lw_list,lw_list.size()-1);


    while(lw_list.size()>0)
    {
        //first dosen't exist in char_code
        char_code.resize(char_code.size()+1);
        char_code[char_code.size()-1].first=lw_list[lw_list.size()-1].first;

        //second exist in char_code
        for(int i=0;i<char_code.size();i++)
        {
            if(lw_list[lw_list.size()-1].second==char_code[i].first)
            {
                //change code of second
                char_code[i].second.push_back('1');

                //change code of first
                char_code[char_code.size()-1].second=char_code[i].second;
                char_code[char_code.size()-1].second.pop_back();
                char_code[char_code.size()-1].second.push_back('0');

            }
        }

        //delete the last part of lw_list
        delete_pair(lw_list,lw_list.size()-1);

    }


    return char_code;

}

void delete_pair(vector<pair<char,int>> & list,int index){

    if(index>0)
    {

        for(int i=0;i<index;i++)
        {
            list[i]=list[i];
        }
    }

    for(int i=index;i<list.size()-1;i++)
    {
        list[i]=list[i+1];
    }
list.resize(list.size()-1);

}

void delete_pair(vector<pair<char,char>> & list,int index){

    if(index>0)
    {

        for(int i=0;i<index;i++)
        {
            list[i]=list[i];
        }
    }

    for(int i=index;i<list.size()-1;i++)
    {
        list[i]=list[i+1];
    }
list.resize(list.size()-1);

}

vector<char> make_new_txt(vector<char> txt,vector <pair<char,string>> char_code){
    vector<char> result;
    for(int i=0;i<txt.size();i++)
    {
        for(int j=0;j< char_code.size();j++)
        {
            if(txt[i]==char_code[j].first)
            {

                for(int t=0;t<char_code[j].second.size();t++)
                {
                    result.push_back(char_code[j].second[t]);
                }
                result.push_back(' ');
                break;

            }
        }
    }
    return result;
}
