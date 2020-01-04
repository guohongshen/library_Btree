#include"Btree.h"

BTree::BTree() {//BTree构造函数
	BTree_Node_root = new BTree_Node;
	answer.tag = -1;
};
/******************************************************************************************************************/
/**************************************************搜索部分********************************************************/
int BTree::search_location(string& x, BTree_Node*& y) {
	int i = 1;
	while (i <= y->key_number && x > y->key[i]) {
		i++;
	}
	return i;
};
void BTree::search(string& x) {//搜索函数
//功能如下：
//在书索引B树上查找关键字x，用answer返回(got,i,tag)；
//若查找成功，则标记tag=1，指针got所指结点中第i个关键字等于x；
//否则tag=0，若要插入关键字为x的记录，应位于got结点中第i-1个和第i个关键字之间。
	int i = 1, found = 0;
	BTree_Node* temp_1 = BTree_Node_root;
	BTree_Node* pr_temp_1 = nullptr;//初始，temp_1指向根节点并将用于指向待查找结点，pr_temp_1指向其双亲
	while (temp_1 != nullptr && found == 0) {//当(查找指针不为空∧未找到相关结点)时
		i = search_location(x, temp_1);
		if (i <= temp_1->key_number && temp_1->key[i] == x)//如果找到
			found = 1;
		else {
			pr_temp_1 = temp_1;
			temp_1 = temp_1->childs[i - 1];
		}//往下走
	}
	if (found == 1) {//查找成功，返回temp_1及它中x的位置i
		answer = { temp_1,i,1 };
		return;
	}
	else {//查找不成功，返回x的插入位置pr_temp_1及i（此时temp_1==nullptr∧pr_temp_1==发出temp_1的结点）
		answer = { pr_temp_1,i,0 };
		return;
	}
};
Book* BTree::search_return_index(string& x)
{
	int i = 1, found = 0;
	BTree_Node* temp_1 = BTree_Node_root;
	BTree_Node* pr_temp_1 = nullptr;//初始，temp_1指向根节点并将用于指向待查找结点，pr_temp_1指向其双亲
	while (temp_1 != nullptr && found == 0) {//当(查找指针不为空∧未找到相关结点)时
		i = search_location(x, temp_1);
		if (i <= temp_1->key_number && temp_1->key[i] == x)//如果找到
			found = 1;
		else {
			pr_temp_1 = temp_1;
			temp_1 = temp_1->childs[i - 1];
		}//往下走
	}
	if (found == 1) {//查找成功，返回地址。
		return temp_1->index[i];
	}
	else {//查找不成功，返回地址为空。
		return nullptr;
	}
};
/******************************************************************************************************************/
/**************************************************插入部分********************************************************/
void BTree::insert_page0(string x, Book* y) {//插入（x，y）元组，即：x作关键词，y做（搜索索引成功后可以得到的）地址。
	search(x);//先查找
	if (answer.tag == 0)//可以插入
	{
		insert_page_1(x, answer.got, answer.i, y);//于是准备插入
	}
	else {
		return;
	}
};
void BTree::produce_new_root(BTree_Node* y, string x, BTree_Node* v, Book* book) {//生成新的根结点:y根v
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
void BTree::insert_page_2(BTree_Node * &y, int z, string & x, BTree_Node * v, Book* book) {//关键字x和新结点指针v分别插到y->key[z]和y->childs[z]（childs[z]应该也可以，不过需要注意一下）
	for (int j = y->key_number;j >= z;j--) {
		y->key[j + 1] = y->key[j];
		y->index[j + 1] = y->index[j];//【ADD it recetly】
		y->childs[j + 1] = y->childs[j];
	}//依次往后挪，结束之后y->key[i]，y->childs[i]和y->index[i]就腾出来了。
	y->key[z] = x;
	y->index[z] = book;//【ADD it recently】
	y->childs[z] = v;//然后对[i]赋值

	if (v != nullptr)
		v->parent = y;
	y->key_number++;//
}
void BTree::insert_split(BTree_Node * &y, int center, BTree_Node * &z) {//将y结点分裂成两个结点，前一半保留在原结点，后一半移入z所指新结点。也即：将y分裂为y和z两个。
	int n = y->key_number;//j：循环的时候使用；n：循环的时候使用，限定循环次数。
	z = new BTree_Node;//生成新结点，下面安排分家问题
	//cout << "new了";
	z->childs[0] = y->childs[center];//中心关键字右侧的孩子，该孩子的所有子女的关键字都比key[center]大
	for (int i = center + 1, j = 1;i <= n;i++, j++) {//将y的后一半孩子们移入z结点。注：j：z孩子们的下标；i：y的孩子们的下标。
		z->key[j] = y->key[i];
		z->index[j] = y->index[i];//【ADD it recently】
		z->childs[j] = y->childs[i];
	}
	z->key_number = n - center;//当前关键字的个数
	z->parent = y->parent;//此时z和y的父亲应该相同，所以需要将z的父结点改为y->parent
	y->key_number = center - 1;//y的关键字个数相应减少
	for (int i = 0;i <= n - center;i++)//z得到的孩子们的父结点目前还是y，需要把它们的父结点改为z
		if (z->childs[i] != NULL)
			z->childs[i]->parent = z;
};
void BTree::insert_page_1(string & x, BTree_Node * &y, int z,Book* book) {//【CORRECT】
	//在B树中y结点的key[z-1]和key[z]之间插入关键字x
	//若插入后结点关键字个数等于b树的阶，则沿着双亲指针链进行结点分裂，使得t仍是m阶B树//!!!!!!！！！！！！！！！！！！！！！！！！！注释中的‘t’需要改正
	string x_temp_1 = x;//临时储存x的值，以防丢失
	Book* book_temp_1 = book;//临时储存book的值，以防丢失
	int center;//分裂时的中间关键字数组的下标
	int finished = 0;//是否插入完成的标志，1：插入完成；0：未完成
	int needNewRoot = 0;//需不需要建立新的根结点，1：需要；0：不需要
	BTree_Node* temp_1;
	if (y == nullptr)//
		produce_new_root(nullptr, x_temp_1, nullptr, book_temp_1);
	else {
		x_temp_1 = x;//拿到x的值
		book_temp_1 = book;
		temp_1 = nullptr;//为temp_1分配内存
		while (needNewRoot == 0 && finished == 0) {
			insert_page_2(y, z, x_temp_1, temp_1, book_temp_1);//将x和temp_1分别插到y->key[i]和y->childs[i]//【ADD 一个参数v】
			if (y->key_number < m)
				finished = 1;//安全，插入完成
			else {//key_number达到最大值，需要调整
				center = (m + 1) / 2;
				insert_split(y, center, temp_1);
				x_temp_1 = y->key[center];//该结点需要升级进入y的父结点中
				book_temp_1 = y->index[center];//同上
				if (y->parent != nullptr) {
					y = y->parent;//更迭到y的父亲
					z = search_location(x_temp_1, y);//在父结点中查找x的插入位置，然后继续循环即可。
				}
				else needNewRoot = 1;//看来需要建立新的父结点
			}
		}
		if (needNewRoot == 1)
			produce_new_root(y, x_temp_1, temp_1, book_temp_1);//建立新的根结点
	}
};
/******************************************************************************************************************/
/**************************************************删除部分********************************************************/
void BTree::delete_page00(string x) {
	search(x);//search(string& x)，参数为引用。
	if (answer.tag)//如果找到
	{
		delete_page1(answer.got, answer.i);//删除
		cout << "此书清空成功！";
		print_page();//打印供用户查看。
	}
	else {//没找到
		cout << "此书不存在！请重试";
		return;
	}
};
void BTree::delete_page0() {
	string temp;
	cout << "请输入需要清库的书号：";
	cin >> temp;
	search(temp);//search(string& x)，参数为引用。
	if (answer.tag)//如果找到
	{
		delete_page1(answer.got, answer.i);//删除
		cout << "清库成功！";
		print_page();//打印供用户查看。
	}
	else {//没找到
		cout << "此书不存在！";
		return;
	}
};
void BTree::delete_page1(BTree_Node * &y, int i) {
	if (y->childs[i] != nullptr) {//若不是在最下层非终端结点，则删除需要做如下工作：
		delete_successor(y, i);//在子树中找出最下层非终端结点的最小关键字替代ki
		delete_remove(y, 1);//对最下层非终端结点的处理（移动）
		delete_restore(y);//调整B树,y：刚刚移动过关键字的结点（删除了最小的关键字，后面的关键字依次前补），如果此时y的关键字个数小于（m-1）/2，则需要调整，否则不需要调整。
	}
	else {//若是最下层非终端结点，则需要做如下工作：
		delete_remove(y, i);//对最下层非终端结点的处理（移动）
		if (y->key_number < (m - 1) / 2)//如果删除后关键字个数小于(m-1)/2（注意：[取上整(m/2)-1]=={取下整[(m-1)/2]}），就需要调整。否则不需要调整。
			delete_restore(y);//调整B树,y：刚刚移动过关键字的结点（删除了最小的关键字，后面的关键字依次前补），此时y的关键字个数小于（m-1）/2，需要调整。
	}
};
void BTree::delete_successor(BTree_Node * &y, int i) {//由后继最下层非终端结点的最小关键字代替结点中关键字key[i]
	BTree_Node* temp = y->childs[i];//temp：拿到y的值，再用来遍历y的最小孩子的最小孩子......
	while (temp->childs[0] != nullptr) {//直到寻找到最小的关键字
		temp = temp->childs[0];
	}
	y->key[i] = temp->key[1];
	y->index[i] = temp->index[1];
	y = temp;//更新y的值，此时y指向原y的第i个孩子中最小的关键字所在的结点。
};
void BTree::delete_remove(BTree_Node * &y, int i)//删除处于关键字集合边缘的关键字：分两种情况，但是处理的代码却是一样的。
{
	int j;//循环体需要使用
	int n = y->key_number;//拿到需要的值
	for (j = i;j < n;j++) {//移动操作：循环执行（n-i）=（m-1-（i-1））次
		y->key[j] = y->key[j + 1];//移动
		y->index[j] = y->index[j + 1];
		y->childs[j] = y->childs[j + 1];//移动
	}
	y->key_number--;//关键字数量相应减一，此时的y指向关键字移动过的结点（函数参数里的y是引用）。
};
void BTree::delete_restore(BTree_Node * &y) {//功能：由于刚刚对y做过最小关键字删除，此时关键字个数不足，B树需要调整。
	int j;//用于循环的重要变量，如关键字、孩子指针的右移、左移等等。
	BTree_Node* temp_0 = y->parent;//temp_0：y的父结点
	if (temp_0 == nullptr) //【原注释：（若调整后出现空的根结点，则删除该根结点，树高减1。)现注释：（如果temp_0为空，就只能说明之前是对根结点进行删除的，而对根结点进行删除就只有一种情况，那就是这个B树就只剩根结点了。那就不用担心了，只有一个根结点的B树的根结点的关键字个数可以为空。）】
	{
		BTree_Node_root = y;
		y = y->parent;
		return;
	}
	BTree_Node* left;//左兄弟
	BTree_Node* right;//右兄弟
	BTree_Node* delete_help;//辅助删除指针
	int finished = 0;//判断是否调整结束：0—>没结束；1—>结束了
	int location = 0;//查找y位于y的父结点中的位置（temp_0->childs[location]==y）
	while (!finished)//没结束（0），就继续循环
	{
		location = 0;
		while (temp_0->childs[location] != y) {
			location++; //确定y在temp_0子树中的位置:temp_0->childs[location]==y。
		}
		if (location == 0)//第一个孩子
		{
			location++;
			left = nullptr;
			right = temp_0->childs[location];//拿到右兄弟
		}
		else if (location == temp_0->key_number)//最后一个孩子
		{
			right = nullptr;
			left = temp_0->childs[location - 1];//拿到左兄弟
		}
		else//中间孩子
		{
			left = temp_0->childs[location - 1];
			right = temp_0->childs[location + 1];//左右兄弟都拿到
		}
		/**下面是判断可不可以借的情况（如果可以就借）：**/
		if (location > 0 && left != nullptr && (left->key_number > (m - 1) / 2))//此时可以向左兄弟借关键字
		{
			y->key_number++;//y的孩子个数提前增加，为下面的右移作铺垫：
			for (j = y->key_number;j > 1;j--)//结点关键字右移
			{
				y->key[j] = y->key[j - 1];
				y->index[j] = y->index[j - 1];
				y->childs[j] = y->childs[j - 1];
			}
			y->key[1] = temp_0->key[location];//父结点的中间关键字（两边是left和y）插入到结点y
			y->index[1] = temp_0->index[location];
			y->childs[1] = y->childs[0];//把相关的子女也右移
			y->childs[0] = left->childs[left->key_number];//加入新的孩子（即：left的最后一个孩子）
			if (y->childs[0] != nullptr)//如果新加入的孩子不为空，就修改y中的孩子的父结点为y。
			{
				y->childs[0]->parent = y;
			}
			temp_0->key[location] = left->key[left->key_number];//左兄弟上的最右端的关键字移到父亲位置
			temp_0->index[location] = left->index[left->key_number];
			left->key_number--;//左兄弟的关键字个数减少
			finished = 1;//结束位置1
			break;//结束调整
		}
		else if (location < temp_0->key_number && right != nullptr && (right->key_number > (m - 1) / 2))//上面的左兄弟没有足够多的关键字的话，就尝试向右兄弟借关键字，如果可以借，就进行如下else if的操作。
		{
			y->key_number++;
			y->key[y->key_number] = temp_0->key[location + 1]; //父结点的中间关键字插入到结点y的最后【注意此处：原先是y->key[y->keynum] = temp_0->key[location]，现改为y->key[y->keynum] = temp_0->key[location+1]】
			y->index[y->key_number] = temp_0->index[location + 1];
			y->childs[y->key_number] = right->childs[0];//加入新的孩子到最后
			if (y->childs[y->key_number] != nullptr) {//修改y中的子女的父结点为y
				y->childs[y->key_number]->parent = y;
			}
			else {}//
			temp_0->key[location + 1] = right->key[1];//右兄弟上的头一个关键字移到父结点的相应位置【注意此处原先是：temp_0->key[location] = right->key[1]，现改为temp_0->key[location+1] = right->key[1]】
			temp_0->index[location + 1] = right->index[1];
			right->childs[0] = right->childs[1];//为啥要写在外面是因为下面的循环顾不上它，所以提前特殊处理了。
			right->index[0] = right->index[1];
			for (j = 1;j < right->key_number;j++)//右兄弟结点关键字左移
			{
				right->key[j] = right->key[j + 1];
				right->index[j] = right->index[j + 1];
				right->childs[j] = right->childs[j + 1];
			}
			right->key_number--;//右兄弟的关键字个数减少
			finished = 1;//结束位置1
			break;//结束调整
		}
		else {//借不到，那么就为合并做准备：
			location = 0;//前面的涉及到location的加减，所以此处需要重新定位【后期此处需要完善以下】
			/*下面是合并*/
			while (temp_0->childs[location] != y) {//重新确定y在temp_0子树的位置
				location++;
			}
		}
		/**下面是准备合并的情况：**/
		if (location > 0 && (temp_0->childs[location - 1]->key_number <= (m - 1) / 2)) //当（左兄弟存在）并且（左兄弟的子女也不多）时，y与左兄弟合并。
		{
			left = temp_0->childs[location - 1];//拿到左兄弟
			y->key_number++;//y的子女数量加一，所以下面的右移开始处是：j=y->key_number
			for (j = y->key_number;j > 1;--j)//将y结点关键字和指针右移1位
			{
				y->key[j] = y->key[j - 1];
				y->index[j] = y->index[j - 1];
				y->childs[j] = y->childs[j - 1];
			}
			y->key[1] = temp_0->key[location];//父结点的相应关键字变成y的头一个关键字
			y->index[1] = temp_0->index[location];
			y->childs[1] = y->childs[0];//最后一个子女也右移，这个子女所包含的关键字们是大于刚刚加入进来的来自父结点的关键字（位于前驱语句）的。
			for (j = 1;j <= y->key_number;++j) //将结点y中关键字和指针移到left中
			{
				left->key[left->key_number + j] = y->key[j];
				left->index[left->key_number + j] = y->index[j];
				left->childs[left->key_number + j] = y->childs[j];
			}
			if (y->childs[0])//在上面的处理中y->childs[0]就没有改变过，所以它的值就是原来的值。如果y->childs[0]不为空，那就标志着y有孩子，于是修改y中的子女的父结点为left；否则，y就没有孩子，也就不存在修改y的孩子的父结点的事了。
			{
				for (j = 1;j <= y->key_number;++j)
					if (left->childs[y->key_number + j])//此处依然要判断，因为y有孩子并不代表孩子个数就等于关键字个数。
						left->childs[y->key_number + j]->parent = left;//修改
					else {}//否则本次循环什么也不做
			}
			left->key_number = left->key_number + y->key_number;//合并后关键字的个数
			temp_0->childs[location] = left;//y被踢出B树了
			for (j = location;j < temp_0->key_number;j++)//将父结点中关键字和指针左移
			{
				temp_0->key[j] = temp_0->key[j + 1];
				temp_0->index[j] = temp_0->index[j + 1];
				temp_0->childs[j] = temp_0->childs[j + 1];
			}
			temp_0->key_number--;
			delete y;
			y = left;
		}
		else //因为temp_0孩子总是成对存在（即：对于temp_0来说，任何一个不为空的孩子必有至少一个不为空的相邻兄弟），既然y都不为空了，那么y一定有至少一个相邻兄弟。于是：既然上面的左兄弟不存在，那么就只能和右兄弟合并了（此时右兄弟肯定是可以和y合并的）。
		{
			right = temp_0->childs[location + 1];//拿到右兄弟
			//if (r == 0)//先不考虑这个
			location++;
			y->key_number++;//y的子女个数提前加一
			y->key[y->key_number] = temp_0->key[location]; //父结点的相应关键字加入到y的关键字集合的最后
			y->index[y->key_number] = temp_0->index[location];
			//cout << endl << "*" << y->key[y->keynum] << "*" << endl;
			y->childs[y->key_number] = right->childs[0]; //从右兄弟左移一个指针
			right->key_number = y->key_number + right->key_number;//合并后关键字的个数
			for (j = 1;j <= right->key_number;++j)//将y右兄弟（right）的关键字和指针右移，给将来y的孩子们和关键字们的加入分别腾出y->keynum个和（y->keynum+1）个空位置。
			{
				right->key[y->key_number + j] = right->key[j];
				right->index[y->key_number + j] = right->index[j];
				right->childs[y->key_number + j] = right->childs[j];
			}
			for (j = 1;j <= y->key_number;++j)//将结点y中关键字和指针移到y右兄弟
			{
				right->key[j] = y->key[j];
				right->index[j] = y->index[j];
				right->childs[j] = y->childs[j];
			}
			right->childs[0] = y->childs[0];//上面的循环只执行了y->keynum次，可以发现还有一个y->childs[0]未移动进来，于是将y->childs[0]也移动到right->childs[0]。
			if (y->childs[0])//修改y的孩子的父结点指针，和上面的一样道理。
			{
				for (j = 0;j < y->key_number;j++) {//
					if (y->childs[j])//
						y->childs[j]->parent = right;
					else {}//否则本次循环什么也不做。
				}
			}
			else {}//否则（y没有孩子）什么也不做
			temp_0->childs[location - 1] = right;//注意之前location加一了，也即此时：temp_0->pchilds[location-1]==y。
			for (j = location;j < temp_0->key_number;++j)//将父结点中关键字和指针左移
			{
				temp_0->key[j] = temp_0->key[j + 1];
				temp_0->index[j] = temp_0->index[j + 1];
				temp_0->childs[j] = temp_0->childs[j + 1];
			}
			temp_0->key_number--;//父结点的关键字个数减1
			delete_help = y;
			delete delete_help;
			delete_help = nullptr;
			y = right;
		}
		/**/
		temp_0 = temp_0->parent;//temp_0更新,需要向查看上层，因为经过一番合并，也即原temp_0的关键字个数可能太少了，需要向它的兄弟借或者和它的兄弟合并。
		if (y->parent->key_number >= (m - 1) / 2 || (temp_0 == nullptr && y->parent->key_number > 0)) {//如果（y的父节点的关键字个数还够） 或者 （y的父结点是根结点而且根结点的关键字个数>1）时，就说明不需要调整了。
			finished = 1;//结束位置1
		}
		else if (temp_0 == nullptr) //此时上面的if不成立，很明显是根结点为空了（注意此时为空，就说明以前：【根结点只有两个孩子，分别是（left和y）或者（y和right），而现在y没了，只剩了left 和 right，y的孩子也尽数被left（或者right）掠去，那left（或者right）也就顺理成章变成了新的根结点】）。则删除该根结点，树高减1
		{
			delete_help = BTree_Node_root;
			BTree_Node_root = y; //新的根结点诞生
			delete delete_help;
			delete_help = nullptr;
			finished = 1;//结束位置1
		}
		else {//如果都不是那只能是y的父结点既不是根结点，也没有足够多的关键字，于是继续循环往上调整。
			y = y->parent;//注意：此时y是temp_0的孩子。
		}
	}
}
/******************************************************************************************************************/
/**************************************************打印部分********************************************************/
void BTree::print_page() {
	BTree_Node* temp_1 = BTree_Node_root;
	print(temp_1);
	//以下是增添的：
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
		cout << y->key[i] << "*";//【ADD】
		cout << y->index[i]->Book_name;//【ADD】
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
/**************************************************保存部分********************************************************/
bool BTree::keep_exit()
{
	ofstream outFile("Library.txt", ios_base::out);
	if (!outFile) {
		cout << "保存失败，请重试！" << endl;
		return false;
	}
	else {
		cout << "正在保存..." << endl;
		if (write(BTree_Node_root, outFile)) {
			cout << "保存成功！" << endl;
			return true;
		}
		else {
			cout << "保存失败，请重试！" << endl;
			return false;
		}
	}
};
bool BTree::write(BTree_Node* y,ofstream& outFile)
{
	char sign;//标志位【$：书，%：借阅，&：预约】
	Book* Book_temp = nullptr;
	Appointment* Appointment_temp = nullptr;
	Borrow* Borrow_temp = nullptr;
	/******/
	string Book_number_temp;//书号
	string Book_name_temp;//书名
	string Book_auther_temp;//作者
	int Book_surplus_temp;//剩余量
	int Book_total_temp;//总库存
	/******/
	unsigned long long Borrow_ID_temp;//借书人身份证号
	string Borrow_name_temp;//借书人姓名
	string Borrow_Book_number_temp;//所借书号
	string Borrow_Book_name_temp;//所借书名
	int Borrow_year_temp;
	int Borrow_month_temp;
	int Borrow_day_temp;
	/******/
	unsigned long long Appointment_ID_temp;//身份证
	string Appointment_name_temp;//预约人
	string Appointment_number_temp;//预约书号
	string Appointment_Book_name_temp;//预约书名
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