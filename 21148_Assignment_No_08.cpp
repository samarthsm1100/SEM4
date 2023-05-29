#include <iostream>
using namespace std;

class Node
{
	char data;
	Node* left;
	Node* right;

	public:

	Node()
	{
	data=' ';
	left=right=NULL;
	}

	Node(char s)
	{
	data=s;
	left=right=NULL;
	}

	friend class OBST;
};

class OBST
{
	Node* root;
	float *p,*q;
	char *input;
	double **w,**c,**r;
	int n;

	public:

	OBST()
	{
		root=NULL;
		p=q=NULL;
		input=NULL;
		n=0;
	}

	void calculate_wt();
	Node* create_tree(int ,int);
	void inorder(Node* root);
	void preorder(Node* root);
	void postorder(Node* root);
	void displayMat();
	void getInfo();
	Node* getroot()
	{
	return root;
	}
};

void OBST::getInfo()
{

			input=new char[n+1];
			p=new float[n];
			q=new float[n+1];

			cout<<"Enter number of identifiers :";
			cin>>n;
			input[0]=' ';
			for(int i=1;i<n+1;i++){
				cout<<"I1"<<i<<" ";
				cin>>input[i];
			}
			cout<<"Enter Succesfull probability-->\n";
			for(int i=0;i<n;i++){
				cout<<"p"<<i<<" ";
				cin>>p[i];
			}
			cout<<"Enter Unsuccesfull probability-->\n";
			for(int i=0;i<n+1;i++){
				cout<<"q"<<i<<" ";
				cin>>q[i];
			}
			this->calculate_wt();

}

void OBST::displayMat()
{
	for(int i=0;i<n+1;i++)
	{
		for(int j=0;j<n+1;j++)
		{

				cout<<"("<<w[j][i]<<","<<c[j][i]<<","<<r[j][i]<<") ";
		}
		cout<<endl;
	}
}
void OBST::calculate_wt()
{
 w=new double*[n+1];
 c=new double*[n+1];
 r=new double*[n+1];
for(int i=0;i<n+1;i++)
{
	w[i]=new double[n+1];
	c[i]=new double[n+1];
	r[i]=new double[n+1];
}

for(int i=0;i<n;i++)
{
	//for diagonal elements
	w[i][i]=q[i];
	r[i][i]=c[i][i]=0;

	//just above diagonal
	w[i][i+1]=q[i]+q[i+1]+p[i];
	r[i][i+1]=i+1;
	c[i][i+1]=w[i][i+1];
}
///edge case
w[n][n]=q[n];
r[n][n]=c[n][n]=0;
for(int m=2;m<=n;m++)
{
	for(int i=0;i<=n-m;i++)
	{
		double min=999;
		int j=i+m;
		int k=0;
		w[i][j]=w[i][j-1]+p[j-1]+q[j];
		for(int i1=i+1;i1<=j;i1++)
		{
			double sum=c[i][i1-1]+c[i1][j];
			if(sum<min)
			{
				min=sum;
				k=i1;
			}
		}
		c[i][j]=w[i][j]+c[i][k-1]+c[k][j];
		r[i][j]=k;
	}
}
//	displayMat(w,c,r);
	root=create_tree(0,n);
};



Node* OBST::create_tree(int i,int j)
{
if(i!=j)
{
	int k=r[i][j];
	Node* nn=new Node(input[k]);
	nn->left=create_tree(i,k-1);
	nn->right=create_tree(k,j);
	return nn;
}
else
{
	return NULL;
}
}

void OBST::inorder(Node* root)
{
if(root!=NULL)
{
inorder(root->left);
cout<<root->data<<" ";
inorder(root->right);
}
}

void OBST::preorder(Node* root)
{
if(root!=NULL)
{
cout<<root->data<<" ";
preorder(root->left);
preorder(root->right);
}
}

void OBST::postorder(Node* root)
{
if(root!=NULL)
{
postorder(root->left);
postorder(root->right);
cout<<root->data<<" ";
}
}

int main()
{
//	string input[]={" ","a1","a2","a3"};
//	double p[]={0.4, 0.1, 0.2};
//	double q[]={0.1, 0.04, 0.09, 0.07};
	OBST obj;
	obj.getInfo();
	while(true){
		int option,num;

		obj.calculate_wt();
		cout<<"\n1.Inorder\n2.Preoder\n3.Postorder\n4.Display Mat\nExit\nChose an option:";
		cin>>option;
		if(option==1){
			obj.inorder(obj.getroot());
			cout<<endl;
		}
		else if(option==2){
			obj.preorder(obj.getroot());
			cout<<endl;
		}
		else if(option==3){
			obj.postorder(obj.getroot());
			cout<<endl;
		}
		else if(option==4){
			obj.displayMat();
		}
		else{
			cout<<"\n-----------THANK YOU !!!!----------\n";
			break;
		}

	}

	return 0;
}
