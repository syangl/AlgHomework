#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

/*
    �ַ���ʶ��ת��Ϊ���ܵ�Ӣ���ı�
    1. ����ǰ���������ı����е������ַ�h�ʶ����ʵ����,��Ҫ������д��ĸ���ʵ���û�д�д��ĸ������ʱ̬�����˳��ò���
        ��Ӧ�ú��ǵ��ʵ����ַ�,������ΪӢ�ı��
    2. Ϊ����Ԥ����Ӣ�Ĵʵ�ļ����밴�մʱ�һ��һ�����ʣ���β���з��ĸ�ʽ
        (�Ѿ�׼����Ӣ�Ĵʵ����ݼ�������Ӣ�ı����� . ! ? , : "()' ��22265��
        �ʵ��м����˳��õ��ʵ�ʱ̬��Ϊȷ���ı�����ﵽ����Ч�����������Ҫ����õ���ʱ̬���δ�Ҳ�������ʵ�)
    3. �㷨��Ƶ�ǰ���ǵ����ڴʵ��г��֣����ת�����ı���������˵���ı��в��ڴʵ��еĴ�
*/

/*
    �ַ������������� . ! ? , : ""()''
*/

/*
   Ԥ����
   �����ֵ����֯ ��ϣ���ϣ����ظ���
   �ļ���fstream
   ������
*/

/*��ⲿ��
* ɨ���ַ�������̬�滮
* �������������ĵ���+OPT�����ַ�������OPT�ǲ�ֺ�Ľ����
* ��ʹ��string����
* ���仯���� �����������飬ȥ��
*/

/*
�ı�����������
*/


int len; //�ı�����
string text; //ԭʼ�ı�
set<string>* dictionary = new set<string>{}; //Ӣ�Ĵʵ�
vector<vector<string>> save;  //���仯����

//�����ı���ⲿ��
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
    /*Ԥ����
        ��ȡ�ļ���ԭʼ�ı�Ϊֻ���л��з��Ĵ������ַ��ı�
        1. Ԥ�������OriginString.txt�ı���ȥ�����з������������ַ���
        2. �����ַ��ܳ���
        3. ��ʼ����������������
        4. ����Ӣ�Ĵʵ�
    */

    //Ԥ�������OriginString.txt�ı� �����ַ��ܳ���
    cout << "---����ԭʼ�ַ����ı�OriginString.txt��" << endl<<endl;
    loadOriginText();
    cout << text << endl<<endl;
    //��ʼ����������������
    for (int i = 0;i < len; i++) {
        save.push_back(vector<string>{""});
    }

    //����Ӣ�Ĵʵ�
    loadDictionary(dictionary);


    //���
    vector<string> res = splitText(0);


    //���������ı��ļ�EnglishTextResult.txt
    ofstream outfile;
    outfile.open("EnglishTextResult.txt");
    
    int flag = 0;
    cout << "---ѡ��Ҫ�õ��Ľ������---" << endl
            <<"--- 1 Ϊ���ȫ��������ϵ��ı���ֽ�,"<<endl
            <<"--- 2 Ϊ���һ������ɶ�����õ��ı�---:" 
            << endl;
    cout << "---�����룺" << endl << endl;
    
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
    cout << "---���Ԥ��(�������ѡ��Ϊ2��Ϊ����ɶ�����ѵ��ı�)---" << endl << endl;
    cout << res[res.size() - 1] << endl << endl;
    cout << "---��������ѱ�����EnglishTextResult.txt�ı���---"<< endl;

    return 0;
}