#include<iostream>
#include<string>
using namespace std;

class Hash {
public:
	//constructor
	Hash(int _maxsize, string _mode);
	Hash(int _data[], int _datasize, int _maxsize, string _mode);


	//method
	bool insert(int key);
	bool mydelete(int key);
	int getKeyIndex(int key);

private:
	int *data;    //储存数据数组
	bool *full;   //判断储存数据的数组在该处是否已经有数据，用于解决冲突
	int maxsize;  //哈希表最大元素个数
	string mode;  //解决冲突的方法：线性探查法，二次探查法和再哈希法。

	int hash(int key);  //哈希函数，可根据具体数据不同而进行修改
	int rehash(int key); //再哈希法所选用的第二个函数。

};


/*
** Hash:构建一个空的哈希表
** _maxsie:规定哈希表的最大储存元素个数
** mode:规定解决冲突时所运用的方法
*/

Hash::Hash(int _maxsize, string _mode) {
	maxsize = _maxsize;
	data = new int[maxsize];
	full = new bool[maxsize];

	for (int i = 0; i < maxszie; i++) {
		full[i] = false;
	}

	if (mode == "linear" || mode == "square" || mode == "rehash") mode = _mode;
	else mode = "lineae";
}


/*
** Hash:根据所给数组来构建一个哈希表
** _data:所给数组
** _datasize:所给数组的元素个数
** __maxsize:规定哈希表中的最大储存元素个数
** _mode:规定解决冲突时所运用的方法
*/

Hash::Hash(int *data, int _datasize, int _maxsize, string _mode) {
	maxsize = _maxszie;
	data = new int[maxsize];
	full = new bool[maxsize];
	for (int i = 0; i < maxsize; i++) {
		full[i] = false;
	}

	if (mode == "linear" || mode == "square" || mode == "rehash") mode = _mode;
	else mode = "lineae";

	for (int i = 0; i < _datasize; i++) {
		this->insert(data[i]);
	}
}

/*
** hash:哈希函数，可根据数据修改，选择最适合的哈希函数
*/
int Hash::hash(int key) {
	return key % maxsize;
}

/*
** rehash:再哈希法中所调用的哈希函数2，这里写为和哈希函数1一样.
*/
int Hash::rehash(int key) {
	return key % maxsize;
}

/*
** getKeyIndex:获取哈希表中数据key所在的位置
*/
int Hash::getKeyIndex(int key) {
	int index = hash(key);

	if (full[index] == true && data[index] == key) return index;
	else {
		//若使用线性探查法
		if (mode == "linear") {
			for (int i = 0; i < maxsize; i++) {
				int posi = (index + i) % maxsize;
				if (full[posi] == true && data[posi] == key) return posi;
			}
		}

		//若使用二次探查法
		else if (mode == "square") {
			for (int i = 0; i < maxsize; i++) {
				int posi = (index + i * i) % maxsize;
				if (full[posi] == true && data[posi] == key) return posi;
			}
		}

		//若使用再哈希法
		else {
			for (int i = 0; i < maxsize; i++) {
				int posi = (index + i * rehash(key)) % maxsize;
				if (full[posi] == true && data[posi] == key) return posi;
			}
		}
	}
	return -1;
}

/*
** insert:向哈希表中插入数据
** key:数据
*/
bool Hash::insert(int key) {
	int posi = hash(key);
	//若该位置没有元素，则不会引起冲突，直接插入
	if (full[posi] == false) {
		data[posi] = key;
		full[posi] == true;
	}

	//若有元素，则需要寻找其他位置来解决冲突
	else {
		if (mode == "linear") {
			
			for (int i = 0; i < maxsize; i++) {
				int posi = (index + i)%maxsize;
				if (full[posi] == false)
				{
					data[posi] = key;
					full[posi] = true;
					return true;
				}
			}
		}

		
		else if (mode == "square") 
		{
			for (int i = 0; i < maxsize; i++)
			{
				int posi = (index + i * i) % maxsize;
				if (full[posi] == false)
				{
					data[posi] = key;
					full[posi] = true;
					return true;
				}
			}
		}

		else
		{
			for (int i = 0; i < maxsize; i++)
			{
				int posi = (index + i * rehash(key)) % maxsize;
				if (full[posi] == false)
				{
					data[posi] = key;
					full[posi] = true;
					return true;
				}
			}
		}
	}
}

/*
** mydelete:删除哈希表中内容为key的元素
*/
bool Hash::mydelete(int key) {
	int posi = this->getKeyIndex(key);
	if (posi != -1 && full[posi] == true)
	{
		full[posi] = false;
		return true;
	}

	else 
		return false;
}
