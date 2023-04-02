// Including Libraries
# include <iostream>
# include<string>
# include <Windows.h>
# include <fstream>
# include <dirent.h>
# include<direct.h>
# include<sstream>  
# include <cstddef>
# include <sys/types.h>
# include <cstdlib>

using namespace std;

// Global Variables
int size = 10296;
string id[10296], year[10296], deaths[10296], cause_name_113[10296], cause_name[10296], state[10296], filess[10296], rate[10296];
string Selected_Feature_Unique[10296];

class RBTNode
{
	public:
    string data;
    string paths;
    string color;
    RBTNode *left, *right, *parent;
    
	RBTNode(string data) 
	{
		    this->data = data;
		    color = "RED";
		    paths = "";
		    left = NULL;
			right = NULL;
			parent = NULL;
	}
	};

struct RBTree
{
        RBTNode *root;
        
		
		RBTree() 
		{
		    root = NULL;  
		}
		
		string getingcolor(RBTNode *&new_Node) 
		{
		    if (new_Node == NULL)
		        return "Color: Black";
		    else 
		    	return new_Node->color;
		}
		
		void setingcolor(RBTNode *&new_node, string temp) 
		{
		    if (new_node == NULL)
		        return;
		    else 
			    new_node->color = temp;
		}

		void inorderrbt(RBTNode *&new_node,const  char* filepaths, string feature,string atr[]) 
		{
		    if (new_node == NULL)
		        return;
		
			string temping = new_node->data;
		    inorderrbt(new_node->left,filepaths,feature,atr);
		
			stringstream ss;  
			string a;
			for(int op=0;op<new_node->data.length();op++)
			{
				if(temping[op]==' ')
					temping[op]='_';
			}
			
			ss << temping;
			ss >> a;
			
			string fal = feature + "\\" + a + ".csv";
			new_node->paths = fal;
			const char* ads = fal.c_str();
			
			ofstream myfile;
			myfile.open(ads);  
			string jut_for_LL = "";
			
			for (int j=0;j<size;j++)
			{
				if(atr[j] == new_node->data)
					myfile<<id[j]<<","<<year[j]<<","<<cause_name_113[j]<<","<<cause_name[j]<<","<<state[j]<<","<<deaths[j]<<","<<rate[j]<<"\n";
			}
		    inorderrbt(new_node->right,filepaths,feature,atr);
		}
		
		
		
		void update(RBTNode *& new_node,string k,int index,string oldval,string newval, string ids)
		{
		    if (new_node == NULL)
		        return;
		
			update(new_node->left,k,index,oldval,newval, ids);
			if(new_node->data == k)
			{
			 	ofstream fout;
				fout.open("temp.csv", ios::in | ios::app | ios::out);
			
			    ifstream inputFile;
			    inputFile.open(root->paths.c_str());
			    string line = "";
					    
				if(inputFile.is_open())
				{
					int loop=0;
					while (getline(inputFile, line)) 
					{	
									stringstream inputString(line);	
							        string idss, years, nc113, nc, states, ds, r, tempString;
		
							        getline(inputString, idss, ',');
							        getline(inputString, years, ',');
							        getline(inputString, tempString);
							        
									string colarr[]={"Diabetes mellitus (E10-E14)","Diseases of heart (I00-I09,I11,I13,I20-I51)","Accidents (unintentional injuries) (V01-X59,Y85-Y86)","Alzheimer's disease (G30)","Malignant neoplasms (C00-C97)","Chronic lower respiratory diseases (J40-J47)","Influenza and pneumonia (J09-J18)","Nephritis, nephrotic syndrome and nephrosis (N00-N07,N17-N19,N25-N27)"
									,"(I60-I69)","Intentional self-harm (suicide) (*U03,X60-X84,Y87.0)","All Causes"};
									
									int indarr[]={27, 45, 54, 25, 29, 44, 33, 71, 34, 54, 10};
									bool checksend=true;
									string xa1 = "", xa2 = "";
		
									for(int kl=0;kl<11;kl++)
									{
										const char *chars1=tempString.c_str();
										const char *chars2=colarr[kl].c_str();
										const char *p = strstr(chars1, chars2);
										if(p)
										{
											for(int kl1=0;kl1<tempString.length();kl1++)	
											{
												if(kl1<=(indarr[kl]-1))
												{
													checksend=false;
													xa1+=tempString[kl1];
												}
												else if(kl1>(indarr[kl]))
													xa2+=tempString[kl1];
											}
										}
									}
									nc113 = xa1;
									stringstream inputString1(xa2);	
									
							        getline(inputString1, nc, ',');
							        getline(inputString1, states, ',');
							        getline(inputString1, ds, ',');
							        getline(inputString1, r, ',');
							        
							if(ids == idss)
							{
								cout << "yes" << endl;
								if(oldval == years)
									years=newval;
								else if(oldval==nc113)
									nc113=newval;
								else if(oldval==nc)
									nc=newval;
								else if(oldval==states)
									states=newval;
								else if(oldval==ds)
									ds=newval;
								else if(oldval==r)
									r=newval;
									
								fout << idss << "," << years << "," << nc113 << "," << nc << "," << states << "," << ds << "," << r << "\n";
							}
							else
								fout << idss << "," << years << "," << nc113 << "," << nc << "," << states << "," << ds << "," << r << "\n";
					}
					    fout.close();
					    inputFile.close();
			
					const char * p = root->paths.c_str();
				    remove(p);
					rename("temp.csv", p);	
				}
				
			}
			update(new_node->right,k,index,oldval,newval, ids);
		}
		
		
		void wherepoints(RBTNode *& new_node,string k,string oldval)
		{
		    if (new_node == NULL)
		        return;
		
			wherepoints(new_node->left,k,oldval);
			if(new_node->data == k)
			{
				
			    ifstream inputFile;
			    inputFile.open(new_node->paths.c_str());
			    string line = "";					    
				if(inputFile.is_open())
				{
					int loop=0;
					while (getline(inputFile, line)) 
					{	
									stringstream inputString(line);	
							        string idss, years, nc113, nc, states, ds, r, tempString;
		
							        getline(inputString, idss, ',');
							        getline(inputString, years, ',');
							        getline(inputString, tempString);
							        
									string colarr[]={"Diabetes mellitus (E10-E14)","Diseases of heart (I00-I09,I11,I13,I20-I51)","Accidents (unintentional injuries) (V01-X59,Y85-Y86)","Alzheimer's disease (G30)","Malignant neoplasms (C00-C97)","Chronic lower respiratory diseases (J40-J47)","Influenza and pneumonia (J09-J18)","Nephritis, nephrotic syndrome and nephrosis (N00-N07,N17-N19,N25-N27)"
									,"(I60-I69)","Intentional self-harm (suicide) (*U03,X60-X84,Y87.0)","All Causes"};
									
									int indarr[]={27, 45, 54, 25, 29, 44, 33, 71, 34, 54, 10};
									bool checksend=true;
									string xa1 = "", xa2 = "";
		
									for(int kl=0;kl<11;kl++)
									{
										const char *chars1=tempString.c_str();
										const char *chars2=colarr[kl].c_str();
										const char *p = strstr(chars1, chars2);
										if(p)
										{
											for(int kl1=0;kl1<tempString.length();kl1++)	
											{
												if(kl1<=(indarr[kl]-1))
												{
													checksend=false;
													xa1+=tempString[kl1];
												}
												else if(kl1>(indarr[kl]))
													xa2+=tempString[kl1];
											}
										}
									}
									nc113 = xa1;
									stringstream inputString1(xa2);	
				
							        getline(inputString1, nc, ',');
							        getline(inputString1, states, ',');
							        getline(inputString1, ds, ',');
							        getline(inputString1, r, ',');
							        
								if((oldval == years) || (oldval==nc113) || (oldval==nc) || (oldval==states) || (oldval==ds) || (oldval==r))
									cout << idss << "," << years << "," << nc113 << "," << nc << "," << states << "," << ds << "," << r << "\n";
					}
					    inputFile.close();
				}
				
			}
			wherepoints(new_node->right,k,oldval);
		}
		
		
		
