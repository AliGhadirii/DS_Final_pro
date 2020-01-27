#include <iostream> 
#include <cstdlib> 
#include<fstream>
#include<map>
#include<string>
#include<vector>
using namespace std;
map<char, string> ourmap;
#define MAX_TREE_HT 100 

struct MinHeapNode {
	char data;
	unsigned freq;
	struct MinHeapNode* left, * right;
};

struct MinHeap {

	unsigned size;
	unsigned capacity;
	struct MinHeapNode** array;
};

struct MinHeapNode* newNode(char data, unsigned freq)
{
	struct MinHeapNode* temp
		= (struct MinHeapNode*)malloc
		(sizeof(struct MinHeapNode));

	temp->left = temp->right = NULL;
	temp->data = data;
	temp->freq = freq;

	return temp;
}

struct MinHeap* createMinHeap(unsigned capacity)

{

	struct MinHeap* minHeap
		= (struct MinHeap*)malloc(sizeof(struct MinHeap));
	minHeap->size = 0;

	minHeap->capacity = capacity;

	minHeap->array
		= (struct MinHeapNode**)malloc(minHeap->
			capacity * sizeof(struct MinHeapNode*));
	return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a,
	struct MinHeapNode** b)
{

	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx)
{

	int smallest = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;

	if (left < minHeap->size && minHeap->array[left]->
		freq < minHeap->array[smallest]->freq)
		smallest = left;

	if (right < minHeap->size && minHeap->array[right]->
		freq < minHeap->array[smallest]->freq)
		smallest = right;

	if (smallest != idx) {
		swapMinHeapNode(&minHeap->array[smallest],
			&minHeap->array[idx]);
		minHeapify(minHeap, smallest);
	}
}

int isSizeOne(struct MinHeap* minHeap)
{

	return (minHeap->size == 1);
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap)

{

	struct MinHeapNode* temp = minHeap->array[0];
	minHeap->array[0]
		= minHeap->array[minHeap->size - 1];

	--minHeap->size;
	minHeapify(minHeap, 0);

	return temp;
}

void insertMinHeap(struct MinHeap* minHeap,
	struct MinHeapNode* minHeapNode)

{

	++minHeap->size;
	int i = minHeap->size - 1;

	while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {

		minHeap->array[i] = minHeap->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}

	minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap)

{

	int n = minHeap->size - 1;
	int i;

	for (i = (n - 1) / 2; i >= 0; --i)
		minHeapify(minHeap, i);
}
string printArr(int arr[], int n)
{
	string test;
	int i;
	for (i = 0; i < n; ++i)
		test += to_string(arr[i]);
	return test;
}
int isLeaf(struct MinHeapNode* root)

{

	return !(root->left) && !(root->right);
}
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size)
{
	struct MinHeap* minHeap = createMinHeap(size);

	for (int i = 0; i < size; ++i)
		minHeap->array[i] = newNode(data[i], freq[i]);

	minHeap->size = size;
	buildMinHeap(minHeap);

	return minHeap;
}
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size)

{
	struct MinHeapNode* left, * right, * top;
	struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);
	while (!isSizeOne(minHeap)) {
		left = extractMin(minHeap);
		right = extractMin(minHeap);
		top = newNode(NULL, left->freq + right->freq);
		top->left = left;
		top->right = right;

		insertMinHeap(minHeap, top);
	}
	return extractMin(minHeap);
}
void printCodes(struct MinHeapNode* root, int arr[], int top)

{
	if (root->left) {

		arr[top] = 0;
		printCodes(root->left, arr, top + 1);
	}
	if (root->right) {

		arr[top] = 1;
		printCodes(root->right, arr, top + 1);
	}
	if (isLeaf(root)) {
		ourmap.insert(pair<char, string>(root->data, printArr(arr, top)));
	}
}
struct MinHeapNode* HuffmanCodes(char data[], int freq[], int size)

{

	struct MinHeapNode* root
		= buildHuffmanTree(data, freq, size);
	int arr[MAX_TREE_HT], top = 0;

	printCodes(root, arr, top);
	return root;
}
string decodepls(struct MinHeapNode* root, string data)
{
	string ans;
	struct MinHeapNode* temp = root;
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i] == '0')
		{
			temp = temp->left;
		}
		else
		{
			temp = temp->right;
		}
		if (temp->left == NULL && temp->right == NULL)
		{
			ans += temp->data;
			temp = root;
		}
	}
	return ans;
}
int main()
{
	map<char, int> map_freq;
	for (int i = 0; i < 128; i++)
	{
		map_freq.insert(pair<char, int>(char(i), 0));
	}
	fstream file, result, decode;
	file.open("text.txt", ios::in);
	result.open("result.txt", ios::out);
	decode.open("decode.txt", ios::out);
	string temp, filetext;
	while (getline(file, temp))
	{
		for (int i = 0; i < temp.size(); i++)
		{
			map_freq[temp[i]]++;
		}
		filetext += temp;
		filetext += '\n';
	}
	/*for (auto i = map_freq.begin(); i != map_freq.end(); i++)
	{
		cout << i->first << " : " << i->second << endl;
	}*/
	vector<char> datas;
	vector<int> freq;
	for (auto i = map_freq.begin(); i != map_freq.end(); i++)
	{
		if (i->second != 0)
		{
			datas.push_back(i->first);
			freq.push_back(i->second);
		}
	}
	/*for (int i = 0; i < datas.size(); i++)
	{
		cout << datas[i] << " : " << freq[i] << endl;
	}*/
	char* datasnew = new char[datas.size()];
	int* freqnew = new int[freq.size()];
	for (int i = 0; i < datas.size(); i++)
	{
		datasnew[i] = datas[i];
		freqnew[i] = freq[i];
	}
	struct MinHeapNode* huff_root = HuffmanCodes(datasnew, freqnew, datas.size());
	for (int i = 0; i < filetext.size(); i++)
	{
		if (filetext[i] == '\n')
		{
			result << "\n";
		}
		else
		{
			result << ourmap[filetext[i]];
		}
	}
	result.close();
	result.open("result.txt", ios::in);
	string tm;
	while (getline(result, tm))
	{
		decode << decodepls(huff_root, tm) << endl;
	}
	return 0;

}