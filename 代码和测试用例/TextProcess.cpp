#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

/*
   预处理
   单词字典的组织 哈希集合（不重复）
   文件流fstream
   标点符号
*/

/*求解部分
* 扫描字符串，动态规划
* 从左往右遇到的单词+OPT（子字符串），OPT是拆分后的结果集
* 解使用string数组
* 记忆化搜索 记忆结果的数组，去重
*/

/*
文本输出按句输出
*/


int len; //文本长度
string text; //原始文本
set<string>* dictionary = new set<string>{}; //英文词典
vector<vector<string>> save;  //记忆化搜索

//处理文本求解部分
vector<string> splitText(int start) {

    if (start >= len) {
        vector<string> tmp;
        tmp.push_back("");
        return tmp;
    }

    if (save[start] != vector<string>{""}) {
        return save[start];
    }

    vector<string> res;
    res.push_back("");
    for (int i = start+1; i <= len; i++) {
        string word = text.substr(start, i-start);
        if (dictionary->count(word)) {
            vector<string> sub_opt = splitText(i);
            for (string var : sub_opt)
            {
                res.push_back((word == "."||word == "?" || word == "!") ? 
                                    word + "\n" + var : word + " " + var);
            }
        }
    }

    save[start] = res;
    return res;
}


void loadDictionary(set<string>* & dictionary) {
    ifstream infile;
    infile.open("Dictionary.txt");
    string str;
	while (!infile.eof())
	{
		infile >> str;
		if (str == "") {}
		else {
			dictionary->insert(str);
		}
	}
}


void loadOriginText() {
    ifstream infile;
    infile.open("OriginString.txt");
    string str;
    while (!infile.eof())
    {
        infile >> str;
        text.append(str);
    }
    len = text.length();
}

//大写替换
void repleaceLitter() {
    for (int i = 0; i < text.length(); i++)
    {
        if (65 <= (int)text[i] && (int)text[i] <= 90) {
            text[i] = text[i] + 32;
        }
    }
}


int main() {
    //预处理读入OriginString.txt文本 计算字符总长度
    cout << "---加载原始字符串文本OriginString.txt：" << endl<<endl;
    loadOriginText();
    repleaceLitter();
    cout << text << endl<<endl;
    //初始化记忆结果集的向量
    for (int i = 0;i < len; i++) {
        save.push_back(vector<string>{""});
    }

    //加载英文词典
    loadDictionary(dictionary);


    //求解
    cout << "正在求解中..." << endl;
    vector<string> res = splitText(0);


    //结果输出到文本文件EnglishTextResult.txt
    ofstream outfile;
    outfile.open("EnglishTextResult.txt");
    
    int number = 0;
    cout<< "---选择你要保存的结果条数（从最后一条开始计数）---" << endl
            << "不超过总结果数:" << res.size()
            << endl;
    cout << "---请输入：";
    
    cin >> number;
    for (int i = res.size() - number; i < res.size(); i++) {
        outfile <<"结果"<<i - res.size() + number + 1 <<":\n" << res[i] << endl << endl;
    }

    outfile.close();
    cout << "---完整结果已保存在EnglishTextResult.txt文本中---"<< endl;

    return 0;
}