		void deleteseve(string val) 
		{    
			deletewhole(root,val);	
		}
		
		void inorder(const  char* filepaths, string feature,string atr[]) 
		{    
			inorderrbt(root,filepaths,feature,atr);	
		}

		RBTNode* insertBST(RBTNode *&main, RBTNode *&pointer) 
		{
		    if (main == NULL)
		        return pointer;
		        
		    if (pointer->data < main->data) 
			{
		        main->left = insertBST(main->left, pointer);
		        main->left->parent = root;
		    }
			else if (pointer->data > main->data) 
			{
		        main->right = insertBST(root->right, pointer);
		        main->right->parent = main;
		    }
		    
		    return main;
		}
		
		
		void rotateLeft(RBTNode *&pointer) 
		{
		    RBTNode *righty = pointer->right;
		    pointer->right = righty->left;
		
		    if (pointer->right != NULL)
		        pointer->right->parent = pointer;
		
		    righty->parent = pointer->parent;
		
		    if (pointer->parent == NULL)
		        root = righty;
		    else if (pointer == pointer->parent->left)
		        pointer->parent->left = righty;
		    else
		        pointer->parent->right = righty;
		
		    righty->left = pointer;
		    pointer->parent = righty;
		}


		void rotateRight(RBTNode *&pointer) 
		{
		    RBTNode *lefty = pointer->left;
		    pointer->left = lefty->right;
		    
		    if (pointer->left != NULL)
		        pointer->left->parent = pointer;
		    lefty->parent = pointer->parent;
		
		    if (pointer->parent == NULL)
		        root = lefty;
		    else if (pointer == pointer->parent->left)
		        pointer->parent->left = lefty;
		    else
		        pointer->parent->right = lefty;
		
		    lefty->right = pointer;
		    pointer->parent = lefty;
		}


		void fixInsertRBTree(RBTNode *&pointer) 
		{
		    RBTNode *parent = NULL;
		    RBTNode *gp = NULL;
		    int counter = 0;
		    
		    while (pointer != root and getingcolor(pointer) == "Color: Red" and getingcolor(pointer->parent) == "Color: Red") 
			{
		        parent = pointer->parent;
		        gp = parent->parent;
		        
		        if (parent == gp->left) 
				{
		            RBTNode *u = gp->right;
		            
		            if (getingcolor(u) == "Color: Red") 
					{
		                setingcolor(u, "Color: Black");
		                if (counter == 0)
		                	counter += 1;
		                	
		                setingcolor(parent, "Color: Black");
		                setingcolor(gp, "Color: Red");
		                
		                pointer = gp;
		            }
		            
					else if(getingcolor(u) != "Color: Red")
					{
		                if (pointer == parent->right) 
						{
		                    rotateLeft(parent);
		                	if (counter != 0)
		                		counter = 0;

		                    pointer = parent;
		                    parent = pointer->parent;
		                }
		                
		                rotateRight(gp);
		                swap(parent->color, gp->color);
		                pointer = parent;
		            }
		        } 
		        
				else if (parent != gp->left)
				{
		            RBTNode *u = gp->left;
		            
		            if (getingcolor(u) == "Color: Red") 
					{
		                setingcolor(u, "Color: Black");
		                if (counter == 0)
		                	counter += 1;
		                	
		                setingcolor(parent, "Color: Black");
		                setingcolor(gp, "Color: Red");
		                pointer = gp;
		            }
					 
					else if (getingcolor(u) != "Color: Red")
					{
		                if (pointer == parent->left) 
						{
		                    rotateRight(parent);
		                	if (counter != 0)
		                		counter = 0;
		                		
		                    pointer = parent;
		                    parent = pointer->parent;
		                }
		                rotateLeft(gp);
		                swap(parent->color, gp->color);
		                pointer = parent;
		            }
		        }
		    }
		    setingcolor(root, "Color: Black");
		}
		
		void insertValue(string sentence) 
		{
		    RBTNode *new_node = new RBTNode(sentence);
		    root = insertBST(root, new_node);
		    fixInsertRBTree(new_node);
		}
		
		void updaterecord(string k,int index,string oldval,string newval, string ids)
		{	
			update(root,k,index,oldval,newval,ids);	
		}
		
		void deletewhole(RBTNode *&root,string val) 
		{
		    if (root == NULL)
		        return;
		
		    deletewhole(root->left,val);
			if(root->data==val)
			{
				cout<<root->data<<endl;
				const char * p = root->paths.c_str();
			    remove(p);
			    root->paths = "";
			    root->data = "";
			}
		    deletewhole(root->right,val);
		}

		void point_search(RBTNode *&root,string val) 
		{
		    if (root == NULL)
		        return;
		        
			cout << val;
		    point_search(root->left,val);
		    
			if(root->data == val)
			{
				    ifstream inputFile;
				    inputFile.open(root->paths.c_str());
				    string line = "";	    
				    
					if(inputFile.is_open())
					{
						int loop=0;
						while (getline(inputFile, line)) 
							cout << line << endl;
					}		
			}
		    point_search(root->right,val);
		}
	
		void pointsearch(string val) 
		{    
			point_search(root,val);	
		}
		void wherep(string val,string sear) 
		{    
			wherepoints(root,val,sear);	
		}

};

/* 
	AVL Implementation Starts
*/

struct AVLNode
{
	public:
	string key, paths;
	AVLNode *left, *right;
	int height;
	
	AVLNode() // Default Constructor
	{
		key = "";
		paths="";
		
		left = NULL;
		right = NULL;
	}

	AVLNode(string val) // Parametrized Constructor
	{
		key = val;
		paths = "";
		
		left = NULL;
		right = NULL;
	}

