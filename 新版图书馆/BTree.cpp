#include"Btree.h"

BTree::BTree() {//BTree���캯��
	BTree_Node_root = new BTree_Node;
	answer.tag = -1;
};
/******************************************************************************************************************/
/**************************************************��������********************************************************/
int BTree::search_location(string& x, BTree_Node*& y) {
	int i = 1;
	while (i <= y->key_number && x > y->key[i]) {
		i++;
	}
	return i;
};
void BTree::search(string& x) {//��������
//�������£�
//��������B���ϲ��ҹؼ���x����answer����(got,i,tag)��
//�����ҳɹ�������tag=1��ָ��got��ָ����е�i���ؼ��ֵ���x��
//����tag=0����Ҫ����ؼ���Ϊx�ļ�¼��Ӧλ��got����е�i-1���͵�i���ؼ���֮�䡣
	int i = 1, found = 0;
	BTree_Node* temp_1 = BTree_Node_root;
	BTree_Node* pr_temp_1 = nullptr;//��ʼ��temp_1ָ����ڵ㲢������ָ������ҽ�㣬pr_temp_1ָ����˫��
	while (temp_1 != nullptr && found == 0) {//��(����ָ�벻Ϊ�ա�δ�ҵ���ؽ��)ʱ
		i = search_location(x, temp_1);
		if (i <= temp_1->key_number && temp_1->key[i] == x)//����ҵ�
			found = 1;
		else {
			pr_temp_1 = temp_1;
			temp_1 = temp_1->childs[i - 1];
		}//������
	}
	if (found == 1) {//���ҳɹ�������temp_1������x��λ��i
		answer = { temp_1,i,1 };
		return;
	}
	else {//���Ҳ��ɹ�������x�Ĳ���λ��pr_temp_1��i����ʱtemp_1==nullptr��pr_temp_1==����temp_1�Ľ�㣩
		answer = { pr_temp_1,i,0 };
		return;
	}
};
Book* BTree::search_return_index(string& x)
{
	int i = 1, found = 0;
	BTree_Node* temp_1 = BTree_Node_root;
	BTree_Node* pr_temp_1 = nullptr;//��ʼ��temp_1ָ����ڵ㲢������ָ������ҽ�㣬pr_temp_1ָ����˫��
	while (temp_1 != nullptr && found == 0) {//��(����ָ�벻Ϊ�ա�δ�ҵ���ؽ��)ʱ
		i = search_location(x, temp_1);
		if (i <= temp_1->key_number && temp_1->key[i] == x)//����ҵ�
			found = 1;
		else {
			pr_temp_1 = temp_1;
			temp_1 = temp_1->childs[i - 1];
		}//������
	}
	if (found == 1) {//���ҳɹ������ص�ַ��
		return temp_1->index[i];
	}
	else {//���Ҳ��ɹ������ص�ַΪ�ա�
		return nullptr;
	}
};
/******************************************************************************************************************/
/**************************************************���벿��********************************************************/
void BTree::insert_page0(string x, Book* y) {//���루x��y��Ԫ�飬����x���ؼ��ʣ�y�������������ɹ�����Եõ��ģ���ַ��
	search(x);//�Ȳ���
	if (answer.tag == 0)//���Բ���
	{
		insert_page_1(x, answer.got, answer.i, y);//����׼������
	}
	else {
		return;
	}
};
void BTree::produce_new_root(BTree_Node* y, string x, BTree_Node* v, Book* book) {//�����µĸ����:y��v
	BTree_Node_root = new BTree_Node;
	BTree_Node_root->key_number = 1;
	BTree_Node_root->childs[0] = y;
	BTree_Node_root->childs[1] = v;
	BTree_Node_root->key[1] = x;
	BTree_Node_root->index[1] = book;
	if (y != nullptr)
		y->parent = BTree_Node_root;
	if (v != nullptr)
		v->parent = BTree_Node_root;
	BTree_Node_root->parent = nullptr;
}
void BTree::insert_page_2(BTree_Node * &y, int z, string & x, BTree_Node * v, Book* book) {//�ؼ���x���½��ָ��v�ֱ�嵽y->key[z]��y->childs[z]��childs[z]Ӧ��Ҳ���ԣ�������Ҫע��һ�£�
	for (int j = y->key_number;j >= z;j--) {
		y->key[j + 1] = y->key[j];
		y->index[j + 1] = y->index[j];//��ADD it recetly��
		y->childs[j + 1] = y->childs[j];
	}//��������Ų������֮��y->key[i]��y->childs[i]��y->index[i]���ڳ����ˡ�
	y->key[z] = x;
	y->index[z] = book;//��ADD it recently��
	y->childs[z] = v;//Ȼ���[i]��ֵ

	if (v != nullptr)
		v->parent = y;
	y->key_number++;//
}
void BTree::insert_split(BTree_Node * &y, int center, BTree_Node * &z) {//��y�����ѳ�������㣬ǰһ�뱣����ԭ��㣬��һ������z��ָ�½�㡣Ҳ������y����Ϊy��z������
	int n = y->key_number;//j��ѭ����ʱ��ʹ�ã�n��ѭ����ʱ��ʹ�ã��޶�ѭ��������
	z = new BTree_Node;//�����½�㣬���氲�ŷּ�����
	//cout << "new��";
	z->childs[0] = y->childs[center];//���Ĺؼ����Ҳ�ĺ��ӣ��ú��ӵ�������Ů�Ĺؼ��ֶ���key[center]��
	for (int i = center + 1, j = 1;i <= n;i++, j++) {//��y�ĺ�һ�뺢��������z��㡣ע��j��z�����ǵ��±ꣻi��y�ĺ����ǵ��±ꡣ
		z->key[j] = y->key[i];
		z->index[j] = y->index[i];//��ADD it recently��
		z->childs[j] = y->childs[i];
	}
	z->key_number = n - center;//��ǰ�ؼ��ֵĸ���
	z->parent = y->parent;//��ʱz��y�ĸ���Ӧ����ͬ��������Ҫ��z�ĸ�����Ϊy->parent
	y->key_number = center - 1;//y�Ĺؼ��ָ�����Ӧ����
	for (int i = 0;i <= n - center;i++)//z�õ��ĺ����ǵĸ����Ŀǰ����y����Ҫ�����ǵĸ�����Ϊz
		if (z->childs[i] != NULL)
			z->childs[i]->parent = z;
};
void BTree::insert_page_1(string & x, BTree_Node * &y, int z,Book* book) {//��CORRECT��
	//��B����y����key[z-1]��key[z]֮�����ؼ���x
	//���������ؼ��ָ�������b���Ľף�������˫��ָ�������н����ѣ�ʹ��t����m��B��//!!!!!!��������������������������������������ע���еġ�t����Ҫ����
	string x_temp_1 = x;//��ʱ����x��ֵ���Է���ʧ
	Book* book_temp_1 = book;//��ʱ����book��ֵ���Է���ʧ
	int center;//����ʱ���м�ؼ���������±�
	int finished = 0;//�Ƿ������ɵı�־��1��������ɣ�0��δ���
	int needNewRoot = 0;//�費��Ҫ�����µĸ���㣬1����Ҫ��0������Ҫ
	BTree_Node* temp_1;
	if (y == nullptr)//
		produce_new_root(nullptr, x_temp_1, nullptr, book_temp_1);
	else {
		x_temp_1 = x;//�õ�x��ֵ
		book_temp_1 = book;
		temp_1 = nullptr;//Ϊtemp_1�����ڴ�
		while (needNewRoot == 0 && finished == 0) {
			insert_page_2(y, z, x_temp_1, temp_1, book_temp_1);//��x��temp_1�ֱ�嵽y->key[i]��y->childs[i]//��ADD һ������v��
			if (y->key_number < m)
				finished = 1;//��ȫ���������
			else {//key_number�ﵽ���ֵ����Ҫ����
				center = (m + 1) / 2;
				insert_split(y, center, temp_1);
				x_temp_1 = y->key[center];//�ý����Ҫ��������y�ĸ������
				book_temp_1 = y->index[center];//ͬ��
				if (y->parent != nullptr) {
					y = y->parent;//������y�ĸ���
					z = search_location(x_temp_1, y);//�ڸ�����в���x�Ĳ���λ�ã�Ȼ�����ѭ�����ɡ�
				}
				else needNewRoot = 1;//������Ҫ�����µĸ����
			}
		}
		if (needNewRoot == 1)
			produce_new_root(y, x_temp_1, temp_1, book_temp_1);//�����µĸ����
	}
};
/******************************************************************************************************************/
/**************************************************ɾ������********************************************************/
void BTree::delete_page00(string x) {
	search(x);//search(string& x)������Ϊ���á�
	if (answer.tag)//����ҵ�
	{
		delete_page1(answer.got, answer.i);//ɾ��
		cout << "������ճɹ���";
		print_page();//��ӡ���û��鿴��
	}
	else {//û�ҵ�
		cout << "���鲻���ڣ�������";
		return;
	}
};
void BTree::delete_page0() {
	string temp;
	cout << "��������Ҫ������ţ�";
	cin >> temp;
	search(temp);//search(string& x)������Ϊ���á�
	if (answer.tag)//����ҵ�
	{
		delete_page1(answer.got, answer.i);//ɾ��
		cout << "���ɹ���";
		print_page();//��ӡ���û��鿴��
	}
	else {//û�ҵ�
		cout << "���鲻���ڣ�";
		return;
	}
};
void BTree::delete_page1(BTree_Node * &y, int i) {
	if (y->childs[i] != nullptr) {//�����������²���ն˽�㣬��ɾ����Ҫ�����¹�����
		delete_successor(y, i);//���������ҳ����²���ն˽�����С�ؼ������ki
		delete_remove(y, 1);//�����²���ն˽��Ĵ����ƶ���
		delete_restore(y);//����B��,y���ո��ƶ����ؼ��ֵĽ�㣨ɾ������С�Ĺؼ��֣�����Ĺؼ�������ǰ�����������ʱy�Ĺؼ��ָ���С�ڣ�m-1��/2������Ҫ������������Ҫ������
	}
	else {//�������²���ն˽�㣬����Ҫ�����¹�����
		delete_remove(y, i);//�����²���ն˽��Ĵ����ƶ���
		if (y->key_number < (m - 1) / 2)//���ɾ����ؼ��ָ���С��(m-1)/2��ע�⣺[ȡ����(m/2)-1]=={ȡ����[(m-1)/2]}��������Ҫ������������Ҫ������
			delete_restore(y);//����B��,y���ո��ƶ����ؼ��ֵĽ�㣨ɾ������С�Ĺؼ��֣�����Ĺؼ�������ǰ��������ʱy�Ĺؼ��ָ���С�ڣ�m-1��/2����Ҫ������
	}
};
void BTree::delete_successor(BTree_Node * &y, int i) {//�ɺ�����²���ն˽�����С�ؼ��ִ������йؼ���key[i]
	BTree_Node* temp = y->childs[i];//temp���õ�y��ֵ������������y����С���ӵ���С����......
	while (temp->childs[0] != nullptr) {//ֱ��Ѱ�ҵ���С�Ĺؼ���
		temp = temp->childs[0];
	}
	y->key[i] = temp->key[1];
	y->index[i] = temp->index[1];
	y = temp;//����y��ֵ����ʱyָ��ԭy�ĵ�i����������С�Ĺؼ������ڵĽ�㡣
};
void BTree::delete_remove(BTree_Node * &y, int i)//ɾ�����ڹؼ��ּ��ϱ�Ե�Ĺؼ��֣���������������Ǵ���Ĵ���ȴ��һ���ġ�
{
	int j;//ѭ������Ҫʹ��
	int n = y->key_number;//�õ���Ҫ��ֵ
	for (j = i;j < n;j++) {//�ƶ�������ѭ��ִ�У�n-i��=��m-1-��i-1������
		y->key[j] = y->key[j + 1];//�ƶ�
		y->index[j] = y->index[j + 1];
		y->childs[j] = y->childs[j + 1];//�ƶ�
	}
	y->key_number--;//�ؼ���������Ӧ��һ����ʱ��yָ��ؼ����ƶ����Ľ�㣨�����������y�����ã���
};
void BTree::delete_restore(BTree_Node * &y) {//���ܣ����ڸոն�y������С�ؼ���ɾ������ʱ�ؼ��ָ������㣬B����Ҫ������
	int j;//����ѭ������Ҫ��������ؼ��֡�����ָ������ơ����Ƶȵȡ�
	BTree_Node* temp_0 = y->parent;//temp_0��y�ĸ����
	if (temp_0 == nullptr) //��ԭע�ͣ�������������ֿյĸ���㣬��ɾ���ø���㣬���߼�1��)��ע�ͣ������temp_0Ϊ�գ���ֻ��˵��֮ǰ�ǶԸ�������ɾ���ģ����Ը�������ɾ����ֻ��һ��������Ǿ������B����ֻʣ������ˡ��ǾͲ��õ����ˣ�ֻ��һ��������B���ĸ����Ĺؼ��ָ�������Ϊ�ա�����
	{
		BTree_Node_root = y;
		y = y->parent;
		return;
	}
	BTree_Node* left;//���ֵ�
	BTree_Node* right;//���ֵ�
	BTree_Node* delete_help;//����ɾ��ָ��
	int finished = 0;//�ж��Ƿ����������0��>û������1��>������
	int location = 0;//����yλ��y�ĸ�����е�λ�ã�temp_0->childs[location]==y��
	while (!finished)//û������0�����ͼ���ѭ��
	{
		location = 0;
		while (temp_0->childs[location] != y) {
			location++; //ȷ��y��temp_0�����е�λ��:temp_0->childs[location]==y��
		}
		if (location == 0)//��һ������
		{
			location++;
			left = nullptr;
			right = temp_0->childs[location];//�õ����ֵ�
		}
		else if (location == temp_0->key_number)//���һ������
		{
			right = nullptr;
			left = temp_0->childs[location - 1];//�õ����ֵ�
		}
		else//�м亢��
		{
			left = temp_0->childs[location - 1];
			right = temp_0->childs[location + 1];//�����ֵܶ��õ�
		}
		/**�������жϿɲ����Խ�������������Ծͽ裩��**/
		if (location > 0 && left != nullptr && (left->key_number > (m - 1) / 2))//��ʱ���������ֵܽ�ؼ���
		{
			y->key_number++;//y�ĺ��Ӹ�����ǰ���ӣ�Ϊ������������̵棺
			for (j = y->key_number;j > 1;j--)//���ؼ�������
			{
				y->key[j] = y->key[j - 1];
				y->index[j] = y->index[j - 1];
				y->childs[j] = y->childs[j - 1];
			}
			y->key[1] = temp_0->key[location];//�������м�ؼ��֣�������left��y�����뵽���y
			y->index[1] = temp_0->index[location];
			y->childs[1] = y->childs[0];//����ص���ŮҲ����
			y->childs[0] = left->childs[left->key_number];//�����µĺ��ӣ�����left�����һ�����ӣ�
			if (y->childs[0] != nullptr)//����¼���ĺ��Ӳ�Ϊ�գ����޸�y�еĺ��ӵĸ����Ϊy��
			{
				y->childs[0]->parent = y;
			}
			temp_0->key[location] = left->key[left->key_number];//���ֵ��ϵ����Ҷ˵Ĺؼ����Ƶ�����λ��
			temp_0->index[location] = left->index[left->key_number];
			left->key_number--;//���ֵܵĹؼ��ָ�������
			finished = 1;//����λ��1
			break;//��������
		}
		else if (location < temp_0->key_number && right != nullptr && (right->key_number > (m - 1) / 2))//��������ֵ�û���㹻��Ĺؼ��ֵĻ����ͳ��������ֵܽ�ؼ��֣�������Խ裬�ͽ�������else if�Ĳ�����
		{
			y->key_number++;
			y->key[y->key_number] = temp_0->key[location + 1]; //�������м�ؼ��ֲ��뵽���y�����ע��˴���ԭ����y->key[y->keynum] = temp_0->key[location]���ָ�Ϊy->key[y->keynum] = temp_0->key[location+1]��
			y->index[y->key_number] = temp_0->index[location + 1];
			y->childs[y->key_number] = right->childs[0];//�����µĺ��ӵ����
			if (y->childs[y->key_number] != nullptr) {//�޸�y�е���Ů�ĸ����Ϊy
				y->childs[y->key_number]->parent = y;
			}
			else {}//
			temp_0->key[location + 1] = right->key[1];//���ֵ��ϵ�ͷһ���ؼ����Ƶ���������Ӧλ�á�ע��˴�ԭ���ǣ�temp_0->key[location] = right->key[1]���ָ�Ϊtemp_0->key[location+1] = right->key[1]��
			temp_0->index[location + 1] = right->index[1];
			right->childs[0] = right->childs[1];//ΪɶҪд����������Ϊ�����ѭ���˲�������������ǰ���⴦���ˡ�
			right->index[0] = right->index[1];
			for (j = 1;j < right->key_number;j++)//���ֵܽ��ؼ�������
			{
				right->key[j] = right->key[j + 1];
				right->index[j] = right->index[j + 1];
				right->childs[j] = right->childs[j + 1];
			}
			right->key_number--;//���ֵܵĹؼ��ָ�������
			finished = 1;//����λ��1
			break;//��������
		}
		else {//�費������ô��Ϊ�ϲ���׼����
			location = 0;//ǰ����漰��location�ļӼ������Դ˴���Ҫ���¶�λ�����ڴ˴���Ҫ�������¡�
			/*�����Ǻϲ�*/
			while (temp_0->childs[location] != y) {//����ȷ��y��temp_0������λ��
				location++;
			}
		}
		/**������׼���ϲ��������**/
		if (location > 0 && (temp_0->childs[location - 1]->key_number <= (m - 1) / 2)) //�������ֵܴ��ڣ����ң����ֵܵ���ŮҲ���ࣩʱ��y�����ֵܺϲ���
		{
			left = temp_0->childs[location - 1];//�õ����ֵ�
			y->key_number++;//y����Ů������һ��������������ƿ�ʼ���ǣ�j=y->key_number
			for (j = y->key_number;j > 1;--j)//��y���ؼ��ֺ�ָ������1λ
			{
				y->key[j] = y->key[j - 1];
				y->index[j] = y->index[j - 1];
				y->childs[j] = y->childs[j - 1];
			}
			y->key[1] = temp_0->key[location];//��������Ӧ�ؼ��ֱ��y��ͷһ���ؼ���
			y->index[1] = temp_0->index[location];
			y->childs[1] = y->childs[0];//���һ����ŮҲ���ƣ������Ů�������Ĺؼ������Ǵ��ڸոռ�����������Ը����Ĺؼ��֣�λ��ǰ����䣩�ġ�
			for (j = 1;j <= y->key_number;++j) //�����y�йؼ��ֺ�ָ���Ƶ�left��
			{
				left->key[left->key_number + j] = y->key[j];
				left->index[left->key_number + j] = y->index[j];
				left->childs[left->key_number + j] = y->childs[j];
			}
			if (y->childs[0])//������Ĵ�����y->childs[0]��û�иı������������ֵ����ԭ����ֵ�����y->childs[0]��Ϊ�գ��Ǿͱ�־��y�к��ӣ������޸�y�е���Ů�ĸ����Ϊleft������y��û�к��ӣ�Ҳ�Ͳ������޸�y�ĺ��ӵĸ��������ˡ�
			{
				for (j = 1;j <= y->key_number;++j)
					if (left->childs[y->key_number + j])//�˴���ȻҪ�жϣ���Ϊy�к��Ӳ��������Ӹ����͵��ڹؼ��ָ�����
						left->childs[y->key_number + j]->parent = left;//�޸�
					else {}//���򱾴�ѭ��ʲôҲ����
			}
			left->key_number = left->key_number + y->key_number;//�ϲ���ؼ��ֵĸ���
			temp_0->childs[location] = left;//y���߳�B����
			for (j = location;j < temp_0->key_number;j++)//��������йؼ��ֺ�ָ������
			{
				temp_0->key[j] = temp_0->key[j + 1];
				temp_0->index[j] = temp_0->index[j + 1];
				temp_0->childs[j] = temp_0->childs[j + 1];
			}
			temp_0->key_number--;
			delete y;
			y = left;
		}
		else //��Ϊtemp_0�������ǳɶԴ��ڣ���������temp_0��˵���κ�һ����Ϊ�յĺ��ӱ�������һ����Ϊ�յ������ֵܣ�����Ȼy����Ϊ���ˣ���ôyһ��������һ�������ֵܡ����ǣ���Ȼ��������ֵܲ����ڣ���ô��ֻ�ܺ����ֵܺϲ��ˣ���ʱ���ֵܿ϶��ǿ��Ժ�y�ϲ��ģ���
		{
			right = temp_0->childs[location + 1];//�õ����ֵ�
			//if (r == 0)//�Ȳ��������
			location++;
			y->key_number++;//y����Ů������ǰ��һ
			y->key[y->key_number] = temp_0->key[location]; //��������Ӧ�ؼ��ּ��뵽y�Ĺؼ��ּ��ϵ����
			y->index[y->key_number] = temp_0->index[location];
			//cout << endl << "*" << y->key[y->keynum] << "*" << endl;
			y->childs[y->key_number] = right->childs[0]; //�����ֵ�����һ��ָ��
			right->key_number = y->key_number + right->key_number;//�ϲ���ؼ��ֵĸ���
			for (j = 1;j <= right->key_number;++j)//��y���ֵܣ�right���Ĺؼ��ֺ�ָ�����ƣ�������y�ĺ����Ǻ͹ؼ����ǵļ���ֱ��ڳ�y->keynum���ͣ�y->keynum+1������λ�á�
			{
				right->key[y->key_number + j] = right->key[j];
				right->index[y->key_number + j] = right->index[j];
				right->childs[y->key_number + j] = right->childs[j];
			}
			for (j = 1;j <= y->key_number;++j)//�����y�йؼ��ֺ�ָ���Ƶ�y���ֵ�
			{
				right->key[j] = y->key[j];
				right->index[j] = y->index[j];
				right->childs[j] = y->childs[j];
			}
			right->childs[0] = y->childs[0];//�����ѭ��ִֻ����y->keynum�Σ����Է��ֻ���һ��y->childs[0]δ�ƶ����������ǽ�y->childs[0]Ҳ�ƶ���right->childs[0]��
			if (y->childs[0])//�޸�y�ĺ��ӵĸ����ָ�룬�������һ������
			{
				for (j = 0;j < y->key_number;j++) {//
					if (y->childs[j])//
						y->childs[j]->parent = right;
					else {}//���򱾴�ѭ��ʲôҲ������
				}
			}
			else {}//����yû�к��ӣ�ʲôҲ����
			temp_0->childs[location - 1] = right;//ע��֮ǰlocation��һ�ˣ�Ҳ����ʱ��temp_0->pchilds[location-1]==y��
			for (j = location;j < temp_0->key_number;++j)//��������йؼ��ֺ�ָ������
			{
				temp_0->key[j] = temp_0->key[j + 1];
				temp_0->index[j] = temp_0->index[j + 1];
				temp_0->childs[j] = temp_0->childs[j + 1];
			}
			temp_0->key_number--;//�����Ĺؼ��ָ�����1
			delete_help = y;
			delete delete_help;
			delete_help = nullptr;
			y = right;
		}
		/**/
		temp_0 = temp_0->parent;//temp_0����,��Ҫ��鿴�ϲ㣬��Ϊ����һ���ϲ���Ҳ��ԭtemp_0�Ĺؼ��ָ�������̫���ˣ���Ҫ�������ֵܽ���ߺ������ֵܺϲ���
		if (y->parent->key_number >= (m - 1) / 2 || (temp_0 == nullptr && y->parent->key_number > 0)) {//�����y�ĸ��ڵ�Ĺؼ��ָ��������� ���� ��y�ĸ�����Ǹ������Ҹ����Ĺؼ��ָ���>1��ʱ����˵������Ҫ�����ˡ�
			finished = 1;//����λ��1
		}
		else if (temp_0 == nullptr) //��ʱ�����if���������������Ǹ����Ϊ���ˣ�ע���ʱΪ�գ���˵����ǰ���������ֻ���������ӣ��ֱ��ǣ�left��y�����ߣ�y��right����������yû�ˣ�ֻʣ��left �� right��y�ĺ���Ҳ������left������right����ȥ����left������right��Ҳ��˳����±�����µĸ���㡿������ɾ���ø���㣬���߼�1
		{
			delete_help = BTree_Node_root;
			BTree_Node_root = y; //�µĸ���㵮��
			delete delete_help;
			delete_help = nullptr;
			finished = 1;//����λ��1
		}
		else {//�����������ֻ����y�ĸ����Ȳ��Ǹ���㣬Ҳû���㹻��Ĺؼ��֣����Ǽ���ѭ�����ϵ�����
			y = y->parent;//ע�⣺��ʱy��temp_0�ĺ��ӡ�
		}
	}
}
/******************************************************************************************************************/
/**************************************************��ӡ����********************************************************/
void BTree::print_page() {
	BTree_Node* temp_1 = BTree_Node_root;
	print(temp_1);
	//����������ģ�
};
void BTree::print(BTree_Node * y) {
	if (y == nullptr) {
		cout << "B tree does not exist";return;
	}
	bool have_child = false;
	cout << "[";
	for (int i = 1;i <= y->key_number;i++)
	{
		if (i == 1);
		else cout << " ";
		cout << y->key[i] << "*";//��ADD��
		cout << y->index[i]->Book_name;//��ADD��
	}
	cout << "]";
	for (int i = 0;i <= y->key_number;i++)
	{
		if (y->childs[i] != nullptr)
		{
			if (i == 0) cout << "<";
			else cout << ",";
			print(y->childs[i]);
			have_child = true;
		}
	}
	if (have_child) cout << ">";
};
void BTree::print_aoru_page()
{
	print_aoru(BTree_Node_root, 0);
};
void BTree::print_aoru(BTree_Node* y,const int height)
{
	if (y == nullptr)return;
	const int num = y->key_number;
	print_aoru(y->childs[0], height + 1);
	for (int i = 1; i <= num; ++i) {
		for (int j = 0; j < height; ++j) { cout << "  "; }
		cout << "---" << y->key[i] << endl;
		print_aoru(y->childs[i], height + 1);
	}
};
/******************************************************************************************************************/
/**************************************************���沿��********************************************************/
bool BTree::keep_exit()
{
	ofstream outFile("Library.txt", ios_base::out);
	if (!outFile) {
		cout << "����ʧ�ܣ������ԣ�" << endl;
		return false;
	}
	else {
		cout << "���ڱ���..." << endl;
		if (write(BTree_Node_root, outFile)) {
			cout << "����ɹ���" << endl;
			return true;
		}
		else {
			cout << "����ʧ�ܣ������ԣ�" << endl;
			return false;
		}
	}
};
bool BTree::write(BTree_Node* y,ofstream& outFile)
{
	char sign;//��־λ��$���飬%�����ģ�&��ԤԼ��
	Book* Book_temp = nullptr;
	Appointment* Appointment_temp = nullptr;
	Borrow* Borrow_temp = nullptr;
	/******/
	string Book_number_temp;//���
	string Book_name_temp;//����
	string Book_auther_temp;//����
	int Book_surplus_temp;//ʣ����
	int Book_total_temp;//�ܿ��
	/******/
	unsigned long long Borrow_ID_temp;//���������֤��
	string Borrow_name_temp;//����������
	string Borrow_Book_number_temp;//�������
	string Borrow_Book_name_temp;//��������
	int Borrow_year_temp;
	int Borrow_month_temp;
	int Borrow_day_temp;
	/******/
	unsigned long long Appointment_ID_temp;//���֤
	string Appointment_name_temp;//ԤԼ��
	string Appointment_number_temp;//ԤԼ���
	string Appointment_Book_name_temp;//ԤԼ����
	int Appointment_year_temp;
	int Appointment_month_temp;
	int Apppointment_day_temp;
	/******/
	for (int i = 0;i <= y->key_number;++i) {
		if (y->childs[i] != nullptr) {
			write(y->childs[i], outFile);
		}
		else{}
		if (i < y->key_number) {
			Book_temp = y->index[i + 1];
			Appointment_temp = Book_temp->Appointment_index;
			Borrow_temp = Book_temp->Borrow_index;
			sign = '$';
			outFile << sign << endl;
			outFile << Book_temp->Book_number << endl;
			outFile << Book_temp->Book_name << endl;
			outFile << Book_temp->Book_auther << endl;
			outFile << Book_temp->Book_surplus << endl;
			outFile << Book_temp->Book_total << endl;
			cout << Book_temp->Book_name << endl;
			while (Borrow_temp != nullptr) {
				sign = '%';
				outFile << sign << endl;
				outFile << Borrow_temp->Borrow_ID << endl;
				outFile << Borrow_temp->Borrow_name << endl;
				outFile << Borrow_temp->Borrow_Book_number << endl;
				outFile << Borrow_temp->Borrow_Book_name << endl;
				outFile << Borrow_temp->Borrow_year << endl;
				outFile << Borrow_temp->Borrow_month << endl;
				outFile << Borrow_temp->Borrow_day << endl;
				Borrow_temp = Borrow_temp->next;
			}
			while (Appointment_temp != nullptr) {
				sign = '&';
				outFile << sign << endl;
				outFile << Appointment_temp->Appointment_ID << endl;
				outFile << Appointment_temp->Appointment_name << endl;
				outFile << Appointment_temp->Appointment_number << endl;
				outFile << Appointment_temp->Appointment_Book_name << endl;
				outFile << Appointment_temp->Appointment_year << endl;
				outFile << Appointment_temp->Appointment_month << endl;
				outFile << Appointment_temp->Apppointment_day << endl;
				Appointment_temp = Appointment_temp->next;
			}
		}
		else{}
	}
	return true;
};