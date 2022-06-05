#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

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
        text.append(str);
    }
    len = text.length();
}

//��д�滻
void repleaceLitter() {
    for (int i = 0; i < text.length(); i++)
    {
        if (65 <= (int)text[i] && (int)text[i] <= 90) {
            text[i] = text[i] + 32;
        }
    }
}


int main() {
    //Ԥ�������OriginString.txt�ı� �����ַ��ܳ���
    cout << "---����ԭʼ�ַ����ı�OriginString.txt��" << endl<<endl;
    loadOriginText();
    repleaceLitter();
    cout << text << endl<<endl;
    //��ʼ����������������
    for (int i = 0;i < len; i++) {
        save.push_back(vector<string>{""});
    }

    //����Ӣ�Ĵʵ�
    loadDictionary(dictionary);


    //���
    cout << "���������..." << endl;
    vector<string> res = splitText(0);


    //���������ı��ļ�EnglishTextResult.txt
    ofstream outfile;
    outfile.open("EnglishTextResult.txt");
    
    int number = 0;
    cout<< "---ѡ����Ҫ����Ľ�������������һ����ʼ������---" << endl
            << "�������ܽ����:" << res.size()
            << endl;
    cout << "---�����룺";
    
    cin >> number;
    for (int i = res.size() - number; i < res.size(); i++) {
        outfile <<"���"<<i - res.size() + number + 1 <<":\n" << res[i] << endl << endl;
    }

    outfile.close();
    cout << "---��������ѱ�����EnglishTextResult.txt�ı���---"<< endl;

    return 0;
}