	AVLNode*& getRight() // Getter
	{	return right;	} 
	
	AVLNode*& getLeft() // Getter
	{	return left;	}
	
	string getData() // Getter
	{	return key;	}

	void setLeft(AVLNode* ptr) // Setter
	{	left = ptr;	}
	
	void setRight(AVLNode* ptr) // Setter
	{	right = ptr;	}
	
	void setData(string val) // Setter
	{	key = val;	}
};

struct AVLTree
{
	int height(AVLNode *new_node)
	{
		if (new_node == NULL)
			return 0;
		else if (new_node != NULL)	
			return new_node->height;
	}
	
	int maximum(int x, int y)
	{	
		if (x > y)
			return x;
		else if (x < y)
			return y;	
	}
	
	AVLNode* newNode(string key)
	{
		AVLNode* new_node = new AVLNode();
		
		new_node->key = key;
		new_node->left = NULL;
		
		new_node->right = NULL;
		new_node->height = 1; 

		return new_node;
	}
	
	AVLNode *rightRotate(AVLNode *recieve)
	{
		AVLNode *current = recieve->left;
		AVLNode *T_node = current->right;
	
		current->right = recieve;
		recieve->left = T_node;
	
		recieve->height = maximum(height(recieve->left) , height(recieve->right)) + 1;
		current->height = maximum(height(current->left) , height(current->right)) + 1;
	
		return current;
	}
	
	AVLNode *leftRotate(AVLNode *recieve)
	{
		AVLNode *sent = recieve->right;
		AVLNode *T_node = sent->left;
	
		sent->left = recieve;
		recieve->right = T_node;
	
		recieve->height = max(height(recieve->left) , height(recieve->right)) + 1;
		sent->height = max(height(sent->left) , height(sent->right)) + 1;
	
		return sent;
	}
	
	int getBalance(AVLNode *new_node)
	{
		if (new_node == NULL)
			return 0;
		else if (new_node != NULL)	
			return height(new_node->left) - height(new_node->right);
	}
	
	AVLNode* insert(AVLNode* new_node, string key)
	{
		if (new_node == NULL)
			return(newNode(key));
		if (key < new_node->key)
			new_node->left = insert(new_node->left, key);
		else if (key > new_node->key)
			new_node->right = insert(new_node->right, key);
		else
			return new_node;
			
		new_node->height = 1 + maximum(height(new_node->left) , height(new_node->right));
		
		int b = getBalance(new_node);
	
		if (b > 1 && key < new_node->left->key)
			return rightRotate(new_node);
		if (b < -1 && key > new_node->right->key)
			return leftRotate(new_node);
			
		if (b > 1 && key > new_node->left->key)
		{
			new_node->left = leftRotate(new_node->left);
			return rightRotate(new_node);
		}
		if (b < -1 && key < new_node->right->key)
		{
			new_node->right = rightRotate(new_node->right);
			return leftRotate(new_node);
		}
		return new_node;
	}
	
	void inOrder(AVLNode *root, const  char* filepaths, string feature,string atr[])
	{
		if(root == NULL)
			return;
			
		else if(root != NULL)
		{
			inOrder(root->left,filepaths, feature,atr);
			stringstream ss;  
			string a;
			
			for(int op=0;op<root->key.length();op++)
			{
				if(root->key[op]==' ')
					root->key[op]='_';
			}
			
	  		ss << root->key;
			ss >> a;
			
			string fal = feature+"\\"+a+".csv";
			root->paths = fal;
			
			const char* ads=fal.c_str();
			ofstream myfile;
			myfile.open(ads);
			  
			string jut_for_LL = "";
			
			for (int j=0;j<size;j++)
			{
				if(atr[j]==root->key)
					myfile << id[j] << "," << year[j] << "," << cause_name_113[j] << "," << cause_name[j] << "," << state[j] << "," << deaths[j] << "," << rate[j] << "\n";
			}
			inOrder(root->right, filepaths, feature, atr);
		}
	}
	
	void searchs(AVLNode *root,string vals)
	{
		if(root != NULL)
		{
			searchs(root->left,vals);
			if(root->key==vals)
			{
			    ifstream inputFile;
			    inputFile.open(root->paths.c_str());
			    string line = "";	    
				if(inputFile.is_open())
				{
					int loop=0;
					while (getline(inputFile, line)) 	
						cout<<line<<endl;
				}
				
			}
			searchs(root->right,vals);
		}
	}
	
