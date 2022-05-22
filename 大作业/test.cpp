#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

/*
    字符串识别转化为可能的英文文本
    1. 问题前提条件：文本当中的所有字符h词都被词典包含,不要包含大写字母，词典中没有大写字母，动词时态包含了常用部分
        不应该含非单词的乱字符,标点符号为英文标点
    2. 为方便预处理，英文词典的加载请按照词表一行一个单词，行尾换行符的格式
        (已经准备好英文词典数据集，包含英文标点符号 . ! ? , : "()' 共22265词
        词典中加入了常用单词的时态，为确保文本处理达到正常效果，如果有需要请把用到的时态变形词也扩充进入词典)
    3. 算法设计的前提是单词在词典中出现，如果转换后文本不完整，说明文本有不在词典中的词
*/

/*
    字符串包含标点符号 . ! ? , : ""()''
*/

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
        text += str;
    }
    len = text.length();
}

//int maxlen = 0, index = 0;
//void textLength(vector<string>& res) {
//    for (int i = 0; i < res.size(); i++) {
//        if (res[i].length() > maxlen) {
//            maxlen = res[i].length();
//            index = i;
//        }
//    }
//}














int main() {
    /*预处理
        读取文件，原始文本为只含有换行符的待处理字符文本
        1. 预处理读入OriginString.txt文本（去除换行符）到待处理字符串
        2. 计算字符总长度
        3. 初始化记忆结果集的向量
        4. 加载英文词典
    */

    //预处理读入OriginString.txt文本 计算字符总长度
    cout << "---加载原始字符串文本OriginString.txt：" << endl<<endl;
    loadOriginText();
    cout << text << endl<<endl;
    //初始化记忆结果集的向量
    for (int i = 0;i < len; i++) {
        save.push_back(vector<string>{""});
    }

    //加载英文词典
    loadDictionary(dictionary);


    //求解
    vector<string> res = splitText(0);


    //结果输出到文本文件EnglishTextResult.txt
    ofstream outfile;
    outfile.open("EnglishTextResult.txt");
    
    int flag = 0;
    cout << "---选择要得到的结果类型---" << endl
            <<"--- 1 为输出全部可能组合的文本拆分解,"<<endl
            <<"--- 2 为输出一个语义可读性最好的文本---:" 
            << endl;
    cout << "---请输入：" << endl << endl;
    
    cin >> flag;
    if (flag == 1) {
		for (int i = 0; i < res.size(); i++) {
			outfile << res[i] << endl;
		}
    }
    else if (flag == 2) {
        textLength(res);
        outfile << res[index] << endl;
    }
   
    outfile.close();
    cout << "---结果预览(结果类型选择为2则为语义可读性最佳的文本)---" << endl << endl;
    cout << res[res.size() - 1] << endl << endl;
    cout << "---完整结果已保存在EnglishTextResult.txt文本中---"<< endl;

    return 0;
}