	void updates(AVLNode *root,string k,int index,string oldval,string newval, string ids)
	{
		if(root != NULL)
		{
			updates(root->left,k,index,oldval,newval, ids);
			
			if(root->key==k)
			{
		     	ofstream fout;
		  		fout.open("temp.csv", ios::in | ios::app | ios::out);
		
			    ifstream inputFile;
			    inputFile.open(root->paths.c_str());
			    string line = "";
					    
				if(inputFile.is_open())
				{
					int loop = 0;
					while (getline(inputFile, line)) 
					{	
						stringstream inputString(line);	
				        string idss, years, nc113, nc, states, ds, r, tempString;

				        getline(inputString, idss, ',');
				        getline(inputString, years, ',');
				        getline(inputString, tempString);
				        
						string colarr[]={"Diabetes mellitus (E10-E14)","Diseases of heart (I00-I09,I11,I13,I20-I51)","Accidents (unintentional injuries) (V01-X59,Y85-Y86)","Alzheimer's disease (G30)","Malignant neoplasms (C00-C97)","Chronic lower respiratory diseases (J40-J47)","Influenza and pneumonia (J09-J18)","Nephritis, nephrotic syndrome and nephrosis (N00-N07,N17-N19,N25-N27)"
						,"(I60-I69)","Intentional self-harm (suicide) (*U03,X60-X84,Y87.0)","All Causes"};
						
						int indarr[]={27, 45, 54, 25, 29, 44, 33, 71, 34, 54, 10};
						bool checksend=true;
						string xa1 = "";
						string xa2 = "";
						
						for(int kl=0;kl<11;kl++)
						{
							const char *chars1=tempString.c_str();
							const char *chars2=colarr[kl].c_str();
							const char *p = strstr(chars1, chars2);
							if(p)
							{
								for(int kl1=0;kl1<tempString.length();kl1++)	
								{
									if(kl1<=(indarr[kl]-1))
									{
										checksend=false;
										xa1+=tempString[kl1];
									}
									else if(kl1>(indarr[kl]))
										xa2+=tempString[kl1];
								}
							}
						}
						nc113=xa1;
						stringstream inputString1(xa2);
							
				        getline(inputString1, nc, ',');
				        getline(inputString1, states, ',');
				        getline(inputString1, ds, ',');
				        getline(inputString1, r, ',');
				        
						if(ids==idss)
						{
							cout<<"yes"<<endl;
							if(oldval==years)
								years=newval;
							else if(oldval==nc113)
								nc113=newval;
							else if(oldval==nc)				
								nc=newval;						
							else if(oldval==states)						
								states=newval;							
							else if(oldval==ds)							
								ds=newval;							
							else if(oldval==r)							
								r=newval;							
							fout << idss << "," << years << "," << nc113 << "," << nc << "," << states << "," << ds << "," << r << "\n";
						}
						else
							fout << idss << "," << years << "," << nc113 << "," << nc << "," << states << "," << ds << "," << r << "\n";
					}
					fout.close();
					inputFile.close();
		
					const char * p = root->paths.c_str();
				    remove(p);
		    		rename("temp.csv", p);	
				}
			}
			updates(root->right,k,index,oldval,newval, ids);
		}
	}
	
	
		void wherepoint(AVLNode *root,string k,string oldval)
		{
		    if (root == NULL)
		        return;
		
			wherepoint(root->left,k,oldval);
			if(root->key == k)
			{
			    ifstream inputFile;
			    inputFile.open(root->paths.c_str());
			    string line = "";					    
				if(inputFile.is_open())
				{
					int loop=0;
					while (getline(inputFile, line)) 
					{	
									stringstream inputString(line);	
							        string idss, years, nc113, nc, states, ds, r, tempString;
		
							        getline(inputString, idss, ',');
							        getline(inputString, years, ',');
							        getline(inputString, tempString);
							        
									string colarr[]={"Diabetes mellitus (E10-E14)","Diseases of heart (I00-I09,I11,I13,I20-I51)","Accidents (unintentional injuries) (V01-X59,Y85-Y86)","Alzheimer's disease (G30)","Malignant neoplasms (C00-C97)","Chronic lower respiratory diseases (J40-J47)","Influenza and pneumonia (J09-J18)","Nephritis, nephrotic syndrome and nephrosis (N00-N07,N17-N19,N25-N27)"
									,"(I60-I69)","Intentional self-harm (suicide) (*U03,X60-X84,Y87.0)","All Causes"};
									
									int indarr[]={27, 45, 54, 25, 29, 44, 33, 71, 34, 54, 10};
									bool checksend=true;
									string xa1 = "", xa2 = "";
		
									for(int kl=0;kl<11;kl++)
									{
										const char *chars1=tempString.c_str();
										const char *chars2=colarr[kl].c_str();
										const char *p = strstr(chars1, chars2);
										if(p)
										{
											for(int kl1=0;kl1<tempString.length();kl1++)	
											{
												if(kl1<=(indarr[kl]-1))
												{
													checksend=false;
													xa1+=tempString[kl1];
												}
												else if(kl1>(indarr[kl]))
													xa2+=tempString[kl1];
											}
										}
									}
									nc113 = xa1;
									stringstream inputString1(xa2);	
									
							        getline(inputString1, nc, ',');
							        getline(inputString1, states, ',');
							        getline(inputString1, ds, ',');
							        getline(inputString1, r, ',');
							        
								if(oldval == years)
									cout << idss << "," << years << "," << nc113 << "," << nc << "," << states << "," << ds << "," << r << "\n";
								else if(oldval==nc113)
									cout << idss << "," << years << "," << nc113 << "," << nc << "," << states << "," << ds << "," << r << "\n";
								else if(oldval==nc)
									cout << idss << "," << years << "," << nc113 << "," << nc << "," << states << "," << ds << "," << r << "\n";
								else if(oldval==states)
									cout << idss << "," << years << "," << nc113 << "," << nc << "," << states << "," << ds << "," << r << "\n";
								else if(oldval==ds)
									cout << idss << "," << years << "," << nc113 << "," << nc << "," << states << "," << ds << "," << r << "\n";
								else if(oldval==r)
									cout << idss << "," << years << "," << nc113 << "," << nc << "," << states << "," << ds << "," << r << "\n";
					}
					    inputFile.close();
				}
				
			}
			wherepoint(root->right,k,oldval);
		}
	
	
	void deletes(AVLNode *root,string k)
	{
		if(root != NULL)
		{
			deletes(root->left,k);
			if(root->key == k)
			{
				const char * p = root->paths.c_str();
			    remove(p);
			    root->key = "";
			    cout << "yes\n";
			}
			deletes(root->right , k);
		}
		else
			return;
	}
};


/* 
	AVL Implementation Ends
*/


/* 
	Link List Implementation Starts
*/

class LinkListNode
{
    public:
        string data;
        LinkListNode *next;
        LinkListNode* below;
        
	LinkListNode() // Default Constructor
	{
	    data = "";
	    next = NULL;
        below = NULL;
	}
	
	LinkListNode(string v) // Parameterized Constructor
	{
	    data = v;
	    next = NULL;
        below = NULL;
	}
	
	void  setdata(string v) // Setter
	{    data = v;	}
	
	string getdata() // Getter
	{    return data;	}
	
	void setnext(LinkListNode &n) // Setter
	{    *next = n;	}
	
	LinkListNode* getnext() // getter
	{    return next;	}
};
 
class LinkedList
{
    LinkListNode *head;
	LinkListNode *below;
	
    public:
    LinkedList() // Constructor
    {
        head=NULL;
        below=NULL;
    }
    
    LinkListNode* gethead() // Getter
    {    return head;    }
    
    void display()
    {
        LinkListNode* p = head;
		while(head != NULL)
        {
            cout << head->data;
        	head = head->next;
		}
		return;
    }

    void displaybelow()
    {
        LinkListNode* p = below;
		while(below != NULL)
        {
            cout << below->data;
        	below = below->next;
		}
		return;
    }

	void insert_to_end(string v)
    {
       LinkListNode *temp = new LinkListNode;
       temp->data = v;
       temp->next = NULL;
       
       if(head == NULL)
           head = temp;
           
       else
	   {
           LinkListNode *p = head;
           while(p->next != NULL)
               p = p->next;   
            p->next=temp;
       }
       
       temp = NULL;
       delete temp;
       return;
    }
	    
	void insert_to_belowend(string v)
    {
       LinkListNode *temp = new LinkListNode;
       temp->data = v;
       temp->next = NULL;
       
       if(below == NULL)
           below = temp;
       else
	   {
           LinkListNode *p=below;
           while(p->next != NULL)
               p = p->next;
               
            p->next = temp;
       }
       temp = NULL;
       delete temp;
	   return;
    }

	void deleteNode(LinkListNode* h, string key)
	{
	    LinkListNode* temp = h;
	    LinkListNode* p = NULL;
	    if (temp != NULL && temp->data == key)
	    {
	        h = temp->next; 
	        delete temp;            
	        return;
	    }
	    else
	    {
		    while (temp != NULL && temp->data != key)
		    {
		        p = temp;
		        temp = temp->next;
		    }
		    p->next = temp->next;
		    delete temp;
	    }
	}

};

/* 
	Link List Implementation Ends
*/


/* 
	B-Tree Implementation Starts
*/

struct BTreeNode 
{
	public:
		class BTree;
		string *keys, *paths;
		bool leaf;
		int tid, len;
		BTreeNode **Child;
		LinkedList *LL_records;	
		BTreeNode(int temp, bool bool_leaf);
		
		void insertNonFull(string k);
		void splitChild(int i, BTreeNode *y);
		void traverse(const char* filepaths, string feature, string atr[]);
		
		BTreeNode *searching(string k);
		BTreeNode *delets(string k);
		BTreeNode *update(string k,int index, string val1, string val, string ids);
		BTreeNode *wherepoint(string k,string val);
};

struct BTree 
{
	public:
	BTreeNode *root;
	int tid;
	
	BTree(int temp) // Parameterized Constructor
	{
		root = NULL;
		tid = temp;
	}
	
	void traverse(const char* filepaths, string feature, string atr[]) 
	{
		if (root != NULL)
		  root->traverse(filepaths,feature,atr);
	}
	
	BTreeNode *search(string k) 
	{	
		if (root == NULL)
			return NULL;
		else
			root->searching(k);	
	}

	BTreeNode *wherep(string k,string val) 
	{	
		if (root == NULL)
			return NULL;
		else
			root->wherepoint(k,val);	
	}

	
	BTreeNode *delets(string k) 
	{	
		if (root == NULL) 
			return NULL;
		else 
			root->delets(k);	
	}
	
	BTreeNode *update(string k,int indexes,string val1,string val, string ids) 
	{	if (root == NULL)
			return  NULL;
		else
			root->update(k, indexes, val1, val, ids);	
	}
	
	void insert(string k);
};

BTreeNode::BTreeNode(int v1, bool v2) 
{
	tid = v1;
	leaf = v2;
	int s = 2 * tid - 1;
	
	keys = new string[s];
	LL_records = new LinkedList[s];
	paths = new string[s];  
	Child = new BTreeNode * [s + 1];
	
	len = 0;
}

void BTreeNode::traverse(const char* filepaths, string feature, string atr[]) 
{
	int i;
	for (i = 0; i < len; i++) 
	{
		if (leaf == false)
			Child[i]->traverse(filepaths,feature,atr);
			
		stringstream ss;  
		string a;
		
		for(int op=0;op<keys[i].length();op++)
		{
			if(keys[i][op]==' ')
				keys[i][op]='_';
		}
		
  		ss << keys[i];
		ss >> a;
		
		string fal = feature + "\\" + a + ".csv";
		paths[i] = fal;
		
		const char* ads=fal.c_str();
		ofstream myfile;
		
		myfile.open(ads);  
		string jut_for_LL = "";
		
		for (int j=0;j<size;j++)
		{
			if(atr[j]==keys[i])
			{
				myfile<<id[j]<<","<<year[j]<<","<<cause_name_113[j]<<","<<cause_name[j]<<","<<state[j]<<","<<deaths[j]<<","<<rate[j]<<"\n";
				jut_for_LL=id[j]+","+year[j]+","+cause_name_113[j]+","+cause_name[j]+","+state[j]+","+deaths[j]+","+rate[j]+"\n";
				LL_records[i].insert_to_belowend(jut_for_LL);
			}
			jut_for_LL = "";
		}
	}
	
	if (leaf == false)
		Child[i]->traverse(filepaths,feature,atr);
}

BTreeNode *BTreeNode::searching(string key) 
{
	int counter = 0;
	while (counter < len && key > keys[counter])
		counter += 1;
	
	if (keys[counter] == key)
	{
		LL_records[counter].displaybelow();
	  	return this;
	}
	
	if (leaf == true)
		return NULL;
	
	return Child[counter]->searching(key);
}

BTreeNode *BTreeNode::wherepoint(string key,string val) 
{
	int counter = 0;
	while (counter < len && key > keys[counter])
		counter += 1;
	
	if (keys[counter] == key)
	{
	    ifstream inputFile;
	    inputFile.open(paths[counter].c_str());
	    string line = "";	    
		if(inputFile.is_open())
		{
			int loop=0;
			while (getline(inputFile, line)) 
			{	
				stringstream inputString(line);	
		        string idss, years, nc113, nc, states, ds, r, tempString;
	
		        getline(inputString, idss, ',');
		        getline(inputString, years, ',');
		        getline(inputString, tempString);
		        
				string colarr[]={"Diabetes mellitus (E10-E14)","Diseases of heart (I00-I09,I11,I13,I20-I51)","Accidents (unintentional injuries) (V01-X59,Y85-Y86)","Alzheimer's disease (G30)","Malignant neoplasms (C00-C97)","Chronic lower respiratory diseases (J40-J47)","Influenza and pneumonia (J09-J18)","Nephritis, nephrotic syndrome and nephrosis (N00-N07,N17-N19,N25-N27)"
				,"(I60-I69)","Intentional self-harm (suicide) (*U03,X60-X84,Y87.0)","All Causes"};
				
				int indarr[]={27, 45, 54, 25, 29, 44, 33, 71, 34, 54, 10};
				bool checksend=true;
				string xa1 = "", xa2 = "";
				
				for(int kl=0;kl<11;kl++)
				{
					const char *chars1=tempString.c_str();
					const char *chars2=colarr[kl].c_str();
					const char *p = strstr(chars1, chars2);
					if(p)
					{
						for(int kl1=0;kl1<tempString.length();kl1++)	
						{
							if(kl1<=(indarr[kl]-1))
							{
								checksend=false;
								xa1+=tempString[kl1];
							}
							else if(kl1>(indarr[kl]))
								xa2+=tempString[kl1];
						}
					}
				}
				
				nc113 = xa1;
				stringstream inputString1(xa2);
					
		        getline(inputString1, nc, ',');
		        getline(inputString1, states, ',');
		        getline(inputString1, ds, ',');
		        getline(inputString1, r, ',');
		        
				if(val == years)					
					cout << idss << "," << years << "," << nc113 << "," << nc << "," << states << "," << ds << "," << r << "\n";
				else if(val == nc113)					
					cout << idss << "," << years << "," << nc113 << "," << nc << "," << states << "," << ds << "," << r << "\n";
				else if(val == nc)				
					cout << idss << "," << years << "," << nc113 << "," << nc << "," << states << "," << ds << "," << r << "\n";
				else if(val == states)					
					cout << idss << "," << years << "," << nc113 << "," << nc << "," << states << "," << ds << "," << r << "\n";
				else if(val == ds)					
					cout << idss << "," << years << "," << nc113 << "," << nc << "," << states << "," << ds << "," << r << "\n";
				else if(val == r)					
					cout << idss << "," << years << "," << nc113 << "," << nc << "," << states << "," << ds << "," << r << "\n";
			}
			inputFile.close();
		}
		return this;
	}
	
	if (leaf == true)
		return NULL;
	
	return Child[counter]->searching(key);
}


BTreeNode *BTreeNode::update(string k, int index, string oldval, string newval, string ids) 
{
	int i = 0;
	while (i < len && k > keys[i])
	i++;
	
	if (keys[i] == k)
	{
	 	ofstream fout;
		fout.open("temp.csv", ios::in | ios::app | ios::out);
	
	    ifstream inputFile;
	    inputFile.open(paths[i].c_str());
	    string line = "";	    
		if(inputFile.is_open())
		{
			int loop=0;
			while (getline(inputFile, line)) 
			{	
				stringstream inputString(line);	
		        string idss, years, nc113, nc, states, ds, r, tempString;
	
		        getline(inputString, idss, ',');
		        getline(inputString, years, ',');
		        getline(inputString, tempString);
		        
				string colarr[]={"Diabetes mellitus (E10-E14)","Diseases of heart (I00-I09,I11,I13,I20-I51)","Accidents (unintentional injuries) (V01-X59,Y85-Y86)","Alzheimer's disease (G30)","Malignant neoplasms (C00-C97)","Chronic lower respiratory diseases (J40-J47)","Influenza and pneumonia (J09-J18)","Nephritis, nephrotic syndrome and nephrosis (N00-N07,N17-N19,N25-N27)"
				,"(I60-I69)","Intentional self-harm (suicide) (*U03,X60-X84,Y87.0)","All Causes"};
				
				int indarr[]={27, 45, 54, 25, 29, 44, 33, 71, 34, 54, 10};
				bool checksend=true;
				string xa1 = "", xa2 = "";
				
				for(int kl=0;kl<11;kl++)
				{
					const char *chars1=tempString.c_str();
					const char *chars2=colarr[kl].c_str();
					const char *p = strstr(chars1, chars2);
					if(p)
					{
						for(int kl1=0;kl1<tempString.length();kl1++)	
						{
							if(kl1<=(indarr[kl]-1))
							{
								checksend=false;
								xa1+=tempString[kl1];
							}
							else if(kl1>(indarr[kl]))
								xa2+=tempString[kl1];
						}
					}
				}
				
				nc113 = xa1;
				stringstream inputString1(xa2);
					
		        getline(inputString1, nc, ',');
		        getline(inputString1, states, ',');
		        getline(inputString1, ds, ',');
		        getline(inputString1, r, ',');
		        
				if(ids == idss)
				{
					cout << "yes" << endl;
					if(oldval == years)					
						years = newval;					
					else if(oldval == nc113)					
						nc113 = newval;				
					else if(oldval == nc)				
						nc = newval;					
					else if(oldval == states)					
						states = newval;					
					else if(oldval == ds)					
						ds = newval;
					else if(oldval == r)					
						r = newval;
					
					fout << idss << "," << years << "," << nc113 << "," << nc << "," << states << "," << ds << "," << r << "\n";
				}
				else
					fout << idss << "," << years << "," << nc113 << "," << nc << "," << states << "," << ds << "," << r << "\n";
			}
			fout.close();
			inputFile.close();
	
			const char * p = paths[i].c_str();
		    remove(p);
			rename("temp.csv", p);	
		}
		
	    return this;
	}
	
	if (leaf == true)
		return NULL;
	
	return Child[i]->update(k, index, oldval, newval, ids);
}

BTreeNode *BTreeNode::delets(string key) 
{
	int i = 0;
	while (i < len && key > keys[i])
		i++;
	
	if (keys[i] == key)
	{
			const char * p = paths[i].c_str();
		    remove(p);
		    keys[i] = "";
		  	return this;
	}
	
	if (leaf == true)
		return NULL;
	
	return Child[i]->delets(key);
}

void BTree::insert(string key) 
{
	if (root == NULL) 
	{
		root = new BTreeNode(tid, true);
		root->keys[0] = key;
		root->LL_records[0].insert_to_end(key);
		root->paths[0] = key;
		root->len = 1;
	} 
	else if (root != NULL) 
	{
		int num = 2 * tid - 1;
		if (root->len == num) 
		{
			BTreeNode *s = new BTreeNode(tid, false);
			s->Child[0] = root;
			s->splitChild(0, root);
			
			int i = 0;
			if (s->keys[0] < key)
				i++;
				
			s->Child[i]->insertNonFull(key);
			root = s;
		} 
		else
			root->insertNonFull(key);
	}
}

void BTreeNode::insertNonFull(string key) 
{
	int x = len - 1;
	
	if (leaf == true) 
	{
		while (x >= 0 && keys[x] > key) 
		{
			keys[x + 1] = keys[x];
			LL_records[x+1]= LL_records[x];
			paths[x + 1] = paths[x];
			x -= 1;
		}
		
		paths[x + 1] = key;
		keys[x + 1] = key;
		LL_records[x + 1].insert_to_end(key);
		len = len + 1;
	} 
	else if (leaf == false)
	{
		while (x >= 0 && keys[x] > key)
			x -= 1;
		
		if (Child[x + 1]->len == 2 * tid - 1) 
		{
			splitChild(x + 1, Child[x + 1]);
			
			if (keys[x + 1] < key)
				x += 1;
		}
		Child[x + 1]->insertNonFull(key);
	}
}

void BTreeNode::splitChild(int x, BTreeNode *old) 
{
	BTreeNode *current = new BTreeNode(old->tid, old->leaf);
	current->len = tid - 1;
	
	for (int a = 0; a < tid - 1; a++)
	{
		current->keys[a] = old->keys[a + tid];
		current->LL_records[a] = old->LL_records[a + tid];
		current->paths[a] = old->paths[a + tid];
	}
	
	if (old->leaf == false) 
	{
		for (int a = 0; a < tid; a++)
			current->Child[a] = old->Child[a + tid];
	}
	
	old->len = tid - 1;
	for (int a = len; a >= x + 1; a--)
		Child[a + 1] = Child[a];
	Child[x + 1] = current;
	
	for (int a = len - 1; a >= x; a--)
	{  	
		keys[a + 1] = keys[a];
		LL_records[a + 1] = LL_records[a];
		paths[a + 1] = paths[a];
	}
	keys[x] = old->keys[tid - 1];
	LL_records[x] = old->LL_records[tid - 1];
	paths[x] = old->paths[tid - 1];
	len = len + 1;
}


/* 
	B-Tree Implementation Ends
*/

int OpearationSelection()
{
	int option = 0;
	cout << "\n Operations" << endl;
	cout << "  1) Create Index \n  2) Point Search \n  3) Range Search \n  4) Update \n  5) Delete \n" << endl;
	cout << " Which Operation do you want to perform : ";
	cin >> option;

   	while (option != 1 and option != 2 and option != 3 and option != 4 and option != 5 )
   	{
	   cout << " .Invalid Value, Please Enter Again: " ; 	
	   cin >> option;   
	}	
	return option;
}

template <typename T> int FindingUniques(T feature[10296], T *uniques)
{
    int index = 0;
    for (int i = 0; i < size; i++)
    {
        int j;
        for (j = 0; j < i; j++)
        {
           if (feature[i] == feature[j])
               break;        	
		}
        if (i == j)
        {
        	uniques[index] = feature[i];
        	index += 1;
		}	
    }
	return index-1;	
}

string GetPath()
{
	char zone[MAX_PATH];
	GetModuleFileNameA(NULL, zone, MAX_PATH);
	string::size_type CurrentPosition = string(zone).find_last_of("\\/");
	
	return string(zone).substr(0, CurrentPosition);
}

int menu()
{
	int option = 0;
	cout << " Main Menu\n\n Select Tree"<< endl;
    cout << "  1) B tree \n  2) Adelson-Velskii and Landis Tree (AVL) \n  3) Red-Black Tree\n" << endl;
   	cout << " Which Tree you want to build : ";
   	cin >> option; 
   	
   	while (option != 1 and option != 2 and option != 3)
   	{
	   cout << "\n Invalid Value, Please Enter Again: " ; 	
	   cin >> option;   
	}
   	return option;
}

int FeatureSelection()
{
	int option = 0;
	cout << "\n Features" << endl;
	cout << "  1) ID \n  2) Year \n  3) 113 Cause Name \n  4) Cause Name \n  5) State \n  6) Deaths \n  7) Death Rate \n" << endl;
	cout << " Which feature do you want to select : ";
	cin >> option;
   	while (option != 1 and option != 2 and option != 3 and option != 4 and option != 5 and option != 6 and option != 7)
   	{
	   cout << " Invalid Value, Please Enter Again: " ; 	
	   cin >> option;   
	}	
	return option;
}

void updation(string ids, string years, string ds, string nc113, string nc, string states, string r, string temps, int counters)
{
	id[counters] = ids;
	year[counters] = years;
	deaths[counters] = ds;
	cause_name_113[counters] = nc113;
	cause_name[counters] = nc;
	state[counters] = states;
	rate[counters] = r;
	filess[counters] = temps;
}

int switching(int feature, string* uniques)
{
	int index = 0;
   	switch (feature) 
	{
		case 1:
			index = FindingUniques(id, uniques);
			for (int x = 0; x < 10296; x++)
			    Selected_Feature_Unique[x] = id[x];
		break;
		case 2:
			index = FindingUniques(year, uniques);
			for (int x = 0; x < 10296; x++)
			    Selected_Feature_Unique[x] = year[x];
		break;
		case 3:
			index = FindingUniques(cause_name_113, uniques);
			for (int x = 0; x < 10296; x++)
			    Selected_Feature_Unique[x] = cause_name_113[x];
		break;
		case 4:
			index = FindingUniques(cause_name, uniques);
			for (int x = 0; x < 10296; x++)
			    Selected_Feature_Unique[x] = cause_name[x];
		break;
		case 5:
			index = FindingUniques(state, uniques);
			for (int x = 0; x < 10296; x++)
			    Selected_Feature_Unique[x] = state[x];
		break;
		case 6:
			index = FindingUniques(deaths, uniques);
			for (int x = 0; x < 10296; x++)
			    Selected_Feature_Unique[x] = deaths[x];
		break;
		case 7:
			index = FindingUniques(rate, uniques);
			for (int x = 0; x < 10296; x++)
			    Selected_Feature_Unique[x] = rate[x];
		break;
	}
	return index;		
}

void readingdata()
{
// Reading Datafiles
    DIR *directory;
	directory = opendir("./ajshd"); //open directory
	
    struct dirent *file;
	static int counters = 0;

    if (directory) 
    { 
    	int counter = 0;
        while ((file = readdir(directory)) != NULL) 
	    {	
	    	counter++;
	    	if (counter > 2)
	    	{
				stringstream ss;  
				ss << file->d_name;
				  
				string s, temps="C:\\Desktop\\Project\\";  
				ss >> s;  
				temps = temps + s;
				
			// Opening Files	
			    ifstream inputFile;
			    inputFile.open(temps.c_str());
			    string line = "";
			    
				if(inputFile.is_open())
				{
					int loop = 0;
					while (getline(inputFile, line)) 
					{	
						if(loop > 0)
						{		
							stringstream inputString(line);	
					        string ids, years, nc113, nc, states, ds, r, tempString;

					        getline(inputString, ids, ',');
					        getline(inputString, years, ',');
					        getline(inputString, tempString);
					        
							string colarr[]={"Diabetes mellitus (E10-E14)","Diseases of heart (I00-I09,I11,I13,I20-I51)","Accidents (unintentional injuries) (V01-X59,Y85-Y86)","Alzheimer's disease (G30)","Malignant neoplasms (C00-C97)","Chronic lower respiratory diseases (J40-J47)","Influenza and pneumonia (J09-J18)","Nephritis, nephrotic syndrome and nephrosis (N00-N07,N17-N19,N25-N27)"
							,"(I60-I69)","Intentional self-harm (suicide) (*U03,X60-X84,Y87.0)","All Causes"};
							
							int indarr[] = {27, 45, 54, 25, 29, 44, 33, 71, 34, 54, 10};
							bool checksend=true;
							string xa1 = "",  xa2 = "";

							for(int a = 0; a < 11; a++)
							{
								const char *chars1 = tempString.c_str();
								const char *chars2 = colarr[a].c_str();
								const char *p = strstr(chars1, chars2);
								if(p)
								{
									for(int b = 0; b < tempString.length(); b++)	
									{
										if(b <= (indarr[a] - 1))
										{
											checksend=false;
											xa1 += tempString[b];
										}
										else if(b > (indarr[a]))
											xa2 += tempString[b];
									}
								}
							}
							nc113 = xa1;
							stringstream inputString1(xa2);	
						
						// Storing	
					        getline(inputString1, nc, ',');
					        getline(inputString1, states, ',');
					        getline(inputString1, ds, ',');
					        getline(inputString1, r, ',');
					        
					        updation(ids, years, ds, nc113, nc, states, r, temps, counters);
							counters += 1;
						}
						loop++;
					}
				}		
			}
        }
        closedir(directory); //closing datafiles folder
    }	
}

void DBMS()
{
	starts:
//  Displaying Menu
   	int tree = menu();
   	
//  If Selected Tree is Btree, Taking order
   	int order = 0; 
   	if(tree == 1)
   	{
   		cout << " Enter order of B tree : ";
   		cin >> order;
	}
	
// Declaring Main Variables
   	string arrays[] = {"Btree" , "AVLTree" , "RBTree"};	
   	string featureselected1 = arrays[tree-1];
   	string locs1 = "./";
	string files1 = featureselected1 + locs1;
	const char * finals1 = files1.c_str();
    int adc = mkdir(finals1);
   	int feature = FeatureSelection();
   	string arrfe[] = {"ID" , "Year" , "113NC" , "NC" , "State" , "Death" , "Rate"};
   	string *uniques = new string[size];
   
//  Selecting Uniques Of Seleccted Feature   	
   	int index = switching(feature, uniques);
	
// Creating File Paths According To Selected Feaures    	
   	string featureselected = arrfe[feature-1];
   	string Folder_Path = GetPath();
   	Folder_Path = Folder_Path + "\\" + arrays[tree-1] + "\\" + featureselected;
	const char * finals = Folder_Path.c_str();
    adc = mkdir(finals);

// Declaring Trees
    BTree BT(order);
    AVLNode *roots = NULL;
	AVLTree AVLT;
	RBTree RBT;

// Performing Insertion & Traversal
    if(tree == 1)
    {
    	for(int i = 0; i < index; i++)
			BT.insert(uniques[i]);
		BT.traverse(finals, Folder_Path, Selected_Feature_Unique);		
	}
	//2002 2003 2004
   	else if(tree == 2)
	{
    	for(int i = 0; i < index; i++)
			roots=AVLT.insert(roots, uniques[i]);
		AVLT.inOrder(roots, finals, Folder_Path, Selected_Feature_Unique);
	}
   	else if(tree == 3)
	{
    	for(int i = 0; i < index; i++)
			RBT.insertValue(uniques[i]);
		RBT.inorder(finals, Folder_Path, Selected_Feature_Unique);
	}

// Performing Operations With Multiple Trees
agains:
	int operation = OpearationSelection();
	if(operation==1) // Tree Creation
	{
		goto starts;
	}
	else if (operation == 2) // Point Search
	{
		string keyselected;
		cout << "Enter the unique value you want details about : ";
		cin.ignore();
		getline(cin,keyselected);
		
		bool condition=false;
		while(!condition)
		{
			for(int x=0; x<index; x++)
			{
				if(uniques[x] == keyselected)
					condition=true;
			}
			if(!condition)
			{
				cout << "Feature and Current Key's Domain Don't Match, Enter the unique value you want details about : ";
				getline(cin,keyselected);
			}
		} 
		
		
		cout<<"Press 1 If You Want To Use Where In Point search: ";
		int wps;
		cin>>wps;
		if(wps!=1)
		{
			if(tree == 1)
				BT.search(keyselected);
			else if(tree == 2)
				AVLT.searchs(roots , keyselected);
			else if(tree == 3)
				RBT.pointsearch(keyselected);				
		}
		else 
		{			
			cout<<"Enter The Value Which You Want To Search: ";
			string for_temp_use="";
			cin.ignore();
			getline(cin,for_temp_use);
			if(tree == 1)
				BT.wherep(keyselected,for_temp_use);
			else if(tree == 2)
				AVLT.wherepoint(roots , keyselected,for_temp_use);
			else if(tree == 3)
				RBT.wherep(keyselected,for_temp_use);				

		}			

	}
	else if(operation == 3) // Range Search
	{
		int range = 0;
		cout << " Enter the number of value you want to search in range search operation:" ;
		cin >> range;
		string rangeskeywords[range];
		
		for(int i = 0; i < range; i++)
		{
			string keyselected;
			cout << " Enter the unique value you want details about : ";
			cin.ignore();
			getline(cin,keyselected);
						
			bool condition=false;
			while(!condition)
			{
				for(int x=0; x<index; x++)
				{
					if(uniques[x] == keyselected)
						condition=true;
				}
				if(condition == false)
				{
					cout << " Feature and Current Key's Domain Don't Match, Enter the unique value you want details about : ";
					getline(cin,keyselected);
				}
			}
			rangeskeywords[i] = keyselected;			
		}
		
		cout<<"Press 1 If You Want To Use Where In Point search: ";
		int wps;
		cin>>wps;
		cout<<endl<<endl<<wps<<endl;
		if(wps!=1)
		{
			for(int i = 0; i < range; i++)
			{
				cout << " Data for Unique Value " << rangeskeywords[i] << endl << endl;
				if(tree == 1)
					BT.search(rangeskeywords[i]);
				else if(tree == 2)
					AVLT.searchs(roots,rangeskeywords[i]);
				else if(tree==3)
					RBT.pointsearch(rangeskeywords[i]);
				cout << endl;
			}			
		}
		if(wps==1)
		{
			
			cout<<"Enter The Value Which You Want To Search: ";
			string for_temp_use="";
			cin.ignore();
			getline(cin,for_temp_use);
			for(int i = 0; i < range; i++)
			{
				cout << " Data for Unique Value " << rangeskeywords[i] << endl << endl;
			if(tree == 1)
				BT.wherep(rangeskeywords[i],for_temp_use);
			else if(tree == 2)
				AVLT.wherepoint(roots , rangeskeywords[i],for_temp_use);
			else if(tree == 3)
				RBT.wherep(rangeskeywords[i],for_temp_use);				
				cout << endl;
			}
		}		
	}
	else if(operation == 4) // Updation
	{
		string key = "", index = "", oldvalue = "", newvalue =  "";
		
		cout<<" Enter The Key Value On Which Tree Is Built : ";
		cin.ignore();
		getline(cin, key);
		
		string allfeatures[] = {"1) ID" , "2) Year" , "3) 113 Cause Name" , "4) Cause Name" "5) State" , "6) Deaths" , "7) Death Rate"};
		cout << " Enter feature you want to update!" << endl;
		
		int selected12= FeatureSelection();
		
		cout << " Enter index you want to update : ";
		cin >> index;
		
		cout << " Enter value present at that index of field " << allfeatures[selected12 - 1] << " for conformation : ";
		cin.ignore();
		getline(cin, oldvalue);
		
		cout << " Enter the new value of field " << allfeatures[selected12 - 1] << " for index " << index << " : ";
		getline(cin, newvalue);
				
		if(tree == 1)
			BT.update(key, 2, oldvalue, newvalue, index);
		else if(tree == 2)
			AVLT.updates(roots, key, 2, oldvalue, newvalue, index);	
		else if(tree==3)
			RBT.updaterecord(key, 2, oldvalue, newvalue, index);	
	}
	else if(operation == 5) // Deletion
	{
			string key;
			
			cout<<" Enter The Key/File You Want To Delete: ";
			cin.ignore();
			getline(cin , key);
			
			if(tree==1)
				BT.delets(key);
			else if(tree==2)
				AVLT.deletes(roots, key);
			else if(tree==3)
				RBT.deleteseve(key);
	}
// Further Continuation
	cout << endl << " If You Want To Continue Press Enter Y else press any key: ";
	char continued;
	cin >> continued;
	
	if(continued == 'Y')
	{
		cout << " Select what operation you want to perform\n";
		goto agains;
	}
}

int main() 
{
// Reading Data From Files
    readingdata();
   
// Data Base Management System
	DBMS();
	   	
	return 0;
}
